
#ifndef INTERFACE_BUTTONS_DETECTOR
#define INTERFACE_BUTTONS_DETECTOR

#include "ButtonsDetector.h"

namespace Detector
{

    /**
     * @brief Represents a buttons detector for a interface action
     */
    class InterfaceButtonsDetector : public ButtonsDetector
    {
    protected:
        ///< Implementation of virtual methods from ButtonsDetector
        virtual bool detectAction(const ButtonState &buttonState, IAction *action) override;
    };

} // namespace Detector

#endif //INTERFACE_BUTTONS_DETECTOR
