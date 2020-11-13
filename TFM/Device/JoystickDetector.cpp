#include "JoystickDetector.h"

#include "DeviceLogger.h"

#include "Energia.h"

namespace Detector
{

    JoystickDetector::JoystickDetector(unsigned long timeBetweenDetections /*= 0*/)
        : IDetector(timeBetweenDetections)
    {
        LOG_DEBUG("JoystickDetector::JoystickDetector()");

        pinMode(buttonPin_, INPUT_PULLUP);
    }

    bool JoystickDetector::checkAction(IAction *action)
    {
        LOG_DEBUG("JoystickDetector::checkAction()");

        JoystickState joystickState{(digitalRead(buttonPin_) == LOW ? 1 : 0), analogRead(xAxisPin_), analogRead(yAxisPin_)};
        return checkAction(joystickState, action);
    }

} // namespace Detector
