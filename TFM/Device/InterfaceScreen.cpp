#include "InterfaceScreen.h"

#include "DeviceLogger.h"

#include "InterfaceAction.h"
#include "WString.h"

InterfaceScreen::~InterfaceScreen()
{
    LOG_DEBUG("InterfaceScreen::~InterfaceScreen()");
    delete[] options_;
}

void InterfaceScreen::drawNewScreen(const String &title, const String options[], uint8_t numberOfOptions,
                                    SelectionCallback selectionCallback)
{
    LOG_DEBUG(String("InterfaceScreen::drawNewScreen() numberOfOptions: ") + String(numberOfOptions));

    // Remove old screen
    if (title_.text != "")
    {
        removeMessage(title_, blackColour);
    }
    for (uint8_t i = 0; i < numberOfOptions_; ++i)
    {
        removeBox(options_[i], blackColour);
    }

    // Update data
    selectedOption_ = 0;
    numberOfOptions_ = numberOfOptions;
    selectionCallback_ = selectionCallback;
    delete[] options_;
    options_ = new Screen::Box[numberOfOptions_];

    // Draw Title text
    const uint8_t titleSize{25};
    title_.text = title;
    title_.yPos = static_cast<uint16_t>(titleSize / 2);
    title_.fontSize = screen_.fontMax();
    drawMessage(title_);

    // Determine options sizes
    const uint16_t xSizeOption{screen_.screenSizeX()};
    const uint16_t ySizeOption{static_cast<uint16_t>((screen_.screenSizeY() - titleSize) / (numberOfOptions_ + 1))};
    const uint16_t spaceBetweenOptions{static_cast<uint16_t>(screen_.screenSizeY() /
                                                             ((numberOfOptions_ + 1) * (numberOfOptions_ + 1) - 1))};

    // Draw each option (retangle and text)
    for (uint8_t i = 0; i < numberOfOptions_; ++i)
    {
        options_[i].xPos = 0;
        options_[i].yPos = titleSize + ySizeOption * i + spaceBetweenOptions * i;
        options_[i].xSize = xSizeOption;
        options_[i].ySize = ySizeOption;
        options_[i].text = options[i];
        drawBox(options_[i]);
    }

    // Select option
    markOption(selectedOption_, true);
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

    // Draw external rectangle
    Screen::Box optionBox;
    optionBox.xPos = options_[option].xPos;
    optionBox.yPos = options_[option].yPos;
    optionBox.xSize = options_[option].xSize;
    optionBox.ySize = options_[option].ySize;
    optionBox.fillBox = false;
    optionBox.colour = selected ? blueColour : cyanColour;
    drawBox(optionBox);

    // Draw second external rectangle
    optionBox.xPos += 1;
    optionBox.yPos += 1;
    optionBox.xSize -= 2;
    optionBox.ySize -= 2;
    drawBox(optionBox);
}
