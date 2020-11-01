#include "AccelerometerDetector.h"

#include "DeviceLogger.h"

#include "Energia.h"

namespace Detector
{

    bool AccelerometerDetector::detectAction(IAction *action)
    {
        LOG_DEBUG("AccelerometerDetector::detectAction()");

        AccelerometerState accelerometerState{analogRead(xAxisPin_), analogRead(yAxisPin_), analogRead(zAxisPin_)};
        return detectAction(accelerometerState, action);
    }

} // namespace Detector
