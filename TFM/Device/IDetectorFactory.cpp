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
            switch (detectorTypes[i])
            {
            case DetectorType::BUTTON:
                detectors_[i] = createButtonDetector();
                break;

            case DetectorType::JOYSTICK:
                detectors_[i] = createJoystickDetector();
                break;

            case DetectorType::ACCELEROMETER:
                detectors_[i] = createAccelerometerDetector();
                break;

            case DetectorType::ACCEL_GYRO:
                detectors_[i] = createAccelGyroDetector();
                break;

            case DetectorType::FSR:
                detectors_[i] = createFSRDetector();
                break;

            case DetectorType::VOICE:
                detectors_[i] = createVoiceDetector();
                break;

            default:
                LOG_WARNING("IDetectorFactory::createDetectors() Unknown specified type");
                break;
            }

            if (!detectors_[i])
            {
                LOG_ERROR("IDetectorFactory::createDetectors() created nullptr detector");
                freeDetectors();
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
