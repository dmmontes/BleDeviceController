
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
    public:
        /**
         * @brief Construct a new Interface Joystick Detector object 
         */
        InterfaceJoystickDetector();

    protected:
        ///< Implementation of virtual methods from JoystickDetector
        virtual bool checkAction(const JoystickState &joystickState, IAction *action) override;

    private:
        const uint16_t moveUpLimit_{924};   ///< Limit to consider a move up in Y axis (read value must be higher)
        const uint16_t moveDownLimit_{100}; ///< Limit to considere a move up in Y axis (read value must be lower)
    };

} // namespace Detector

#endif //INTERFACE_JOYSTICK_DETECTOR
