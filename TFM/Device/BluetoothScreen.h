#ifndef BLUETOOTH_SCREEN
#define BLUETOOTH_SCREEN

#include "Screen.h"

/**
 * @brief Screen of the device. Draw in the display a menu of options (interface state)
 */
class BluetoothScreen : public Screen
{
public:
    /**
     * @brief Construct a new Bluetooth Screen object 
     */
    BluetoothScreen();

    /**
     * @brief Destroy the Bluetooth Screen object
     */
    ~BluetoothScreen();

    /**
     * @brief Draw a searching message in the title
     */
    void drawSearchingMessage();

    /**
     * @brief Draw pin verification messages
     * 
     * @param pin Pin to pair
     */
    void drawPinVerification(uint32_t pin);

    /**
     * @brief Draw pin verification messages
     */
    void removePinVerification();

    /**
     * @brief Draw an image representing connection correct 
     */
    void drawConnectionCorrect();

private:
    Message title_;                ///< Title message
    uint8_t numberOfPinMessages_;  ///< Number of pin messages
    Screen::Message *pinMessages_; ///< Messages related to pin
};

#endif //BLUETOOTH_SCREEN
