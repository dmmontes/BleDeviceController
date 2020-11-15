#ifndef BLUETOOTH_CONNECTION_STATE_MACHINE
#define BLUETOOTH_CONNECTION_STATE_MACHINE

#include <cstdint>

#include "BluetoothScreen.h"
#include "IBluetoothConnectionState.h"

/**
 * @brief Interface for states of a bluetooth connection
 */
class IBluetoothConnectionStateMachine
{
public:
    /**
     * @brief States of a bluetooth connection process
     */
    enum class ConnectionState
    {
        SEARCHING,  ///< Searching state, devices can search for the device
        CONNECTING, ///< Connecting state, trying to connect
        PAIRING,    ///< Pairing state, trying to pair with other device
        CONNECTED   //< Connected state, devices connected
    };

    /**
     * @brief Destroy the IBluetoothConnectionStateMachine object
     */
    virtual ~IBluetoothConnectionStateMachine() = default;

    /**
     * @brief Change the state of the machine to the next
     * 
     * @param newState New state of bluetooth connection
     * @param screen pointer to the actual screen
     */
    virtual void changeState(ConnectionState newState, BluetoothScreen *screen) = 0;
};

/**
 * @brief Represents the state machine of a bluetooth connection
 */
class BluetoothConnectionStateMachine : public IBluetoothConnectionStateMachine
{
public:
    /**
     * @brief Construct a new BluetoothConnectionStateMachine object
     * 
     * @param configurationParams Parameters to configure a bluetooth connection 
     */
    BluetoothConnectionStateMachine(IBluetoothConnectionState::ConfigurationParams &configurationParams);

    /**
     * @brief Destroy the BluetoothConnectionStateMachine object
     */
    virtual ~BluetoothConnectionStateMachine();

    ///< Implementation of virtual methods from IBluetoothConnectionState
    virtual void changeState(IBluetoothConnectionStateMachine::ConnectionState newState,
                             BluetoothScreen *screen) override;

    /**
     * @brief Function to handle the state of the bluetooth connection as a state machine
     * 
     * @param connected Indicates if BLE is connected
     */
    void handleState(bool connected);

    /**
     * @brief Indicates if devices are paired and connected
     * 
     * @return true if devices are paired and connected, false if not
     */
    bool isConnected();

private:
    IBluetoothConnectionState *connectionState_;                          ///< State of the bluetooth connection
    BluetoothScreen *screen_;                                             ///< Pointer to bluetooth screen
    IBluetoothConnectionState::ConfigurationParams &configurationParams_; ///< Bluetooth configuration params
};

#endif //BLUETOOTH_CONNECTION_STATE_MACHINE
