#include "AccelerometerDetector.h"

#include "DeviceLogger.h"

#include "Energia.h"

namespace Detector
{
    AccelerometerDetector::AccelerometerDetector(unsigned long timeBetweenDetections /*= 0*/)
        : IDetector(timeBetweenDetections), xAxisPin_{23}, yAxisPin_{24}, zAxisPin_{25}, accelerometerLimit_{512}
    {
        LOG_DEBUG("AccelerometerDetector::AccelerometerDetector()");
    }

    bool AccelerometerDetector::checkAction(IAction *action)
    {
        LOG_DEBUG("AccelerometerDetector::checkAction()");

        AccelerometerState accelerometerState{static_cast<int16_t>(analogRead(xAxisPin_) - accelerometerLimit_),
                                              static_cast<int16_t>(analogRead(yAxisPin_) - accelerometerLimit_),
                                              static_cast<int16_t>(analogRead(zAxisPin_) - accelerometerLimit_)};
        return checkAction(accelerometerState, action);
    }

} // namespace Detector
