/*
  ==============================================================================

    SynthSound.h
    Created: 22 Feb 2025 5:08:12pm
    Author:  soatm

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound {

public: 
    bool appliesToNote(int midiNoteNumber) override { return true; };
    bool appliesToChannel(int midiChannel) override { return true; };

};