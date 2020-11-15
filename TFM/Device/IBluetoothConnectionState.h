
#ifndef I_BLUETOOTH_CONNECTION_STATE
#define I_BLUETOOTH_CONNECTION_STATE

#include "BluetoothScreen.h"

class IBluetoothConnectionStateMachine;

/**
 * @brief Represents the state of a bluetooth connection
 */
class IBluetoothConnectionState
{
public:
    /**
     * @brief Parameters to configure a bluetooth connection 
     */
    struct ConfigurationParams
    {
        bool pinSet{false};       ///< Indicates if pin is set for pairing
        uint32_t pin{0};          ///< Pin for pairing devices
        bool pairingEnded{false}; ///< Indicates if pairing has ended
        bool pairedDevices{true}; ///< Indicates if devices are paired
    };

    /**
     * @brief Construct a new IBluetoothConnectionState object
     * 
     * @param stateMachine Bluetooth connection state machine
     * @param screen Screen to represents the state connection
     * @param configurationParams Parameters to configure a bluetooth connection 
     */
    IBluetoothConnectionState(IBluetoothConnectionStateMachine *stateMachine, BluetoothScreen *screen,
                              ConfigurationParams &configurationParams)
        : stateMachine_{stateMachine}, screen_{screen}, configurationParams_(configurationParams) {}

    /**
     * @brief Destroy the IBluetoothConnectionState object
     */
    virtual ~IBluetoothConnectionState() = default;

    /**
     * @brief Function to handle the state of the bluetooth connection as a state machine
     * 
     * @param connected Indicates if BLE is connected
     */
    virtual void handleState(bool connected) = 0;

    /**
     * @brief Indicates if devices are paired and connected
     * 
     * @return true if devices are paired and connected, false if not
     */
    virtual bool isConnected() = 0;

protected:
    IBluetoothConnectionStateMachine *stateMachine_; ///< Bluetooth connection state machine
    BluetoothScreen *screen_;                        ///< Screen to display state information
    ConfigurationParams &configurationParams_;       ///< Parameters to configure a bluetooth connection
};

#endif //I_BLUETOOTH_CONNECTION_STATE
