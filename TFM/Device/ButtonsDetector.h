
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
         * 
         * @param timeBetweenDetections Turns between 2 consecutive detections
         */
        ButtonsDetector(unsigned long timeBetweenDetections = 0);

        ///< Implementation of virtual methods from IDetector
        virtual bool checkAction(IAction *action) override;

    protected:
        /**
         * @brief Represents the state of the buttons 
         */
        struct ButtonState
        {
            bool button1Pressed; ///< Indicates if button 1 is pressed or not
            bool button2Pressed; ///< Indicates if button 2 is pressed or not
        };

        /**
         * @brief Detect user action given the buttons state
         * 
         * @param buttonState state of the button
         * @param action[out] action to be filled by detector
         * @return bool Indicates if an action has been detected
         */
        virtual bool checkAction(const ButtonState &buttonState, IAction *action) = 0;

    private:
        const uint8_t button1Pin_ = 33; ///< Pin number variable for Button 1 in MKII
        const uint8_t button2Pin_ = 32; ///< Pin number variable for Button 2 in MKII
    };

} // namespace Detector

#endif //BUTTONS_DETECTOR
