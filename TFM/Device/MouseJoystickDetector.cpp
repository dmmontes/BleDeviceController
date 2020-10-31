#include "MouseJoystickDetector.h"

#include "DeviceLogger.h"

#include "Energia.h"
#include "MouseAction.h"

namespace Detector
{

    void MouseJoystickDetector::detectAction(const JoystickState &joystickState, IAction *action)
    {
        LOG_DEBUG(String("MouseJoystickDetector::detectAction() button: ") + String(joystickState.button) + String(", xAxis: ") + String(joystickState.xAxis) + String(", yAxis: ") + String(joystickState.yAxis));

        // Read the value of button
        if (buttonState != joystickState.button)
        {
            LOG_DEBUG("Button changed");
            buttonState = joystickState.button;
            static_cast<MouseAction *>(action)->middleClick(buttonState == 0);
        }

        // Read the analog value of joystick x axis
        int16_t xMouseMove{0};
        int8_t xAxisMove{joystickState.xAxis - middleAxisValue_};
        if (abs(xAxisMove) > axisTreshold_)
        {
            xMouseMove = map(xAxisMove, -axisMoveLimit_, axisMoveLimit_, -mouseMoveLimit_, mouseMoveLimit_);
            LOG_DEBUG(String("Joystick X moved, units: ") + String(xMouseMove));
        }

        // Read the analog value of joystick y axis
        int16_t yMouseMove{0};
        int8_t yAxisMove{joystickState.yAxis - middleAxisValue_};
        if (abs(yAxisMove) > axisTreshold_)
        {
            yMouseMove = map(yAxisMove, -axisMoveLimit_, axisMoveLimit_, -mouseMoveLimit_, mouseMoveLimit_);
            LOG_DEBUG(String("Joystick X moved, units: ") + String(yMouseMove));
        }

        // Update axis movement
        static_cast<MouseAction *>(action)->moveCursor(xMouseMove, yMouseMove);
    }

} // namespace Detector