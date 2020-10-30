
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
     * @param deviceContext Pointer to actual context
     */
    InterfaceState(DeviceContext *deviceContext);

protected:
    ///< Implementation of virtual methods from IState
    virtual void processAction() override;

private:
    Screen screen_; ///< Screen of the device. Draw in the display a menu of options
};

#endif //INTERFACE_STATE
