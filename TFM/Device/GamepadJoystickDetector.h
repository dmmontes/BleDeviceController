
#ifndef GAMEPAD_JOYSTICK_DETECTOR
#define GAMEPAD_JOYSTICK_DETECTOR

#include "JoystickDetector.h"

namespace Detector
{

    /**
     * @brief Represents a joystick detector for a gamepad action
     */
    class GamepadJoystickDetector : public JoystickDetector
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
        bool joystickbuttonPressed_{false};     ///< Indicates if joystick button is pressed or not
        bool upButtonPressed_{false};           ///< Indicates if up button is pressed or not
        bool downButtonPressed_{false};         ///< Indicates if down button is pressed or not
        bool rightButtonPressed_{false};        ///< Indicates if right button is pressed or not
        bool leftButtonPressed_{false};         ///< Indicates if left button is pressed or not
    };

} // namespace Detector

#endif //GAMEPAD_JOYSTICK_DETECTOR
