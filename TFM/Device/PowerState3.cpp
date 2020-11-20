#include "PowerState3.h"

#include "DeviceLogger.h"

#include "Energia.h"
#include "PowerStateMachine.h"

PowerState3::PowerState3(IPowerStateMachine *stateMachine)
    : IPowerState(stateMachine),
      timesDetecting_{0},
      timesLimitToLowerState_{-10},
      timesLimitToHigherState_{3},
      delayTime_{1000}
{
    LOG_DEBUG("PowerState3::PowerState3()");
}

void PowerState3::detectionResult(bool detectedAction)
{
    LOG_DEBUG(String("PowerState3::detectionResult()  detectedAction: ") + String(detectedAction));

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
    LOG_DEBUG(String("PowerState3::detectionResult()  timesDetecting_: ") + String(timesDetecting_) +
              String(", delaying ms: ") + String(delayTime_));

    // Delay time to save power
    delay(delayTime_);

    // Check if is needed to change to new state
    if (timesDetecting_ <= timesLimitToLowerState_)
    {
        stateMachine_->changeState(IPowerStateMachine::PowerState::PW4);
    }
    else if (timesDetecting_ >= timesLimitToHigherState_)
    {
        stateMachine_->changeState(IPowerStateMachine::PowerState::PW2);
    }
}
