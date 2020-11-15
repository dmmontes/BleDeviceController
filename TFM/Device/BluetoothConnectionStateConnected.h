
#ifndef BLUETOOTH_CONNECTION_STATE_CONNECTED
#define BLUETOOTH_CONNECTION_STATE_CONNECTED

#include "IBluetoothConnectionState.h"

/**
 * @brief Represents the state of connected in a bluetooth connection
 */
class BluetoothConnectionStateConnected : public IBluetoothConnectionState
{
public:
    /**
     * @brief Construct a new BluetoothConnectionStateConnected object
     * 
     * @param stateMachine Bluetooth connection state machine
     * @param screen Screen to represents the state connection
     * @param configurationParams Parameters to configure a bluetooth connection 
     */
    BluetoothConnectionStateConnected(IBluetoothConnectionStateMachine *stateMachine, BluetoothScreen *screen,
                                      IBluetoothConnectionState::ConfigurationParams &configurationParams);

    ///< Implementation of virtual methods from IBluetoothConnectionState
    virtual void handleState(bool connected) override;
    virtual bool isConnected() override;

private:
    bool connectionLost_;             ///< Indicates if connection has been lost or not
    unsigned long timeToSearch_;      ///< Time to start searching again if connection lost
    const unsigned long timeToReset_; ///< Time to reset connection after connection lost

    unsigned long timeToTurnOff_;              ///< Time to turn off the screen
    const unsigned long connectionOkDuration_; ///< Duration (ms) of the image "connection ok" in the screen
};

#endif //BLUETOOTH_CONNECTION_STATE_CONNECTED
