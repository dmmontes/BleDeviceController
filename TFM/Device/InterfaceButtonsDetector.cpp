#include "InterfaceButtonsDetector.h"

#include "DeviceLogger.h"

#include "InterfaceAction.h"

namespace Detector
{

    bool InterfaceButtonsDetector::checkAction(const ButtonState &buttonState, IAction *action)
    {
        LOG_DEBUG(String("InterfaceButtonsDetector::checkAction() button1: ") + String(buttonState.button1Pressed) + String(", button 2: ") + String(buttonState.button2Pressed));

        bool actionDetected{false};

        // Read the value of button 1
        if (button1Pressed_ != buttonState.button1Pressed)
        {
            button1Pressed_ = buttonState.button1Pressed;
            if (button1Pressed_)
            {
                LOG_DEBUG("InterfaceButtonsDetector::checkAction() Button 1 pressed");
                static_cast<InterfaceAction *>(action)->selectOption();
                actionDetected = true;
                return actionDetected;
            }
        }

        // Read the value of button 2
        if (button2Pressed_ != buttonState.button2Pressed)
        {
            button2Pressed_ = buttonState.button2Pressed;
            if (button2Pressed_)
            {
                LOG_DEBUG("InterfaceButtonsDetector::checkAction() Button 2 pressed");
                static_cast<InterfaceAction *>(action)->selectOption();
                actionDetected = true;
            }
        }
        return actionDetected;
    }

} // namespace Detector
