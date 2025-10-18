/*
  ==============================================================================

    FilterComponent.cpp
    Created: 9 Jun 2025 2:31:21pm
    Author:  soatm

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent()
{
    juce::StringArray choices{ "Low-Pass", "Band-Pass", "High-Pass" };
    filterTypeSelector.addItemList(choices, 1);
    addAndMakeVisible(filterTypeSelector);

    // NOTE: Attachment is NOT created here - it will be created by switchToOscillator()
    // in PluginEditor to ensure proper parameter routing

    filterSelectorLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    filterSelectorLabel.setFont(15.0f);
    filterSelectorLabel.setJustificationType(juce::Justification::left);
    addAndMakeVisible(filterSelectorLabel);

    // Setup sliders UI-only (no parameter attachments)
    filterFreqSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterFreqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    filterFreqSlider.setRange(20.0, 20000.0, 0.1);
    filterFreqSlider.setSkewFactorFromMidPoint(1000.0);  // Logarithmic scale centered at 1kHz
    addAndMakeVisible(filterFreqSlider);

    filterFreqLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    filterFreqLabel.setFont(15.0f);
    filterFreqLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(filterFreqLabel);

    filterResSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterResSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    filterResSlider.setRange(1.0, 10.0, 0.1);
    addAndMakeVisible(filterResSlider);

    filterResLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    filterResLabel.setFont(15.0f);
    filterResLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(filterResLabel);
}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText("Filter", labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);
}

void FilterComponent::resized()
{
    const auto startY = 55;
    const auto sliderWidth = 100;
    const auto sliderHeight = 90;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;

    filterTypeSelector.setBounds(10, startY + 5, 90, 30);
    filterSelectorLabel.setBounds(10, startY - labelYOffset, 90, labelHeight);

    filterFreqSlider.setBounds(filterTypeSelector.getRight(), startY, sliderWidth, sliderHeight);
    filterSelectorLabel.setBounds(filterFreqSlider.getX(), filterFreqSlider.getY() - labelYOffset, filterFreqSlider.getWidth(), labelHeight);

    filterResSlider.setBounds(filterFreqSlider.getRight(), startY, sliderWidth, sliderHeight);
    filterResLabel.setBounds(filterResSlider.getX(), filterResSlider.getY() - labelYOffset, filterResSlider.getWidth(), labelHeight);
}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void FilterComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);

    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);

    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}

void FilterComponent::attachToParameters(juce::AudioProcessorValueTreeState& apvts,
                                         const juce::String& filterTypeSelectorId,
                                         const juce::String& filterFreqId,
                                         const juce::String& filterResId)
{
    filterTypeSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, filterTypeSelectorId, filterTypeSelector);
    filterFreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, filterFreqId, filterFreqSlider);
    filterResAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, filterResId, filterResSlider);
}

void FilterComponent::detachParameters()
{
    filterTypeSelectorAttachment.reset();
    filterFreqAttachment.reset();
    filterResAttachment.reset();
}