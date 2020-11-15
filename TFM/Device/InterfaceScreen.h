#ifndef INTERFACE_SCREEN
#define INTERFACE_SCREEN

#include "Screen.h"

/**
 * @brief Screen of the device. Draw in the display a menu of options (interface state)
 */
class InterfaceScreen : public Screen
{
public:
    ///< Callback when an option is selected. Parameter is option selected
    typedef void (*SelectionCallback)(uint8_t);

    /**
     * @brief Construct a new Interface Screen object
     * 
     * @param options Array of string for each option
     * @param numberOfOptions Number of options
     * @param selectionCallback Callback to be called when an option is selected
     */
    InterfaceScreen(const String options[], uint8_t numberOfOptions, SelectionCallback selectionCallback);

    /**
     * @brief Destroy the Interface Screen object
     */
    ~InterfaceScreen();

    /**
     * @brief  Draw in the display a menu of options
     * 
     * @param action Action done by the user
     */
    void draw(int8_t action);

private:
    /**
     * @brief Draw a rectangle over selected options and "delete" it over un selected option
     * 
     * @param option Option to be marked
     * @param selected Indicates if option is selected or not
     */
    void markOption(uint8_t option, bool selected);

    const String title_;        ///< Title of the screen
    const uint16_t titleYSize_; ///< Vertical size of the title

    uint8_t selectedOption_;        ///< Indicates the position of the selected options
    const uint8_t numberOfOptions_; ///< Number of options to be displayed
    Screen::Box *options_;          ///< Indicates the position of each option

    SelectionCallback selectionCallback_; ///< Callback when an option is selected
};

#endif //INTERFACE_SCREEN
