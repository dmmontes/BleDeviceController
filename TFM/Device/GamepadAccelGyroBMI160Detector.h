
#ifndef GAMEPAD_ACCEL_GYRO_BMI160_DETECTOR
#define GAMEPAD_ACCEL_GYRO_BMI160_DETECTOR

#include "AccelGyroBMI160Detector.h"

namespace Detector
{

    /**
     * @brief Represents a accelerometer detector for a gamepad action
     */
    class GamepadAccelGyroBMI160Detector : public AccelGyroBMI160Detector
    {
    public:
        /**
         * @brief Construct a new Gamepad Accelerometer Detector object
         */
        GamepadAccelGyroBMI160Detector();

    protected:
        ///< Implementation of virtual methods from JoystickDetector
        virtual bool checkAction(const AccelGyroState &accelGyroState, IAction *action) override;

    private:
        /**
         * @brief State of the turning 
         */
        enum class TurningState : uint8_t
        {
            NEGATIVE_TURNING, ///< Negative turning state
            NOT_TURNING,      ///< Not turning state
            POSITIVE_TURNING  ///< Positive turning state
        };

        /**
         * @brief Update the state of the turn 
         * 
         * @param actualState Actual state of the turn
         * @param timesDetecting Consecutive times detecting a movement
         * @param value Value read from gyroscope
         * @param lowLimit Low limit to consider a negative turn
         * @param highLimit High limit to consider a positive turn
         */
        void updateTurnState(TurningState &actualState, int8_t &timesDetecting, int16_t value, int16_t lowLimit,
                             int16_t highLimit);

        /**
         * @brief Check if jump movement has happened
         * 
         * @param value Value read from gyroscope
         * @param action action to be done
         * @return true if a movement has been detected, false otherwise
         */
        bool checkJump(int16_t value, IAction *action);

        /**
         * @brief Check if crouch or stand movements have happened
         * 
         * @param xValue value read from xAxis's gyroscope
         * @param zValue value read from zAxis's gyroscope
         * @param action action to be done
         * @return true if a movement has been detected, false otherwise
         */
        bool checkCrouchStand(int16_t xValue, int16_t zValue, IAction *action);

        const int16_t turnUpLimit_{100};       ///< Limit value in xGyro to consider a turn up movement
        const int16_t turnDownLimit_{-100};    ///< Limit value in xGyro to consider a turn down movement
        const int16_t turnRightLimit_{100};    ///< Limit value in xGyro to consider a turn right movement
        const int16_t turnLeftLimit_{-100};    ///< Limit value in xGyro to consider a turn left movement
        const int16_t jumpLimit_{-400};        ///< Limit value in xAccel to consider a jump action
        const int16_t xCrouchedLimit_{100};    ///< Limit value in xAccel to consider a crouched action
        const int16_t zCrouchedLimit_{-100};   ///< Limit value in zAccel to consider a crouched action
        const int16_t standLimit_{-300};       ///< Limit value in zAccel to consider a stand-up action
        const uint8_t timesToChangeState_{10}; ///< Consecutive times detecting a movement needed to change state

        ///< Horizontal turn state of the camera (left, not turning, right)
        TurningState horizontalState_{TurningState::NOT_TURNING};
        ///< Vertical turn state of the camera (down, not turning, up)
        TurningState verticalState_{TurningState::NOT_TURNING};

        int8_t horTimesDetecting_{0}; ///< Consecutive times detecting a movement needed to change horizontal state
        int8_t verTimesDetecting_{0}; ///< Consecutive times detecting a movement needed to change vertical state

        bool turnUpCamera_{false};      ///< Indicates if camera should be turn up
        bool turnDownCamera_{false};    ///< Indicates if camera should be turn down
        bool turnRightCamera_{false};   ///< Indicates if camera should be turn right
        bool turnLeftCamera_{false};    ///< Indicates if camera should be turn left
        bool jumpButtonPressed_{false}; ///< Indicates if jump button is pressed

        bool crouched_{false};                         ///< Indicates if character is crouched or not
        bool crouchKeyPressed_{false};                 ///< Indicates if crouch key has been pressed
        const uint32_t timesToCrouchStand_{10};        ///< Wait after detect a crouch (false positives when jumping)
        uint32_t timesContToCrouchStand_{10};          ///< Times cont to crouch(false positives when jumping)
        unsigned long timeToDetectCrouchStand_{0};     ///< Consecutive times detecting a crouch/stand movement
        unsigned long timeBetweenCrouchStand_{1000};   ///< Time to detect again a crouch/stand movement
        unsigned long timeAfterJumpCrouchStand_{2000}; ///< Time to detect again a crouch/stand movement after a jump
    };

} // namespace Detector

#endif //GAMEPAD_ACCEL_GYRO_BMI160_DETECTOR
