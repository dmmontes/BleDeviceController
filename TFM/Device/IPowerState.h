
#ifndef I_POWER_STATE
#define I_POWER_STATE

// Forward declaration
class IPowerStateMachine;

/**
 * @brief Represents the state of a power consumption
 */
class IPowerState
{
public:
    /**
     * @brief Construct a new IPowerState object
     * 
     * @param stateMachine power state machine
     */
    IPowerState(IPowerStateMachine *stateMachine) : stateMachine_{stateMachine} {}

    /**
     * @brief Destroy the IPowerState object
     */
    virtual ~IPowerState() = default;

    /**
     * @brief Be Notified about the detection result 
     * 
     * @param detectedAction Indicates if an action has been detected
     */
    virtual void detectionResult(bool detectedAction) = 0;

protected:
    IPowerStateMachine *stateMachine_; ///< Bluetooth connection state machine
};

#endif //I_POWER_STATE
