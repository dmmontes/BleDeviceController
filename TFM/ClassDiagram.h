@startuml

title Diagrama de clases del controlador

interface IBleController
{
    + virtual bool sendData(uint8_t* data, size_t dataSize()) = 0
    # virtual void configureServices() = 0
}

class BleMouseController
{

}
IBleController <|-down- BleMouseController

class BleGamepadController
{

}
IBleController <|-down- BleGamepadController

package Energia_Ble_Library  <<Folder>> {

    class Ble
    {
        + void addServices(Ble_Service)
        + void writeValue(uint8_t* data, size_t dataSize())
    }
    
    IBleController "1" *-left- "1" Ble
    class Ble_Service
    {
    
    }
    Ble "1" *-- "*" Ble_Service
    
    class Ble_Characteristic
    {
    
    }
    Ble_Service "1" *-- "*" Ble_Characteristic
    
    class Ble_Descriptor
    {
    
    }
    Ble_Characteristic "1" *-- "*" Ble_Descriptor

}

enum BleType
{
  MOUSE
  GAMEPAD
}

class BleControllerFactory
{
    + IBleController* createBleController(BleType type);
}
BleControllerFactory "create" ..> IBleController
BleControllerFactory -right- BleType


class Device
{
    + void setup()
    + void loop()
}

Interface IState
{
	+ void addDetectors(IDetector* detectors)
    + void detectActions(IAction* action)
    # virtual void processAction(ActionData* action) = 0
    # Context*
}

Interface IPowerStateMachine
{
    + virtual void detectionResult(bool detectedAction) = 0;
}

Interface IPowerState
{
    + virtual void detectionResult(bool detectedAction) = 0;
}

class PowerStateMachine
{
    
}
IPowerStateMachine <|-- PowerStateMachine
IState -up-> PowerStateMachine
PowerStateMachine -- IPowerState

class PowerState1
{

}
IPowerState <|-up- PowerState1

class PowerState2
{

}
IPowerState <|-up- PowerState2

class PowerState3
{

}
IPowerState <|-up- PowerState3

class PowerState4
{

}
IPowerState <|-up- PowerState4


class BluetoothState
{

}
IState <|-down- BluetoothState
IState <|-down- InterfaceState
BluetoothState -right-> IBleController

Interface IBluetoothConnectionStateMachine
{
    + virtual void changeState(State newState, BluetoothScreen *screen) = 0;
}

Interface IBluetoothConnectionState
{
    + virtual void handleState(bool connected) = 0
    + virtual bool isConnected() = 0
}
IBluetoothConnectionState --> BluetoothScreen

class BluetoothConnectionStateMachine
{

}
IBluetoothConnectionStateMachine <|-down- BluetoothConnectionStateMachine
BluetoothConnectionStateMachine -- IBluetoothConnectionState
BluetoothState --> BluetoothConnectionStateMachine

class BluetoothConnectionStateSearching
{

}
IBluetoothConnectionState <|-- BluetoothConnectionStateSearching

class BluetoothConnectionStateConnecting
{

}
IBluetoothConnectionState <|-- BluetoothConnectionStateConnecting

class BluetoothConnectionStatePairing
{

}
IBluetoothConnectionState <|-- BluetoothConnectionStatePairing

class BluetoothConnectionStateConnected
{

}
IBluetoothConnectionState <|-- BluetoothConnectionStateConnected

class MouseBluetoothState
{

}
BluetoothState <|-down- MouseBluetoothState

class GamepadBluetoothState
{

}
BluetoothState <|-down- GamepadBluetoothState

class InterfaceState
{

}
InterfaceState --> InterfaceScreen

class Message
{
    + String text
    + uint16_t yPos
    + uint8_t fontSize
    + bool fontSolid
    + uint16_t colour
}

class Box
{
    + uint16_t xPos
    + uint16_t yPos
    + uint16_t xSize
    + uint16_t ySize
    + uint16_t colour
    + bool fillBox
    + String text
    + uint16_t textColour
}

class Image
{
    + uint16_t xPos
    + uint16_t yPos
    + uint16_t xSize
    + uint16_t ySize
    + uint16_t *picture
}

class Screen
{
    + void drawMessage(const Message &message)
    + void removeMessage(const Message &message, uint16_t colour)
    + void drawBox(const Box &box)
    + void drawImage(const Image &image)
}
Screen -- Image
Screen -- Box
Screen -- Message

class InterfaceScreen
{
    void draw(int8_t action);
}
Screen <|-- InterfaceScreen

