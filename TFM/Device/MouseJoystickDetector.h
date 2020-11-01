
#ifndef MOUSE_JOYSTICK_DETECTOR
#define MOUSE_JOYSTICK_DETECTOR

#include "JoystickDetector.h"

namespace Detector
{

    /**
     * @brief Represents a joystick detector for a mouse action
     */
    class MouseJoystickDetector : public JoystickDetector
    {
    protected:
        ///< Implementation of virtual methods from JoystickDetector
        virtual void setDetectionType(IDetector::DetectionType detectionType) override;
        virtual bool detectAction(const JoystickState &joystickState, IAction *action) override;

    private:
        typedef int16_t (MouseJoystickDetector::*MapAxisToCursor)(int16_t); ///< Function to map from axis to cursor values
        /**
         * @brief Linear function to map from axis to cursor values
         * 
         * @param axisValue Value detected in joystick's axis
         * @return int16_t Mapped value to cursor's scale
         */
        int16_t linearMapAxisToCursor(int16_t axisValue);

        /**
         * @brief Polynomial function to map from axis to cursor values
         * 
         * @param axisValue Value detected in joystick's axis
         * @return int16_t Mapped value to cursor's scale
         */
        int16_t PolyMapAxisToCursor(int16_t axisValue);

        MapAxisToCursor mapAxisToCursor_ = &MouseJoystickDetector::linearMapAxisToCursor; ///< Function to map from axis to cursor values
        const uint16_t middleAxisValue_{512};                                             ///< Middle value of axis (0-1024)
        const uint16_t axisTreshold_{100};                                                ///< Minimum value to consider a movement in axis
        const uint16_t axisMoveLimit_{middleAxisValue_ - axisTreshold_};                  ///< Maximum absolute value of axis's movement
        const uint8_t mouseMoveLimit_{5};                                                 ///< Maximum absolute value of mouse's movement
        uint8_t buttonState{1};                                                           ///< State of the button (0 press, 1 released)
    };

} // namespace Detector

#endif //MOUSE_JOYSTICK_DETECTOR
