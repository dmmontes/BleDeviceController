#include "InterfaceState.h"

#include "DeviceLogger.h"

int cont = 0;

InterfaceState::InterfaceState(IContext &context, IAction &action) : IState(context, action)
{
    LOG_DEBUG("InterfaceState::InterfaceState()");
}

void InterfaceState::processAction(const IAction::ActionData &actionData)
{
    LOG_DEBUG("InterfaceState::processAction()");
    screen_.draw(Screen::ScreenAction::NONE);
    context_.changeState(IContext::StateType::MOUSE);
}
