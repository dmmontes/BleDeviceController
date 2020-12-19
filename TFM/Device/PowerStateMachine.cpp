#include "PowerStateMachine.h"

#include "DeviceLogger.h"

#include "PowerState1.h"
#include "PowerState2.h"
#include "PowerState3.h"
#include "PowerState4.h"

PowerStateMachine::PowerStateMachine(PowerStateChangedFxn powerStateChangedFxn)
    : powerState_{nullptr}, powerStateChangedFxn_{powerStateChangedFxn}
{
    LOG_DEBUG("PowerStateMachine::PowerStateMachine()");
    changeState(IPowerStateMachine::PowerState::PW1);
}

PowerStateMachine::~PowerStateMachine()
{
    LOG_DEBUG("PowerStateMachine::PowerStateMachine()");
    delete powerState_;
}

void PowerStateMachine::changeState(IPowerStateMachine::PowerState newState)
{
    LOG_ERROR(String("PowerStateMachine::changeState() newState: ") +
              String(static_cast<uint8_t>(newState) + 1));

    delete powerState_;
    switch (newState)
    {
    case IPowerStateMachine::PowerState::PW1:
        powerState_ = new PowerState1(this);
        break;
    case IPowerStateMachine::PowerState::PW2:
        powerState_ = new PowerState2(this);
        break;
    case IPowerStateMachine::PowerState::PW3:
        powerState_ = new PowerState3(this);
        break;
    case IPowerStateMachine::PowerState::PW4:
        powerState_ = new PowerState4(this);
        break;
    default:
        LOG_DEBUG("PowerStateMachine::changeState() Unrecognized state");
        break;
    }
    powerStateChangedFxn_(newState);
}

void PowerStateMachine::detectionResult(bool detectedAction)
{
    LOG_DEBUG(String("PowerStateMachine::detectionResult() detectedAction: ") + String(detectedAction));
    powerState_->detectionResult(detectedAction);
}
