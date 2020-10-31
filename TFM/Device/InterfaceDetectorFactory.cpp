#include "InterfaceDetectorFactory.h"

#include "DeviceLogger.h"

#include "MouseButtonsDetector.h"
#include "MouseJoystickDetector.h"

namespace Detector
{

    IDetector *InterfaceDetectorFactory::createButtonDetector()
    {
        LOG_DEBUG("InterfaceDetectorFactory::createButtonDetector()");
        return nullptr;
    }
    IDetector *InterfaceDetectorFactory::createJoystickDetector()
    {
        LOG_DEBUG("InterfaceDetectorFactory::createButtonDetector()");
        return nullptr;
    }

} // namespace Detector
