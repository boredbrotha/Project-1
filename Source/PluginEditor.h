/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "OscComponent.h"
#include "AdsrComponent.h"
#include "MGainComponent.h"
#include "PitchRackComponent.h"
#include "FilterComponent.h"

//==============================================================================
/**
*/
class Project1AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Project1AudioProcessorEditor (Project1AudioProcessor&);
    ~Project1AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void switchToOscillator(int oscNum);
    void savePresetButtonClicked();
    void loadPresetButtonClicked();

    int currentOscillator = 0;  // Initialize to 0 so first switchToOscillator(1) call works

    juce::TextButton osc1Button {"1"};
    juce::TextButton osc2Button {"2"};
    juce::TextButton savePresetButton {"Save"};
    juce::TextButton loadPresetButton {"Load"};

    Project1AudioProcessor& audioProcessor;

    MGainComponent mGain;

    OscComponent osc;

    AdsrComponent adsr;

    PitchRackComponent pitchR;

    FilterComponent filter;



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Project1AudioProcessorEditor)
};
