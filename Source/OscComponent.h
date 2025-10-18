/*
  ==============================================================================

    OscComponent.h
    Created: 19 Feb 2025 7:05:12pm
    Author:  soatm

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscComponent  : public juce::Component
{
public:
    OscComponent();
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void attachToParameters(juce::AudioProcessorValueTreeState& apvts, const juce::String& waveSelectorId);
    void detachParameters();

private:

    juce::ComboBox oscWaveSelector;
    juce::Label oscLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachment;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
