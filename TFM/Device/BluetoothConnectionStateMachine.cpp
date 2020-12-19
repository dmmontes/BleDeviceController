#include "BluetoothConnectionStateMachine.h"

#include "DeviceLogger.h"

#include "BluetoothConnectionStateConnected.h"
#include "BluetoothConnectionStateConnecting.h"
#include "BluetoothConnectionStatePairing.h"
#include "BluetoothConnectionStateSearching.h"

BluetoothConnectionStateMachine::BluetoothConnectionStateMachine(
    IBluetoothConnectionState::ConfigurationParams &configurationParams, BluetoothScreen *screen)
    : connectionState_{nullptr}, screen_{screen}, configurationParams_{configurationParams}
{
    LOG_DEBUG("BluetoothConnectionStateMachine::BluetoothConnectionStateMachine()");
    changeState(IBluetoothConnectionStateMachine::ConnectionState::SEARCHING, screen_);
}

BluetoothConnectionStateMachine::~BluetoothConnectionStateMachine()
{
    LOG_DEBUG("BluetoothConnectionStateMachine::BluetoothConnectionStateMachine()");
    delete screen_;
    delete connectionState_;
}

void BluetoothConnectionStateMachine::changeState(IBluetoothConnectionStateMachine::ConnectionState newState,
                                                  BluetoothScreen *screen)
{
    LOG_DEBUG(String("BluetoothConnectionStateMachine::changeState() newState: ") +
              String(static_cast<uint8_t>(newState)));

    screen_ = screen;
    delete connectionState_;

    switch (newState)
    {
    case IBluetoothConnectionStateMachine::ConnectionState::SEARCHING:
        connectionState_ = new BluetoothConnectionStateSearching(this, screen, configurationParams_);
        break;
    case IBluetoothConnectionStateMachine::ConnectionState::CONNECTING:
        connectionState_ = new BluetoothConnectionStateConnecting(this, screen, configurationParams_);
        break;
    case IBluetoothConnectionStateMachine::ConnectionState::PAIRING:
        connectionState_ = new BluetoothConnectionStatePairing(this, screen, configurationParams_);
        break;
    case IBluetoothConnectionStateMachine::ConnectionState::CONNECTED:
        connectionState_ = new BluetoothConnectionStateConnected(this, screen, configurationParams_);
        break;
    default:
        LOG_DEBUG("BluetoothConnectionStateMachine::changeState() Unrecognized state");
        break;
    }
}

void BluetoothConnectionStateMachine::handleState(bool connected)
{
    LOG_DEBUG(String("BluetoothConnectionStateMachine::handleState() connected: ") + String(connected));
    connectionState_->handleState(connected);
}

bool BluetoothConnectionStateMachine::isConnected()
{
    LOG_DEBUG("BluetoothConnectionStateMachine::isConnected()");
    return connectionState_->isConnected();
}
