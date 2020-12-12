#include "FSRDetector.h"

#include "DeviceLogger.h"

#include "Energia.h"

namespace Detector
{

    FSRDetector::FSRDetector(unsigned long timeBetweenDetections /*= 0*/)
        : IDetector(timeBetweenDetections)
    {
        LOG_DEBUG("FSRDetector::FSRDetector()");
    }

    bool FSRDetector::checkAction(IAction *action)
    {
        LOG_DEBUG("FSRDetector::checkAction()");

        FSRState FSRState{analogRead(fsr1Pin_), analogRead(fsr2Pin_)};
        return checkAction(FSRState, action);
    }

} // namespace Detector
