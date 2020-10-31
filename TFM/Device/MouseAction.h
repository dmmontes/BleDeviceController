
#ifndef MOUSE_ACTION
#define MOUSE_ACTION

#include "IAction.h"

/**
 * @brief Represents a mouse action
 */
class MouseAction : public IAction
{
public:
    ///< Implementation of virtual methods from IAction
    virtual IAction::ActionData getActionData() override;

    /**
     * @brief Add rigth click information to the action
     * 
     * @param pressed True if click is pressed, false if it is released
     */
    void rightClick(bool pressed);

    /**
     * @brief Add left click information to the action
     * 
     * @param pressed True if click is pressed, false if it is released
     */
    void leftClick(bool pressed);

    /**
     * @brief Add middle click information to the action
     * 
     * @param pressed True if click is pressed, false if it is released
     */
    void middleClick(bool pressed);

    /**
     * @brief Move cursor's position in X/Y axis
     * 
     * @param moveX units to move in X axis
     * @param moveY units to move in Y axis
     */
    void moveCursor(int8_t moveX, int8_t moveY);

private:
    /**
     * @brief Type of mouse click
     */
    enum class MouseClick : uint8_t
    {
        RELEASED = 0,
        LEFT = 1,
        RIGHT = 2,
        MIDDLE = 4,
        BACK = 8,
        FORWARD = 16,
        ALL = 31
    };

    int8_t mouseAction[5]; ///< Data representation of a mouse action
};

#endif //MOUSE_ACTION
