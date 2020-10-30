
#ifndef DEVICE_LOGGER
#define DEVICE_LOGGER

#include <cstdint>

#include "WString.h"

/**
 * @brief Class for logging messages
 */
class DeviceLogger
{
public:
    /**
     * @brief Level of verbosity of logs
     */
    enum class Verbosity : uint8_t
    {
        NONE = 0, ///< Logs are not shown
        ERROR,    ///< Only print error logs
        WARNING,  ///< Print warning and error logs
        DEBUG     ///< Print all types of errors
    };

    /**
     * @brief Set the Verbosity of logging
     * 
     * @param verbosity Verbosity of logging
     */
    static void setVerbosity(Verbosity verbosity);

    /**
     * @brief Get the singleton Instance of the class
     * 
     * @return DeviceLogger& Reference to DeviceLogger
     */
    static DeviceLogger &getInstance();

    /**
     * @brief Log a  message
     * 
     * @param verbosity verbosity of the message
     * @param message message dto be logged
     */
    void logMessage(Verbosity verbosity, const String &message);

protected:
    static Verbosity VERBOSITY;     ///< Level of verbosity logging
    static bool SERIAL_INITIALIZED; ///< Indicates if serial has been initilized
};

#define LOG_DEBUG(message) (DeviceLogger::getInstance().logMessage(DeviceLogger::Verbosity::DEBUG, String("DEBUG: ") + message))
#define LOG_WARNING(message) (DeviceLogger::getInstance().logMessage(DeviceLogger::Verbosity::WARNING, String("WARNING: ") + message))
#define LOG_ERROR(message) (DeviceLogger::getInstance().logMessage(DeviceLogger::Verbosity::ERROR, String("ERROR: ") + message))

#endif //DEVICE_LOGGER
