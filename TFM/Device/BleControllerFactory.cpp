#include "BleControllerFactory.h"
#include "BleMouseController.h"

namespace Ble
{

    IBleController *BleControllerFactory::createBleController(BleType type, String name, bool useSecurity)
    {
        Serial.print("BleControllerFactory::createBleController() BleType: ");
        Serial.println(static_cast<uint8_t>(type));

        if (bleController_)
        {
            Serial.println("BleControllerFactory::createBleController() Previouse Ble Controller should be destroyed before");
            return nullptr;
        }

        switch (type)
        {
        case BleControllerFactory::BleType::MOUSE:
            bleController_ = (IBleController *)malloc(sizeof(*bleController_));
            break;
        default:
            Serial.println("BleControllerFactory::createBleController() Error, not specified type");
            break;
        }
        return bleController_;
    }

    void BleControllerFactory::deleteBleController(IBleController *bleController)
    {
        Serial.println("BleControllerFactory::deleteBleController()");
        if (bleController != bleController_)
        {
            Serial.println("BleControllerFactory::deleteBleController() Ble Controller different from created previously");
            return;
        }

        free(bleController_);
        bleController_ = nullptr;
    }

} // namespace Ble
