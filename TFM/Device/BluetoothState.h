
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
     * @param context Reference to actual context
     * @param bleController Reference to a Ble controller
     */
    BluetoothState(IContext &context, Ble::IBleController &bleController);

    ///< Implementation of virtual methods from IState
    virtual bool isDetectionEnabled() override;

protected:
    Ble::IBleController &bleController_; ///< Controller of Ble connection
};

#endif //BLUETOOTH_STATE
