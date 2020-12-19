#include "FSRDetector.h"

#include "DeviceLogger.h"

#include "Energia.h"

namespace Detector
{

    FSRDetector::FSRDetector(unsigned long timeBetweenDetections /*= 0*/)
        : IDetector(timeBetweenDetections)
    {
        LOG_DEBUG("FSRDetector::FSRDetector()");
    }

    void FSRDetector::setDetectionType(IDetector::DetectionType detectionType)
    {
        LOG_DEBUG(String("FSRDetector::setDetectionType() detectionType: ") +
                  String(static_cast<uint8_t>(detectionType)));

        detectionType_ = detectionType;
        switch (detectionType_)
        {
        case IDetector::DetectionType::QUALITY:
        case IDetector::DetectionType::NORMAL:
            pinMode(fsr1Pin_, INPUT_PULLUP);
            pinMode(fsr2Pin_, INPUT_PULLUP);
            break;
        case IDetector::DetectionType::LOW_POWER:
        case IDetector::DetectionType::SUSPEND:
            pinMode(fsr1Pin_, INPUT_PULLDOWN);
            pinMode(fsr2Pin_, INPUT_PULLDOWN);
            break;
        default:
            LOG_WARNING("FSRDetector::setDetectionType() unknown DetectionType");
            break;
        }
    }

    bool FSRDetector::checkAction(IAction *action)
    {
        LOG_DEBUG("FSRDetector::checkAction()");

        // Check if device is in low power mode
        if (detectionType_ == IDetector::DetectionType::LOW_POWER)
        {
            LOG_DEBUG("FSRDetector::checkAction() sensor in low power mode");
            return false;
        }

        // Get the data
        FSRState FSRState{analogRead(fsr1Pin_), analogRead(fsr2Pin_)};
        return checkAction(FSRState, action);
    }

} // namespace Detector
