
#ifndef MOUSE_DETECTOR_FACTORY
#define MOUSE_DETECTOR_FACTORY

#include "IDetectorFactory.h"

namespace Detector
{
    /**
     * @brief Factory of IDetectors for mouse state
     */
    class MouseDetectorFactory : public IDetectorFactory
    {
    protected:
        ///< Implementation of virtual methods from IDetectorFactory
        virtual DetectorPtr createButtonDetector() override;
        virtual DetectorPtr createJoystickDetector() override;
        virtual DetectorPtr createAccelerometerDetector() override;
    };

} // namespace Detector

#endif //MOUSE_DETECTOR_FACTORY
