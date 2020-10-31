#include "MouseButtonsDetector.h"

#include "DeviceLogger.h"

#include "MouseAction.h"

namespace Detector
{

    void MouseButtonsDetector::detectAction(const ButtonState &buttonState, IAction *action)
    {
        LOG_DEBUG(String("MouseButtonsDetector::detectAction() button1: ") + String(buttonState.button1) + String(", button 2: ") + String(buttonState.button2));

        // Read the value of button 1
        if (button1State_ != buttonState.button1)
        {
            LOG_DEBUG("Button 1 changed");
            button1State_ = buttonState.button1;
            static_cast<MouseAction *>(action)->rightClick(button1State_ == 0);
        }

        // Read the value of button 2
        if (button2State_ != buttonState.button2)
        {
            LOG_DEBUG("Button 2 changed");
            button2State_ = buttonState.button2;
            static_cast<MouseAction *>(action)->leftClick(button2State_ == 0);
        }
    }

} // namespace Detector