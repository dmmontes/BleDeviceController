#include "GamepadFSRDetector.h"

#include "DeviceLogger.h"

#include "Energia.h"

namespace Detector
{

    GamepadFSRDetector::GamepadFSRDetector()
        : FSRDetector()
    {
        LOG_DEBUG("GamepadFSRDetector::GamepadFSRDetector()");
    }

    bool GamepadFSRDetector::checkAction(const FSRState &FSRState, IAction *action)
    {
        LOG_DEBUG(String("GamepadFSRDetector::checkAction() fsr1 value: ") + String(FSRState.fsr1) +
                  String(", fsr2 value: ") + String(FSRState.fsr2));

        bool actionDetected{false};

        // Check the state of every fsr
        actionDetected |= checkKey(FSRState.fsr1 > fsr1PressedLimit_, GamepadAction::Key::W, action);
        actionDetected |= checkKey(FSRState.fsr2 > fsr2PressedLimit_, GamepadAction::Key::S, action);

        return actionDetected;
    }

} // namespace Detector
