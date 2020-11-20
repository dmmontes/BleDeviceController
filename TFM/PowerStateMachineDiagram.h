@startuml

[*] -> PowerState1 : Initial State
PowerState1 --> PowerState2 : TimesWithoutDetecting > 10
PowerState2 --> PowerState1 : TimesDetecting > 5
PowerState2 --> PowerState3 : TimesWithoutDetecting > 20
PowerState3 --> PowerState2 : TimesDetecting > 3
PowerState3 --> PowerState4 : TimesWithoutDetecting > 10
PowerState4 --> PowerState3 : ButtonPressed

@enduml