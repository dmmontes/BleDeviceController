#include "Screen.h"

#include "DeviceLogger.h"

void Screen::draw(ScreenAction action)
{
    LOG_DEBUG(String("Screen::draw() action :") + String(static_cast<uint8_t>(action)));
}
