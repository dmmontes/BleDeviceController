
#ifndef BLUETOOTH_CONNECTION_STATE_SEARCHING
#define BLUETOOTH_CONNECTION_STATE_SEARCHING

#include "IBluetoothConnectionState.h"

/**
 * @brief Represents the state of searching in a bluetooth connection
 */
class BluetoothConnectionStateSearching : public IBluetoothConnectionState
{
public:
    /**
     * @brief Construct a new BluetoothConnectionStateSearching object
     * 
     * @param stateMachine Bluetooth connection state machine
     * @param screen Screen to represents the state connection
     * @param configurationParams Parameters to configure a bluetooth connection 
     */
    BluetoothConnectionStateSearching(IBluetoothConnectionStateMachine *stateMachine, BluetoothScreen *screen,
                                      IBluetoothConnectionState::ConfigurationParams &configurationParams);

    ///< Implementation of virtual methods from IBluetoothConnectionState
    virtual void handleState(bool connected) override;
    virtual bool isConnected() override;

private:
    bool connectionLost_; ///< Indicates if last state was connected
};

#endif //BLUETOOTH_CONNECTION_STATE_SEARCHING
