#include "ButtonsDetector.h"

#include "DeviceLogger.h"

#include "Energia.h"

namespace Detector
{

    ButtonsDetector::ButtonsDetector()
    {
        LOG_DEBUG("ButtonsDetector::ButtonsDetector()");

        pinMode(button1Pin_, INPUT_PULLUP);
        pinMode(button2Pin_, INPUT_PULLUP);
    }

    void ButtonsDetector::detectAction(IAction *action)
    {
        LOG_DEBUG("ButtonsDetector::detectAction()");

        ButtonState buttonState{digitalRead(button1Pin_), digitalRead(button2Pin_)};
        detectAction(buttonState, action);
    }

} // namespace Detector