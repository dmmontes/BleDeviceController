#include <arduinoFFT.h>
// uncomment when doing classification
#include "model.h"
#define MIC 6
#define NUM_SAMPLES 64
#define SAMPLING_FREQUENCY 128
#define SOUND_THRESHOLD 10

unsigned int samplingPeriod;
unsigned long microSeconds;

int32_t backgroundSound;
double features[NUM_SAMPLES];
float featuresF[NUM_SAMPLES];
arduinoFFT fft;
Eloquent::ML::Port::SVM svm;

void setup() {
    Serial.begin(9600);
    pinMode(MIC, INPUT);

    samplingPeriod = round(1000000*(1.0/SAMPLING_FREQUENCY));
    calibrate();

}

void loop() {
    if (!soundDetected()) {
        delay(10);
        return;
    }

    captureWord();
    printFeatures();

// uncomment when doing classification
    for (uint16_t i = 0; i < NUM_SAMPLES; i++) {
        featuresF[i] = features[i];
    }
    Serial.print("You said ");
    Serial.println(svm.predictLabel(featuresF));

    delay(1000);

}

/**

    Get analog readings
    @return
    */
int16_t readMic() {
    return (analogRead(MIC) - 512) >> 2;
}

/**

    Get "ambient" volume
    */
void calibrate() {
    for (int i = 0; i < 200; i++)
        backgroundSound += readMic();

    backgroundSound /= 200;

    Serial.print("Threshold set at ");
    Serial.println(backgroundSound);
}

bool soundDetected() {
    return abs(readMic() - backgroundSound) >= SOUND_THRESHOLD;
}

void captureWord() {
        // tone(40, 4699, 10); 
    for (uint16_t i = 0; i < NUM_SAMPLES; i++) {
        microSeconds = micros();
        features[i] = readMic();

        while(micros() < (microSeconds + samplingPeriod));
    }
        // tone(40, 4699, 100);

    fft.Windowing(features, NUM_SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);

}

void printFeatures() {
    const uint16_t numFeatures = sizeof(features) / sizeof(double);

    for (int i = 0; i < numFeatures; i++) {
        Serial.print(features[i]);
        Serial.print(i == numFeatures - 1 ? '\n' : ',');
    }

}