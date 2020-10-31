
#ifndef INTERFACE_ACTION
#define INTERFACE_ACTION

#include "IAction.h"

/**
 * @brief Represents a interface action
 */
class InterfaceAction : public IAction
{
public:
    ///< Implementation of virtual methods from IAction
    virtual IAction::ActionData getActionData() override;
};

#endif //INTERFACE_ACTION
