
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
        virtual bool checkAction(const JoystickState &joystickState, IAction *action) override;

    private:
        /**
         * @brief Detect if axisValue represents a mouse movement
         * 
         * @param axisMove Move value detected in joystick's axis
         * @return int8_t Mouse movement, from 0 to mouseMoveLimit_
         */
        int8_t detectMouseMovement(int16_t axisMove);

        ///< Function to map from axis to cursor values
        typedef int16_t (MouseJoystickDetector::*MapAxisToCursor)(int16_t);

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

        ///< Function to map from axis to cursor values
        MapAxisToCursor mapAxisToCursor_ = &MouseJoystickDetector::linearMapAxisToCursor;

        // Linear mapping values
        const uint16_t middleAxisValue_{512}; ///< Middle value of axis (0-1024)
        const uint16_t axisTreshold_{100};    ///< Minimum value for a movement in axis

        ///< Maximum absolute value of axis's movement
        const uint16_t axisMoveLimit_{static_cast<uint16_t>(middleAxisValue_ - axisTreshold_)};
        const uint8_t mouseMoveLimit_{5}; ///< Maximum absolute value of mouse's movement

        // Polynomial grade 2 mapping values (maps to mouseMoveLimit_)
        const float polyA_{0.0000257187};  ///< A value in a polynomial function (ax2 + bx + c)
        const float polyB_{-0.0009004226}; ///< B value in a polynomial function (ax2 + bx + c)
        const float polyC_{1.148687};      ///< C value in a polynomial function (ax2 + bx + c)

        uint8_t buttonPressed_{0}; ///< State of the button (0 press, 1 released)
    };

} // namespace Detector

#endif //MOUSE_JOYSTICK_DETECTOR
