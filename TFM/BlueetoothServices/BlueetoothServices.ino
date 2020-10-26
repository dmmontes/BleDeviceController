#include <BLE.h>

/* HID Class Report Descriptor */
/* Short items: size is 0, 1, 2 or 3 specifying 0, 1, 2 or 4 (four) bytes */
/* of data as per HID Class standard */
#define HIDINPUT(size)             (0x80 | size)
#define HIDOUTPUT(size)            (0x90 | size)
#define FEATURE(size)           (0xb0 | size)
#define COLLECTION(size)        (0xa0 | size)
#define END_COLLECTION(size)    (0xc0 | size)

/* Global items */
#define USAGE_PAGE(size)        (0x04 | size)
#define LOGICAL_MINIMUM(size)   (0x14 | size)
#define LOGICAL_MAXIMUM(size)   (0x24 | size)
#define PHYSICAL_MINIMUM(size)  (0x34 | size)
#define PHYSICAL_MAXIMUM(size)  (0x44 | size)
#define UNIT_EXPONENT(size)     (0x54 | size)
#define UNIT(size)              (0x64 | size)
#define REPORT_SIZE(size)       (0x74 | size)  //bits
#define REPORT_ID(size)         (0x84 | size)
#define REPORT_COUNT(size)      (0x94 | size)  //bytes
#define PUSH(size)              (0xa4 | size)
#define POP(size)               (0xb4 | size)

/* Local items */
#define USAGE(size)                 (0x08 | size)
#define USAGE_MINIMUM(size)         (0x18 | size)
#define USAGE_MAXIMUM(size)         (0x28 | size)
#define DESIGNATOR_INDEX(size)      (0x38 | size)
#define DESIGNATOR_MINIMUM(size)    (0x48 | size)
#define DESIGNATOR_MAXIMUM(size)    (0x58 | size)
#define STRING_INDEX(size)          (0x78 | size)
#define STRING_MINIMUM(size)        (0x88 | size)
#define STRING_MAXIMUM(size)        (0x98 | size)
#define DELIMITER(size)             (0xa8 | size)

//Mouse Actions
#define MOUSE_LEFT 1
#define MOUSE_RIGHT 2
#define MOUSE_MIDDLE 4
#define MOUSE_BACK 8
#define MOUSE_FORWARD 16
#define MOUSE_ALL (MOUSE_LEFT | MOUSE_RIGHT | MOUSE_MIDDLE) 


/* State Variables for Button Chars */
// Buttons are active low so initial state is 1
uint8_t button1State = 1;
uint8_t button2State = 1;

/* Pin number variables for Buttons on MSP432P401R LaunchPad */
uint8_t button1Pin = 33;
uint8_t button2Pin = 32;

// HID Service and Characteristics

BLE_Char protocolModeCharacteristic =
{
  {0x4E, 0x2A},
  BLE_READABLE | BLE_WRITABLE_NORSP
};

static const uint8_t inputDescriptorValue[] = {0x01, 0x01};
BLE_Descriptor inputReportDescriptor
{
  {0x08, 0x29},
  BLE_PERMIT_READ,
  &inputDescriptorValue,
  sizeof(inputDescriptorValue)
};

BLE_Char inputReportCharacteristic =
{
  {0x4D, 0x2A},
  BLE_READABLE | BLE_NOTIFIABLE,
  NULL,
  &inputReportDescriptor
};

BLE_Char reportMapCharacteristic =
{
  {0x4B, 0x2A},
  BLE_READABLE
};

BLE_Char hidInfoCharacteristic =
{
  {0x4A, 0x2A},
  BLE_READABLE
};

BLE_Char m_hidControlCharacteristic =
{
  {0x4C, 0x2A},
  BLE_WRITABLE_NORSP
};

BLE_Char *hidServiceChars[] = {&hidInfoCharacteristic, &reportMapCharacteristic, &protocolModeCharacteristic, &inputReportCharacteristic, &m_hidControlCharacteristic};

BLE_Service hidService =
{
  {0x12, 0x18},
  5, hidServiceChars
};

