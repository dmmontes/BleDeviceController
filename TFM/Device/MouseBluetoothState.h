
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
     * @param context Reference to actual context
     * @param bleController Reference to a Ble controller
     */
    MouseBluetoothState(IContext &context, Ble::IBleController &bleController);
};

#endif //MOUSE_BLUETOOTH_STATE
