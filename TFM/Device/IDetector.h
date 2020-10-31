
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
         * @brief General process of the device, detecting actions performed by user 
         * 
         * @param action[out] action to be filled by detector
         */
        virtual void detectAction(IAction *action) = 0;
    };

    typedef IDetector *DetectorPtr; ///< Vector of pointers to IDetector objects

} // namespace Detector

#endif //I_DETECTOR
