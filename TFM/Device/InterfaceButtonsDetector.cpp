#include "InterfaceButtonsDetector.h"

#include "DeviceLogger.h"

#include "InterfaceAction.h"

namespace Detector
{

    bool InterfaceButtonsDetector::detectAction(const ButtonState &buttonState, IAction *)
    {
        LOG_DEBUG(String("InterfaceButtonsDetector::detectAction() button1: ") + String(buttonState.button1Pressed) + String(", button 2: ") + String(buttonState.button2Pressed));

        return true;
    }

} // namespace Detector
