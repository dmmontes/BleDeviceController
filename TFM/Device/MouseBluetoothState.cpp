#include "MouseBluetoothState.h"

#include "DeviceLogger.h"
#include "MouseAction.h"

MouseBluetoothState::MouseBluetoothState(IContext &context, Ble::IBleController &bleController) : BluetoothState(context, bleController)
{
    LOG_DEBUG("MouseBluetoothState::MouseBluetoothState()");

    // Add mouse bluetooth detectors
    const size_t numDetectors{3};
    IContext::DetectorType detectors[numDetectors]{IContext::DetectorType::BUTTON, IContext::DetectorType::JOYSTICK, IContext::DetectorType::ACCELEROMETER};
    context_.setDetectors(detectors, numDetectors);
}
