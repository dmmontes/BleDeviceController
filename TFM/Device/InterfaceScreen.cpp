#include "InterfaceScreen.h"

#include "DeviceLogger.h"

#include "InterfaceAction.h"
#include "WString.h"

InterfaceScreen::InterfaceScreen(const String options[], uint8_t numberOfOptions, SelectionCallback selectionCallback)
    : title_{"Choose control mode"},
      titleYSize_{25},
      selectedOption_{0},
      numberOfOptions_{numberOfOptions},
      xSizeOption_{screen_.screenSizeX()},
      ySizeOption_{static_cast<uint16_t>((screen_.screenSizeY() - titleYSize_) / (numberOfOptions_ + 1))},
      options_{new OptionPosition[numberOfOptions_]},
      selectionCallback_{selectionCallback}
{
    LOG_DEBUG(String("InterfaceScreen::InterfaceScreen() numberOfOptions: ") + String(numberOfOptions_));

    // Initialize screen
    screen_.clear(blackColour);
    screen_.setOrientation(0);
    screen_.setPenSolid(true);
    screen_.setFontSize(screen_.fontMax());
    screen_.setFontSolid(false);

    // Draw Title text
    uint16_t xTitleText{static_cast<uint16_t>((xSizeOption_ - screen_.fontSizeX() * title_.length()) / 2)};
    uint16_t yTitleText{static_cast<uint16_t>((titleYSize_ - screen_.fontSizeY()) / 2)};
    screen_.gText(xTitleText, yTitleText, title_, whiteColour);

    // Determine options position and draw them
    const uint16_t spaceBetweenOptions_{static_cast<uint16_t>(screen_.screenSizeY() /
                                                              ((numberOfOptions_ + 1) * (numberOfOptions_ + 1) - 1))};
    for (uint8_t i = 0; i < numberOfOptions_; ++i)
    {
        // Draw rectangle option
        options_[i].xPos = 0;
        options_[i].yPos = titleYSize_ + ySizeOption_ * i + spaceBetweenOptions_ * i;
        screen_.dRectangle(options_[i].xPos, options_[i].yPos, xSizeOption_, ySizeOption_, cyanColour);

        // Draw Insided text
        uint16_t xText{static_cast<uint16_t>((xSizeOption_ - screen_.fontSizeX() * options[i].length()) / 2)};
        uint16_t yText{static_cast<uint16_t>(options_[i].yPos + ((ySizeOption_ - screen_.fontSizeY()) / 2))};
        screen_.gText(xText, yText, options[i], blackColour);
    }

    // Select option
    markOption(selectedOption_, true);
}

InterfaceScreen::~InterfaceScreen()
{
    LOG_DEBUG("InterfaceScreen::~InterfaceScreen()");
    delete[] options_;
}

void InterfaceScreen::draw(int8_t action)
{
    LOG_DEBUG(String("InterfaceScreen::draw() action :") + String(static_cast<int8_t>(action)));

    // Check if action is move up/down
    if ((action & static_cast<int8_t>(InterfaceAction::IntercaceMoves::DOWN)) ==
        static_cast<int8_t>(InterfaceAction::IntercaceMoves::DOWN))
    {
        markOption(selectedOption_, false);
        selectedOption_ = (selectedOption_ + 1) % numberOfOptions_;
        markOption(selectedOption_, true);
    }
    else if ((action & static_cast<int8_t>(InterfaceAction::IntercaceMoves::UP)) ==
             static_cast<int8_t>(InterfaceAction::IntercaceMoves::UP))
    {
        markOption(selectedOption_, false);
        selectedOption_ = (selectedOption_ != 0) ? (selectedOption_ - 1) : (numberOfOptions_ - 1);
        markOption(selectedOption_, true);
    }

    // Check if action is select
    if ((action & static_cast<int8_t>(InterfaceAction::IntercaceMoves::SELECT)) ==
        static_cast<int8_t>(InterfaceAction::IntercaceMoves::SELECT))
    {
        selectionCallback_(selectedOption_);
    }
}

void InterfaceScreen::markOption(uint8_t option, bool selected)
{
    LOG_DEBUG(String("InterfaceScreen::markOption() option: ") + String(option) +
              String(", selected: ") + String(selected));

    screen_.setPenSolid(false);
    const uint16_t colour{selected ? blueColour : cyanColour};

    //Draw 2 not solid rectangles
    screen_.dRectangle(options_[option].xPos, options_[option].yPos, xSizeOption_, ySizeOption_, colour);
    screen_.dRectangle(options_[option].xPos + 1, options_[option].yPos + 1,
                       xSizeOption_ - 2, ySizeOption_ - 2, colour);
}
