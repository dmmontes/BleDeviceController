
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
            NORMAL, // Normal detection, use of simple functions, linears, etc
            QUALITY // Quality detection, complex funcion, polynomials,
        };

        /**
         * @brief Set the Detection Type of detecotr
         * 
         * @param detectionType Type of detection
         */
        virtual void setDetectionType(DetectionType detectionType) {}

        /**
         * @brief General process of the device, detecting actions performed by user 
         * 
         * @param action[out] action to be filled by detector
         * @return bool Indicates if an action has been detected
         */
        virtual bool detectAction(IAction *action) = 0;
    };

    typedef IDetector *DetectorPtr; ///< Vector of pointers to IDetector objects

} // namespace Detector

#endif //I_DETECTOR
