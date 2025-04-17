/*
  ==============================================================================

    SynthVoice.h
    Created: 22 Feb 2025 5:08:21pm
    Author:  soatm

  ==============================================================================
*/

#pragma once
 
#include <JuceHeader.h>
#include "SynthSound.h"
#include "AdsrData.h"
#include "OscData.h"
#include "MGainData.h"

class SynthVoice : public juce::SynthesiserVoice {

public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;

    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;

    void stopNote(float velocity, bool allowTailOff) override;

    void controllerMoved(int controllerNumber, int newControllerValue) override;

    void pitchWheelMoved(int newPitchWheelValue) override;

    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);

    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

    void update(const float attack, const float decay, const float sustain, const float release, const float mGainLinear);

    OscData& getOscillator() { return osc; };


private:
    OscData osc;
    AdsrData adsr;
    juce::AudioBuffer<float> synthBuffer;
    MGainData mGain;
    bool isPrepared{ false };

};
