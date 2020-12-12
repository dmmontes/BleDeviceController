#include "GamepadButtonsDetector.h"

#include "DeviceLogger.h"

#include "GamepadAction.h"

namespace Detector
{

    bool GamepadButtonsDetector::checkAction(const ButtonState &buttonState, IAction *action)
    {
        LOG_DEBUG(String("GamepadButtonsDetector::checkAction() button1Pressed: ") + String(buttonState.button1Pressed) + String(", button2Pressed: ") + String(buttonState.button2Pressed));

        bool actionDetected{false};

        actionDetected |= checkKey(buttonState.button1Pressed, GamepadAction::Key::NUMBER1, action);
        actionDetected |= checkKey(buttonState.button2Pressed, GamepadAction::Key::NUMBER2, action);

        return actionDetected;
    }

} // namespace Detector
