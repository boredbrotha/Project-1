/*
  ==============================================================================

    MGainData.h
    Created: 16 Apr 2025 8:18:22pm
    Author:  soatm

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class MGainData : public juce::dsp::Gain<float> {

public:
    void updateMGain(const float mGainlinear);
    
};