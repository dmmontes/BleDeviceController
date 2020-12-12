
#ifndef GAMEPAD_BUTTONS_DETECTOR
#define GAMEPAD_BUTTONS_DETECTOR

#include "ButtonsDetector.h"
#include "GamepadDetector.h"

namespace Detector
{

    /**
     * @brief Represents a buttons detector for a gamepad action
     */
    class GamepadButtonsDetector : public ButtonsDetector, public GamepadDetector
    {
    protected:
        ///< Implementation of virtual methods from ButtonsDetector
        virtual bool checkAction(const ButtonState &buttonState, IAction *action) override;
    };

} // namespace Detector

#endif //GAMEPAD_BUTTONS_DETECTOR
