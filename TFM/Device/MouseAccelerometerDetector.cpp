#include "MouseAccelerometerDetector.h"

#include "DeviceLogger.h"

#include "Energia.h"
#include "MouseAction.h"

namespace Detector
{

    MouseAccelerometerDetector::MouseAccelerometerDetector()
        : AccelerometerDetector(50) //Time between detections = 30 ms
    {
        LOG_DEBUG("MouseAccelerometerDetector::MouseAccelerometerDetector()");
    }

    bool MouseAccelerometerDetector::checkAction(const AccelerometerState &accelerometerState, IAction *action)
    {
        LOG_DEBUG(String("MouseAccelerometerDetector::checkAction() xAxis: ") + String(accelerometerState.xAxis) + String(", yAxis: ") + String(accelerometerState.yAxis) + String(", zAxis: ") + String(accelerometerState.zAxis));

        bool actionDetected{false};

        // Detecting scroll. Note scroll down is negative value
        int8_t mouseScroll = detectScroll(scrollUpLimit_ - accelerometerState.zAxis, scrollUpMoveLimit_);
        if (mouseScroll == 0)
        {
            mouseScroll = -detectScroll(accelerometerState.yAxis - scrollDownLimit_, scrollDownMoveLimit_);
        }

        if (mouseScroll != 0)
        {
            actionDetected = true;
        }
        static_cast<MouseAction *>(action)->scroll(mouseScroll);
        return actionDetected;
    }

    uint8_t MouseAccelerometerDetector::detectScroll(int16_t scrollMove, uint16_t scrollMoveLimit)
    {
        LOG_DEBUG(String("MouseAccelerometerDetector::detectScroll() scrollMove: ") + String(scrollMove) +
                  String(", scrollMoveLimit: ") + String(scrollMoveLimit));

        uint8_t mouseScrollMove{0};
        if (scrollMove > 0)
        {
            mouseScrollMove = map(scrollMove, 1, scrollMoveLimit, 1, mouseScrollLimit_);
        }
        return mouseScrollMove;
    }

} // namespace Detector
