#include "GamepadAccelerometerDetector.h"

#include "DeviceLogger.h"

#include "GamepadDetectorUtil.h"

namespace Detector
{

    GamepadAccelerometerDetector::GamepadAccelerometerDetector()
        : AccelerometerDetector(50) //Time between detections = 30 ms
    {
        LOG_DEBUG("GamepadAccelerometerDetector::GamepadAccelerometerDetector()");
    }

    bool GamepadAccelerometerDetector::checkAction(const AccelerometerState &accelerometerState, IAction *action)
    {
        LOG_DEBUG(String("GamepadAccelerometerDetector::checkAction() xAxis: ") +
                  String(accelerometerState.xAxis) + String(", yAxis: ") + String(accelerometerState.yAxis) +
                  String(", zAxis: ") + String(accelerometerState.zAxis));

        bool actionDetected{false};

        // Check the state of everoy button (LEFT, RIGH)
        actionDetected |= GamepadDetectorUtil::checkButton(leftButtonPressed_,
                                                           accelerometerState.xAxis < leftTurnLimit_, GamepadAction::Key::A, action);
        actionDetected |= GamepadDetectorUtil::checkButton(rightButtonPressed_,
                                                           accelerometerState.xAxis > rightTurnLimit_,
                                                           GamepadAction::Key::D, action);
        return actionDetected;
    }

} // namespace Detector
