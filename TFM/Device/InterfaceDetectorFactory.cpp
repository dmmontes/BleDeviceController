#include "InterfaceDetectorFactory.h"

#include "DeviceLogger.h"

#include "InterfaceButtonsDetector.h"
#include "InterfaceJoystickDetector.h"

namespace Detector
{

    IDetector *InterfaceDetectorFactory::createButtonDetector()
    {
        LOG_DEBUG("InterfaceDetectorFactory::createButtonDetector()");
        return new InterfaceButtonsDetector();
    }
    IDetector *InterfaceDetectorFactory::createJoystickDetector()
    {
        LOG_DEBUG("InterfaceDetectorFactory::createButtonDetector()");
        return new InterfaceJoystickDetector();
    }

} // namespace Detector
