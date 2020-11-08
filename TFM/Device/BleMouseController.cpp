#include "BleMouseController.h"

#include "DeviceLogger.h"

/* HID Class Report Descriptor */
/* Short items: size is 0, 1, 2 or 3 specifying 0, 1, 2 or 4 (four) bytes */
/* of data as per HID Class standard */
#define HIDINPUT(size) (0x80 | size)
#define HIDOUTPUT(size) (0x90 | size)
#define FEATURE(size) (0xb0 | size)
#define COLLECTION(size) (0xa0 | size)
#define END_COLLECTION(size) (0xc0 | size)

/* Global items */
#define USAGE_PAGE(size) (0x04 | size)
#define LOGICAL_MINIMUM(size) (0x14 | size)
#define LOGICAL_MAXIMUM(size) (0x24 | size)
#define PHYSICAL_MINIMUM(size) (0x34 | size)
#define PHYSICAL_MAXIMUM(size) (0x44 | size)
#define UNIT_EXPONENT(size) (0x54 | size)
#define UNIT(size) (0x64 | size)
#define REPORT_SIZE(size) (0x74 | size) //bits
#define REPORT_ID(size) (0x84 | size)
#define REPORT_COUNT(size) (0x94 | size) //bytes
#define PUSH(size) (0xa4 | size)
#define POP(size) (0xb4 | size)

/* Local items */
#define USAGE(size) (0x08 | size)
#define USAGE_MINIMUM(size) (0x18 | size)
#define USAGE_MAXIMUM(size) (0x28 | size)
#define DESIGNATOR_INDEX(size) (0x38 | size)
#define DESIGNATOR_MINIMUM(size) (0x48 | size)
#define DESIGNATOR_MAXIMUM(size) (0x58 | size)
#define STRING_INDEX(size) (0x78 | size)
#define STRING_MINIMUM(size) (0x88 | size)
#define STRING_MAXIMUM(size) (0x98 | size)
#define DELIMITER(size) (0xa8 | size)

//Mouse Actions
#define MOUSE_LEFT 1
#define MOUSE_RIGHT 2
#define MOUSE_MIDDLE 4
#define MOUSE_BACK 8
#define MOUSE_FORWARD 16
#define MOUSE_ALL (MOUSE_LEFT | MOUSE_RIGHT | MOUSE_MIDDLE)

namespace Ble
{

    BleMouseController::BleMouseController(String &name, bool useSecurity)
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

          ///< HID Characteristic: Protocol Mode
          protocolModeCharacteristic_{{0x4E, 0x2A}, BLE_READABLE | BLE_WRITABLE_NORSP},

          ///< HID Characteristics
          hidServiceCharacteristics_{&hidInfoCharacteristic_, &reportMapCharacteristic_, &protocolModeCharacteristic_, &inputReportCharasteristic_, &hidControlCharacteristic_},

          ///< HID Service
          hidService_{{0x12, 0x18}, 5, hidServiceCharacteristics_}
    {
        LOG_DEBUG("BleMouseController::BleMouseController()");
        initBLE(name, useSecurity);
    }

    bool BleMouseController::sendData(int8_t *data, size_t dataSize)
    {
        LOG_DEBUG("BleMouseController::sendData()");

        int returnCode = ble.writeValue(&inputReportCharasteristic_, data, dataSize);
        return (returnCode == 0 ? true : false);
    }

    void BleMouseController::configureServices()
    {
        LOG_DEBUG("BleMouseController::configureServices()");

        // Add Service
        ble.addService(&hidService_);

        // Write characteristics values
        const uint8_t hidInfo[] = {0x01, 0x01, 0x25, 0x02};
        ble.writeValue(&hidInfoCharacteristic_, hidInfo, sizeof(hidInfo));

        const uint8_t _reportMapValues[] = {
            USAGE_PAGE(1), 0x01, // USAGE_PAGE (Generic Desktop)
            USAGE(1), 0x02,      // USAGE (Mouse)
            COLLECTION(1), 0x01, // COLLECTION (Application)
            USAGE(1), 0x01,      //   USAGE (Pointer)
            COLLECTION(1), 0x00, //   COLLECTION (Physical)
            REPORT_ID(1), 0x01,  //     REPORT_ID (1)
            // ------------------------------------------------- Buttons (Left, Right, Middle, Back, Forward)
            USAGE_PAGE(1), 0x09,      //     USAGE_PAGE (Button)
            USAGE_MINIMUM(1), 0x01,   //     USAGE_MINIMUM (Button 1)
            USAGE_MAXIMUM(1), 0x05,   //     USAGE_MAXIMUM (Button 5)
            LOGICAL_MINIMUM(1), 0x00, //     LOGICAL_MINIMUM (0)
            LOGICAL_MAXIMUM(1), 0x01, //     LOGICAL_MAXIMUM (1)
            REPORT_SIZE(1), 0x01,     //     REPORT_SIZE (1)
            REPORT_COUNT(1), 0x05,    //     REPORT_COUNT (5)
            HIDINPUT(1), 0x02,        //     INPUT (Data, Variable, Absolute) ;5 button bits
            // ------------------------------------------------- Padding
            REPORT_SIZE(1), 0x03,  //     REPORT_SIZE (3)
            REPORT_COUNT(1), 0x01, //     REPORT_COUNT (1)
            HIDINPUT(1), 0x03,     //     INPUT (Constant, Variable, Absolute) ;3 bit padding
            // ------------------------------------------------- X/Y position, Wheel
            USAGE_PAGE(1), 0x01,      //     USAGE_PAGE (Generic Desktop)
            USAGE(1), 0x30,           //     USAGE (X)
            USAGE(1), 0x31,           //     USAGE (Y)
            USAGE(1), 0x38,           //     USAGE (Wheel)
            LOGICAL_MINIMUM(1), 0x81, //     LOGICAL_MINIMUM (-127)
            LOGICAL_MAXIMUM(1), 0x7f, //     LOGICAL_MAXIMUM (127)
            REPORT_SIZE(1), 0x08,     //     REPORT_SIZE (8)
            REPORT_COUNT(1), 0x03,    //     REPORT_COUNT (3)
            HIDINPUT(1), 0x06,        //     INPUT (Data, Variable, Relative) ;3 bytes (X,Y,Wheel)
            // ------------------------------------------------- Horizontal wheel
            USAGE_PAGE(1), 0x0c,      //     USAGE PAGE (Consumer Devices)
            USAGE(2), 0x38, 0x02,     //     USAGE (AC Pan)
            LOGICAL_MINIMUM(1), 0x81, //     LOGICAL_MINIMUM (-127)
            LOGICAL_MAXIMUM(1), 0x7f, //     LOGICAL_MAXIMUM (127)
            REPORT_SIZE(1), 0x08,     //     REPORT_SIZE (8)
            REPORT_COUNT(1), 0x01,    //     REPORT_COUNT (1)
            HIDINPUT(1), 0x06,        //     INPUT (Data, Var, Rel)
            END_COLLECTION(0),        //   END_COLLECTION
            END_COLLECTION(0)         // END_COLLECTION
        };
        ble.writeValue(&reportMapCharacteristic_, _reportMapValues, sizeof(_reportMapValues));

        ble.writeValue(&protocolModeCharacteristic_, (uint8_t)1);
    }

} // namespace Ble
