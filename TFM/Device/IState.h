
#ifndef I_STATE
#define I_STATE

#include "DeviceContext.h"

/**
 * @brief Represents a state of the device. 
 */
class IState
{
public:
    /**
     * @brief Construct a new IState object
     * 
     * @param deviceContext Pointer to actual context
     */
    IState(DeviceContext *deviceContext);

    /**
     * @brief General process of the device, detecting actions performed by user 
     */
    void detectAction();

protected:
    /**
     * @brief Process an action detected 
     */
    virtual void processAction() = 0;

    DeviceContext *deviceContext_; ///< Pointer to device's context
};

#endif //I_STATE
