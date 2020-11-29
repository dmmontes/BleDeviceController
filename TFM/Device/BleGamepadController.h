
#ifndef BLE_GAMEPAD_CONTROLLER
#define BLE_GAMEPAD_CONTROLLER

#include "IBleController.h"

namespace Ble
{

    /**
     * @brief Ble Controller for HID Gamepad's functionality
     */
    class BleGamepadController : public IBleController
    {
    public:
        /**
         * @brief Construct a new Ble Gamepad Controller object
         * 
         * @param name Name of the Ble device to be shown advertising
         * @param useSecurity Use Pin's verification in BLE's connection
         */
        BleGamepadController(String &name, bool useSecurity);

        ///< Implementation of virtual methods from IBleController
        virtual bool sendData(int8_t *data, size_t dataSize) override;

    protected:
        ///< Implementation of virtual methods from IBleController
        virtual void configureServices() override;

    private:
        BLE_Char hidInfoCharacteristic_;        ///< HID Characteristic: Protocol Mode
        BLE_Char reportMapCharacteristic_;      ///< HID Characteristic: Report Map
        BLE_Char hidControlCharacteristic_;     ///< HID Characteristic: Hid Control
        const uint8_t inputReportValue_[2];     ///< Input Report Descriptor's value
        BLE_Descriptor inputReportDescriptor_;  ///< HID Descriptor: Input Report
        BLE_Char inputReportCharasteristic_;    ///< HID Characteristic: Input Report
        const uint8_t outputReportValue_[2];    ///< Output Report Descriptor's value
        BLE_Descriptor outputReportDescriptor_; ///< HID Descriptor: Output Report
        BLE_Char outputReportCharasteristic_;   ///< HID Characteristic: Output Report
        // const uint8_t inputReportMediaKeysValue_[2];    ///< Input Report Media Keys Descriptor's value
        // BLE_Descriptor inputReportMediaKeysDescriptor_; ///< HID Descriptor: Input Report Media Keys
        // BLE_Char inputReportMediaKeysCharasteristic_;   ///< HID Characteristic: Input Report Media Keys
        BLE_Char protocolModeCharacteristic_;    ///< HID Characteristic: Protocol Mode
        BLE_Char *hidServiceCharacteristics_[7]; ///< HID Characteristic: Protocol Mode
        BLE_Service hidService_;                 ///< HID Characteristic: Protocol Mode
    };

} // namespace Ble

#endif //BLE_GAMEPAD_CONTROLLER
