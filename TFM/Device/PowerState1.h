
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
    bool firstResult_;                       ///< Indicates if it is first time detecting in this state
    unsigned long timeToChangeToLowerState_; ///< Time to change to a lower power consumption state
    const uint16_t timeLimitToLowerState_;   ///< Limit times to change to a lower power consumption state
};

#endif //POWER_STATE_1
