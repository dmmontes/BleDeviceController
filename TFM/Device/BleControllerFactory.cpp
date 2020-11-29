#include "BleControllerFactory.h"

#include "DeviceLogger.h"

#include "BleMouseController.h"
#include "BleGamepadController.h"

namespace Ble
{

    IBleController *BleControllerFactory::createBleController(BleType type, String name, bool useSecurity)
    {
        LOG_DEBUG(String("BleControllerFactory::createBleController() BleType: ") + String(static_cast<uint8_t>(type)));

        if (bleController_)
        {
            LOG_WARNING("BleControllerFactory::createBleController() Previouse Ble Controller should be destroyed before");
            return nullptr;
        }

        switch (type)
        {
        case BleControllerFactory::BleType::MOUSE:
            bleController_ = new BleMouseController(name, useSecurity);
            break;
        case BleControllerFactory::BleType::GAMEPAD:
            bleController_ = new BleGamepadController(name, useSecurity);
            break;
        default:
            LOG_WARNING("BleControllerFactory::createBleController() Unknown specified type");
            break;
        }
        return bleController_;
    }

    void BleControllerFactory::deleteBleController(IBleController *bleController)
    {
        LOG_DEBUG("BleControllerFactory::deleteBleController()");
        if (bleController != bleController_)
        {
            LOG_WARNING("BleControllerFactory::deleteBleController() Ble Controller different from created previously");
            return;
        }

        // free(bleController_);
        delete bleController_;
        bleController_ = nullptr;
    }

} // namespace Ble
