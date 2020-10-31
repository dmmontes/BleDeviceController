#include "IDetectorFactory.h"

#include "DeviceLogger.h"

namespace Detector
{

    IDetectorFactory::~IDetectorFactory()
    {
        LOG_DEBUG("IDetectorFactory::~IDetectorFactory()");
        freeDetectors();
    }

    DetectorPtr *IDetectorFactory::createDetectors(DetectorType *detectorTypes, size_t numDetectors)
    {
        LOG_DEBUG("IDetectorFactory::createDetectors()");

        if (detectors_)
        {
            LOG_WARNING("IDetectorFactory::createDetectors() Previous detectors should be destroyed before");
            return nullptr;
        }

        freeDetectors();
        detectors_ = new DetectorPtr[numDetectors];

        for (size_t i = 0; i < numDetectors; ++i)
        {
            DetectorPtr detector{nullptr};
            switch (detectorTypes[i])
            {
            case DetectorType::BUTTON:
                detector = createButtonDetector();
                break;

            case DetectorType::JOYSTICK:
                detector = createJoystickDetector();
                break;

            default:
                LOG_WARNING("IDetectorFactory::createDetectors() Unknown specified type");
                break;
            }

            if (!detector)
            {
                LOG_ERROR("IDetectorFactory::createDetectors() created nullptr detector");
                freeDetectors();
                return nullptr;
            }
        }

        return detectors_;
    }

    void IDetectorFactory::deleteDetectors(DetectorPtr *detectors)
    {
        LOG_DEBUG("IDetectorFactory::deleteDetectors()");

        if (detectors_ != detectors)
        {
            LOG_WARNING("IDetectorFactory::deleteDetectors() detectors different from created previously");
        }
        freeDetectors();
    }

    void IDetectorFactory::freeDetectors()
    {
        LOG_DEBUG("IDetectorFactory::freeDetectors()");

        for (size_t i = 0; i < numDetectors_; ++i)
        {
            delete detectors_[i];
            detectors_[i] = nullptr;
        }
        delete[] detectors_;
        detectors_ = nullptr;
    }

} // namespace Detector
