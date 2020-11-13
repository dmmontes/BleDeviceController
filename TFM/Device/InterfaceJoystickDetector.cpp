#include "InterfaceJoystickDetector.h"

#include "DeviceLogger.h"

#include "Energia.h"
#include "InterfaceAction.h"

namespace Detector
{

    InterfaceJoystickDetector::InterfaceJoystickDetector()
        : JoystickDetector(300) //Times between detections = 300ms
    {
        LOG_DEBUG("InterfaceJoystickDetector::InterfaceJoystickDetector()");
    }

    bool InterfaceJoystickDetector::checkAction(const JoystickState &joystickState, IAction *action)
    {
        LOG_DEBUG(String("InterfaceJoystickDetector::checkAction() button: ") + String(joystickState.buttonPressed) + String(", xAxis: ") + String(joystickState.xAxis) + String(", yAxis: ") + String(joystickState.yAxis));

        bool actionDetected{false};

        if (joystickState.yAxis > moveUpLimit_)
        {
            LOG_DEBUG("InterfaceJoystickDetector::checkAction() Move Up");
            static_cast<InterfaceAction *>(action)->moveUp();
            actionDetected = true;
        }
        else if (joystickState.yAxis < moveDownLimit_)
        {
            LOG_DEBUG("InterfaceJoystickDetector::checkAction() Move Down");
            static_cast<InterfaceAction *>(action)->moveDown();
            actionDetected = true;
        }
        return actionDetected;
    }

} // namespace Detector
