#include "BleGamepadController.h"

#include "DeviceLogger.h"

#include "BleConfigurationUtils.h"

namespace Ble
{

    BleGamepadController::BleGamepadController(String &name, bool useSecurity)
        ///< HID Characteristic: Hid Info
        : hidInfoCharacteristic_{
              {0x4A, 0x2A},
              BLE_READABLE},

          ///< HID Characteristic: Report Map
          reportMapCharacteristic_{{0x4B, 0x2A}, BLE_READABLE},

          ///< HID Characteristic: Hid Control
          hidControlCharacteristic_{{0x4C, 0x2A}, BLE_WRITABLE_NORSP},

          ///< HID Descriptor: Input Report
          inputReportValue_{0x01, 0x01}, inputReportDescriptor_{{0x08, 0x29}, BLE_PERMIT_READ, &inputReportValue_, 2},

          ///< HID Characteristic: Input Report
          inputReportCharasteristic_{{0x4D, 0x2A}, BLE_READABLE | BLE_NOTIFIABLE, NULL, &inputReportDescriptor_},

          ///< HID Descriptor: Output Report
          outputReportValue_{0x01, 0x02}, outputReportDescriptor_{{0x08, 0x29}, BLE_PERMIT_READ, &outputReportValue_, 2},

          ///< HID Characteristic: Output Report
          outputReportCharasteristic_{{0x4D, 0x2A}, BLE_READABLE | BLE_NOTIFIABLE, NULL, &outputReportDescriptor_},

          //   ///< HID Descriptor: Input Report Media Keys
          //   inputReportMediaKeysValue_{0x02, 0x01}, inputReportMediaKeysDescriptor_{{0x08, 0x29}, BLE_PERMIT_READ, &inputReportMediaKeysValue_, 2},

          //   ///< HID Characteristic: Input Report Media Keys
          //   inputReportMediaKeysCharasteristic_{{0x4D, 0x2A}, BLE_READABLE | BLE_NOTIFIABLE, NULL, &inputReportMediaKeysDescriptor_},

          ///< HID Characteristic: Protocol Mode
          protocolModeCharacteristic_{{0x4E, 0x2A}, BLE_READABLE | BLE_WRITABLE_NORSP},

          ///< HID Characteristics
          hidServiceCharacteristics_{&hidInfoCharacteristic_, &reportMapCharacteristic_, &protocolModeCharacteristic_, &inputReportCharasteristic_, &outputReportCharasteristic_, /*&inputReportMediaKeysCharasteristic_,*/ &hidControlCharacteristic_},

          ///< HID Service
          hidService_{{0x12, 0x18}, 6, hidServiceCharacteristics_}
    {
        LOG_DEBUG("BleGamepadController::BleGamepadController()");
        initBLE(name, useSecurity);
    }

    bool BleGamepadController::sendData(int8_t *data, size_t dataSize)
    {
        LOG_DEBUG("BleGamepadController::sendData()");

        int returnCode = ble.writeValue(&inputReportCharasteristic_, data, dataSize);
        return (returnCode == 0 ? true : false);
    }

