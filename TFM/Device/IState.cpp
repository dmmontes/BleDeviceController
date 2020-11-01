#include "IState.h"

#include "DeviceLogger.h"

IState::IState(IContext &context) : context_(context)
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

    // Process an action if detected
    if (!detectedAction)
    {
        LOG_DEBUG("IState::detectAction() No action detected");
        return;
    }
    processAction(action->getActionData());
}
