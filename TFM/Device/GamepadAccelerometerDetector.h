
#ifndef GAMEPAD_ACCELEROMETER_DETECTOR
#define GAMEPAD_ACCELEROMETER_DETECTOR

#include "AccelerometerDetector.h"

namespace Detector
{

    /**
     * @brief Represents a accelerometer detector for a gamepad action
     */
    class GamepadAccelerometerDetector : public AccelerometerDetector
    {
    public:
        /**
         * @brief Construct a new Gamepad Accelerometer Detector object
         */
        GamepadAccelerometerDetector();

    protected:
        ///< Implementation of virtual methods from AccelerometerDetector
        virtual bool checkAction(const AccelerometerState &accelerometerState, IAction *action) override;

    private:
        const int8_t rightTurnLimit_{100}; ///< Limit value in xAxis to consider a scroll down movement
        const int8_t leftTurnLimit_{-100}; ///< Limit value in zAxis to consider a scroll up movement

        bool rightButtonPressed_{false}; ///< Indicates if right button is pressed or not
        bool leftButtonPressed_{false};  ///< Indicates if left button is pressed or not
    };

} // namespace Detector

#endif //GAMEPAD_ACCELEROMETER_DETECTOR
