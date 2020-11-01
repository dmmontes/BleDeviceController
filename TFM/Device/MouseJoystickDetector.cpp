#include "MouseJoystickDetector.h"

#include "DeviceLogger.h"

#include "Energia.h"
#include "MouseAction.h"

namespace Detector
{

    void MouseJoystickDetector::setDetectionType(IDetector::DetectionType detectionType)
    {
        LOG_DEBUG(String("MouseJoystickDetector::setDetectionType() detectionType: ") + String(static_cast<uint8_t>(detectionType)));
        switch (detectionType)
        {
        case IDetector::DetectionType::NORMAL:
            mapAxisToCursor_ = &MouseJoystickDetector::linearMapAxisToCursor;
            break;
        case IDetector::DetectionType::QUALITY:
            mapAxisToCursor_ = &MouseJoystickDetector::PolyMapAxisToCursor;
        default:
            LOG_WARNING("MouseJoystickDetector::setDetectionType() unknown DetectionType");
            break;
        }
    }

    bool MouseJoystickDetector::detectAction(const JoystickState &joystickState, IAction *action)
    {
        LOG_DEBUG(String("MouseJoystickDetector::detectAction() button: ") + String(joystickState.button) + String(", xAxis: ") + String(joystickState.xAxis) + String(", yAxis: ") + String(joystickState.yAxis));

        bool actionDetected{false};

        // Read the value of button
        if (buttonState != joystickState.button)
        {
            LOG_DEBUG("Button changed");
            buttonState = joystickState.button;
            static_cast<MouseAction *>(action)->middleClick(buttonState == 0);
            actionDetected = true;
        }

        // Read the analog value of joystick x axis
        int16_t xMouseMove{0};
        int16_t xAxisMove{joystickState.xAxis - middleAxisValue_};
        LOG_DEBUG(String("Joystick X ") + String(xAxisMove));
        if (abs(xAxisMove) > axisTreshold_)
        {
            xMouseMove = (this->*mapAxisToCursor_)(xAxisMove);
            LOG_DEBUG(String("Joystick X moved, units: ") + String(xMouseMove));
            actionDetected = true;
        }

        // Read the analog value of joystick y axis
        int16_t yMouseMove{0};
        int16_t yAxisMove{middleAxisValue_ - joystickState.yAxis};
        LOG_DEBUG(String("Joystick Y ") + String(yAxisMove));
        if (abs(yAxisMove) > axisTreshold_)
        {
            yMouseMove = (this->*mapAxisToCursor_)(yAxisMove);
            LOG_DEBUG(String("Joystick Y moved, units: ") + String(yMouseMove));
            actionDetected = true;
        }

        static_cast<MouseAction *>(action)->moveCursor(xMouseMove, yMouseMove);
        delay(15);
        return actionDetected;
    }

    int16_t MouseJoystickDetector::linearMapAxisToCursor(int16_t axisValue)
    {
        LOG_DEBUG("MouseJoystickDetector::linearMapAxisToCursor_()");
        return map(axisValue, -axisMoveLimit_, axisMoveLimit_, -mouseMoveLimit_, mouseMoveLimit_);
    }

    int16_t MouseJoystickDetector::PolyMapAxisToCursor(int16_t axisValue)
    {
        LOG_DEBUG("MouseJoystickDetector::PolyMapAxisToCursor_()");
        return (axisValue < 0 ? -1 : 1) * (1.148687 - 0.0009004226 * axisValue + 0.0000257187 * axisValue * axisValue);
    }

} // namespace Detector
