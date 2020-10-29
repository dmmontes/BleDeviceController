
#ifndef I_BLE_CONTROLLER
#define I_BLE_CONTROLLER

#include "BLE.h"

// #include "../../../../Desktop/energia-1.8.10E23-windows/energia-1.8.10E23-windows/energia-1.8.10E23/hardware\energia\msp430\cores\msp430\Energia.h"

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
