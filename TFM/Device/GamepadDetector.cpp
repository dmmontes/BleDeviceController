#include "GamepadDetector.h"

#include "DeviceLogger.h"

namespace Detector
{
    uint8_t GamepadDetector::ID{0};

    bool GamepadDetector::checkKey(bool keyPressed, GamepadAction::Key key, IAction *action)
    {
        LOG_DEBUG(String("GamepadDetector::checkKey() detectorId: ") + String(detectorId_) +
                  String(", keyPressed: ") + String(keyPressed) + String(", key: ") +
                  String(static_cast<uint8_t>(key)));

        bool actionDetected{false};

        // Read the value of button
        if (static_cast<GamepadAction *>(action)->isKeypressed(key) != keyPressed)
        {
            // Update gamepad action
            if (keyPressed)
            {
                actionDetected = static_cast<GamepadAction *>(action)->pressKey(key, detectorId_);
            }
            else
            {
                actionDetected = static_cast<GamepadAction *>(action)->releaseKey(key, detectorId_);
            }
        }
        return actionDetected;
    }

} // namespace Detector
