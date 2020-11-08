#include "InterfaceState.h"

#include "DeviceLogger.h"

int cont = 0;

InterfaceState::InterfaceState(IContext &context) : IState(context)
{
    LOG_DEBUG("InterfaceState::InterfaceState()");

    // Add interface detectors
    const size_t numDetectors{2};
    IContext::DetectorType detectors[numDetectors]{IContext::DetectorType::BUTTON, IContext::DetectorType::JOYSTICK};
    context_.setDetectors(detectors, numDetectors);
}

void InterfaceState::processAction(const IAction::ActionData &)
{
    LOG_DEBUG("InterfaceState::processAction()");
    screen_.draw(Screen::ScreenAction::NONE);
    context_.changeState(IContext::StateType::MOUSE);
}

bool InterfaceState::isDetectionEnabled()
{
    LOG_DEBUG("InterfaceState::isDetectionEnabled()");
    return true;
}
