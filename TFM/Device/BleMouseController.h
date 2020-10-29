
#ifndef BLE_MOUSE_CONTROLLER
#define BLE_MOUSE_CONTROLLER

#include "IBleController.h"

namespace Ble
{

    /**
     * @brief Ble Controller for HID Mouse's functionality
     */
    class BleMouseController : public IBleController
    {
    public:
        /**
         * @brief Construct a new Ble Mouse Controller object
         * 
         * @param name Name of the Ble device to be shown advertising
         * @param useSecurity Use Pin's verification in BLE's connection
         */
        BleMouseController(String &name, bool useSecurity);

        ///< Implementation of virtual methods from IBleController
        virtual bool sendData(int8_t *data, size_t dataSize) override;

    protected:
        ///< Implementation of virtual methods from IBleController
        virtual void configureServices() override;

    private:
        BLE_Char hidInfoCharacteristic_;         ///< HID Characteristic: Protocol Mode
        BLE_Char reportMapCharacteristic_;       ///< HID Characteristic: Report Map
        BLE_Char hidControlCharacteristic_;      ///< HID Characteristic: Hid Control
        const uint8_t inputReportValue_[2];      ///< Input Report Descriptor's value
        BLE_Descriptor inputReportDescriptor_;   ///< HID Descriptor: Input Report
        BLE_Char inputReportCharasteristic_;     ///< HID Characteristic: Input Report
        BLE_Char protocolModeCharacteristic_;    ///< HID Characteristic: Protocol Mode
        BLE_Char *hidServiceCharacteristics_[5]; ///< HID Characteristic: Protocol Mode
        BLE_Service hidService_;                 ///< HID Characteristic: Protocol Mode
    };

} // namespace Ble

#endif //BLE_MOUSE_CONTROLLER
