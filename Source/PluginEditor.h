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
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Project1AudioProcessor& audioProcessor;

    MGainComponent mGain;

    OscComponent osc;

    AdsrComponent adsr;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscSelAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Project1AudioProcessorEditor)
};
