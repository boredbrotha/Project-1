/*
  ==============================================================================

    MGainComponent.h
    Created: 5 Mar 2025 6:24:53pm
    Author:  soatm

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class MGainComponent  : public juce::Component
{
public:
    MGainComponent(juce::AudioProcessorValueTreeState& apvts);
    ~MGainComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    juce::Slider mSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MGainComponent)
};
