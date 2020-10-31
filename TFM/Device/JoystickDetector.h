
#ifndef JOYSTICK_DETECTOR
#define JOYSTICK_DETECTOR

#include "IDetector.h"

namespace Detector
{

    /**
     * @brief Represents a joystick detector of user's actions
     */
    class JoystickDetector : public IDetector
    {
    public:
        /**
         * @brief Construct a new Joystick Detector object
         */
        JoystickDetector();

        ///< Implementation of virtual methods from IDetector
        virtual void detectAction(IAction *action) override;

    protected:
        /**
         * @brief Represents the state of the joystick 
         */
        struct JoystickState
        {
            uint8_t button; ///< Value of button (0 press, 1 released)
            int16_t xAxis;  ///< Value of x Axis (0-1024)
            int16_t yAxis;  ///< Value of x Axis (0-1024)
        };

        /**
         * @brief Detect user action given the joystick state
         * 
         * @param joystickState state of the joystick
         * @param action[out] action to be filled by detector
         */
        virtual void detectAction(const JoystickState &joystickState, IAction *action) = 0;

    private:
        const uint8_t buttonPin_ = 5; // the number of the joystick select pin in MKII
        const uint8_t xAxisPin_ = 2;  // the number of the joystick X-axis analog in MKII
        const uint8_t yAxisPin_ = 26; // the number of the joystick Y-axis analog in MKII
    };

} // namespace Detector

#endif //JOYSTICK_DETECTOR
