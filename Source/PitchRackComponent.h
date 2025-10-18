/*
  ==============================================================================

    PitchRackComponent.h
    Created: 6 May 2025 2:15:41pm
    Author:  soatm

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class PitchRackComponent  : public juce::Component
{
public:
    PitchRackComponent(juce::AudioProcessorValueTreeState& apvts);
    ~PitchRackComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void attachToParameters(juce::AudioProcessorValueTreeState& apvts,
                           const juce::String& octaveId,
                           const juce::String& semitoneId);
    void detachParameters();

private:

    void setPitchParams(juce::Slider& slider);

    juce::Slider octaveSlider;
    juce::Slider semitoneSlider;
    juce::Label octaveLabel;
    juce::Label semitoneLabel;

    using pSliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<pSliderAttachment> octaveAttachment;
    std::unique_ptr<pSliderAttachment> semitoneAttachment;



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PitchRackComponent)
};
