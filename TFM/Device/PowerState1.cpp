#include "PowerState1.h"

#include "DeviceLogger.h"

#include "Energia.h"
#include "PowerStateMachine.h"

PowerState1::PowerState1(IPowerStateMachine *stateMachine)
    : IPowerState(stateMachine),
      timesDetecting_{0},
      timesLimitToLowerState_{-10}
{
    LOG_DEBUG("PowerState1::PowerState1()");
}

void PowerState1::detectionResult(bool detectedAction)
{
    LOG_DEBUG(String("PowerState1::detectionResult()  detectedAction: ") + String(detectedAction));

    // Check if timesDetecting_ has to be reset (i.e: we detect an action after 3 turns no detecting) and add the result
    int8_t addedTime = (detectedAction ? 1 : -1);
    if (timesDetecting_ * addedTime > 0)
    {
        timesDetecting_ += addedTime;
    }
    else
    {
        timesDetecting_ = addedTime;
    }
    LOG_DEBUG(String("PowerState1::detectionResult()  timesDetecting_: ") + String(timesDetecting_));

    // Check if is needed to change to new state
    if (timesDetecting_ <= timesLimitToLowerState_)
    {
        stateMachine_->changeState(IPowerStateMachine::PowerState::PW2);
    }
}