class BluetoothScreen
{
    + void drawSearchingMessage()
    + void drawPinVerification(uint32_t pin)
    + void removePinVerification()
    + void drawConnectionCorrect()
}
Screen <|-- BluetoothScreen


enum DetectionType
{
  NORMAL
  QUALITY
}

interface IDetector
{
    detectAction(IAction* action)
    virtual checkAction(IAction* action) = 0
    virtual void setDetectionType(DetectionType detectionType)
}
IState "1" *-left- "*" IDetector
IDetector -left- DetectionType

class ButtonDetector
{

}
IDetector <|-down- ButtonDetector

class ButtonIface
{

}
ButtonDetector <|-down- ButtonIface

class ButtonMouse
{

}
ButtonDetector <|-down- ButtonMouse

class ButtonGamepad
{

}
ButtonDetector <|-down- ButtonGamepad

class JoystickDetector
{

}
IDetector <|-down- JoystickDetector

class JoyIface
{

}
JoystickDetector <|-down- JoyIface

class JoyMouse
{

}
JoystickDetector <|-down- JoyMouse

class JoyGamepad
{

}
JoystickDetector <|-down- JoyGamepad

class AccelerometerDetector
{

}
IDetector <|-down- AccelerometerDetector

class AccMouse
{

}
AccelerometerDetector <|-down- AccMouse

class AccGamepad
{

}
AccelerometerDetector <|-down- AccGamepad

class AccelGyroDetector
{

}
IDetector <|-down- AccelGyroDetector

class AccGyroGamepad
{

}
AccelGyroDetector <|-down- AccGyroGamepad

package Energia_BMI160_Library  <<Folder>> {

    class BMI160GenClass
    {
        + void begin(int mode, int pin)
    }

    class CurieIMUClass
    {
        + void getGyro(int& xAxis, int& yAxis, int& zAxis)
        + void getAccel(int& xAxis, int& yAxis, int& zAxis)
    }
    CurieIMUClass <|-- BMI160GenClass
    
    class BMI160Class
    {
        + void getGyro(int& xAxis, int& yAxis, int& zAxis)
        + void getAccel(int& xAxis, int& yAxis, int& zAxis)
    }
    BMI160Class <|-- CurieIMUClass
}
AccelGyroDetector -- BMI160GenClass : use 


enum StateType
{
    INTERFACE
    MOUSE
    GAMEPAD
}

enum DetectorType
{
	BUTTON,
    JOYSTICK,
    ACCELEROMETER,
    ACCELGYRO
}

class Context
{
	+ void addDetectors(DetectorType* detectors)
    + void detectActions(IAction* action)
    + void changeState(StateType newState)
    + IBleController* getBleController()
    - IState*
}
Context -left- IState
Context -up- StateType
Context -up- DetectorType
Context -right-> BleControllerFactory
Context "Create" ..> IDetectorFactory
Context  .left.> IAction

class ActionData
{
    + uint8_t* data
    + size_t dataSize
}

interface IAction
{
	+ virtual ActionData getActionData() = 0
}
IAction -up- ActionData

enum InterfaceMoves
{
  NONE
  UP
  DOWN
  SELECT
}

class InterfaceAction
{
}
IAction <|-down- InterfaceAction
InterfaceAction -- InterfaceMoves

class MouseAction
{
    + void rightClick(bool pressed);
    + void leftClick(bool pressed);
    + void middleClick(bool pressed);
    + void moveCursor(bool pressed);
}
IAction <|-down- MouseAction

enum Key
{
  W
  S
  A
  D
  C
  SPACE
  UP
  DOWN
  LEFT
  RIGHT
  NUMBER1
  NUMBER2
  NUMBER3
}

class GamepadAction
{
    + void pressKey(Key k)
    + void releaseKey(Key k)
}
IAction <|-down- GamepadAction
GamepadAction -- Key


interface IDetectorFactory
{
	+ virtual IDetector* createDetector(DetectorType detector) = 0
}

class InterfaceDetectorFactory
{
	
}
IDetectorFactory <|-down- InterfaceDetectorFactory
InterfaceDetectorFactory "create" ..> IDetector

class MouseDetectorFactory
{

}
IDetectorFactory <|-down- MouseDetectorFactory
MouseDetectorFactory "create" ..> IDetector

class GamepadDetectorFactory
{

}
IDetectorFactory <|-down- GamepadDetectorFactory
GamepadDetectorFactory "create" ..> IDetector

Device *-left- Context
Device "Create" .right.> BleControllerFactory

@enduml