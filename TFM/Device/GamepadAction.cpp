#include "GamepadAction.h"

#include "DeviceLogger.h"

IAction::ActionData GamepadAction::getActionData()
{
    LOG_DEBUG("GamepadAction::getActionData()");

    // Send detected action
    memcpy(previousGamepadAction_, gamepadAction_, sizeof(gamepadAction_));
    return IAction::ActionData{previousGamepadAction_, sizeof(previousGamepadAction_)};
}

bool GamepadAction::pressKey(Key key, uint8_t detectorId)
{
    LOG_DEBUG("GamepadAction::pressKey() key: " + translateKey(key));
    bool success{false};

    // Check that there is a free position in the data and key was not pressed
    size_t freePos{sizeof(gamepadAction_)};
    int8_t pressedKey{static_cast<int8_t>(key)};
    for (size_t i = 0; i < sizeof(gamepadAction_); ++i)
    {
        if (gamepadAction_[i] == pressedKey)
        {
            LOG_DEBUG("Key was pressed");
            return success;
        }
        else if (gamepadAction_[i] == 0x00)
        {
            freePos = i;
            success = true;
        }
    }

    // If free pos found, writes the key
    if (freePos < sizeof(gamepadAction_))
    {
        gamepadAction_[freePos] = pressedKey;
        keyOwners_[freePos] = detectorId;
    }
    return success;
}

bool GamepadAction::releaseKey(Key key, uint8_t detectorId)
{
    LOG_DEBUG("GamepadAction::releaseKey() key: " + translateKey(key));
    bool success{false};

    // Remove if key is pressed in the data
    int8_t releasedKey{static_cast<int8_t>(key)};
    for (size_t i = 0; i < sizeof(gamepadAction_); ++i)
    {
        if (gamepadAction_[i] == releasedKey && keyOwners_[i] == detectorId)
        {
            gamepadAction_[i] = 0x00;
            keyOwners_[i] = 0x00;
            success = true;
        }
    }
    return success;
}

bool GamepadAction::isKeypressed(Key key)
{
    LOG_DEBUG("GamepadAction::isKeypressed() key: " + translateKey(key));

    // Search if key is pressed in the data
    int8_t searchedKey{static_cast<int8_t>(key)};
    for (size_t i = 0; i < sizeof(gamepadAction_); ++i)
    {
        if (gamepadAction_[i] == searchedKey)
        {
            return true;
        }
    }
    return false;
}

String GamepadAction::translateKey(Key key)
{
    LOG_DEBUG("GamepadAction::translateKey()");
    switch (key)
    {
    case GamepadAction::Key::A:
        return "A";
    case GamepadAction::Key::C:
        return "C";
    case GamepadAction::Key::D:
        return "D";
    case GamepadAction::Key::P:
        return "P";
    case GamepadAction::Key::S:
        return "S";
    case GamepadAction::Key::W:
        return "W";
    case GamepadAction::Key::SPACE:
        return "SPACE";
    case GamepadAction::Key::UP:
        return "UP";
    case GamepadAction::Key::DOWN:
        return "DOWN";
    case GamepadAction::Key::RIGHT:
        return "RIGHT";
    case GamepadAction::Key::LEFT:
        return "LEFT";
    case GamepadAction::Key::NUMBER1:
        return "NUMBER1";
    case GamepadAction::Key::NUMBER2:
        return "NUMBER2";
    case GamepadAction::Key::NUMBER3:
        return "NUMBER3";
    default:
        break;
    }
    LOG_WARNING("GamepadAction::translateKey() Undefined key");
    return String{};
}
