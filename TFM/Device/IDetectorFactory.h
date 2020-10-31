
#ifndef I_DETECTOR_FACTORY
#define I_DETECTOR_FACTORY

#include "IDetector.h"

namespace Detector
{
    /**
     * @brief Factory of IDetectors.
     */
    class IDetectorFactory
    {
    public:
        /**
         * @brief Type of detector factory
         */
        enum class DetectorFactory : uint8_t
        {
            MOUSE ///< Mouse Detector Factory
        };

        /**
         * @brief Type of detector 
         */
        enum class DetectorType : uint8_t
        {
            BUTTON,   ///< Button detector
            JOYSTICK, ///< Joystick detecktor
        };

        /**
         * @brief Destroy the IDetectorFactory object
         */
        virtual ~IDetectorFactory();

        /**
         * @brief Create a vector of pointer to IDetector
         * 
         * @param detectorTypes vector of Types of Detectors
         * @param numDetectors number of detectors
         * @return DetectorPtr* vector of pointers to IDetector
         */
        DetectorPtr *createDetectors(DetectorType *detectorTypes, size_t numDetectors);

        /**
         * @brief Delete a Detector object
         * 
         * @param detector vector of pointers to IDetector
         */
        void deleteDetectors(DetectorPtr *detectors);

    protected:
        /**
         * @brief Free allocated memory for detectors
         */
        void freeDetectors();

        /**
         * @brief Create a Button Detector object
         * 
         * @return DetectorPtr Pointer to Button Detector object
         */
        virtual DetectorPtr createButtonDetector() = 0;

        /**
         * @brief Create a Joystick Detector object
         * 
         * @return DetectorPtr Pointer to Joystick Detector object
         */
        virtual DetectorPtr createJoystickDetector() = 0;

    private:
        DetectorPtr *detectors_{nullptr}; ///< Vector of pointers to IDetector
        size_t numDetectors_{0};          ///< Number of detectors
    };

} // namespace Detector

#endif //I_DETECTOR_FACTORY
