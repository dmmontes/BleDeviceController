#include "GamepadDetectorFactory.h"

#include "DeviceLogger.h"

#include "GamepadButtonsDetector.h"
#include "GamepadJoystickDetector.h"
#include "GamepadAccelerometerDetector.h"
#include "GamepadAccelGyroBMI160Detector.h"
#include "GamepadFSRDetector.h"

namespace Detector
{

    DetectorPtr GamepadDetectorFactory::createButtonDetector()
    {
        LOG_DEBUG("GamepadDetectorFactory::createButtonDetector()");
        return new GamepadButtonsDetector();
    }

    DetectorPtr GamepadDetectorFactory::createJoystickDetector()
    {
        LOG_DEBUG("GamepadDetectorFactory::createJoystickDetector()");
        return new GamepadJoystickDetector();
    }

    DetectorPtr GamepadDetectorFactory::createAccelerometerDetector()
    {
        LOG_DEBUG("GamepadDetectorFactory::createAccelerometerDetector()");
        return new GamepadAccelerometerDetector();
    }

    DetectorPtr GamepadDetectorFactory::createAccelGyroDetector()
    {
        LOG_DEBUG("GamepadDetectorFactory::createAccelGyroDetector()");
        return new GamepadAccelGyroBMI160Detector();
    }

    DetectorPtr GamepadDetectorFactory::createFSRDetector()
    {
        LOG_DEBUG("GamepadDetectorFactory::createFSRDetector()");
        return new GamepadFSRDetector();
    }

} // namespace Detector
