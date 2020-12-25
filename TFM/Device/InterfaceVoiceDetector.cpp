#include "InterfaceVoiceDetector.h"

#include "DeviceLogger.h"

#include "InterfaceAction.h"

namespace Detector
{

    bool InterfaceVoiceDetector::checkAction(const VoiceDetector::Words &word, IAction *action)
    {
        LOG_DEBUG(String("InterfaceVoiceDetector::checkAction() word: ") + String(static_cast<uint8_t>(word)));

        bool actionDetected{false};
        if (word == VoiceDetector::Words::START)
        {
            static_cast<InterfaceAction *>(action)->selectOption();
            actionDetected = true;
        }
        return actionDetected;
    }

} // namespace Detector
