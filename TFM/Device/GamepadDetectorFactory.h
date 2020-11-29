
#ifndef GAMEPAD_DETECTOR_FACTORY
#define GAMEPAD_DETECTOR_FACTORY

#include "IDetectorFactory.h"

namespace Detector
{
    /**
     * @brief Factory of IDetectors for gamepad state
     */
    class GamepadDetectorFactory : public IDetectorFactory
    {
    protected:
        ///< Implementation of virtual methods from IDetectorFactory
        virtual DetectorPtr createButtonDetector() override;
        virtual DetectorPtr createJoystickDetector() override;
        virtual DetectorPtr createAccelerometerDetector() override;
        virtual DetectorPtr createAccelGyroDetector() override;
    };

} // namespace Detector

#endif //GAMEPAD_DETECTOR_FACTORY
