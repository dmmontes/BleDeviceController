
#ifndef MOUSE_BUTTONS_DETECTOR
#define MOUSE_BUTTONS_DETECTOR

#include "ButtonsDetector.h"

namespace Detector
{

    /**
     * @brief Represents a buttons detector for a mouse action
     */
    class MouseButtonsDetector : public ButtonsDetector
    {
    protected:
        ///< Implementation of virtual methods from ButtonsDetector
        virtual bool detectAction(const ButtonState &buttonState, IAction *action) override;

    private:
        bool button1Pressed_{0}; ///< State of the button 1 (0 press, 1 released)
        bool button2Pressed_{0}; ///< State of the button 2 (0 press, 1 released)
    };

} // namespace Detector

#endif //MOUSE_BUTTONS_DETECTOR
