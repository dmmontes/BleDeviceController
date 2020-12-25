
#ifndef INTERFACE_DETECTOR_FACTORY
#define INTERFACE_DETECTOR_FACTORY

#include "IDetectorFactory.h"

namespace Detector
{
    /**
     * @brief Factory of IDetectors for interface state
     */
    class InterfaceDetectorFactory : public IDetectorFactory
    {
    protected:
        ///< Implementation of virtual methods from IDetectorFactory
        virtual DetectorPtr createButtonDetector() override;
        virtual DetectorPtr createJoystickDetector() override;
        virtual DetectorPtr createVoiceDetector() override;
    };

} // namespace Detector

#endif //INTERFACE_DETECTOR_FACTORY
