
#ifndef I_DETECTOR
#define I_DETECTOR

#include "IAction.h"

namespace Detector
{
    /**
     * @brief Represents a detector of user's actions
     */
    class IDetector
    {
    public:
        /**
         * @brief Type of detection
         */
        enum class DetectionType
        {
            QUALITY,   // Quality detection, complex funcion, polynomials
            NORMAL,    // Normal detection, use of simple functions, linears, etc
            LOW_POWER, // Low Power Mode
            SUSPEND    // Suspend mode
        };

        /**
         * @brief Destroy the IDetector object
         */
        virtual ~IDetector() = default;

        /**
         * @brief Set the Detection Type of detecotr
         * 
         * @param DetectionType Type of detection
         */
        virtual void setDetectionType(DetectionType) {}

        /**
         * @brief Detects actions performed by user if detector doesn't have to wait turns until next detection
         * 
         * @param action[out] action to be filled by detector
         * @return bool Indicates if an action has been detected
         */
        bool detectAction(IAction *action);

    protected:
        /**
         * @brief Construct a new IDetector object
         * 
         * @param timeBetweenDetections Turns between 2 consecutive detections
         */
        IDetector(unsigned long timeBetweenDetections = 0);

        /**
         * @brief Detector check if an action has been performed by the user
         * 
         * @param action[out] action to be filled by detector
         * @return bool Indicates if an action has been detected
         */
        virtual bool checkAction(IAction *action) = 0;

        unsigned long timeToDetect_;          ///< Time until next detections
        unsigned long timeBetweenDetections_; ///< Time between 2 consecutive detections in milliseconds
    };

    typedef IDetector *DetectorPtr; ///< Vector of pointers to IDetector objects

} // namespace Detector

#endif //I_DETECTOR
