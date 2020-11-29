#include "MouseDetectorFactory.h"

#include "DeviceLogger.h"

#include "MouseButtonsDetector.h"
#include "MouseJoystickDetector.h"
#include "MouseAccelerometerDetector.h"

namespace Detector
{

    DetectorPtr MouseDetectorFactory::createButtonDetector()
    {
        LOG_DEBUG("MouseDetectorFactory::createButtonDetector()");
        return new MouseButtonsDetector();
    }

    DetectorPtr MouseDetectorFactory::createJoystickDetector()
    {
        LOG_DEBUG("MouseDetectorFactory::createJoystickDetector()");
        return new MouseJoystickDetector();
    }

    DetectorPtr MouseDetectorFactory::createAccelerometerDetector()
    {
        LOG_DEBUG("MouseDetectorFactory::createAccelerometerDetector()");
        return new MouseAccelerometerDetector();
    }

} // namespace Detector
