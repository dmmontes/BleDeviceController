#include "GamepadJoystickDetector.h"

#include "DeviceLogger.h"

#include "GamepadDetectorUtil.h"

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

        // Check the state of everoy button (UP, DOWN, LEFT, RIGH, JOYSTICK)
        actionDetected |= GamepadDetectorUtil::checkButton(upButtonPressed_, joystickState.yAxis > moveUpRightLimit_,
                                                           GamepadAction::Key::W, action);
        actionDetected |= GamepadDetectorUtil::checkButton(downButtonPressed_, joystickState.yAxis < moveDownLeftLimit_,
                                                           GamepadAction::Key::S, action);
        actionDetected |= GamepadDetectorUtil::checkButton(rightButtonPressed_, joystickState.xAxis > moveUpRightLimit_,
                                                           GamepadAction::Key::D, action);
        actionDetected |= GamepadDetectorUtil::checkButton(leftButtonPressed_, joystickState.xAxis < moveDownLeftLimit_,
                                                           GamepadAction::Key::A, action);
        actionDetected |= GamepadDetectorUtil::checkButton(joystickbuttonPressed_, joystickState.buttonPressed,
                                                           GamepadAction::Key::NUMBER3, action);
        return actionDetected;
    }

} // namespace Detector
