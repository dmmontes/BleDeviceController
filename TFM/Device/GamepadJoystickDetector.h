
#ifndef GAMEPAD_JOYSTICK_DETECTOR
#define GAMEPAD_JOYSTICK_DETECTOR

#include "JoystickDetector.h"
#include "GamepadDetector.h"

namespace Detector
{

    /**
     * @brief Represents a joystick detector for a gamepad action
     */
    class GamepadJoystickDetector : public JoystickDetector, public GamepadDetector
    {
    public:
        /**
         * @brief Construct a new Gamepad Joystick Detector object 
         */
        GamepadJoystickDetector();

    protected:
        ///< Implementation of virtual methods from JoystickDetector
        virtual bool checkAction(const JoystickState &joystickState, IAction *action) override;

    private:
        const uint16_t moveUpRightLimit_{750};  ///< Limit to consider a move up/right (read value must be higher)
        const uint16_t moveDownLeftLimit_{200}; ///< Limit to considere a move down/left (read value must be lower)
    };

} // namespace Detector

#endif //GAMEPAD_JOYSTICK_DETECTOR
