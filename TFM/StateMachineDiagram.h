@startuml

state BondedDevice <<choice>>
state Pin <<choice>>

[*] -> InterfaceState
InterfaceState --> BluetoothState : Selected
BluetoothState --> BluetoothConnectionStateSearching : Search device
BluetoothConnectionStateSearching --> BluetoothConnectionStateConnecting : Connecting Device
BluetoothConnectionStateConnecting --> BondedDevice : Check bonded
BondedDevice --> BluetoothConnectionStatePairing : [Not bonded]
BluetoothConnectionStatePairing --> Pin : Check Security Pin
Pin --> BluetoothConnectionStateSearching : Incorrect Pin
Pin --> BluetoothConnectionStateConnected : Correct Pin
BondedDevice --> BluetoothConnectionStateConnected : [Bonded]
BluetoothConnectionStateConnected --> BluetoothConnectionStateSearching : LostConnection

@enduml