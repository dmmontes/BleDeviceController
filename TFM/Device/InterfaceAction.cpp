#include "InterfaceAction.h"

#include "DeviceLogger.h"

IAction::ActionData InterfaceAction::getActionData()
{
    LOG_DEBUG("InterfaceAction::getActionData()");
    return IAction::ActionData{nullptr, 0};
}
