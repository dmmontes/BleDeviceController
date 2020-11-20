#include "PowerState2.h"

#include "DeviceLogger.h"

#include "Energia.h"
#include "PowerStateMachine.h"

PowerState2::PowerState2(IPowerStateMachine *stateMachine)
    : IPowerState(stateMachine),
      timesDetecting_{0},
      timesLimitToLowerState_{-20},
      timesLimitToHigherState_{5},
      delayTime_{100}
{
    LOG_DEBUG("PowerState2::PowerState2()");
}

void PowerState2::detectionResult(bool detectedAction)
{
    LOG_DEBUG(String("PowerState2::detectionResult()  detectedAction: ") + String(detectedAction));

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
    LOG_DEBUG(String("PowerState2::detectionResult()  timesDetecting_: ") + String(timesDetecting_) +
              String(", delaying ms: ") + String(delayTime_));

    // Delay time to save power
    delay(delayTime_);

    // Check if is needed to change to new state
    if (timesDetecting_ <= timesLimitToLowerState_)
    {
        stateMachine_->changeState(IPowerStateMachine::PowerState::PW3);
    }
    else if (timesDetecting_ >= timesLimitToHigherState_)
    {
        stateMachine_->changeState(IPowerStateMachine::PowerState::PW1);
    }
}
