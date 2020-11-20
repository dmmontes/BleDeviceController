#include "BluetoothConnectionStateConnected.h"

#include "DeviceLogger.h"

#include "Energia.h"
#include "BluetoothConnectionStateMachine.h"

BluetoothConnectionStateConnected::BluetoothConnectionStateConnected(
    IBluetoothConnectionStateMachine *stateMachine, BluetoothScreen *screen,
    IBluetoothConnectionState::ConfigurationParams &configurationParams)
    : IBluetoothConnectionState(stateMachine, screen, configurationParams),
      connectionLost_{false},
      timeToSearch_{0},
      timeToReset_{1000},
      timeToTurnOff_{0},
      connectionOkDuration_{2000}
{
    LOG_DEBUG("BluetoothConnectionStateConnected::BluetoothConnectionStateConnected()");
}

void BluetoothConnectionStateConnected::handleState(bool connected)
{
    LOG_DEBUG(String("BluetoothConnectionStateConnected::handleState() connected: ") + String(connected));

    // Draw connection ok image
    if (timeToTurnOff_ == 0)
    {
        timeToTurnOff_ = millis() + connectionOkDuration_;
        screen_->drawConnectionCorrect();
    }

    // Turn off the screen
    if (timeToTurnOff_ < millis() && screen_)
    {
        delete screen_;
        screen_ = nullptr;
    }

    // Start to search again if connection has been lost during "timeToReset"
    if (connectionLost_)
    {
        if (connected)
        {
            connectionLost_ = false;
        }
        else if (timeToSearch_ < millis())
        {
            LOG_DEBUG("BluetoothConnectionStateConnected::handleState() state changed to Searching");
            timeToTurnOff_ = 0;
            delete screen_;
            screen_ = nullptr;
            stateMachine_->changeState(IBluetoothConnectionStateMachine::ConnectionState::SEARCHING, screen_);
        }
    }
    else if (!connected)
    {
        connectionLost_ = true;
        timeToSearch_ = millis() + timeToReset_;
    }
}

bool BluetoothConnectionStateConnected::isConnected()
{
    LOG_DEBUG("BluetoothConnectionStateConnected::isConnected()");
    return true;
}
