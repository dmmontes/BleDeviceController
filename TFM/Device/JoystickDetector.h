
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
         * 
         * @param action[out] action to be filled by detector
         * @return bool Indicates if an action has been detected
         */
        JoystickDetector(uint8_t turnsBetweenDetections = 0, uint8_t turnsToDetect = 0);

        ///< Implementation of virtual methods from IDetector
        virtual bool checkAction(IAction *action) override;

    protected:
        /**
         * @brief Represents the state of the joystick 
         */
        struct JoystickState
        {
            bool buttonPressed; ///< Indicates if button is pressed
            uint16_t xAxis;     ///< Value of x Axis (0-1024)
            uint16_t yAxis;     ///< Value of y Axis (0-1024)
        };

        /**
         * @brief Detect user action given the joystick state
         * 
         * @param joystickState state of the joystick
         * @param action[out] action to be filled by detector
         * @return bool Indicates if an action has been detected
         */
        virtual bool checkAction(const JoystickState &joystickState, IAction *action) = 0;

    private:
        const uint8_t buttonPin_ = 5; // the number of the joystick select pin in MKII
        const uint8_t xAxisPin_ = 2;  // the number of the joystick X-axis pin in MKII
        const uint8_t yAxisPin_ = 26; // the number of the joystick Y-axis pin in MKII
    };

} // namespace Detector

#endif //JOYSTICK_DETECTOR
