#include "BluetoothConnectionStateSearching.h"

#include "DeviceLogger.h"

#include "BluetoothConnectionStateMachine.h"
#include "Energia.h"

BluetoothConnectionStateSearching::BluetoothConnectionStateSearching(
    IBluetoothConnectionStateMachine *stateMachine, BluetoothScreen *screen,
    IBluetoothConnectionState::ConfigurationParams &configurationParams)
    : IBluetoothConnectionState(stateMachine, screen, configurationParams),
      connectionLost_{true},
      searchingLed_{37},
      timeToBlink_{0},
      blinkDuration_{5000}
{
    LOG_DEBUG("BluetoothConnectionStateSearching::BluetoothConnectionStateSearching()");
    pinMode(searchingLed_, OUTPUT);
}

void BluetoothConnectionStateSearching::handleState(bool connected)
{
    LOG_DEBUG(String("BluetoothConnectionStateSearching::handleState() connected: ") + String(connected));
    blink();

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
        analogWrite(searchingLed_, 0);
        stateMachine_->changeState(IBluetoothConnectionStateMachine::ConnectionState::CONNECTING, screen_);
    }
}

bool BluetoothConnectionStateSearching::isConnected()
{
    LOG_DEBUG("BluetoothConnectionStateSearching::isConnected()");
    return false;
}

void BluetoothConnectionStateSearching::blink()
{
    LOG_DEBUG("BluetoothConnectionStateSearching::blink()");

    // Calculate the blinking time
    unsigned long actualTime{millis()};
    if (timeToBlink_ < actualTime)
    {
        timeToBlink_ = actualTime + blinkDuration_;
    }

    // Calculate the blink value from its position in its range duration
    long blinkPosition{static_cast<long>(timeToBlink_ - actualTime - blinkDuration_ / 2)};
    uint8_t brightness{static_cast<uint8_t>(map(abs(blinkPosition), 0, blinkDuration_ / 2, 0, 25))};
    analogWrite(searchingLed_, brightness);
}
