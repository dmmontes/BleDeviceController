#include "GamepadVoiceDetector.h"

#include "DeviceLogger.h"

#include "GamepadAction.h"

namespace Detector
{

    bool GamepadVoiceDetector::checkAction(const VoiceDetector::Words &word, IAction *action)
    {
        LOG_DEBUG(String("GamepadVoiceDetector::checkAction() word: ") + String(static_cast<uint8_t>(word)));

        bool actionDetected{false};

        // Release key if pressed
        if (keyPressed_)
        {
            actionDetected |= checkKey(false, GamepadAction::Key::P, action);
            keyPressed_ = false;
        }
        // If paused check if restart
        else if (paused_)
        {
            paused_ = (word != VoiceDetector::Words::START);
            actionDetected |= checkKey(!paused_, GamepadAction::Key::P, action);
            keyPressed_ = actionDetected;
        }
        // If active, check if pause
        else
        {
            paused_ = (word == VoiceDetector::Words::PAUSE);
            actionDetected |= checkKey(paused_, GamepadAction::Key::P, action);
            keyPressed_ = actionDetected;
        }

        return actionDetected;
    }

} // namespace Detector
