/*
  ==============================================================================

    FilterComponent.h
    Created: 9 Jun 2025 2:31:21pm
    Author:  soatm

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterComponent : public juce::Component
{
public:
    FilterComponent();
    ~FilterComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void attachToParameters(juce::AudioProcessorValueTreeState& apvts,
                           const juce::String& filterTypeSelectorId,
                           const juce::String& filterFreqId,
                           const juce::String& filterResId);
    void detachParameters();

private:
    juce::ComboBox filterTypeSelector{ "Filter Type" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeSelectorAttachment;

    juce::Slider filterFreqSlider;
    juce::Slider filterResSlider;

    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<Attachment> filterFreqAttachment;
    std::unique_ptr<Attachment> filterResAttachment;

    juce::Label filterSelectorLabel{ "Filter Type", "Filter Type" };
    juce::Label filterFreqLabel{ "Filter Freq", "Filter Freq" };
    juce::Label filterResLabel{ "Filter Res", "FilterRes" };

    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilterComponent)
};
