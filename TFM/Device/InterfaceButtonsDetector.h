
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
        virtual bool checkAction(const ButtonState &buttonState, IAction *action) override;

    private:
        bool button1Pressed_{0}; ///< Indicates if button 1 is pressed or not
        bool button2Pressed_{0}; ///< Indicates if button 2 is pressed or not
    };

} // namespace Detector

#endif //INTERFACE_BUTTONS_DETECTOR
