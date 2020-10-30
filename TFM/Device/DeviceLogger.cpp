#include "DeviceLogger.h"

#include "Energia.h"

DeviceLogger::Verbosity DeviceLogger::VERBOSITY{Verbosity::NONE};
bool DeviceLogger::SERIAL_INITIALIZED{false};

void DeviceLogger::setVerbosity(Verbosity verbosity)
{
    if (!SERIAL_INITIALIZED)
    {
        Serial.begin(9600);
        SERIAL_INITIALIZED = true;
    }
    VERBOSITY = verbosity;
    getInstance().logMessage(DeviceLogger::Verbosity::DEBUG, String("DeviceLogger::setVerbosity(): ") + String(static_cast<uint8_t>(verbosity)));
}

DeviceLogger &DeviceLogger::getInstance()
{
    static DeviceLogger deviceLogger; ///< Singleton, pointer to the object
    return deviceLogger;
}

void DeviceLogger::logMessage(Verbosity verbosity, const String &message)
{
    if (verbosity <= VERBOSITY)
    {
        Serial.println(message);
    }
}
