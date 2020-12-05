#include "PowerState1.h"

#include "DeviceLogger.h"

#include "Energia.h"
#include "PowerStateMachine.h"

PowerState1::PowerState1(IPowerStateMachine *stateMachine)
    : IPowerState(stateMachine),
      firstResult_{true},
      timeToChangeToLowerState_{0},
      timeLimitToLowerState_{10000}
{
    LOG_DEBUG("PowerState1::PowerState1()");
}

void PowerState1::detectionResult(bool detectedAction)
{
    LOG_DEBUG(String("PowerState1::detectionResult()  detectedAction: ") + String(detectedAction));
    unsigned long actualTime = millis();

    // Set initial time in first detection
    if (firstResult_)
    {
        firstResult_ = false;
        timeToChangeToLowerState_ = actualTime + timeLimitToLowerState_;
    }

    // Check if goes to next state
    if (detectedAction)
    {
        timeToChangeToLowerState_ = actualTime + timeLimitToLowerState_;
    }
    else if (timeToChangeToLowerState_ < actualTime)
    {
        stateMachine_->changeState(IPowerStateMachine::PowerState::PW2);
    }
}
