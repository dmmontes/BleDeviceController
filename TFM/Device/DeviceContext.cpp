#include "DeviceContext.h"

#include "DeviceLogger.h"

#include "InterfaceAction.h"
#include "InterfaceDetectorFactory.h"
#include "InterfaceState.h"
#include "MouseAction.h"
#include "MouseBluetoothState.h"
#include "MouseDetectorFactory.h"

DeviceContext::DeviceContext(Ble::BleControllerFactory &bleControllerFactory) : bleControllerFactory_(bleControllerFactory)
{
    LOG_DEBUG("DeviceContext::DeviceContext()");
    changeState(DeviceContext::StateType::INTERFACE);
}

DeviceContext::~DeviceContext()
{
    LOG_DEBUG("DeviceContext::~DeviceContext()");
    cleanup();
}

void DeviceContext::detectAction()
{
    LOG_DEBUG("DeviceContext::detectAction()");
    state_->detectAction();
}

void DeviceContext::setDetectors(DetectorType *detectorTypes, size_t numDetectors)
{
    LOG_DEBUG("DeviceContext::setDetectors()");
    Detector::IDetectorFactory::DetectorType factoryDetectorTypes[numDetectors];
    for (size_t i = 0; i < numDetectors; ++i)
    {
        factoryDetectorTypes[i] = static_cast<Detector::IDetectorFactory::DetectorType>(static_cast<uint8_t>(detectorTypes[i]));
    }

    detectors_ = detectorFactory_->createDetectors(factoryDetectorTypes, numDetectors);
    if (!detectors_)
    {
        LOG_ERROR("DeviceContext::setDetectors() failed creation detectors");
        return;
    }
    state_->setDetectors(detectors_, numDetectors);
}

void DeviceContext::changeState(StateType newState)
{
    LOG_DEBUG("DeviceContext::changeState()");
    cleanup();

    // Create the new state
    switch (newState)
    {
    case DeviceContext::StateType::INTERFACE:
        detectorFactory_ = new Detector::InterfaceDetectorFactory();
        action_ = new InterfaceAction();
        state_ = new InterfaceState(*this, *action_);
        break;

    case DeviceContext::StateType::MOUSE:
        detectorFactory_ = new Detector::MouseDetectorFactory();
        action_ = new MouseAction();
        bleController_ = bleControllerFactory_.createBleController(Ble::BleControllerFactory::BleType::MOUSE, "Mouse Controller", true);
        state_ = new MouseBluetoothState(*this, *action_, *bleController_);
        break;

    default:
        LOG_WARNING("DeviceContext::changeState() Unknown state");
        break;
    }
}

void DeviceContext::cleanup()
{
    LOG_DEBUG("DeviceContext::cleanup()");

    //Delete detector factory
    detectorFactory_->deleteDetectors(detectors_);
    delete detectorFactory_;
    detectorFactory_ = nullptr;

    // Delete ble controller
    bleControllerFactory_.deleteBleController(bleController_);
    bleController_ = nullptr;

    // Delete action
    delete action_;
    action_ = nullptr;

    // Delete state
    delete state_;
    state_ = nullptr;
}
