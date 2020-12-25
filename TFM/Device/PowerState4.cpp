#include "PowerState4.h"

#include "DeviceLogger.h"

#include "Energia.h"
#include "PowerStateMachine.h"
#include "ti/devices/msp432p4xx/driverlib/pcm.h"

const uint8_t BUTTON1_PIN{33};
const uint8_t BUTTON2_PIN{32};

void WakeUp()
{
    detachInterrupt(digitalPinToInterrupt(BUTTON1_PIN));
    detachInterrupt(digitalPinToInterrupt(BUTTON2_PIN));
}

PowerState4::PowerState4(IPowerStateMachine *stateMachine)
    : IPowerState(stateMachine),
      delayTime_{500}
{
    LOG_DEBUG("PowerState4::PowerState4()");
}

void PowerState4::detectionResult(bool)
{
    LOG_DEBUG("PowerState4::detectionResult()  Going to sleep");

    // Attach to interruptions and go to sleep
    attachInterrupt(digitalPinToInterrupt(BUTTON1_PIN), WakeUp, CHANGE);
    attachInterrupt(digitalPinToInterrupt(BUTTON2_PIN), WakeUp, CHANGE);

    // Go to LPM4
    PCM_gotoLPM4();

    // Wake-up and avoid doing action of button
    delay(delayTime_);

    // Wake Up and going to previous energy state
    stateMachine_->changeState(IPowerStateMachine::PowerState::PW1);
}
