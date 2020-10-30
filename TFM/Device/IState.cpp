#include "IState.h"

#include "DeviceLogger.h"

IState::IState(DeviceContext *deviceContext) : deviceContext_(deviceContext)
{
    LOG_DEBUG("IState::IState()");
}

void IState::detectAction()
{
    LOG_DEBUG("IState::detectAction()");
    processAction();
}