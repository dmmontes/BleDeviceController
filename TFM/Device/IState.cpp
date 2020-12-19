#include "IState.h"

#include "DeviceLogger.h"

#include "Energia.h"

///< Indicates if detection type has changed
bool NEW_DETECTION_TYPE{false};

///< Indicates the detection type
Detector::IDetector::DetectionType DETECTION_TYPE{Detector::IDetector::DetectionType::QUALITY};

/**
 * @brief Callback to notify when detection type changed
 * 
 * @param detectionType Type of detection
 */
void changeDetectionType(IPowerStateMachine::PowerState newState)
{
    NEW_DETECTION_TYPE = true;
    DETECTION_TYPE = static_cast<Detector::IDetector::DetectionType>(static_cast<uint8_t>(newState));
}

IState::IState(IContext &context) : context_(context), powerStateMachine_(&changeDetectionType)
{
    LOG_DEBUG("IState::IState()");
}

void IState::setDetectors(Detector::DetectorPtr *detectors, size_t numDetectors)
{
    LOG_DEBUG(String("IState::setDetectors() numDetectors: ") + String(numDetectors));
    detectors_ = detectors;
    numDetectors_ = numDetectors;
}

void IState::detectAction(IAction *action)
{
    LOG_DEBUG(String("IState::detectAction() numDetectors: ") + String(numDetectors_));

    // Check if is needed to detect actions
    if (!isDetectionEnabled())
    {
        LOG_DEBUG("IState::detectAction() Not detecting action");
        return;
    }

    // Try to detect an action with detectors
    bool detectedAction{false};
    for (size_t i = 0; i < numDetectors_; ++i)
    {
        detectedAction |= detectors_[i]->detectAction(action);
    }

    // Notifiy to the power state about the detection result
    powerStateMachine_.detectionResult(detectedAction);

    // Change detection type if power state changes
    if (NEW_DETECTION_TYPE)
    {
        NEW_DETECTION_TYPE = false;
        //Notify to detectors
        for (size_t i = 0; i < numDetectors_; ++i)
        {
            detectors_[i]->setDetectionType(DETECTION_TYPE);
        }

        // Notify to screen
        if (*deviceScreen_ != nullptr)
        {
            DETECTION_TYPE == Detector::IDetector::DetectionType::QUALITY
                ? (*deviceScreen_)->turnOn()
                : (*deviceScreen_)->turnOff();
        }
    }

    // Process an action if detected
    if (detectedAction)
    {
        processAction(action->getActionData());
    }
}
