#include "AccelGyroBMI160Detector.h"

#include "DeviceLogger.h"

#include "BMI160Gen.h"
#include "WString.h"

namespace Detector
{
    AccelGyroBMI160Detector::AccelGyroBMI160Detector(unsigned long timeBetweenDetections /*= 0*/)
        : IDetector(timeBetweenDetections)
    {
        LOG_DEBUG("AccelGyroBMI160Detector::AccelGyroBMI160Detector()");

        // Iniciate BMI160 for I2C mode
        BMI160.begin(BMI160GenClass::I2C_MODE, 0x69);
        uint8_t dev_id = BMI160.getDeviceID();
        LOG_DEBUG(String("DEVICE ID: ") + String(dev_id, HEX));

        // Set the accelerometer range to 250 degrees/second
        BMI160.setGyroRange(250);
        LOG_DEBUG("Initializing IMU device...done.");
    }

    bool AccelGyroBMI160Detector::checkAction(IAction *action)
    {
        LOG_DEBUG("AccelGyroBMI160Detector::checkAction()");

        // Reads Gyro and Accelerometer values
        AccelGyroState accelGyroState;
        BMI160.readAccelerometer(accelGyroState.xAccel, accelGyroState.yAccel, accelGyroState.zAccel);
        BMI160.readGyro(accelGyroState.xGyro, accelGyroState.yGyro, accelGyroState.zGyro);

        // Map value to detector limits
        accelGyroState.xAccel = map(accelGyroState.xAccel, -maxSensorValue_, maxSensorValue_, -maxMappedValue_,
                                    maxMappedValue_);
        accelGyroState.yAccel = map(accelGyroState.yAccel, -maxSensorValue_, maxSensorValue_, -maxMappedValue_,
                                    maxMappedValue_);
        accelGyroState.zAccel = map(accelGyroState.zAccel, -maxSensorValue_, maxSensorValue_, -maxMappedValue_,
                                    maxMappedValue_);
        accelGyroState.xGyro = map(accelGyroState.xGyro, -maxSensorValue_, maxSensorValue_, -maxMappedValue_,
                                   maxMappedValue_);
        accelGyroState.yGyro = map(-accelGyroState.yGyro, -maxSensorValue_, maxSensorValue_, -maxMappedValue_,
                                   maxMappedValue_);
        accelGyroState.zGyro = map(accelGyroState.zGyro, -maxSensorValue_, maxSensorValue_, -maxMappedValue_,
                                   maxMappedValue_);

        return checkAction(accelGyroState, action);
    }

} // namespace Detector
