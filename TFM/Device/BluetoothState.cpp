#include "BluetoothState.h"

#include "DeviceLogger.h"

BluetoothState::BluetoothState(IContext &context, Ble::IBleController &bleController) : IState(context), bleController_(bleController)
{
    LOG_DEBUG("BluetoothState::BluetoothState()");
}

bool BluetoothState::isDetectionEnabled()
{
    LOG_DEBUG("BluetoothState::isDetectionEnabled()");
    ble.handleEvents();
    return ble.isConnected();
}
