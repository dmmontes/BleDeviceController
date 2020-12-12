
#ifndef FSR_DETECTOR
#define FSR_DETECTOR

#include "IDetector.h"

namespace Detector
{

    /**
     * @brief Represents 2 FSR detectors of user's actions
     */
    class FSRDetector : public IDetector
    {
    public:
        /**
         * @brief Construct a new FSR Detector object
         * 
         * @param timeBetweenDetections Turns between 2 consecutive detections
         */
        FSRDetector(unsigned long timeBetweenDetections = 0);

        ///< Implementation of virtual methods from IDetector
        virtual bool checkAction(IAction *action) override;

    protected:
        /**
         * @brief Represents the state of the FSR 
         */
        struct FSRState
        {
            uint16_t fsr1; ///< Value of fsr detector 1 (0-1024)
            uint16_t fsr2; ///< Value of fsr detector 2 (0-1024)
        };

        /**
         * @brief Detect user action given the FSR state
         * 
         * @param FSRState state of the FSR
         * @param action[out] action to be filled by detector
         * @return bool Indicates if an action has been detected
         */
        virtual bool checkAction(const FSRState &FSRState, IAction *action) = 0;

    private:
        const uint8_t fsr1Pin_ = 27; // the number of the FSR 1 pin
        const uint8_t fsr2Pin_ = 28; // the number of the FSR 2 pin
    };

} // namespace Detector

#endif //FSR_DETECTOR
