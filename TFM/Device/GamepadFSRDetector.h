#ifndef GAMEPAD_FSR_DETECTOR
#define GAMEPAD_FSR_DETECTOR

#include "FSRDetector.h"
#include "GamepadDetector.h"

namespace Detector
{

    /**
     * @brief Represents a FSR detector for a gamepad action
     */
    class GamepadFSRDetector : public FSRDetector, public GamepadDetector
    {
    public:
        /**
         * @brief Construct a new Gamepad FSR Detector object 
         */
        GamepadFSRDetector();

    protected:
        ///< Implementation of virtual methods from FSRDetector
        virtual bool checkAction(const FSRState &FSRState, IAction *action) override;

    private:
        const uint16_t fsr1PressedLimit_{400}; ///< Limit to consider that fsr 1 is pressed (read value must be higher)
        const uint16_t fsr2PressedLimit_{400}; ///< Limit to consider that fsr 2 is pressed (read value must be higher)
    };

} // namespace Detector

#endif //GAMEPAD_FSR_DETECTOR
