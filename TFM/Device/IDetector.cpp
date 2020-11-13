#include "IDetector.h"

#include "DeviceLogger.h"

namespace Detector
{

    IDetector::IDetector(uint8_t turnsBetweenDetections /*= 0*/, uint8_t turnsToDetect /*= 0*/)
        : turnsToDetect_(turnsToDetect), turnsBetweenDetections_(turnsBetweenDetections)
    {
        LOG_DEBUG("IDetector::IDetector()");
    }

    bool IDetector::detectAction(IAction *action)
    {
        LOG_DEBUG("IDetector::detectAction()");
        bool actionDetected{false};

        // Check if it is turn to detect
        if (turnsToDetect_ == 0)
        {
            //If an action is detected resest the "turnsToDetect"
            actionDetected = checkAction(action);
            if (actionDetected)
            {
                turnsToDetect_ = turnsBetweenDetections_;
            }
        }
        else
        {
            --turnsToDetect_;
        }
        return actionDetected;
    }

} // namespace Detector