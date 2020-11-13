#include "MouseButtonsDetector.h"

#include "DeviceLogger.h"

#include "MouseAction.h"

namespace Detector
{

    bool MouseButtonsDetector::checkAction(const ButtonState &buttonState, IAction *action)
    {
        LOG_DEBUG(String("MouseButtonsDetector::checkAction() button1Pressed: ") + String(buttonState.button1Pressed) + String(", button 2: ") + String(buttonState.button2Pressed));

        bool actionDetected{false};

        // Read the value of button 1
        if (button1Pressed_ != buttonState.button1Pressed)
        {
            LOG_DEBUG("MouseButtonsDetector::checkAction() Button 1 changed");
            button1Pressed_ = buttonState.button1Pressed;
            static_cast<MouseAction *>(action)->leftClick(button1Pressed_);
            actionDetected = true;
        }

        // Read the value of button 2
        if (button2Pressed_ != buttonState.button2Pressed)
        {
            LOG_DEBUG("MouseButtonsDetector::checkAction() Button 2 changed");
            button2Pressed_ = buttonState.button2Pressed;
            static_cast<MouseAction *>(action)->rightClick(button2Pressed_);
            actionDetected = true;
        }
        return actionDetected;
    }

} // namespace Detector
