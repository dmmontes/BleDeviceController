
#ifndef GAMEPAD_ACTION
#define GAMEPAD_ACTION

#include "IAction.h"
#include "WString.h"

/**
 * @brief Represents a Gamepad action
 */
class GamepadAction : public IAction
{
public:
    /**
     * @brief Type of Gamepad keys
     */
    enum class Key : uint8_t
    {
        A = 0x04,       ///< Represents key "A"
        C = 0x06,       ///< Represents key "C"
        D = 0x07,       ///< Represents key "D"
        S = 0x16,       ///< Represents key "S"
        W = 0x1a,       ///< Represents key "W"
        SPACE = 0x2C,   ///< Represents key "SPACE"
        UP = 0x52,      ///< Represents key "UP"
        DOWN = 0x51,    ///< Represents key "DOWN"
        RIGHT = 0x4F,   ///< Represents key "RIGHT"
        LEFT = 0x50,    ///< Represents key "LEFT"
        NUMBER1 = 0x1e, ///< Represents key "1"
        NUMBER2 = 0x1f, ///< Represents key "2"
        NUMBER3 = 0x20  ///< Represents key    "3"
    };

    ///< Implementation of virtual methods from IAction
    virtual IAction::ActionData getActionData() override;

    /**
     * @brief Add press key information to the action
     * 
     * @param key Key pressed
     * @param detectorId Id of the detector
     * @return true if action is success, false otherwise
     */
    bool pressKey(Key key, uint8_t detectorId);

    /**
     * @brief Add left click information to the action
     * 
     * @param pressed Key released
     * @param detectorId Id of the detector
     * @return true if action is success, false otherwise
     */
    bool releaseKey(Key key, uint8_t detectorId);

    /**
     * @brief Indicates if a key is pressed or not
     * 
     * @param key Key pressed
     * @param return if key is pressed
     */
    bool isKeypressed(Key key);

private:
    /**
     * @brief Translate the key into a string
     * 
     * @param key key to be translated
     * @return String String representing the key
     */
    String translateKey(Key key);

    int8_t previousGamepadAction_[8]{0, 0, 0, 0, 0, 0, 0, 0}; ///< Data representation of the previous Gamepad action
    int8_t gamepadAction_[8]{0, 0, 0, 0, 0, 0, 0, 0};         ///< Data representation of a Gamepad action
    uint8_t keyOwners_[8]{0, 0, 0, 0, 0, 0, 0, 0};            ///< Owners (detector Id) of the key pressed
};

#endif //GAMEPAD_ACTION
