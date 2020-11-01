#include "MouseDetectorFactory.h"

#include "DeviceLogger.h"

#include "MouseButtonsDetector.h"
#include "MouseJoystickDetector.h"
#include "MouseAccelerometerDetector.h"

namespace Detector
{

    IDetector *MouseDetectorFactory::createButtonDetector()
    {
        LOG_DEBUG("MouseDetectorFactory::createButtonDetector()");
        return new MouseButtonsDetector();
    }

    IDetector *MouseDetectorFactory::createJoystickDetector()
    {
        LOG_DEBUG("MouseDetectorFactory::createJoystickDetector()");
        return new MouseJoystickDetector();
    }

    IDetector *MouseDetectorFactory::createAccelerometerDetector()
    {
        LOG_DEBUG("MouseDetectorFactory::createAccelerometerDetector()");
        return new MouseAccelerometerDetector();
    }

} // namespace Detector
