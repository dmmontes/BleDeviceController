#include "BleControllerFactory.h"

// /* Pin number variables for Buttons on MSP432P401R LaunchPad */
// static const uint8_t button1Pin = 33;
// static const uint8_t button2Pin = 32;

// // constants won't change. They're used here to
// // set pin numbers:
// static const uint8_t joystickSel = 5; // the number of the joystick select pin
// static const uint8_t joystickX = 2;   // the number of the joystick X-axis analog
// static const uint8_t joystickY = 26;  // the number of the joystick Y-axis analog

// static const int MIDDLE_READ_VALUE = 512;
// static const int JOYSTICK_TRESHOLD = 100;
// static const int MOVEMENT_LIMIT = MIDDLE_READ_VALUE - JOYSTICK_TRESHOLD;
// static const int MOUSE_MOVEMENT_LIMIT = 20;

// /* State Variables for Button Chars */
// // Buttons are active low so initial state is 1
// uint8_t button1State = 1;
// uint8_t button2State = 1;

// // variables will change:
// int joystickSelState = 1; // variable for reading the joystick sel status

Ble::BleControllerFactory bleControllerFactory;

void setup()
{
  Serial.begin(9600);
  Serial.print("BleMouseController::deleteBleController() BleType: ");

  // // Note that the switches on the MSP432P401R LP need pullups
  // pinMode(button1Pin, INPUT_PULLUP);
  // pinMode(button2Pin, INPUT_PULLUP);

  // // initialize the pushbutton pin as an input:
  // pinMode(joystickSel, INPUT_PULLUP);

  // button1State = digitalRead(button1Pin);
  // button2State = digitalRead(button2Pin);
  Ble::IBleController *mouseController = bleControllerFactory.createBleController(Ble::BleControllerFactory::BleType::MOUSE, String("Device Controller"), false);
  bleControllerFactory.deleteBleController(mouseController);
}

// the loop routine runs over and over again forever as a task.
void loop()
{
  ble.handleEvents();
  Serial.println("BleMouseController::deleteBleController() BleType: ");
  // ble.handleEvents();

  // if (ble.isConnected())
  // {

  //   bool action = false;
  //   mouseAction[1]=0;
  //   mouseAction[2]=0;

  //   // Read the state of both buttons and send a notification
  //   uint8_t newButton1State = digitalRead(button1Pin);
  //   if (button1State != newButton1State)
  //   {
  //     button1State = newButton1State;
  //     Serial.print("Button 1 Val Changed ="); Serial.println(button1State);

  //     mouseAction[0] = (button1State == 0) ? MOUSE_LEFT : 0;
  //     action = true;
  //   }

  //   uint8_t newButton2State = digitalRead(button2Pin);
  //   if (button2State != newButton2State)
  //   {
  //     button2State = newButton2State;
  //     Serial.print("Button 2 Val Changed = "); Serial.println(button2State);

  //     mouseAction[0] = (button2State == 0) ? MOUSE_RIGHT : 0;
  //     action = true;
  //   }

  //   uint8_t newjoystickSelState = digitalRead(joystickSel);
  //   if (joystickSelState != newjoystickSelState)
  //   {
  //     joystickSelState = newjoystickSelState;
  //     Serial.print("Joystick button Val Changed = "); Serial.println(joystickSelState);

  //     mouseAction[0] = (joystickSelState == 0) ? MOUSE_MIDDLE : 0;
  //     action = true;
  //   }

  //   // read the analog value of joystick x axis
  //   const int joystickXState = analogRead(joystickX);
  //   int difference = joystickXState - MIDDLE_READ_VALUE;
  //   if (abs(difference) > JOYSTICK_TRESHOLD)
  //   {
  //     difference = map (difference, -MOVEMENT_LIMIT, MOVEMENT_LIMIT, -MOUSE_MOVEMENT_LIMIT, MOUSE_MOVEMENT_LIMIT);
  //     Serial.print("Joystick X: units moved = "); Serial.println(difference);

  //     mouseAction[1] = difference;
  //     action = true;
  //   }

  //   // read the analog value of joystick x axis
  //   const int joystickYState = analogRead(joystickY);
  //   difference = MIDDLE_READ_VALUE - joystickYState;
  //   if (abs(difference) > JOYSTICK_TRESHOLD)
  //   {
  //     difference = map (difference, -MOVEMENT_LIMIT, MOVEMENT_LIMIT, -MOUSE_MOVEMENT_LIMIT, MOUSE_MOVEMENT_LIMIT);
  //     Serial.print("Joystick Y: units moved = "); Serial.println(difference);

  //     mouseAction[2] = difference;
  //     action = true;
  //   }

  //   if (action)
  //   {
  //     ble.writeValue(&inputReportCharacteristic, mouseAction, sizeof(mouseAction));
  //   }

  // }
}
