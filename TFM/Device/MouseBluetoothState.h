
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
     * @param action Reference to action to be done
     * @param bleController Reference to a Ble controller
     */
    MouseBluetoothState(IContext &context, IAction &action, Ble::IBleController &bleController);

    ///< Implementation of virtual methods from IState
    virtual void processAction(const IAction::ActionData &actionData) override;
};

#endif //MOUSE_BLUETOOTH_STATE
