
#ifndef POWER_STATE_4
#define POWER_STATE_4

#include <cstdint>

#include "IPowerState.h"

/**
 * @brief Represents the state 4 in power consumption
 */
class PowerState4 : public IPowerState
{
public:
    /**
     * @brief Construct a new PowerState4 object
     * 
     * @param stateMachine power state machine
     */
    PowerState4(IPowerStateMachine *stateMachine);

    ///< Implementation of virtual methods from IPowerState
    virtual void detectionResult(bool detectedAction) override;

private:
    const uint32_t delayTime_; ///< Delay time for each detected action in order to save power
};

#endif //POWER_STATE_4
