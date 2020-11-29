
#ifndef GAMEPAD_BLUETOOTH_STATE
#define GAMEPAD_BLUETOOTH_STATE

#include "BluetoothState.h"

/**
 * @brief Represents an state where device are sending data through bluetooth as a HID Gamepad
 */
class GamepadBluetoothState : public BluetoothState
{
public:
    /**
     * @brief Construct a new Gamepad Bluetooth State object
     * 
     * @param context Reference to actual context
     * @param bleController Reference to a Ble controller
     * @param extraSensors Indicates if inlcude extra sensors or not
     */
    GamepadBluetoothState(IContext &context, Ble::IBleController &bleController, bool extraSensors);
};

#endif //GAMEPAD_BLUETOOTH_STATE
