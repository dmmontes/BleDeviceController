#include "MouseDetectorFactory.h"

#include "DeviceLogger.h"

#include "MouseButtonsDetector.h"
#include "MouseJoystickDetector.h"

namespace Detector
{

    IDetector *MouseDetectorFactory::createButtonDetector()
    {
        LOG_DEBUG("MouseDetectorFactory::createButtonDetector()");
        return new MouseButtonsDetector();
    }
    IDetector *MouseDetectorFactory::createJoystickDetector()
    {
        LOG_DEBUG("MouseDetectorFactory::createButtonDetector()");
        return new MouseJoystickDetector();
    }

} // namespace Detector
