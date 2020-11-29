#include "MouseJoystickDetector.h"

#include "DeviceLogger.h"

#include "Energia.h"
#include "MouseAction.h"

namespace Detector
{

    MouseJoystickDetector::MouseJoystickDetector()
        : JoystickDetector(15) //Time between detections = 15 ms
    {
        LOG_DEBUG("MouseJoystickDetector::MouseJoystickDetector()");
    }

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
            break;
        default:
            LOG_WARNING("MouseJoystickDetector::setDetectionType() unknown DetectionType");
            break;
        }
    }

    bool MouseJoystickDetector::checkAction(const JoystickState &joystickState, IAction *action)
    {
        LOG_DEBUG(String("MouseJoystickDetector::checkAction() button: ") + String(joystickState.buttonPressed) + String(", xAxis: ") + String(joystickState.xAxis) + String(", yAxis: ") + String(joystickState.yAxis));

        bool actionDetected{false};

        // Read the value of button
        if (buttonPressed_ != joystickState.buttonPressed)
        {
            LOG_DEBUG("MouseJoystickDetector::checkAction() Button changed");
            buttonPressed_ = joystickState.buttonPressed;
            static_cast<MouseAction *>(action)->middleClick(buttonPressed_);
            actionDetected = true;
        }

        // Read the analog value of joystick's axis
        int8_t xMouseMove{detectMouseMovement(joystickState.xAxis - middleAxisValue_)};
        int8_t yMouseMove{detectMouseMovement(middleAxisValue_ - joystickState.yAxis)};
        if (xMouseMove != 0 || yMouseMove != 0)
        {
            static_cast<MouseAction *>(action)->moveCursor(xMouseMove, yMouseMove);
            actionDetected = true;
        }

        return actionDetected;
    }

    int8_t MouseJoystickDetector::detectMouseMovement(int16_t axisMove)
    {
        LOG_DEBUG(String("MouseJoystickDetector::detectMouseMovement() axisMove: ") + String(axisMove));

        int16_t mouseMove{0};
        if (abs(axisMove) > axisTreshold_)
        {
            mouseMove = (this->*mapAxisToCursor_)(axisMove);
        }
        return mouseMove;
    }

    int16_t MouseJoystickDetector::linearMapAxisToCursor(int16_t axisValue)
    {
        LOG_DEBUG(String("MouseJoystickDetector::linearMapAxisToCursor_() axisValue: ") + String(axisValue));
        return map(axisValue, -axisMoveLimit_, axisMoveLimit_, -mouseMoveLimit_, mouseMoveLimit_);
    }

    int16_t MouseJoystickDetector::PolyMapAxisToCursor(int16_t axisValue)
    {
        LOG_DEBUG(String("MouseJoystickDetector::PolyMapAxisToCursor_() axisValue: ") + String(axisValue));
        uint16_t absAxisValue = abs(axisValue);
        return (axisValue < 0 ? -1 : 1) * (polyA_ * absAxisValue * absAxisValue + polyB_ * absAxisValue + polyC_);
    }

} // namespace Detector
