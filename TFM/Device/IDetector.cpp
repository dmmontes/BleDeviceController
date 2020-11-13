#include "IDetector.h"

#include "DeviceLogger.h"

#include "Energia.h"

namespace Detector
{

    IDetector::IDetector(unsigned long timeBetweenDetections /*= 0*/)
        : timeToDetect_(0), timeBetweenDetections_(timeBetweenDetections)
    {
        LOG_DEBUG("IDetector::IDetector()");
    }

    bool IDetector::detectAction(IAction *action)
    {
        LOG_DEBUG("IDetector::detectAction()");
        bool actionDetected{false};

        // Check if it is turn to detect
        unsigned long actualTime = millis();
        if (timeToDetect_ < actualTime)
        {
            //If an action is detected resest the "turnsToDetect"
            actionDetected = checkAction(action);
            if (actionDetected)
            {
                timeToDetect_ = actualTime + timeBetweenDetections_;
            }
        }
        return actionDetected;
    }

} // namespace Detector
