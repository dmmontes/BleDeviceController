
#ifndef INTERFACE_JOYSTICK_DETECTOR
#define INTERFACE_JOYSTICK_DETECTOR

#include "JoystickDetector.h"

namespace Detector
{

    /**
     * @brief Represents a joystick detector for a interface action
     */
    class InterfaceJoystickDetector : public JoystickDetector
    {
    protected:
        ///< Implementation of virtual methods from JoystickDetector
        virtual bool detectAction(const JoystickState &joystickState, IAction *action) override;
    };

} // namespace Detector

#endif //INTERFACE_JOYSTICK_DETECTOR
