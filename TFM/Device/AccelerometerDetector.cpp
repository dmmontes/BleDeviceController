#include "AccelerometerDetector.h"

#include "DeviceLogger.h"

#include "Energia.h"

namespace Detector
{
    AccelerometerDetector::AccelerometerDetector(uint8_t turnsBetweenDetections /*= 0*/, uint8_t turnsToDetect /*= 0*/)
        : IDetector(turnsBetweenDetections, turnsToDetect)
    {
        LOG_DEBUG("AccelerometerDetector::AccelerometerDetector()");
    }

    bool AccelerometerDetector::checkAction(IAction *action)
    {
        LOG_DEBUG("AccelerometerDetector::checkAction()");

        AccelerometerState accelerometerState{analogRead(xAxisPin_), analogRead(yAxisPin_), analogRead(zAxisPin_)};
        return checkAction(accelerometerState, action);
    }

} // namespace Detector