    void BleGamepadController::configureServices()
    {
        LOG_DEBUG("BleGamepadController::configureServices()");

        // Add Service
        ble.addService(&hidService_);

        // Write characteristics values
        const uint8_t hidInfo[] = {0x01, 0x01, 0x25, 0x02};
        ble.writeValue(&hidInfoCharacteristic_, hidInfo, sizeof(hidInfo));

        const uint8_t _reportMapValues[] = {
            USAGE_PAGE(1), 0x01, // USAGE_PAGE (Generic Desktop Ctrls)
            USAGE(1), 0x06,      // USAGE (Keyboard)
            COLLECTION(1), 0x01, // COLLECTION (Application)
            // ------------------------------------------------- Keyboard
            REPORT_ID(1), 0x01,       //   REPORT_ID (1)
            USAGE_PAGE(1), 0x07,      //   USAGE_PAGE (Kbrd/Keypad)
            USAGE_MINIMUM(1), 0xE0,   //   USAGE_MINIMUM (0xE0)
            USAGE_MAXIMUM(1), 0xE7,   //   USAGE_MAXIMUM (0xE7)
            LOGICAL_MINIMUM(1), 0x00, //   LOGICAL_MINIMUM (0)
            LOGICAL_MAXIMUM(1), 0x01, //   Logical Maximum (1)
            REPORT_SIZE(1), 0x01,     //   REPORT_SIZE (1)
            REPORT_COUNT(1), 0x08,    //   REPORT_COUNT (8)
            HIDINPUT(1), 0x02,        //   INPUT (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
            REPORT_COUNT(1), 0x01,    //   REPORT_COUNT (1) ; 1 byte (Reserved)
            REPORT_SIZE(1), 0x08,     //   REPORT_SIZE (8)
            HIDINPUT(1), 0x01,        //   INPUT (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
            REPORT_COUNT(1), 0x05,    //   REPORT_COUNT (5) ; 5 bits (Num lock, Caps lock, Scroll lock, Compose, Kana)
            REPORT_SIZE(1), 0x01,     //   REPORT_SIZE (1)
            USAGE_PAGE(1), 0x08,      //   USAGE_PAGE (LEDs)
            USAGE_MINIMUM(1), 0x01,   //   USAGE_MINIMUM (0x01) ; Num Lock
            USAGE_MAXIMUM(1), 0x05,   //   USAGE_MAXIMUM (0x05) ; Kana
            HIDOUTPUT(1), 0x02,       //   OUTPUT (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position
            REPORT_COUNT(1), 0x01,    //   REPORT_COUNT (1) ; 3 bits (Padding)
            REPORT_SIZE(1), 0x03,     //   REPORT_SIZE (3)
            HIDOUTPUT(1), 0x01,       //   OUTPUT (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position
            REPORT_COUNT(1), 0x06,    //   REPORT_COUNT (6) ; 6 bytes (Keys)
            REPORT_SIZE(1), 0x08,     //   REPORT_SIZE(8)
            LOGICAL_MINIMUM(1), 0x00, //   LOGICAL_MINIMUM(0)
            LOGICAL_MAXIMUM(1), 0x65, //   LOGICAL_MAXIMUM(0x65) ; 101 keys
            USAGE_PAGE(1), 0x07,      //   USAGE_PAGE (Kbrd/Keypad)
            USAGE_MINIMUM(1), 0x00,   //   USAGE_MINIMUM (0)
            USAGE_MAXIMUM(1), 0x65,   //   USAGE_MAXIMUM (0x65)
            HIDINPUT(1), 0x00,        //   INPUT (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
            END_COLLECTION(0),        // END_COLLECTION
            // ------------------------------------------------- Media Keys
            // USAGE_PAGE(1), 0x0C,         // USAGE_PAGE (Consumer)
            // USAGE(1), 0x01,              // USAGE (Consumer Control)
            // COLLECTION(1), 0x01,         // COLLECTION (Application)
            // REPORT_ID(1), MEDIA_KEYS_ID, //   REPORT_ID (3)
            // USAGE_PAGE(1), 0x0C,         //   USAGE_PAGE (Consumer)
            // LOGICAL_MINIMUM(1), 0x00,    //   LOGICAL_MINIMUM (0)
            // LOGICAL_MAXIMUM(1), 0x01,    //   LOGICAL_MAXIMUM (1)
            // REPORT_SIZE(1), 0x01,        //   REPORT_SIZE (1)
            // REPORT_COUNT(1), 0x10,       //   REPORT_COUNT (16)
            // USAGE(1), 0xB5,              //   USAGE (Scan Next Track)     ; bit 0: 1
            // USAGE(1), 0xB6,              //   USAGE (Scan Previous Track) ; bit 1: 2
            // USAGE(1), 0xB7,              //   USAGE (Stop)                ; bit 2: 4
            // USAGE(1), 0xCD,              //   USAGE (Play/Pause)          ; bit 3: 8
            // USAGE(1), 0xE2,              //   USAGE (Mute)                ; bit 4: 16
            // USAGE(1), 0xE9,              //   USAGE (Volume Increment)    ; bit 5: 32
            // USAGE(1), 0xEA,              //   USAGE (Volume Decrement)    ; bit 6: 64
            // USAGE(2), 0x23, 0x02,        //   Usage (WWW Home)            ; bit 7: 128
            // USAGE(2), 0x94, 0x01,        //   Usage (My Computer) ; bit 0: 1
            // USAGE(2), 0x92, 0x01,        //   Usage (Calculator)  ; bit 1: 2
            // USAGE(2), 0x2A, 0x02,        //   Usage (WWW fav)     ; bit 2: 4
            // USAGE(2), 0x21, 0x02,        //   Usage (WWW search)  ; bit 3: 8
            // USAGE(2), 0x26, 0x02,        //   Usage (WWW stop)    ; bit 4: 16
            // USAGE(2), 0x24, 0x02,        //   Usage (WWW back)    ; bit 5: 32
            // USAGE(2), 0x83, 0x01,        //   Usage (Media sel)   ; bit 6: 64
            // USAGE(2), 0x8A, 0x01,        //   Usage (Mail)        ; bit 7: 128
            // HIDINPUT(1), 0x02,           //   INPUT (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
            // END_COLLECTION(0)            // END_COLLECTION
        };
        ble.writeValue(&reportMapCharacteristic_, _reportMapValues, sizeof(_reportMapValues));

        ble.writeValue(&protocolModeCharacteristic_, (uint8_t)1);
    }

} // namespace Ble
