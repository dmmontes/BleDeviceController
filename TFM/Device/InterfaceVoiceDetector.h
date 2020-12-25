
#ifndef INTERFACE_VOICE_DETECTOR
#define INTERFACE_VOICE_DETECTOR

#include "VoiceDetector.h"

namespace Detector
{
    /**
     * @brief Represents a Voice detector for a interface action
     */
    class InterfaceVoiceDetector : public VoiceDetector
    {
    protected:
        ///< Implementation of virtual methods from VoiceDetector
        virtual bool checkAction(const VoiceDetector::Words &word, IAction *action) override;
    };

} // namespace Detector

#endif //INTERFACE_VOICE_DETECTOR
