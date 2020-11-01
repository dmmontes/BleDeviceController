#include "IBleController.h"

#include "DeviceLogger.h"

namespace Ble
{
    IBleController::~IBleController()
    {
        LOG_DEBUG("IBleController::~IBleController()");
        ble.end();
    }

    void IBleController::initBLE(String &name, bool useSecurity)
    {
        LOG_DEBUG("IBleController::initBLE()");

        ble.setLogLevel(BLE_LOG_NONE);
        ble.begin();

        configureServices();

        /* Start Advertising */
        ble.setAdvertName(&name);
        ble.startAdvert();

        /* Setup security params */
        if (useSecurity)
        {
            // ble.setPairingMode(BLE_SECURITY_WAIT_FOR_REQUEST);
            // ble.setIoCapabilities(BLE_DISPLAY_YES_NO);
        }
        ble.useBonding(true);

        /* Print a message to the console */
        LOG_DEBUG("IBleController::initBLE() Start advertising");
    }

} // namespace Ble
