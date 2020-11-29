
#ifndef INTERFACE_STATE
#define INTERFACE_STATE

#include "IState.h"
#include "InterfaceScreen.h"

/**
 * @brief Represents an interface state where device shows in a screen an option menu
 */
class InterfaceState : public IState
{
public:
    /**
     * @brief Construct a new Interface State object
     * 
     * @param context Reference to actual context
     */
    InterfaceState(IContext &context);

protected:
    ///< Implementation of virtual methods from IState
    virtual void processAction(const IAction::ActionData &actionData) override;
    virtual bool isDetectionEnabled() override;

private:
    /**
     * @brief Callback to be called whan an option is selected. It changes the state to a new one
     * 
     * @param selectedOption option selected
     */
    void selectedOption(uint8_t selectedOption);

    InterfaceScreen screen_;  ///< Screen of the device. Draw in the display a menu of options
    bool gamepadMode_{false}; ///< Indicates if gamepad mode has been selected
};

#endif //INTERFACE_STATE
