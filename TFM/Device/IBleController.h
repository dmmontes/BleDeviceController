
#ifndef I_BLE_CONTROLLER
#define I_BLE_CONTROLLER

#include "BLE.h"

namespace Ble
{

    class IBleController
    {
    public:
        /**
         * @brief Destroy the IBleController object
         */
        virtual ~IBleController();

        /**
         * @brief Set the Pin Callbacks Parameter to verify pairing devices
         * 
         * @param getPinText Function to get the text to verify pairing devices 
         * @param getPinNumber Function to get the pin number to verify pairing devices 
         * @param setPairingResult Function to set the pairing result
         * @param acceptButtonPin Button to accept the connection (Equal pin)
         * @param rejectButtonPin Button to reject the connection (Different pin)
         */
        void setPinCallbacksParameters(displayStringFxn_t getPinText,
                                       displayUIntFxn_t getPinNumber, setPairingResultFxn_t setPairingResult,
                                       int acceptButtonPin, int rejectButtonPin);

        /**
         * @brief Send data/action via BLE to receiver device
         * 
         * @param data data to be sent
         * @param dataSize size of the data
         * @return true if data has been sent correctly, false otherwise
         */
        virtual bool sendData(int8_t *data, size_t dataSize) = 0;

    protected:
        /**
         * @brief Configure BLE's services, characteristics, descriptors to be used
         */
        virtual void configureServices() = 0;

        /**
         * @brief Init Ble Services and start advertising
         * 
         * @param name Name of the Ble device to be shown advertising
         * @param useSecurity Use Pin's verification in BLE's connection
         * @note This method will call to @ref configureServices method
         */
        void initBLE(String &name, bool useSecurity);
    };

} // namespace Ble

#endif //I_BLE_CONTROLLER
