@startuml
skinparam SequenceGroupBodyBackGroundColor transparent

box "Usuario" #LightBlue
actor Usuario
end box

box "Controlador" #LightGreen
participant Controlador
participant Procesador
participant MóduloBluetooth 
end box


box "Ordenador" #LightSalmon
participant ReceptorBluetooth 
participant Ordenador
participant VideoJuego
end box


activate Usuario
Usuario -> Controlador : Encender Controlador
note left
Iniciar Dispositivo
Controlador
end note

activate Controlador
Controlador -> Usuario: Interfaz Iniciada
Usuario -> Controlador : Elegir Modo

Controlador -> Procesador : Procesar Modo
activate Procesador
Procesador -> MóduloBluetooth : Configurar Servicios GATT
activate MóduloBluetooth 
MóduloBluetooth -> Procesador : Bluetooth Activo

Procesador -> Usuario: Modo Selecionado Correctamente
deactivate Procesador


Usuario -> Ordenador : Conexión Bluetooth
note left
Emparejar Dispositivos
Bluetooth
end note
activate Ordenador
Ordenador -> ReceptorBluetooth : Empareja Dispositivo

activate ReceptorBluetooth 
ReceptorBluetooth -> MóduloBluetooth : Empareja Dispositivo

MóduloBluetooth -> Procesador : Dispositivo Emparejado
activate Procesador
Procesador -> Controlador: Apagar Interfaz
Controlador -> Procesador: Ok
deactivate Controlador
Procesador -> MóduloBluetooth : Conexión Correcta
deactivate Procesador

MóduloBluetooth -> ReceptorBluetooth : Conexión Correcta
deactivate MóduloBluetooth 

ReceptorBluetooth -> Ordenador : Conexión Correcta
Ordenador -> Usuario : Conexión Correcta

loop  
Usuario -> Controlador : Acción 
note left
Pulsar boton, 
mover joystick,
acelerómetro, etc
end note

activate Controlador
Controlador -> Controlador : Detectar Acción
Controlador -> Procesador : Procesa Acción
deactivate Controlador

activate Procesador
Procesador -> Procesador : Traducción Acción -> \nDatos Standard BLE
Procesador -> MóduloBluetooth : Enviar Datos

activate MóduloBluetooth 
MóduloBluetooth -> ReceptorBluetooth : Enviar Características GATT \n(Vía BLE)
deactivate MóduloBluetooth 
deactivate Procesador

ReceptorBluetooth -> ReceptorBluetooth : Traduccion Característica -> \n Datos Ordenador
ReceptorBluetooth -> Ordenador : Enviar acción

alt modo == raton
Ordenador -> Ordenador : Actualizar Interfaz
else modo == gamePad
Ordenador -> VideoJuego : Procesa Acción
activate VideoJuego 
VideoJuego -> Ordenador : Actualizar Interfaz
end
Ordenador -> Usuario : Actualizar Interfaz
end

deactivate VideoJuego 
deactivate Ordenador 
deactivate ReceptorBluetooth
deactivate Usuario
@enduml