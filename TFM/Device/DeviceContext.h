
#ifndef DEVICE_CONTEXT
#define DEVICE_CONTEXT

#include <cstdint>

#include "BleControllerFactory.h"

class IState;

/**
 * @brief Represents the context of the device. It manages its states and process actions performed by user
 */
class DeviceContext
{
public:
    /**
     * @brief Type of Detector
     */
    enum class DetectorType : uint8_t
    {
        BUTTON,       ///< Buton Detector
        JOYSTICK,     ///< Joystick Detector
        ACCELEROMETER ///< Accelerometer Detector
    };

    /**
     * @brief Type of devices's states
     */
    enum class StateType : uint8_t
    {
        INTERFACE, ///< Showing initial interface
        MOUSE      ///< Ble mouse mode
    };

    /**
     * @brief Construct a new Device Context object 
     * 
     * @param bleControllerFactory Reference to a factory of Ble controllers
     */
    DeviceContext(Ble::BleControllerFactory &bleControllerFactory);

    /**
     * @brief Destroy the Device Context object 
     */
    ~DeviceContext();

    /**
     * @brief General process of the device, detecting actions performed by user 
     */
    void detectAction();

    /**
     * @brief Change the state of the device to a new one
     * 
     * @param newState New state of the device
     */
    void changeState(StateType newState);

private:
    /**
     * @brief Free allocated memory and reset attributes 
     */
    void cleanup();

    Ble::BleControllerFactory &bleControllerFactory_; ///< Factory of Ble controllers
    Ble::IBleController *bleController_;              ///< Ble Controller being used by state
    IState *state_{nullptr};                          ///< Pointer to actual state of the device
};

#endif //DEVICE_CONTEXT
