#include "DeviceContext.h"

#include "DeviceLogger.h"

#include "InterfaceState.h"
#include "MouseBluetoothState.h"

DeviceContext::DeviceContext(Ble::BleControllerFactory &bleControllerFactory) : bleControllerFactory_(bleControllerFactory)
{
    LOG_DEBUG("DeviceContext::DeviceContext()");
    changeState(DeviceContext::StateType::INTERFACE);
}

DeviceContext::~DeviceContext()
{
    LOG_DEBUG("DeviceContext::~DeviceContext()");
    cleanup();
}

void DeviceContext::detectAction()
{
    LOG_DEBUG("DeviceContext::detectAction()");
    state_->detectAction();
}

void DeviceContext::changeState(StateType newState)
{
    LOG_DEBUG("DeviceContext::changeState()");
    cleanup();

    // Create the new state
    switch (newState)
    {
    case DeviceContext::StateType::INTERFACE:
        state_ = new InterfaceState(this);
        break;
    case DeviceContext::StateType::MOUSE:
        bleController_ = bleControllerFactory_.createBleController(Ble::BleControllerFactory::BleType::MOUSE, "Mouse Controller", true);
        state_ = new MouseBluetoothState(this, *bleController_);
        break;

    default:
        LOG_WARNING("DeviceContext::changeState() Unknown state");
        break;
    }
}

void DeviceContext::cleanup()
{
    LOG_DEBUG("DeviceContext::cleanup()");

    // Delete ble controller
    bleControllerFactory_.deleteBleController(bleController_);
    bleController_ = nullptr;

    // Delete state
    delete state_;
    state_ = nullptr;
}
