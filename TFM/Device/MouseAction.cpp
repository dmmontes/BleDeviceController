#include "MouseAction.h"

#include "DeviceLogger.h"

IAction::ActionData MouseAction::getActionData()
{
    LOG_DEBUG("MouseAction::getActionData()");
    return IAction::ActionData{mouseAction, sizeof(mouseAction)};
}

void MouseAction::rightClick(bool pressed)
{
    LOG_DEBUG(String("MouseAction::rightClick() pressed: ") + String(pressed));
    mouseAction[0] = static_cast<int8_t>(pressed ? MouseClick::RIGHT : MouseClick::RELEASED);
}

void MouseAction::leftClick(bool pressed)
{
    LOG_DEBUG(String("MouseAction::leftClick() pressed: ") + String(pressed));
    mouseAction[0] = static_cast<int8_t>(pressed ? MouseClick::LEFT : MouseClick::RELEASED);
}

void MouseAction::middleClick(bool pressed)
{
    LOG_DEBUG(String("MouseAction::middleClick() pressed: ") + String(pressed));
    mouseAction[0] = static_cast<int8_t>(pressed ? MouseClick::MIDDLE : MouseClick::RELEASED);
}

void MouseAction::moveCursor(int8_t xMove, int8_t yMove)
{
    LOG_DEBUG(String("MouseAction::moveCursor() xMove: ") + String(xMove) + String(", yMove: ") + String(yMove));
    mouseAction[1] = xMove;
    mouseAction[2] = yMove;
}

void MouseAction::scroll(int8_t scrollMove)
{
    LOG_DEBUG(String("MouseAction::scroll() scrollMove: ") + String(scrollMove));
    mouseAction[3] = scrollMove;
}
