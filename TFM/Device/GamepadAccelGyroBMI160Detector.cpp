#include "GamepadAccelGyroBMI160Detector.h"

#include "DeviceLogger.h"

#include "GamepadDetectorUtil.h"
#include "Energia.h"

namespace Detector
{

    GamepadAccelGyroBMI160Detector::GamepadAccelGyroBMI160Detector()
        : AccelGyroBMI160Detector(50) //Time between detections = 30 ms
    {
        LOG_DEBUG("GamepadAccelGyroBMI160Detector::GamepadAccelGyroBMI160Detector()");
    }

    bool GamepadAccelGyroBMI160Detector::checkAction(const AccelGyroState &accelGyroState, IAction *action)
    {
        LOG_DEBUG(String("GamepadAccelGyroBMI160Detector::checkAction() xAccel: ") + String(accelGyroState.xAccel) +
                  String(", yAccel: ") + String(accelGyroState.yAccel) + String(", zAccel: ") + String(accelGyroState.zAccel));
        LOG_DEBUG(String("GamepadAccelGyroBMI160Detector::checkAction() xGyro: ") + String(accelGyroState.xGyro) +
                  String(", yGyro: ") + String(accelGyroState.yGyro) + String(", zGyro: ") + String(accelGyroState.zGyro));

        bool actionDetected{false};

        // Check vertical turns of the camera
        updateTurnState(verticalState_, verTimesDetecting_, accelGyroState.yGyro, turnDownLimit_, turnUpLimit_);
        actionDetected |= GamepadDetectorUtil::checkButton(turnUpCamera_,
                                                           verticalState_ == TurningState::POSITIVE_TURNING,
                                                           GamepadAction::Key::UP, action);
        actionDetected |= GamepadDetectorUtil::checkButton(turnDownCamera_,
                                                           verticalState_ == TurningState::NEGATIVE_TURNING,
                                                           GamepadAction::Key::DOWN, action);

        // Check horizontal turns of the camera
        updateTurnState(horizontalState_, horTimesDetecting_, accelGyroState.zGyro, turnLeftLimit_, turnRightLimit_);
        actionDetected |= GamepadDetectorUtil::checkButton(turnRightCamera_,
                                                           horizontalState_ == TurningState::POSITIVE_TURNING,
                                                           GamepadAction::Key::RIGHT, action);
        actionDetected |= GamepadDetectorUtil::checkButton(turnLeftCamera_,
                                                           horizontalState_ == TurningState::NEGATIVE_TURNING,
                                                           GamepadAction::Key::LEFT, action);

        // Check that if is time to detect jump / crouch / stan-up action again
        if (timeToDetectCrouchStand_ < millis())
        {
            actionDetected |= checkJump(accelGyroState.zAccel, action);
            if (!jumpButtonPressed_)
            {
                actionDetected |= checkCrouchStand(accelGyroState.xAccel, accelGyroState.zAccel, action);
            }
        }
        else
        {
            // Release key if any pressed
            if (jumpButtonPressed_)
            {
                static_cast<GamepadAction *>(action)->releaseKey(GamepadAction::Key::SPACE);
                jumpButtonPressed_ = false;
            }
            else if (crouchKeyPressed_)
            {
                static_cast<GamepadAction *>(action)->releaseKey(GamepadAction::Key::C);
                crouchKeyPressed_ = false;
            }
        }

        return actionDetected;
    }

