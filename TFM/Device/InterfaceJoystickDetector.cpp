#include "InterfaceJoystickDetector.h"

#include "DeviceLogger.h"

#include "Energia.h"
#include "InterfaceAction.h"

namespace Detector
{

    bool InterfaceJoystickDetector::detectAction(const JoystickState &joystickState, IAction *)
    {
        LOG_DEBUG(String("InterfaceJoystickDetector::detectAction() button: ") + String(joystickState.buttonPressed) + String(", xAxis: ") + String(joystickState.xAxis) + String(", yAxis: ") + String(joystickState.yAxis));

        return true;
    }

} // namespace Detector
