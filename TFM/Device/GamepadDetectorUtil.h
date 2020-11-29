
#ifndef GAMEPAD_DETECTOR_UTIL
#define GAMEPAD_DETECTOR_UTIL

#include "DeviceLogger.h"

#include "GamepadAction.h"

namespace Detector
{
    namespace GamepadDetectorUtil
    {
        /**
         * @brief Check if button has changed its state
         * 
         * @param buttonState Previous state of the button
         * @param buttonState Actual state of the button
         * @param key Key that represents the button
         * @param action Action to be performed
         * @return true if button has changed its state, false otherwise
         */
        inline bool checkButton(bool &previousButtonState, bool buttonState, GamepadAction::Key key, IAction *action)
        {
            LOG_DEBUG(String("GamepadDetectorUtil::checkButton() previousButtonState: ") + String(previousButtonState) +
                      String(", buttonState: ") + String(buttonState) + String(", key: ") +
                      String(static_cast<uint8_t>(key)));

            bool actionDetected{false};

            // Read the value of button
            if (previousButtonState != buttonState)
            {
                LOG_DEBUG("GamepadJoystickDetector::checkButton() Button changed");
                previousButtonState = buttonState;
                actionDetected = true;

                // Update gamepad action
                if (buttonState)
                {
                    static_cast<GamepadAction *>(action)->pressKey(key);
                }
                else
                {
                    static_cast<GamepadAction *>(action)->releaseKey(key);
                }
            }
            return actionDetected;
        }

    } // namespace GamepadDetectorUtil
} // namespace Detector

#endif //GAMEPAD_DETECTOR_UTIL
