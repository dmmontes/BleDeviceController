#include "PowerState3.h"

#include "DeviceLogger.h"

#include "Energia.h"
#include "PowerStateMachine.h"

PowerState3::PowerState3(IPowerStateMachine *stateMachine)
    : IPowerState(stateMachine),
      firstResult_{true},
      timeToChangeToLowerState_{0},
      timeLimitToLowerState_{10000},
      timeToChangeToHigherState_{0},
      timeLimitToHigherState_{5000},
      timesLimitToHigherState_{2},
      timesDetecting_{0},
      delayTime_{1000}
{
    LOG_DEBUG("PowerState3::PowerState3()");
}

void PowerState3::detectionResult(bool detectedAction)
{
    LOG_DEBUG(String("PowerState3::detectionResult()  detectedAction: ") + String(detectedAction));
    unsigned long actualTime = millis();

    // Set initial time in first detection
    if (firstResult_)
    {
        firstResult_ = false;
        timeToChangeToLowerState_ = actualTime + timeLimitToLowerState_;
        timeToChangeToHigherState_ = actualTime + timeLimitToHigherState_;
    }

    // If detected action, check if goes to higher level
    if (detectedAction)
    {
        timeToChangeToLowerState_ = actualTime + timeLimitToLowerState_;
        ++timesDetecting_;
        if (timesDetecting_ == timesLimitToHigherState_)
        {
            stateMachine_->changeState(IPowerStateMachine::PowerState::PW2);
            return;
        }
    }
    // If no detected action, check if goes to lower level
    else if (timeToChangeToLowerState_ < actualTime)
    {
        stateMachine_->changeState(IPowerStateMachine::PowerState::PW4);
        return;
    }
    // Check if times detecting should be reset
    else if (timeToChangeToHigherState_ < actualTime)
    {
        timeToChangeToHigherState_ = actualTime + timeLimitToHigherState_;
        timesDetecting_ = 0;
    }

    // Delay time to save power
    delay(delayTime_);
}
