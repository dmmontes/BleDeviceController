#include "VoiceDetector.h"

#include "DeviceLogger.h"

#include "Energia.h"

namespace Detector
{

    VoiceDetector::VoiceDetector(unsigned long timeBetweenDetections /*= 0*/)
        : IDetector(timeBetweenDetections)
    {
        pinMode(microphonePin_, INPUT);
        delay(500);

        // Calibrate Background sound
        for (uint8_t i = 0; i < calibrationSamples_; ++i)
        {
            backgroundSound_ += readMicrophone();
        }
        backgroundSound_ /= calibrationSamples_;

        LOG_DEBUG(String("VoiceDetector::VoiceDetector() backgroundSound: ") + String(backgroundSound_));
    }

    bool VoiceDetector::checkAction(IAction *action)
    {
        LOG_DEBUG("VoiceDetector::checkAction()");

        Words word{Words::UNKNOWN};
        if (isSoundDetected())
        {
            captureWord();

            float samples[numberOfSamples_];
            for (uint16_t i = 0; i < numberOfSamples_; i++)
            {
                samples[i] = samples_[i];
            }
            word = translateWord(svmModel_.predictLabel(samples));
        }

        return checkAction(word, action);
    }

    int16_t VoiceDetector::readMicrophone() const
    {
        int16_t value{static_cast<int16_t>((analogRead(microphonePin_) - middleMicrophoneValue_) >> 2)};
        LOG_DEBUG(String("VoiceDetector::readMicrophone() value: ") + String(value));
        return value;
    }

    bool VoiceDetector::isSoundDetected() const
    {
        bool detected{abs(readMicrophone() - backgroundSound_) >= soundTreshold_};
        LOG_DEBUG(String("VoiceDetector::isSoundDetected() soundDetected: ") + String(detected));
        return detected;
    }

    void VoiceDetector::captureWord()
    {
        LOG_DEBUG("VoiceDetector::captureWord()");

        // Capture samples
        for (uint8_t i = 0; i < numberOfSamples_; ++i)
        {
            timeToNextSampling_ = micros() + samplingPeriod_;
            samples_[i] = readMicrophone();

            while (micros() < timeToNextSampling_)
            {
            };
        }

        // Performs the fast fourier transform
        fastFourierTransform_.Windowing(samples_, numberOfSamples_, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    }

    VoiceDetector::Words VoiceDetector::translateWord(String detectedWord)
    {
        LOG_DEBUG(String("VoiceDetector::translateWord() detectedWord") + detectedWord);

        if (detectedWord == "pause")
        {
            return Words::PAUSE;
        }
        else if (detectedWord == "start")
        {
            return Words::START;
        }
        return Words::UNKNOWN;
    }

} // namespace Detector
