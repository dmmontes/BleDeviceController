#include "InterfaceButtonsDetector.h"

#include "DeviceLogger.h"

#include "InterfaceAction.h"

namespace Detector
{

    bool InterfaceButtonsDetector::detectAction(const ButtonState &buttonState, IAction *action)
    {
        LOG_DEBUG(String("InterfaceButtonsDetector::detectAction() button1: ") + String(buttonState.button1) + String(", button 2: ") + String(buttonState.button2));
        return true;
    }

} // namespace Detector
