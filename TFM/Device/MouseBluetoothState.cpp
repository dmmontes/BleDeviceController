#include "MouseBluetoothState.h"

#include "DeviceLogger.h"

MouseBluetoothState::MouseBluetoothState(DeviceContext *deviceContext, Ble::IBleController &bleController) : BluetoothState(deviceContext, bleController)
{
    LOG_DEBUG("MouseBluetoothState::MouseBluetoothState()");
}

void MouseBluetoothState::processAction()
{
    LOG_DEBUG("MouseBluetoothState::processAction()");
}