
#ifndef I_ACTION
#define I_ACTION

#include <cstdint>
#include <cstddef>

/**
 * @brief Represents a generic action (interface, mouse, gamepad, etc)
 */
class IAction
{
public:
    /**
     * @brief Representation of actions through data 
     */
    struct ActionData
    {
        int8_t *data;
        size_t dataSize;
    };

    /**
     * @brief Destroy the IAction object
     */
    virtual ~IAction() = default;

    /**
     * @brief General process of the device, detecting actions performed by user 
     */
    virtual ActionData getActionData() = 0;
};

#endif //I_ACTION
