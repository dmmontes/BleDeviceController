#include "GamepadJoystickDetector.h"

#include "DeviceLogger.h"

namespace Detector
{

    GamepadJoystickDetector::GamepadJoystickDetector()
        : JoystickDetector(50) //Times between detections = 200ms
    {
        LOG_DEBUG("GamepadJoystickDetector::GamepadJoystickDetector()");
    }

    bool GamepadJoystickDetector::checkAction(const JoystickState &joystickState, IAction *action)
    {
        LOG_DEBUG(String("GamepadJoystickDetector::checkAction() button: ") + String(joystickState.buttonPressed) + String(", xAxis: ") + String(joystickState.xAxis) + String(", yAxis: ") + String(joystickState.yAxis));

        bool actionDetected{false};

        // Check the state of every button (UP, DOWN, LEFT, RIGH, JOYSTICK)
        actionDetected |= checkKey(joystickState.yAxis > moveUpRightLimit_, GamepadAction::Key::W, action);
        actionDetected |= checkKey(joystickState.yAxis < moveDownLeftLimit_, GamepadAction::Key::S, action);
        actionDetected |= checkKey(joystickState.xAxis > moveUpRightLimit_, GamepadAction::Key::D, action);
        actionDetected |= checkKey(joystickState.xAxis < moveDownLeftLimit_, GamepadAction::Key::A, action);
        actionDetected |= checkKey(joystickState.buttonPressed, GamepadAction::Key::NUMBER3, action);

        return actionDetected;
    }

} // namespace Detector
