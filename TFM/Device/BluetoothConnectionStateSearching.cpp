#include "BluetoothConnectionStateSearching.h"

#include "DeviceLogger.h"

#include "BluetoothConnectionStateMachine.h"

BluetoothConnectionStateSearching::BluetoothConnectionStateSearching(
    IBluetoothConnectionStateMachine *stateMachine, BluetoothScreen *screen,
    IBluetoothConnectionState::ConfigurationParams &configurationParams)
    : IBluetoothConnectionState(stateMachine, screen, configurationParams),
      connectionLost_{true}
{
    LOG_DEBUG("BluetoothConnectionStateSearching::BluetoothConnectionStateSearching()");
}

void BluetoothConnectionStateSearching::handleState(bool connected)
{
    LOG_DEBUG(String("BluetoothConnectionStateSearching::handleState() connected: ") + String(connected));

    if (!screen_)
    {
        screen_ = new BluetoothScreen();
        screen_->drawSearchingMessage();
        configurationParams_.pinSet = false;
    }
    if (!connected)
    {
        connectionLost_ = false;
    }
    else if (!connectionLost_)
    {
        LOG_DEBUG("BluetoothConnectionStateSearching::handleState() state changed to Connecting");
        stateMachine_->changeState(IBluetoothConnectionStateMachine::ConnectionState::CONNECTING, screen_);
    }
}

bool BluetoothConnectionStateSearching::isConnected()
{
    LOG_DEBUG("BluetoothConnectionStateSearching::isConnected()");
    return false;
}