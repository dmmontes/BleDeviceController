
#ifndef I_STATE
#define I_STATE

#include "IDetector.h"
#include "IContext.h"
#include "IAction.h"
#include "PowerStateMachine.h"
#include "Screen.h"

/**
 * @brief Represents a state of the device. 
 */
class IState
{
public:
    /**
     * @brief Construct a new IState object
     * 
     * @param context Reference to actual context
     * @param action Reference to action to be done
     */
    IState(IContext &context);

    /**
     * @brief Destroy the IState object 
     */
    virtual ~IState() = default;

    /**
     * @brief Add a vector of pointers to detectors (of user's actions) to the general process 
     * 
     * @param detectors vector of pointers to detectors 
     * @param numDetectors number of detectors
     */
    void setDetectors(Detector::DetectorPtr *detectors, size_t numDetectors);

    /**
     * @brief General process of the device, detecting actions performed by user 
     * 
     * @param action Pointer to action to be done
     */
    void detectAction(IAction *action);

protected:
    /**
     * @brief Process an action detected 
     * 
     * @param actionData data of the action to be performed
     */
    virtual void processAction(const IAction::ActionData &actionData) = 0;

    /**
     * @brief Indicates if detections should be performed
     */
    virtual bool isDetectionEnabled() = 0;

    IContext &context_;              ///< Pointer to device's context
    Screen **deviceScreen_{nullptr}; ///< Screen of the device

private:
    PowerStateMachine powerStateMachine_;       ///< State machiche of power consumption
    Detector::DetectorPtr *detectors_{nullptr}; ///< vector of pointers to detectors
    size_t numDetectors_{0};                    ///< Number of detectors
};

#endif //I_STATE
