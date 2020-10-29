#include "IBleController.h"

namespace Ble
{
    IBleController::~IBleController()
    {
        Serial.println("IBleController::~IBleController()");
        ble.end();
    }

    void IBleController::initBLE(String &name, bool useSecurity)
    {
        Serial.println("IBleController::initBLE()");

        ble.setLogLevel(BLE_LOG_ERRORS | BLE_LOG_RPCS | BLE_LOG_REC_MSGS | BLE_LOG_ALL);
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
        Serial.println("IBleController::initBLE() Start advertising");
    }

} // namespace Ble
