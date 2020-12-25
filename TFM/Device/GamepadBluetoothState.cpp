#include "GamepadBluetoothState.h"

#include "DeviceLogger.h"
#include "GamepadAction.h"

GamepadBluetoothState::GamepadBluetoothState(IContext &context, Ble::IBleController &bleController, bool extraSensors)
    : BluetoothState(context, bleController)
{
    LOG_DEBUG("GamepadBluetoothState::GamepadBluetoothState()");

    // Add gamepad bluetooth detectors
    if (extraSensors)
    {
        const size_t numDetectors{6};
        IContext::DetectorType detectors[numDetectors]{IContext::DetectorType::BUTTON, IContext::DetectorType::JOYSTICK, IContext::DetectorType::ACCELEROMETER, IContext::DetectorType::ACCEL_GYRO, IContext::DetectorType::FSR, IContext::DetectorType::VOICE};
        context_.setDetectors(detectors, numDetectors);
    }
    else
    {
        const size_t numDetectors{2};
        IContext::DetectorType detectors[numDetectors]{IContext::DetectorType::BUTTON, IContext::DetectorType::JOYSTICK};
        context_.setDetectors(detectors, numDetectors);
    }
}
