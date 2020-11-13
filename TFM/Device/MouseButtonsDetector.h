
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
        virtual bool checkAction(const ButtonState &buttonState, IAction *action) override;

    private:
        bool button1Pressed_{0}; ///< Indicates if button 1 is pressed or not
        bool button2Pressed_{0}; ///< Indicates if button 2 is pressed or not
    };

} // namespace Detector

#endif //MOUSE_BUTTONS_DETECTOR
