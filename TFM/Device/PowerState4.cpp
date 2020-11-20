#include "PowerState4.h"

#include "DeviceLogger.h"

#include "Energia.h"
#include "PowerStateMachine.h"

const uint8_t BUTTON1_PIN{33};
const uint8_t BUTTON2_PIN{32};
bool SLEPT{true};
void WakeUp()
{
    detachInterrupt(digitalPinToInterrupt(BUTTON1_PIN));
    detachInterrupt(digitalPinToInterrupt(BUTTON2_PIN));
    SLEPT = false;
}

PowerState4::PowerState4(IPowerStateMachine *stateMachine)
    : IPowerState(stateMachine),
      blueLed_{37},
      greenLed_{38},
      brightness_{10},
      activated_{true},
      delayTime_{5000}
{
    LOG_DEBUG("PowerState4::PowerState4()");
    pinMode(blueLed_, OUTPUT);
    pinMode(greenLed_, OUTPUT);
}

void PowerState4::detectionResult(bool)
{
    LOG_DEBUG("PowerState4::detectionResult()  Going to sleep");

    // Attach to interruptions and go to sleep
    SLEPT = true;
    attachInterrupt(digitalPinToInterrupt(BUTTON1_PIN), WakeUp, CHANGE);
    attachInterrupt(digitalPinToInterrupt(BUTTON2_PIN), WakeUp, CHANGE);
    while (SLEPT)
    {
        // Blink and sleep
        uint16_t actualBrightness{static_cast<uint16_t>(activated_ ? brightness_ : 0)};
        activated_ = !activated_;
        analogWrite(blueLed_, actualBrightness);
        analogWrite(greenLed_, actualBrightness);
        delay(delayTime_);
    }
    // Turn off leds
    analogWrite(blueLed_, 0);
    analogWrite(greenLed_, 0);

    // Wake Up and going to previous energy state
    stateMachine_->changeState(IPowerStateMachine::PowerState::PW3);
}
