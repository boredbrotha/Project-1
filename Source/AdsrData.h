/*
  ==============================================================================

    AdsrData.h
    Created: 24 Feb 2025 2:07:49pm
    Author:  soatm

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
class AdsrData : public juce::ADSR {

public:
    void updateADSR(const float attack, const float decay, const float sustain, const float release);

private:
    juce::ADSR::Parameters adsrParams;



};