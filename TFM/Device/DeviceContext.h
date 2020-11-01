
#ifndef DEVICE_CONTEXT
#define DEVICE_CONTEXT

#include "BleControllerFactory.h"
#include "IAction.h"
#include "IContext.h"
#include "IDetectorFactory.h"

class IState;

/**
 * @brief Represents the context of the device. It manages its states and process actions performed by user
 */
class DeviceContext : public IContext
{
public:
    /**
     * @brief Construct a new Device Context object 
     * 
     * @param bleControllerFactory Reference to a factory of Ble controllers
     */
    DeviceContext(Ble::BleControllerFactory &bleControllerFactory);

    /**
     * @brief Destroy the Device Context object 
     */
    virtual ~DeviceContext();

    ///< Implementation of virtual methods from IContext
    virtual void setDetectors(DetectorType *detectorTypes, size_t numDetectors) override;
    virtual void changeState(StateType newState) override;

    /**
     * @brief General process of the device, detecting actions performed by user 
     */
    void detectAction();

private:
    /**
     * @brief Free allocated memory and reset attributes 
     */
    void cleanup();

    /**
     * @brief Set the Detection Type of detectors 
     */
    void setDetectionType();

    Ble::BleControllerFactory &bleControllerFactory_; ///< Factory of Ble controllers
    Ble::IBleController *bleController_{nullptr};     ///< Ble Controller being used by state
    Detector::IDetectorFactory *detectorFactory_{nullptr}; ///< Factory of detectors
    Detector::DetectorPtr *detectors_{nullptr};            ///< Vector of detectors
    size_t numDetectors_{0};                               ///< Number of detectors
    IAction *action_{nullptr};                             ///< Action to be performed
    IState *state_{nullptr};                               ///< Pointer to actual state of the device

    Detector::IDetector::DetectionType detectionType_{Detector::IDetector::DetectionType::QUALITY}; ///< Type of detection
};

#endif //DEVICE_CONTEXT
