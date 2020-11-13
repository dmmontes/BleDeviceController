#ifndef SCREEN
#define SCREEN

#include "Screen_HX8353E.h"

/**
 * @brief Screen of the device
 */
class Screen
{
protected:
    /**
     * @brief Construct a new Screen object 
     */
    Screen();

    /**
     * @brief Destroy the Screen object 
     */
    ~Screen();

    const uint8_t resetPin_;       ///< Pin used for reset action
    const uint8_t dataCommandPin_; ///< Pin used for data command
    const uint8_t chipSelectPin_;  ///< Pin used for chip select
    const uint8_t backlightPin_;   ///< Pin used for backlight
    Screen_HX8353E screen_;        ///< Screen to be used
};

#endif //SCREEN
