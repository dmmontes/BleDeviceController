
#ifndef POWER_STATE_1
#define POWER_STATE_1

#include <cstdint>

#include "IPowerState.h"

/**
 * @brief Represents the state 1 in power consumption
 */
class PowerState1 : public IPowerState
{
public:
    /**
     * @brief Construct a new PowerState1 object
     * 
     * @param stateMachine power state machine
     */
    PowerState1(IPowerStateMachine *stateMachine);

    ///< Implementation of virtual methods from IPowerState
    virtual void detectionResult(bool detectedAction) override;

private:
    ///< Indicates the consecutive times detecting (or not) actions (positive if detects, negative if no detects action)
    int8_t timesDetecting_;

    const int8_t timesLimitToLowerState_; ///< Limit of times to change to a lower power consumption state
};

#endif //POWER_STATE_1
