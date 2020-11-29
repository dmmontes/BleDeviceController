#include "Screen.h"

#include "DeviceLogger.h"

Screen::Screen()
    : resetPin_{17},
      dataCommandPin_{31},
      chipSelectPin_{13},
      backlightPin_{39},
      screen_{resetPin_, dataCommandPin_, chipSelectPin_, backlightPin_}
{
    LOG_DEBUG("Screen::Screen()");

    screen_.begin();
    screen_.clear(blackColour);
    screen_.setOrientation(0);
};

Screen::~Screen()
{
    LOG_DEBUG("Screen::~Screen()");

    screen_.clear(blackColour);
    screen_.setDisplay(false);
    screen_.setBacklight(false);
};

void Screen::drawMessage(const Message &message)
{
    LOG_DEBUG(String("Screen::drawMessage() message: ") + message.text);

    screen_.setFontSize(message.fontSize);
    screen_.setFontSolid(message.fontSolid);

    uint16_t xPos{static_cast<uint16_t>((screen_.screenSizeX() - screen_.fontSizeX() * message.text.length()) / 2)};
    uint16_t yPos{static_cast<uint16_t>(message.yPos - screen_.fontSizeY() / 2)};
    screen_.gText(xPos, yPos, message.text, message.colour);
}

void Screen::removeMessage(const Message &message, uint16_t colour)
{
    LOG_DEBUG(String("Screen::removeMessage() message: ") + message.text);

    // Calculates the position of the message
    uint16_t xPos{static_cast<uint16_t>((screen_.screenSizeX() - screen_.fontSizeX() * message.text.length()) / 2)};
    uint16_t yPos{static_cast<uint16_t>(message.yPos - screen_.fontSizeY() / 2)};

    // Fill it with a colour rectangle
    screen_.setPenSolid(true);
    screen_.dRectangle(xPos, yPos, screen_.fontSizeX() * message.text.length(), screen_.fontSizeY(), colour);
}

void Screen::drawBox(const Box &box)
{
    LOG_DEBUG("Screen::drawBox()");

    screen_.setPenSolid(box.fillBox);
    screen_.dRectangle(box.xPos, box.yPos, box.xSize, box.ySize, box.colour);

    if (box.text.length() != 0)
    {
        Message message;
        message.text = box.text;
        message.yPos = box.yPos + box.ySize / 2;
        message.fontSize = screen_.fontMax();
        message.fontSolid = false;
        message.colour = box.textColour;
        drawMessage(message);
    }
}

void Screen::removeBox(const Box &box, uint16_t colour)
{
    LOG_DEBUG("Screen::removeBox()");

    // Fill it with a colour rectangle
    screen_.setPenSolid(true);
    screen_.dRectangle(box.xPos, box.yPos, box.xSize, box.ySize, colour);
}

void Screen::drawImage(const Image &image)
{
    LOG_DEBUG("Screen::drawImage()");

    for (uint16_t i = 0; i < image.xSize; ++i)
    {
        for (uint16_t j = 0; j < image.ySize; ++j)
        {
            const uint16_t imageXPos{static_cast<uint16_t>(image.xPos + i)};
            const uint16_t imageYPos{static_cast<uint16_t>(image.yPos + j)};
            if ((imageXPos < screen_.screenSizeX()) && (imageYPos < screen_.screenSizeY()))
            {
                uint16_t index = j * image.xSize + i;
                const uint16_t colour = image.picture[index];
                screen_.point(imageXPos, imageYPos, colour);
            }
        }
    }
}
