#ifndef POWER_STATE_MACHINE
#define POWER_STATE_MACHINE

#include <cstdint>

#include "IPowerState.h"

/**
 * @brief Interface for states of power
 */
class IPowerStateMachine
{
public:
    /**
     * @brief Types of power states, where a lower number indicates a higher consume
     */
    enum class PowerState
    {
        PW1, ///< Power state 1, the device is totally active
        PW2, ///< Power state 2
        PW3, ///< Power state 3
        PW4  ///< Power state 4, the device is sleept
    };

    /**
     * @brief Destroy the IPowerStateMachine object
     */
    virtual ~IPowerStateMachine() = default;

    /**
     * @brief Change the state of the machine to the indicated
     * 
     * @param newState New state of power consume
     */
    virtual void changeState(PowerState newState) = 0;
};

// Function to notify changes in power state
typedef void (*PowerStateChangedFxn)(IPowerStateMachine::PowerState newState);

/**
 * @brief Represents the state machine of power consumption
 */
class PowerStateMachine : public IPowerStateMachine
{
public:
    /**
     * @brief Construct a new PowerStateMachine object
     * 
     * @param powerStateChanged Function to notify power state changed
     */
    PowerStateMachine(PowerStateChangedFxn powerStateChangedFxn);

    /**
     * @brief Destroy the PowerStateMachine object
     */
    virtual ~PowerStateMachine();

    ///< Implementation of virtual methods from IPowerStateMachine
    virtual void changeState(IPowerStateMachine::PowerState newState) override;

    /**
     * @brief Be Notified about the detection result 
     * 
     * @param detectedAction Indicates if an action has been detected
     */
    void detectionResult(bool detectedAction);

private:
    IPowerState *powerState_;                   ///< State of the power consumption
    PowerStateChangedFxn powerStateChangedFxn_; ///< Function to notify power state changed
};

#endif //POWER_STATE_MACHINE
