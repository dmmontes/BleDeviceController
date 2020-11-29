#include "InterfaceState.h"

#include "DeviceLogger.h"

#include "WString.h"

const uint8_t UNKNOWN_OPTION{255};       ///< Represents an unknown option
uint8_t SELECTED_OPTION{UNKNOWN_OPTION}; ///< Selected Option
const uint8_t NUMBER_OF_OPTIONS{2};      ///< Number of options
///< Option's messages
const String CONTROL_MODE_TITLE{"Choose control mode"};
const String CONTROL_MODE_OPTIONS[NUMBER_OF_OPTIONS]{String("Mouse Controller"), String("Gamepad Controller")};
const String GAMEPAD_MODE_TITLE{"Use extra sensors?"};
const String GAMEPAD_MODE_OPTIONS[NUMBER_OF_OPTIONS]{String("Yes"), String("No")};

void callbackSelectedOption(uint8_t selectedOption)
{
    LOG_DEBUG("InterfaceState::callbackSelectedOption()");
    SELECTED_OPTION = selectedOption;
}

InterfaceState::InterfaceState(IContext &context)
    : IState(context)
{
    LOG_DEBUG("InterfaceState::InterfaceState()");

    // Draw initial screen
    screen_.drawNewScreen(CONTROL_MODE_TITLE, CONTROL_MODE_OPTIONS, NUMBER_OF_OPTIONS, &callbackSelectedOption);

    // Add interface detectors
    const size_t numDetectors{2};
    IContext::DetectorType detectors[numDetectors]{IContext::DetectorType::BUTTON, IContext::DetectorType::JOYSTICK};
    context_.setDetectors(detectors, numDetectors);
}

void InterfaceState::processAction(const IAction::ActionData &actionData)
{
    LOG_DEBUG("InterfaceState::processAction()");

    screen_.draw(*actionData.data);
    if (SELECTED_OPTION != UNKNOWN_OPTION)
    {
        selectedOption(SELECTED_OPTION);
        SELECTED_OPTION = UNKNOWN_OPTION;
    }
}

bool InterfaceState::isDetectionEnabled()
{
    LOG_DEBUG("InterfaceState::isDetectionEnabled()");
    return true;
}

void InterfaceState::selectedOption(uint8_t selectedOption)
{
    LOG_DEBUG(String("InterfaceState::selectedOption(), selectedOption: ") + String(selectedOption));

    switch (selectedOption)
    {
    case 0:
        if (!gamepadMode_)
        {
            context_.changeState(IContext::StateType::MOUSE);
        }
        else
        {
            context_.changeState(IContext::StateType::GAMEPAD, true);
        }
        break;
    case 1:
        if (!gamepadMode_)
        {
            // Draw gamepads screen
            screen_.drawNewScreen(GAMEPAD_MODE_TITLE, GAMEPAD_MODE_OPTIONS, NUMBER_OF_OPTIONS, &callbackSelectedOption);
            gamepadMode_ = true;
        }
        else
        {
            context_.changeState(IContext::StateType::GAMEPAD, false);
        }

        break;
    default:
        LOG_WARNING("InterfaceState::selectedOption(), Unknown option");
        break;
    }
}
