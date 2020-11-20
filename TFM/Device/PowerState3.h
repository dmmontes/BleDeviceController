
#ifndef POWER_STATE_3
#define POWER_STATE_3

#include <cstdint>

#include "IPowerState.h"

/**
 * @brief Represents the state 3 in power consumption
 */
class PowerState3 : public IPowerState
{
public:
    /**
     * @brief Construct a new PowerState3 object
     * 
     * @param stateMachine power state machine
     */
    PowerState3(IPowerStateMachine *stateMachine);

    ///< Implementation of virtual methods from IPowerState
    virtual void detectionResult(bool detectedAction) override;

private:
    ///< Indicates the consecutive times detecting (or not) actions (positive if detects, negative if no detects action)
    int8_t timesDetecting_;

    const int8_t timesLimitToLowerState_;  ///< Limit of times to change to a lower power consumption state
    const int8_t timesLimitToHigherState_; ///< Limit of times to change to a higher power consumption state
    const uint32_t delayTime_;             ///< Delay time for each detected action in order to save power
};

#endif //POWER_STATE_3
