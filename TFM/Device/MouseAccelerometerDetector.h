
#ifndef MOUSE_ACCELEROMETER_DETECTOR
#define MOUSE_ACCELEROMETER_DETECTOR

#include "AccelerometerDetector.h"

namespace Detector
{

    /**
     * @brief Represents a accelerometer detector for a mouse action
     */
    class MouseAccelerometerDetector : public AccelerometerDetector
    {
    public:
        /**
         * @brief Construct a new Mouse Accelerometer Detector object
         */
        MouseAccelerometerDetector();

    protected:
        ///< Implementation of virtual methods from JoystickDetector
        virtual bool checkAction(const AccelerometerState &accelerometerState, IAction *action) override;

    private:
        /**
         * @brief Detect if axisValue represents an scroll movement
         * 
         * @param scrollMove Scroll value detected in accelerometer's axis
         * @param scrollLimitValue Limit value (in axis) for scrolling
         * @return uint8_t Scroll movement, from 1 to mouseScrollLimit
         */
        uint8_t detectScroll(int16_t scrollMove, uint16_t scrollMoveLimit);

        const uint16_t analogReadLimit_{1024}; ///< Maximum analog value read
        const uint16_t scrollDownLimit_{500};  ///< Limit value in yAxis to considere a scroll down movement
        const uint16_t scrollUpLimit_{500};    ///< Limit value in zAxis to considere a scroll up movement
        const uint8_t mouseScrollLimit_{5};    ///< Limit mouse value scrolling down/up

        ///< Limit scroll down moving value
        const uint16_t scrollDownMoveLimit_{static_cast<uint16_t>(analogReadLimit_ - scrollDownLimit_)};
        ///< Limit scroll up moving value
        const uint16_t scrollUpMoveLimit_{static_cast<uint16_t>(analogReadLimit_ - scrollUpLimit_)};
    };

} // namespace Detector

#endif //MOUSE_ACCELEROMETER_DETECTOR
