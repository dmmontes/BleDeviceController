
#ifndef I_CONTEXT
#define I_CONTEXT

#include <cstdint>

/**
 * @brief Represents a generic context of an object. Interface to be uses by the states of the context
 */
class IContext
{
public:
    /**
     * @brief Type of Detector
     */
    enum class DetectorType : uint8_t
    {
        BUTTON,        ///< Buton Detector
        JOYSTICK,      ///< Joystick Detector
        ACCELEROMETER, ///< Accelerometer Detector
        ACCEL_GYRO,    ///< Accelerometer-Gyroscope Detector
        FSR            ///< Force Sensitive Resistor Detector
    };

    /**
     * @brief Type of devices's states
     */
    enum class StateType : uint8_t
    {
        INTERFACE, ///< Showing initial interface
        MOUSE,     ///< Ble mouse mode
        GAMEPAD    ///< Ble gamepad mode
    };

    /**
     * @brief Destroy the Device Context object 
     */
    virtual ~IContext() = default;

    /**
     * @brief Add a vector of detectors (of user's actions) to the general process 
     * 
     * @param detectorTypes Types of detectors to be added
     * @param numDetectors number of detectors
     */
    virtual void setDetectors(DetectorType *detectorTypes, size_t numDetectors) = 0;

    /**
     * @brief Change the state of the device to a new one
     * 
     * @param newState New state of the device
     * @param extraSensors Indicates if add extra sensors or not
     */
    virtual void changeState(StateType newState, bool extraSensors = false) = 0;
};

#endif //DEVICE_CONTEXT
