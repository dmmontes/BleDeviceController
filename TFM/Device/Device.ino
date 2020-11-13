#include "DeviceLogger.h"
#include "BleControllerFactory.h"
#include "DeviceContext.h"

Ble::BleControllerFactory bleControllerFactory;
DeviceContext deviceContext(bleControllerFactory);

void setup()
{
  DeviceLogger::setVerbosity(DeviceLogger::Verbosity::WARNING);
  deviceContext.changeState(DeviceContext::StateType::INTERFACE);
}

// the loop routine runs over and over again forever as a task.
void loop()
{
  deviceContext.detectAction();
}
