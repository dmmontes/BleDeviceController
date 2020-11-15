
#ifndef BLUETOOTH_CONNECTION_STATE_PAIRING
#define BLUETOOTH_CONNECTION_STATE_PAIRING

#include "IBluetoothConnectionState.h"

/**
 * @brief Represents the state of pairing in a bluetooth connection
 */
class BluetoothConnectionStatePairing : public IBluetoothConnectionState
{
public:
    /**
     * @brief Construct a new BluetoothConnectionStatePairing object
     * 
     * @param stateMachine Bluetooth connection state machine
     * @param screen Screen to represents the state connection
     * @param configurationParams Parameters to configure a bluetooth connection 
     */
    BluetoothConnectionStatePairing(IBluetoothConnectionStateMachine *stateMachine, BluetoothScreen *screen,
                                    IBluetoothConnectionState::ConfigurationParams &configurationParams);

    ///< Implementation of virtual methods from IBluetoothConnectionState
    virtual void handleState(bool connected) override;
    virtual bool isConnected() override;

private:
    bool connectionLost_; ///< Indicates if last state was connected
};

#endif //BLUETOOTH_CONNECTION_STATE_PAIRING
