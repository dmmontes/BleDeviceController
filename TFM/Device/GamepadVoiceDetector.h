
#ifndef GAMEPAD_VOICE_DETECTOR
#define GAMEPAD_VOICE_DETECTOR

#include "VoiceDetector.h"
#include "GamepadDetector.h"

namespace Detector
{
    /**
     * @brief Represents a Voice detector for a Gamepad action
     */
    class GamepadVoiceDetector : public VoiceDetector, public GamepadDetector
    {
    protected:
        ///< Implementation of virtual methods from VoiceDetector
        virtual bool checkAction(const VoiceDetector::Words &word, IAction *action) override;

    private:
        bool paused_{false};     ///< Indicates if paused is active
        bool keyPressed_{false}; ///< Indicates if key is pressed
    };

} // namespace Detector

#endif //GAMEPAD_VOICE_DETECTOR
