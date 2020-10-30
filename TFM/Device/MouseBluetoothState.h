
#ifndef MOUSE_BLUETOOTH_STATE
#define MOUSE_BLUETOOTH_STATE

#include "BluetoothState.h"

/**
 * @brief Represents an state where device are sending data through bluetooth as a HID Mouse
 */
class MouseBluetoothState : public BluetoothState
{
public:
    /**
     * @brief Construct a new Mouse Bluetooth State object
     * 
     * @param bleController Reference to a Ble controller
     * @param deviceContext Pointer to actual context
     */
    MouseBluetoothState(DeviceContext *deviceContext, Ble::IBleController &bleController);

    ///< Implementation of virtual methods from IState
    virtual void processAction() override;
};

#endif //MOUSE_BLUETOOTH_STATE
