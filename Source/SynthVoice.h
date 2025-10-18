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
#include "PitchRackData.h"
#include "FilterData.h"

class SynthVoice : public juce::SynthesiserVoice {

public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;

    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;

    void stopNote(float velocity, bool allowTailOff) override;

    void controllerMoved(int controllerNumber, int newControllerValue) override;

    void pitchWheelMoved(int newPitchWheelValue) override;

    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);

    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

    void update(const float attack1, const float attack2, 
                const float decay1, const float decay2,
                const float sustain1, const float sustain2,
                const float release1, const float release2,
                const float mGainLinear1, const float mGainLinear2 ,
                const float pRackO1, const float pRackO2,
                const float pRackS1, const float pRackS2);


    FilterData& getFilter1() { return filter1; };
    OscData& getOscillator1() { return osc1; };

    FilterData& getFilter2() { return filter2; };
    OscData& getOscillator2() { return osc2; };

    void updateFilter(const int filterType1, const float frequency1, const float resonance1,
                      const int filterType2, const float frequency2, const float resonance2);





private:

    //Initializing the backends of all the components used in the synth.

    //Initializing the components of Oscillator 1:
    OscData osc1;
    AdsrData adsr1;
    MGainData mGain1;
    PitchRackData pRack1;
    FilterData filter1;

    //Initializing the components of Oscillator 2:
    OscData osc2;
    AdsrData adsr2;
    MGainData mGain2;
    PitchRackData pRack2;
    FilterData filter2;


    juce::AudioBuffer<float> synthBuffer;
    juce::AudioBuffer<float> osc2Buffer;
    bool isPrepared{ false };

};
