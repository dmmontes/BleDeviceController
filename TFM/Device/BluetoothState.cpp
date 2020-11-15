#include "BluetoothState.h"

#include "DeviceLogger.h"

IBluetoothConnectionState::ConfigurationParams BLUETOOTH_CONFIGURATION_PARAMS;

/**
 * @brief Do-Nothing. Callback to get text to be displayed when pairing devices
 */
void setPinText(const char[]) {}

/**
 * @brief Callback to get the pin to verify pairing devices
 * 
 * @param pin Pin number to verify pairing devices
 */
void setPin(uint32_t pin)
{
    LOG_DEBUG(String("BluetoothState::setPin() pin: ") + String(pin));
    BLUETOOTH_CONFIGURATION_PARAMS.pin = pin;
    BLUETOOTH_CONFIGURATION_PARAMS.pinSet = true;
}

/**
 * @brief Set the pairing result of devices
 * 
 * @param connected Indicates if devices are paired or not
 */
void setPairingResult(bool paired)
{
    LOG_DEBUG(String("BluetoothState::setPairingResult() paired: ") + String(paired));
    BLUETOOTH_CONFIGURATION_PARAMS.pairingEnded = true;
    BLUETOOTH_CONFIGURATION_PARAMS.pairedDevices = paired;
}

BluetoothState::BluetoothState(IContext &context, Ble::IBleController &bleController)
    : IState{context},
      bleController_{bleController},
      bluetoothConnectionStateMachine_{BLUETOOTH_CONFIGURATION_PARAMS}
{
    LOG_DEBUG("BluetoothState::BluetoothState()");
    bleController_.setPinCallbacksParameters(&setPinText, &setPin, &setPairingResult, 33, 32);
}

BluetoothState::~BluetoothState()
{
    LOG_DEBUG("BluetoothState::~BluetoothState()");
}

bool BluetoothState::isDetectionEnabled()
{
    LOG_DEBUG("BluetoothState::isDetectionEnabled()");
    ble.handleEvents();
    bool connected{ble.isConnected()};
    bluetoothConnectionStateMachine_.handleState(connected);
    return connected && bluetoothConnectionStateMachine_.isConnected();
}
