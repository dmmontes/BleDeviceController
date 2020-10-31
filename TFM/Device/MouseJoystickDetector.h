
#ifndef MOUSE_JOYSTICK_DETECTOR
#define MOUSE_JOYSTICK_DETECTOR

#include "JoystickDetector.h"

namespace Detector
{

    /**
     * @brief Represents a joystick detector for a mouse action
     */
    class MouseJoystickDetector : public JoystickDetector
    {
    protected:
        ///< Implementation of virtual methods from JoystickDetector
        virtual void detectAction(const JoystickState &joystickState, IAction *action) override;

    private:
        const int middleAxisValue_{512};                            ///< Middle value of axis (0-1024)
        const int axisTreshold_{100};                               ///< Minimum value to consider a movement in axis
        const int axisMoveLimit_{middleAxisValue_ - axisTreshold_}; ///< Maximum absolute value of axis's movement
        const int mouseMoveLimit_{20};                              ///< Maximum absolute value of mouse's movement
        int buttonState{1};                                         ///< State of the button (0 press, 1 released)
    };

} // namespace Detector

#endif //MOUSE_JOYSTICK_DETECTOR
