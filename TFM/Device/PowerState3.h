
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
    bool firstResult_;                        ///< Indicates if it is first time detecting in this state
    unsigned long timeToChangeToLowerState_;  ///< Time to change to a lower power consumption state
    const uint16_t timeLimitToLowerState_;    ///< Limit times to change to a lower power consumption state
    unsigned long timeToChangeToHigherState_; ///< Time to change to a higher power consumption state
    const uint16_t timeLimitToHigherState_;   ///< Limit times to change to a higher power consumption state
    const int8_t timesLimitToHigherState_;    ///< Limit of times to change to a higher power consumption state
    uint8_t timesDetecting_;                  ///< Number of times detecting an action
    const uint32_t delayTime_;                ///< Delay time for each detected action in order to save power
};

#endif //POWER_STATE_3
