
#ifndef ACCELEROMETER_DETECTOR
#define ACCELEROMETER_DETECTOR

#include "IDetector.h"

namespace Detector
{

    /**
     * @brief Represents a accelerometer detector of user's actions
     */
    class AccelerometerDetector : public IDetector
    {
    public:
        /**
         * @brief Construct a new Accelerometer Detector object
         * 
         * @param timeBetweenDetections Turns between 2 consecutive detections
         */
        AccelerometerDetector(unsigned long timeBetweenDetections = 0);

        ///< Implementation of virtual methods from IDetector
        virtual bool checkAction(IAction *action) override;

    protected:
        /**
         * @brief Represents the state of the accelerometer 
         */
        struct AccelerometerState
        {
            uint16_t xAxis; ///< Value of x Axis (0-1024)
            uint16_t yAxis; ///< Value of y Axis (0-1024)
            uint16_t zAxis; ///< Value of z Axis (0-1024)
        };

        /**
         * @brief Detect user action given the accelerometer state
         * 
         * @param accelerometerState state of the accelerometer
         * @param action[out] action to be filled by detector
         * @return bool Indicates if an action has been detected
         */
        virtual bool checkAction(const AccelerometerState &accelerometerState, IAction *action) = 0;

    private:
        const uint8_t xAxisPin_ = 23; // the number of the accelerometer X-axis pin in MKII
        const uint8_t yAxisPin_ = 24; // the number of the accelerometer Y-axis pin in MKII
        const uint8_t zAxisPin_ = 25; // the number of the accelerometer X-axis pin in MKII
    };

} // namespace Detector

#endif //ACCELEROMETER_DETECTOR
