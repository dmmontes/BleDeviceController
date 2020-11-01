
#ifndef INTERFACE_STATE
#define INTERFACE_STATE

#include "IState.h"
#include "Screen.h"

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
    Screen screen_; ///< Screen of the device. Draw in the display a menu of options
};

#endif //INTERFACE_STATE
