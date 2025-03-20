/*
  ==============================================================================

    OscData.h
    Created: 19 Feb 2025 7:09:24pm
    Author:  soatm

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
class OscData : public juce::dsp::Oscillator<float> {
public:
    void setWaveType(const int choice);

    void prepareToPlay(juce::dsp::ProcessSpec spec);


    void setWaveFrequency(const int midiNoteNumber);
    void getNextAudioBlock(juce::dsp::AudioBlock<float>& block);

private:
};
