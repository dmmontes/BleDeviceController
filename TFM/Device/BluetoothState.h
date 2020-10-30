
#ifndef BLUETOOTH_STATE
#define BLUETOOTH_STATE

#include "IState.h"
#include "IBleController.h"

/**
 * @brief Represents an state where device are sending data through bluetooth
 */
class BluetoothState : public IState
{
public:
    /**
     * @brief Construct a new Bluetooth State object
     * 
     * @param bleController Reference to a Ble controller
     * @param deviceContext Pointer to actual context
     */
    BluetoothState(DeviceContext *deviceContext, Ble::IBleController &bleController) : IState(deviceContext), bleController_(bleController) {}

protected:
    Ble::IBleController &bleController_; ///< Controller of Ble connection
};

#endif //BLUETOOTH_STATE
