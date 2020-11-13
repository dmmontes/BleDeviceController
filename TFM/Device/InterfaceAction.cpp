#include "InterfaceAction.h"

#include "DeviceLogger.h"

IAction::ActionData InterfaceAction::getActionData()
{
    LOG_DEBUG("InterfaceAction::getActionData()");

    // Return action data and reset the actual move
    previousMove_ = actualMove_;
    actualMove_ = static_cast<int8_t>(IntercaceMoves::NONE);
    IAction::ActionData actionData{&previousMove_, 1};
    return actionData;
}

void InterfaceAction::moveUp()
{
    LOG_DEBUG("InterfaceAction::moveUp()");
    actualMove_ |= static_cast<int8_t>(IntercaceMoves::UP);
}

void InterfaceAction::moveDown()
{
    LOG_DEBUG("InterfaceAction::moveDown()");
    actualMove_ |= static_cast<int8_t>(IntercaceMoves::DOWN);
}

void InterfaceAction::selectOption()
{
    LOG_DEBUG("InterfaceAction::selectOption()");
    actualMove_ |= static_cast<int8_t>(IntercaceMoves::SELECT);
}
