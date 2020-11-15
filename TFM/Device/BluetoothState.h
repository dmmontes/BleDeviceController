
#ifndef BLUETOOTH_STATE
#define BLUETOOTH_STATE

#include <cstdint>

#include "IBleController.h"
#include "BluetoothConnectionStateMachine.h"
#include "IState.h"

/**
 * @brief Represents an state where device are sending data through bluetooth
 */
class BluetoothState : public IState
{
public:
    /**
     * @brief Construct a new Bluetooth State object
     * 
     * @param context Reference to actual context
     * @param bleController Reference to a Ble controller
     */
    BluetoothState(IContext &context, Ble::IBleController &bleController);

    /**
     * @brief Destroy the Bluetooth State object
     */
    ~BluetoothState();

    ///< Implementation of virtual methods from IState
    virtual bool isDetectionEnabled() override;

protected:
    Ble::IBleController &bleController_; ///< Controller of Ble connection

private:
    BluetoothConnectionStateMachine bluetoothConnectionStateMachine_; ///< State machine of bluetooth connection
};

#endif //BLUETOOTH_STATE
