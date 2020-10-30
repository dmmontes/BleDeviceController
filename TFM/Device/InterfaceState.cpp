#include "InterfaceState.h"

#include "DeviceLogger.h"

int cont = 0;

InterfaceState::InterfaceState(DeviceContext *deviceContext) : IState(deviceContext)
{
    LOG_DEBUG("InterfaceState::InterfaceState()");
}

void InterfaceState::processAction()
{
    LOG_DEBUG("InterfaceState::processAction()");
    screen_.draw(Screen::ScreenAction::NONE);
    deviceContext_->changeState(DeviceContext::StateType::MOUSE);
}
