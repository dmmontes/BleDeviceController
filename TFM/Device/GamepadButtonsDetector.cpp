#include "GamepadButtonsDetector.h"

#include "DeviceLogger.h"

#include "GamepadAction.h"

namespace Detector
{

    bool GamepadButtonsDetector::checkAction(const ButtonState &buttonState, IAction *action)
    {
        LOG_DEBUG(String("GamepadButtonsDetector::checkAction() button1Pressed: ") + String(buttonState.button1Pressed) + String(", button2Pressed: ") + String(buttonState.button2Pressed));

        bool actionDetected{false};

        // Read the value of button 1
        if (button1Pressed_ != buttonState.button1Pressed)
        {
            LOG_DEBUG("GamepadButtonsDetector::checkAction() Button 1 changed");
            button1Pressed_ = buttonState.button1Pressed;
            actionDetected = true;

            // Update gamepad action
            if (button1Pressed_)
            {
                static_cast<GamepadAction *>(action)->pressKey(GamepadAction::Key::NUMBER1);
            }
            else
            {
                static_cast<GamepadAction *>(action)->releaseKey(GamepadAction::Key::NUMBER1);
            }
        }

        // Read the value of button 2
        if (button2Pressed_ != buttonState.button2Pressed)
        {
            LOG_DEBUG("GamepadButtonsDetector::checkAction() Button 2 changed");
            button2Pressed_ = buttonState.button2Pressed;
            actionDetected = true;

            // Update gamepad action
            if (button2Pressed_)
            {
                static_cast<GamepadAction *>(action)->pressKey(GamepadAction::Key::NUMBER2);
            }
            else
            {
                static_cast<GamepadAction *>(action)->releaseKey(GamepadAction::Key::NUMBER2);
            }
        }
        return actionDetected;
    }

} // namespace Detector
