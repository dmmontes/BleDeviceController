@startuml

[*] -> PowerState1 : Initial State
PowerState1 -right-> PowerState2 : No action detected in 10s
PowerState2 -left-> PowerState1 : Detected 3 actions in 5s
PowerState2 -right-> PowerState3 : No action detected in 10s
PowerState3 -left-> PowerState2 : Detected 2 actions in 3s
PowerState3 -right-> PowerState4 : No action detected in 10s
PowerState4 -right-> PowerState3 : ButtonPressed

@enduml