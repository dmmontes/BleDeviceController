#include "IState.h"

#include "DeviceLogger.h"

IState::IState(IContext &context, IAction &action) : context_(context), action_(action)
{
    LOG_DEBUG("IState::IState()");
}

void IState::setDetectors(Detector::DetectorPtr *detectors, size_t numDetectors)
{
    LOG_DEBUG("IState::setDetectors()");
    detectors_ = detectors;
    numDetectors_ = numDetectors;
}

void IState::detectAction()
{
    LOG_DEBUG("IState::detectAction()");
    for (size_t i = 0; i < numDetectors_; ++i)
    {
        detectors_[i]->detectAction(&action_);
    }
    processAction(action_.getActionData());
}