
#ifndef BUTTONS_DETECTOR
#define BUTTONS_DETECTOR

#include "IDetector.h"

namespace Detector
{

    /**
     * @brief Represents a buttons detector of user's actions
     */
    class ButtonsDetector : public IDetector
    {
    public:
        /**
         * @brief Construct a new Buttons Detector object
         */
        ButtonsDetector();

        ///< Implementation of virtual methods from IDetector
        virtual void detectAction(IAction *action) override;

    protected:
        /**
         * @brief Represents the state of the buttons 
         */
        struct ButtonState
        {
            uint8_t button1; ///< Value of button 1 (0 press, 1 released)
            uint8_t button2; ///< Value of button 1 (0 press, 1 released)
        };

        /**
         * @brief Detect user action given the buttons state
         * 
         * @param buttonState state of the button
         * @param action[out] action to be filled by detector
         */
        virtual void detectAction(const ButtonState &buttonState, IAction *action) = 0;

    private:
        const uint8_t button1Pin_ = 33; ///< Pin number variable for Button 1 in MKII
        const uint8_t button2Pin_ = 32; ///< Pin number variable for Button 2 in MKII
    };

} // namespace Detector

#endif //BUTTONS_DETECTOR
