#include "MouseAction.h"

#include "DeviceLogger.h"

IAction::ActionData MouseAction::getActionData()
{
    LOG_DEBUG("MouseAction::getActionData()");

    // Send detected action and reset the new one (only cursor/scroll moves)
    memcpy(previousMouseAction_, mouseAction_, sizeof(mouseAction_));
    moveCursor(0, 0);
    scroll(0);
    return IAction::ActionData{previousMouseAction_, sizeof(mouseAction_)};
}

void MouseAction::rightClick(bool pressed)
{
    LOG_DEBUG(String("MouseAction::rightClick() pressed: ") + String(pressed));
    mouseAction_[0] += (pressed ? 1 : -1) * static_cast<int8_t>(MouseClick::RIGHT);
}

void MouseAction::leftClick(bool pressed)
{
    LOG_DEBUG(String("MouseAction::leftClick() pressed: ") + String(pressed));
    mouseAction_[0] += (pressed ? 1 : -1) * static_cast<int8_t>(MouseClick::LEFT);
}

void MouseAction::middleClick(bool pressed)
{
    LOG_DEBUG(String("MouseAction::middleClick() pressed: ") + String(pressed));
    mouseAction_[0] += (pressed ? 1 : -1) * static_cast<int8_t>(MouseClick::MIDDLE);
}

void MouseAction::moveCursor(int8_t xMove, int8_t yMove)
{
    LOG_DEBUG(String("MouseAction::moveCursor() xMove: ") + String(xMove) + String(", yMove: ") + String(yMove));
    mouseAction_[1] = xMove;
    mouseAction_[2] = yMove;
}

void MouseAction::scroll(int8_t scrollMove)
{
    LOG_DEBUG(String("MouseAction::scroll() scrollMove: ") + String(scrollMove));
    mouseAction_[3] = scrollMove;
}