void setup() {
  Serial.begin(9600);
  ble.setLogLevel(BLE_LOG_ERRORS | BLE_LOG_RPCS | BLE_LOG_REC_MSGS | BLE_LOG_ALL);
  ble.begin();

  // Note that the switches on the MSP432P401R LP need pullups
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);

  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);

  ble.addService(&hidService);

  const uint8_t hidInfo[] = {0x01, 0x01, 0x25, 0x02};
  ble.writeValue(&hidInfoCharacteristic, hidInfo, sizeof(hidInfo));

  const uint8_t _reportMapValue[] = { 
    USAGE_PAGE(1),       0x01, // USAGE_PAGE (Generic Desktop)
    USAGE(1),            0x02, // USAGE (Mouse)
    COLLECTION(1),       0x01, // COLLECTION (Application)
    USAGE(1),            0x01, //   USAGE (Pointer)
    COLLECTION(1),       0x00, //   COLLECTION (Physical)
    REPORT_ID(1),        0x01, //     REPORT_ID (1)
    // ------------------------------------------------- Buttons (Left, Right, Middle, Back, Forward)
    USAGE_PAGE(1),       0x09, //     USAGE_PAGE (Button)
    USAGE_MINIMUM(1),    0x01, //     USAGE_MINIMUM (Button 1)
    USAGE_MAXIMUM(1),    0x05, //     USAGE_MAXIMUM (Button 5)
    LOGICAL_MINIMUM(1),  0x00, //     LOGICAL_MINIMUM (0)
    LOGICAL_MAXIMUM(1),  0x01, //     LOGICAL_MAXIMUM (1)
    REPORT_SIZE(1),      0x01, //     REPORT_SIZE (1)
    REPORT_COUNT(1),     0x05, //     REPORT_COUNT (5)
    HIDINPUT(1),         0x02, //     INPUT (Data, Variable, Absolute) ;5 button bits
    // ------------------------------------------------- Padding
    REPORT_SIZE(1),      0x03, //     REPORT_SIZE (3)
    REPORT_COUNT(1),     0x01, //     REPORT_COUNT (1)
    HIDINPUT(1),         0x03, //     INPUT (Constant, Variable, Absolute) ;3 bit padding
    // ------------------------------------------------- X/Y position, Wheel
    USAGE_PAGE(1),       0x01, //     USAGE_PAGE (Generic Desktop)
    USAGE(1),            0x30, //     USAGE (X)
    USAGE(1),            0x31, //     USAGE (Y)
    USAGE(1),            0x38, //     USAGE (Wheel)
    LOGICAL_MINIMUM(1),  0x81, //     LOGICAL_MINIMUM (-127)
    LOGICAL_MAXIMUM(1),  0x7f, //     LOGICAL_MAXIMUM (127)
    REPORT_SIZE(1),      0x08, //     REPORT_SIZE (8)
    REPORT_COUNT(1),     0x03, //     REPORT_COUNT (3)
    HIDINPUT(1),         0x06, //     INPUT (Data, Variable, Relative) ;3 bytes (X,Y,Wheel)
    // ------------------------------------------------- Horizontal wheel
    USAGE_PAGE(1),       0x0c, //     USAGE PAGE (Consumer Devices)
    USAGE(2),      0x38, 0x02, //     USAGE (AC Pan)
    LOGICAL_MINIMUM(1),  0x81, //     LOGICAL_MINIMUM (-127)
    LOGICAL_MAXIMUM(1),  0x7f, //     LOGICAL_MAXIMUM (127)
    REPORT_SIZE(1),      0x08, //     REPORT_SIZE (8)
    REPORT_COUNT(1),     0x01, //     REPORT_COUNT (1)
    HIDINPUT(1),         0x06, //     INPUT (Data, Var, Rel)
    END_COLLECTION(0),         //   END_COLLECTION
    END_COLLECTION(0)          // END_COLLECTION
  };
  ble.writeValue(&reportMapCharacteristic, _reportMapValue, sizeof(_reportMapValue));
  
  ble.writeValue(&protocolModeCharacteristic,(uint8_t)1);

  /* Start Advertising */
  ble.setAdvertName("BLE I/O Demo");
  ble.startAdvert();

  /* Setup security params */
  ble.setPairingMode(BLE_SECURITY_WAIT_FOR_REQUEST);
  ble.setIoCapabilities(BLE_DISPLAY_YES_NO);
  ble.useBonding(true);

  /* Print a message to the console */
  Serial.println(" BLE Energia Buttons/LED Demo");

}

// the loop routine runs over and over again forever as a task.
void loop() {
  ble.handleEvents();

  if (ble.isConnected())
  {
    // Read the state of both buttons and send a notification
    // if either is pressed, note that your app will
    // need to register for notifications by writing 01:00
    // to the button char's CCCD
    uint8_t newButton1State = digitalRead(button1Pin);
    uint8_t newButton2State = digitalRead(button2Pin);

    if (button1State != newButton1State)
    {
      button1State = newButton1State;
      Serial.print("Button 1 Val Changed="); Serial.println(button1State);
      
      uint8_t m[5];
      m[0] = (button1State == 0) ? MOUSE_LEFT : 0;
      m[1] = 0;
      m[2] = 0;
      m[3] = 0;
      m[4] = 0;
      ble.writeValue(&inputReportCharacteristic, m, sizeof(m));
    }

    if (button2State != newButton2State)
    {
      button2State = newButton2State;
      Serial.print("Button 2 Val Changed="); Serial.println(button2State);

      uint8_t m[5];
      m[0] = (button2State == 0) ? MOUSE_RIGHT : 0;
      m[1] = 0;
      m[2] = 0;
      m[3] = 0;
      m[4] = 0;
      ble.writeValue(&inputReportCharacteristic, m, sizeof(m));
    }
  }
}
