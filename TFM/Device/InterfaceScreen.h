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
     * @brief Destroy the Interface Screen object
     */
    ~InterfaceScreen();

    /**
     * @brief Construct a new Interface Screen object
     * 
     * @param title Title of the screen
     * @param options Array of string for each option
     * @param numberOfOptions Number of options
     * @param selectionCallback Callback to be called when an option is selected
     */
    void drawNewScreen(const String &title, const String options[], uint8_t numberOfOptions,
                       SelectionCallback selectionCallback);

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

    Screen::Message title_;         ///< Title of the screen
    uint8_t selectedOption_{0};     ///< Indicates the position of the selected options
    uint8_t numberOfOptions_{0};    ///< Number of options to be displayed
    Screen::Box *options_{nullptr}; ///< Indicates the position of each option

    SelectionCallback selectionCallback_; ///< Callback when an option is selected
};

#endif //INTERFACE_SCREEN
