#include "BluetoothConnectionStatePairing.h"

#include "DeviceLogger.h"

#include "BluetoothConnectionStateMachine.h"

BluetoothConnectionStatePairing::BluetoothConnectionStatePairing(
    IBluetoothConnectionStateMachine *stateMachine, BluetoothScreen *screen,
    IBluetoothConnectionState::ConfigurationParams &configurationParams)
    : IBluetoothConnectionState(stateMachine, screen, configurationParams)
{
    LOG_DEBUG("BluetoothConnectionStatePairing::BluetoothConnectionStatePairing()");
}

void BluetoothConnectionStatePairing::handleState(bool connected)
{
    LOG_DEBUG(String("BluetoothConnectionStatePairing::handleState() connected: ") + String(connected));

    if (configurationParams_.pairingEnded)
    {
        LOG_DEBUG(String("BluetoothConnectionStatePairing::handleState() state changed to: ") +
                  String(configurationParams_.pairedDevices ? "Connected" : "Searching"));

        configurationParams_.pinSet = false;
        screen_->removePinVerification();
        if (configurationParams_.pairedDevices)
        {
            stateMachine_->changeState(IBluetoothConnectionStateMachine::ConnectionState::CONNECTED, screen_);
        }
        else
        {
            stateMachine_->changeState(IBluetoothConnectionStateMachine::ConnectionState::SEARCHING, screen_);
        }
    }
}

bool BluetoothConnectionStatePairing::isConnected()
{
    LOG_DEBUG("BluetoothConnectionStatePairing::isConnected()");
    return false;
}
