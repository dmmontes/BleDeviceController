
#ifndef ACCEL_GYRO_BMI160_DETECTOR
#define ACCEL_GYRO_BMI160_DETECTOR

#include "IDetector.h"

namespace Detector
{

    /**
     * @brief Represents a accelerometer-gyroscope (BMI160) detector of user's actions
     */
    class AccelGyroBMI160Detector : public IDetector
    {
    public:
        /**
         * @brief Construct a new AccelGyroBMI160Detector Detector object
         * 
         * @param timeBetweenDetections Turns between 2 consecutive detections
         */
        AccelGyroBMI160Detector(unsigned long timeBetweenDetections = 0);

        ///< Implementation of virtual methods from IDetector
        virtual bool checkAction(IAction *action) override;

    protected:
        /**
         * @brief Represents the state of the accelerometer-gyroscope 
         */
        struct AccelGyroState
        {
            int xAccel; ///< Value of x Axis Accelerometer
            int yAccel; ///< Value of y Axis Accelerometer
            int zAccel; ///< Value of z Axis Accelerometer

            int xGyro; ///< Value of x Axis Gyroscope
            int yGyro; ///< Value of y Axis Gyroscope
            int zGyro; ///< Value of z Axis Gyroscope
        };

        /**
         * @brief Detect user action given the accelerometer-gyroscope state
         * 
         * @param accelGyroState state of the accelerometer-gyroscope
         * @param action[out] action to be filled by detector
         * @return bool Indicates if an action has been detected
         */
        virtual bool checkAction(const AccelGyroState &accelGyroState, IAction *action) = 0;

    private:
        const uint16_t maxSensorValue_{32768}; ///< Maximum value read by sensor
        const uint16_t maxMappedValue_{512};   ///< Maximos value mapped to detect movements
    };

} // namespace Detector

#endif //ACCEL_GYRO_BMI160_DETECTOR
