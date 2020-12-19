@startuml

[*] --> PowerState1 : Initial State
PowerState1 --> PowerState2 : No action detected in 10s
PowerState2 -up-> PowerState1 : Detected action
PowerState2 -right-> PowerState3 : No action detected in 10s
PowerState3 -up-> PowerState1 : Detected action
PowerState3 -right-> PowerState4 : No action detected in 10s
PowerState4 -up-> PowerState1 : ButtonPressed

@enduml