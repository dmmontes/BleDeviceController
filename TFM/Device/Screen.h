#ifndef SCREEN
#define SCREEN

#include "Screen_HX8353E.h"

#include "WString.h"

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

    /**
     * @brief Indicates the message to be displayed and its upper left corner position 
     */
    struct Message
    {
        String text{""};              ///< Text to be displayed
        uint16_t yPos{0};             ///< Upper-Left corner of the Message. Position in Y axis
        uint8_t fontSize{0};          ///< Size of the font
        bool fontSolid{false};        ///< Indicates if fonf is solid or not
        uint16_t colour{whiteColour}; ///< Colour of the message
    };

    /**
     * @brief Box to be drawn with optinal message 
     */
    struct Box
    {
        uint16_t xPos{0};                 ///< Upper-Left corner of the box. Position in X axis
        uint16_t yPos{0};                 ///< Upper-Left corner of the box. Position in Y axis
        uint16_t xSize{0};                ///< Horizontal size
        uint16_t ySize{0};                ///< Vertical size
        uint16_t colour{cyanColour};      ///< Colour of the box
        bool fillBox{true};               ///< Indicates if box should be filled or not
        String text{""};                  ///< Optional text to be displayed in the center
        uint16_t textColour{blackColour}; ///< Colour of the box
    };

    /**
     * @brief Box to be drawn with optinal message 
     */
    struct Image
    {
        uint16_t xPos{0};  ///< Upper-Left corner of the box. Position in X axis
        uint16_t yPos{0};  ///< Upper-Left corner of the box. Position in Y axis
        uint16_t xSize{0}; ///< Horizontal size
        uint16_t ySize{0}; ///< Vertical size
        uint16_t *picture; ///< Pointer to picture data
    };

    /**
     * @brief Draw a Message in the screen
     * 
     * @param message Message to be drawn
     */
    void drawMessage(const Message &message);

    /**
     * @brief Remove a message with a colour rectangle
     * 
     * @param message Message to be removed
     * @param colour Colour of the rectangle
     */
    void removeMessage(const Message &message, uint16_t colour);

    /**
     * @brief Draw a Box in the screen
     * 
     * @param box Box to be drawn
     */
    void drawBox(const Box &box);

    /**
     * @brief Draw an image in the screen
     * 
     * @param image Image to be drawn
     */
    void drawImage(const Image &image);

    const uint8_t resetPin_;       ///< Pin used for reset action
    const uint8_t dataCommandPin_; ///< Pin used for data command
    const uint8_t chipSelectPin_;  ///< Pin used for chip select
    const uint8_t backlightPin_;   ///< Pin used for backlight
    Screen_HX8353E screen_;        ///< Screen to be used
};

#endif //SCREEN