    void GamepadAccelGyroBMI160Detector::updateTurnState(TurningState &actualState, int8_t &timesDetecting,
                                                         int16_t value, int16_t lowLimit, int16_t highLimit)
    {
        LOG_DEBUG(String("GamepadAccelGyroBMI160Detector::updateTurnState() actualState: ") +
                  String(static_cast<uint8_t>(actualState)) + String(", timesDetecting: ") + String(timesDetecting) + String(", value") + String(value));

        switch (actualState)
        {
        case TurningState::NEGATIVE_TURNING:
            // Check if value is higher than high limit
            if (value > highLimit)
            {
                // If times detecting is equal to limit, change to NOT TURNING state
                timesDetecting++;
                if (timesDetecting == timesToChangeState_)
                {
                    actualState = TurningState::NOT_TURNING;
                    timesDetecting = 0;
                }
            }
            // If value is lower reset the times detecting
            else
            {
                timesDetecting = 0;
            }
            break;

        case TurningState::NOT_TURNING:
            // Check if value is higher than high limit
            if (value > highLimit)
            {
                // If times detecting is equal to limit, change to POSITIVE_TURNING state
                timesDetecting = 1 + (timesDetecting > 0 ? timesDetecting : 0);
                if (timesDetecting == timesToChangeState_)
                {
                    actualState = TurningState::POSITIVE_TURNING;
                    timesDetecting = 0;
                }
            }
            // Check if value is lower than low limit
            else if (value < lowLimit)
            {
                // If times detecting is equal to limit, change to NEGATIVE_TURNING state
                timesDetecting = -1 + (timesDetecting < 0 ? timesDetecting : 0);
                if (abs(timesDetecting) == timesToChangeState_)
                {
                    actualState = TurningState::NEGATIVE_TURNING;
                    timesDetecting = 0;
                }
            }
            // If value is lower reset the times detecting
            else
            {
                timesDetecting = 0;
            }
            break;

        case TurningState::POSITIVE_TURNING:
            // Check if value is lower than low limit
            if (value < lowLimit)
            {
                // If times detecting is equal to limit, change to NOT TURNING state
                timesDetecting++;
                if (timesDetecting == timesToChangeState_)
                {
                    actualState = TurningState::NOT_TURNING;
                    timesDetecting = 0;
                }
            }
            // If value is lower reset the times detecting
            else
            {
                timesDetecting = 0;
            }
            break;

        default:
            LOG_WARNING("GamepadAccelGyroBMI160Detector::GamepadAccelGyroBMI160Detector() Incorrect state");
            break;
        }
    }

    bool GamepadAccelGyroBMI160Detector::checkJump(int16_t value, IAction *action)
    {
        LOG_DEBUG(String("GamepadAccelGyroBMI160Detector::checkJump() value: ") + String(value));

        // Check Jump button if not crouched
        bool actionDetected{!crouched_ && (value < jumpLimit_)};
        if (actionDetected)
        {
            // If jumped disable crouch / stand-up actions
            jumpButtonPressed_ = true;
            static_cast<GamepadAction *>(action)->pressKey(GamepadAction::Key::SPACE);
            timeToDetectCrouchStand_ = millis() + timeAfterJumpCrouchStand_;
            timesContToCrouchStand_ = timesToCrouchStand_;
        }
        return actionDetected;
    }

    bool GamepadAccelGyroBMI160Detector::checkCrouchStand(int16_t xValue, int16_t zValue, IAction *action)
    {
        LOG_DEBUG(String("GamepadAccelGyroBMI160Detector::checkCrouchStand() xValue: ") + String(xValue) +
                  String(", zValue: ") + String(zValue));
        bool actionDetected{false};

        // Check if it is time to crounch/stand (retarded x times due to false positive jumping)
        if (++timesContToCrouchStand_ == timesToCrouchStand_)
        {
            crouched_ = !crouched_;
            crouchKeyPressed_ = true;
            actionDetected = true;
            static_cast<GamepadAction *>(action)->pressKey(GamepadAction::Key::C);
            timeToDetectCrouchStand_ = millis() + timeBetweenCrouchStand_;
            return actionDetected;
        }

        // Check if crouch or stand-up movement are happening
        if (crouched_ ? (zValue < standLimit_) : (xValue < xCrouchedLimit_ && zValue > zCrouchedLimit_))
        {
            timesContToCrouchStand_ = 0;
        }
        return actionDetected;
    }

} // namespace Detector
