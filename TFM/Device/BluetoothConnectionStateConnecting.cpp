#include "BluetoothConnectionStateConnecting.h"

#include "DeviceLogger.h"

#include "IBleController.h"
#include "BluetoothConnectionStateMachine.h"

BluetoothConnectionStateConnecting::BluetoothConnectionStateConnecting(
    IBluetoothConnectionStateMachine *stateMachine, BluetoothScreen *screen,
    IBluetoothConnectionState::ConfigurationParams &configurationParams)
    : IBluetoothConnectionState(stateMachine, screen, configurationParams)
{
    LOG_DEBUG("BluetoothConnectionStateConnecting::BluetoothConnectionStateConnecting()");
}

void BluetoothConnectionStateConnecting::handleState(bool connected)
{
    LOG_DEBUG(String("BluetoothConnectionStateConnecting::handleState() connected: ") + String(connected));

    delay(1000); //Wait if pair notification comes
    ble.handleEvents();
    if (configurationParams_.pinSet)
    {
        LOG_DEBUG("BluetoothConnectionStateConnecting::handleState() state changed to Pairing");
        screen_->drawPinVerification(configurationParams_.pin);
        configurationParams_.pairingEnded = false;
        stateMachine_->changeState(IBluetoothConnectionStateMachine::ConnectionState::PAIRING, screen_);
    }
    else
    {
        LOG_DEBUG("BluetoothConnectionStateConnecting::handleState() state changed to Connected");
        stateMachine_->changeState(IBluetoothConnectionStateMachine::ConnectionState::CONNECTED, screen_);
    }
}

bool BluetoothConnectionStateConnecting::isConnected()
{
    LOG_DEBUG("BluetoothConnectionStateConnecting::isConnected()");
    return false;
}
