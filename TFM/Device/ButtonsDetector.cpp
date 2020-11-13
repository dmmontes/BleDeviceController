#include "ButtonsDetector.h"

#include "DeviceLogger.h"

#include "Energia.h"

namespace Detector
{

    ButtonsDetector::ButtonsDetector(uint8_t turnsBetweenDetections /*= 0*/, uint8_t turnsToDetect /*= 0*/)
        : IDetector(turnsBetweenDetections, turnsToDetect)
    {
        LOG_DEBUG("ButtonsDetector::ButtonsDetector()");

        pinMode(button1Pin_, INPUT_PULLUP);
        pinMode(button2Pin_, INPUT_PULLUP);
    }

    bool ButtonsDetector::checkAction(IAction *action)
    {
        LOG_DEBUG("ButtonsDetector::checkAction()");

        ButtonState buttonState{(digitalRead(button1Pin_) == LOW ? true : false), (digitalRead(button2Pin_) == LOW ? true : false)};
        return checkAction(buttonState, action);
    }

} // namespace Detector
