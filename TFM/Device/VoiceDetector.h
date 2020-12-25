
#ifndef VOICE_DETECTOR
#define VOICE_DETECTOR

#include "arduinoFFT.h"
#include "IDetector.h"
#include "model.h"

namespace Detector
{

    /**
     * @brief Represents a Voice detector of user's actions
     */
    class VoiceDetector : public IDetector
    {
    public:
        /**
         * @brief Construct a new Voice Detector object
         * 
         * @param timeBetweenDetections Turns between 2 consecutive detections
         */
        VoiceDetector(unsigned long timeBetweenDetections = 0);

        ///< Implementation of virtual methods from IDetector
        virtual bool checkAction(IAction *action) override;

    protected:
        /**
         * @brief Represents the recognized words by detector
         */
        enum class Words
        {
            START,  ///< "Start" word
            PAUSE,  ///< "Pause" word
            UNKNOWN ///< "Unknown" word
        };

        /**
         * @brief Detect user action given the Voice state
         * 
         * @param detectedWord detected word
         * @param action[out] action to be filled by detector
         * @return bool Indicates if an action has been detected
         */
        virtual bool checkAction(const Words &detectedWord, IAction *action) = 0;

    private:
        /**
         * @brief Read the microphone value and mapping to range of [-127, 127]
         * 
         * @return int16_t microphone value
         */
        int16_t readMicrophone() const;

        /**
         * @brief Indicates if a sound has been detected 
         * 
         * @return true if a sound has been detected, false otherwise
         */
        bool isSoundDetected() const;

        /**
         * @brief Records samples of sound and capture the word
         */
        void captureWord();

        /**
         * @brief Translates the word detected from model (string) to a enumerator
         * 
         * @param detectedWord Detected word from model
         * @return Words Enumerator word
         */
        Words translateWord(String detectedWord);

        arduinoFFT fastFourierTransform_;  ///< Object to perform Fast-Fourier-Transforms
        Eloquent::ML::Port::SVM svmModel_; ///< Trained model based in support vector machine

        const uint8_t calibrationSamples_{200};     ///< Number of samples for calibration
        const uint16_t middleMicrophoneValue_{512}; ///< Middle value of microphone detector
        const uint8_t microphonePin_{6};            ///< Pin number variable for microphone in MKII
        int32_t backgroundSound_{0};                ///< Background sound of the microphone

        const uint8_t numberOfSamples_{64};     ///< Number of samples for the word detection
        const uint16_t samplingFrequency_{128}; ///< Frequency of sampling
        const uint8_t soundTreshold_{10};       ///< Treshold to considerer a sound
        double samples_[64];                    ///< Value of each sample

        const uint16_t samplingPeriod_{0};    ///< Duration of sampling in micro seconds
        unsigned long timeToNextSampling_{0}; ///< Time to do the next sampling
    };

} // namespace Detector

#endif //VOICE_DETECTOR
