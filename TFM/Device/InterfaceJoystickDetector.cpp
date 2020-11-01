#include "InterfaceJoystickDetector.h"

#include "DeviceLogger.h"

#include "Energia.h"
#include "InterfaceAction.h"

namespace Detector
{

    bool InterfaceJoystickDetector::detectAction(const JoystickState &joystickState, IAction *action)
    {
        LOG_DEBUG(String("InterfaceJoystickDetector::detectAction() button: ") + String(joystickState.button) + String(", xAxis: ") + String(joystickState.xAxis) + String(", yAxis: ") + String(joystickState.yAxis));
        return true;
    }

} // namespace Detector
