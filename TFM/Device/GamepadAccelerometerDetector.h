
#ifndef GAMEPAD_ACCELEROMETER_DETECTOR
#define GAMEPAD_ACCELEROMETER_DETECTOR

#include "AccelerometerDetector.h"
#include "GamepadDetector.h"

namespace Detector
{

    /**
     * @brief Represents a accelerometer detector for a gamepad action
     */
    class GamepadAccelerometerDetector : public AccelerometerDetector, public GamepadDetector
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
        const int8_t rightTurnLimit_{80}; ///< Limit value in xAxis to consider a scroll down movement
        const int8_t leftTurnLimit_{-80}; ///< Limit value in zAxis to consider a scroll up movement
    };

} // namespace Detector

#endif //GAMEPAD_ACCELEROMETER_DETECTOR
