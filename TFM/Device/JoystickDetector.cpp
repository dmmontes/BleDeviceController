#include "JoystickDetector.h"

#include "DeviceLogger.h"

#include "Energia.h"

namespace Detector
{

    JoystickDetector::JoystickDetector()
    {
        LOG_DEBUG("JoystickDetector::JoystickDetector()");

        pinMode(buttonPin_, INPUT_PULLUP);
    }

    void JoystickDetector::detectAction(IAction *action)
    {
        LOG_DEBUG("JoystickDetector::detectAction()");

        JoystickState joystickState{digitalRead(buttonPin_), analogRead(xAxisPin_), analogRead(yAxisPin_)};
        detectAction(joystickState, action);
    }

} // namespace Detector