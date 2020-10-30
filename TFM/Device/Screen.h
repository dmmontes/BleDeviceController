#ifndef SCREEN
#define SCREEN

#include <cstdint>

/**
 * @brief Screen of the device. Draw in the display a menu of options
 */
class Screen
{
public:
    enum class ScreenAction : uint8_t
    {
        NONE,  ///< No action
        UP,    ///< Up action
        DOWN,  ///< Down action
        SELECT ///< Select action
    };

    /**
     * @brief  Draw in the display a menu of options
     * 
     * @param action Action done by the user
     */
    void draw(ScreenAction action);
};

#endif //SCREEN
