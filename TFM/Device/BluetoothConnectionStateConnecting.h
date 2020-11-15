
#ifndef BLUETOOTH_CONNECTION_STATE_CONNECTING
#define BLUETOOTH_CONNECTION_STATE_CONNECTING

#include "IBluetoothConnectionState.h"

/**
 * @brief Represents the state of connecting in a bluetooth connection
 */
class BluetoothConnectionStateConnecting : public IBluetoothConnectionState
{
public:
    /**
     * @brief Construct a new BluetoothConnectionStateConnecting object
     * 
     * @param stateMachine Bluetooth connection state machine
     * @param screen Screen to represents the state connection
     * @param configurationParams Parameters to configure a bluetooth connection 
     */
    BluetoothConnectionStateConnecting(IBluetoothConnectionStateMachine *stateMachine, BluetoothScreen *screen,
                                       IBluetoothConnectionState::ConfigurationParams &configurationParams);

    ///< Implementation of virtual methods from IBluetoothConnectionState
    virtual void handleState(bool connected) override;
    virtual bool isConnected() override;
};

#endif //BLUETOOTH_CONNECTION_STATE_CONNECTING
