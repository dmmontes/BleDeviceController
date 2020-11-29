
#ifndef BLE_CONFIGURATION_UTILS
#define BLE_CONFIGURATION_UTILS

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

#endif //BLE_CONFIGURATION_UTILS
