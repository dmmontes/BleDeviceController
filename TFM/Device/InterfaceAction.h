
#ifndef INTERFACE_ACTION
#define INTERFACE_ACTION

#include "IAction.h"

#include "cstdint"

/**
 * @brief Represents a interface action
 */
class InterfaceAction : public IAction
{
public:
    /**
     * @brief Types of moves to do in the interface
     */
    enum class IntercaceMoves : uint8_t
    {
        NONE = 0,  ///< No action
        UP = 1,    ///< Up action
        DOWN = 2,  ///< Down action
        SELECT = 4 ///< Select action
    };

    ///< Implementation of virtual methods from IAction
    virtual IAction::ActionData getActionData() override;

    /**
     * @brief Action of move up in the interface 
     */
    virtual void moveUp();

    /**
     * @brief Action of move down in the interface 
     */
    virtual void moveDown();

    /**
     * @brief Action of select option in the interface 
     */
    virtual void selectOption();

private:
    int8_t previousMove_{static_cast<uint8_t>(IntercaceMoves::NONE)}; ///< Previous move done
    int8_t actualMove_{static_cast<uint8_t>(IntercaceMoves::NONE)};   ///< Actual move done
};

#endif //INTERFACE_ACTION
