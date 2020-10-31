
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
     */
    virtual void changeState(StateType newState) = 0;
};

#endif //DEVICE_CONTEXT
