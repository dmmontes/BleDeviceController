#include "InterfaceDetectorFactory.h"

#include "DeviceLogger.h"

#include "InterfaceButtonsDetector.h"
#include "InterfaceJoystickDetector.h"

namespace Detector
{

    DetectorPtr InterfaceDetectorFactory::createButtonDetector()
    {
        LOG_DEBUG("InterfaceDetectorFactory::createButtonDetector()");
        return new InterfaceButtonsDetector();
    }

    DetectorPtr InterfaceDetectorFactory::createJoystickDetector()
    {
        LOG_DEBUG("InterfaceDetectorFactory::createButtonDetector()");
        return new InterfaceJoystickDetector();
    }

} // namespace Detector
