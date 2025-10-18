/*
  ==============================================================================

    AdsrComponent.cpp
    Created: 24 Feb 2025 2:08:25pm
    Author:  soatm

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdsrComponent.h"

//==============================================================================
AdsrComponent::AdsrComponent(juce::String name)
{
    componentName = name;

    // Setup sliders UI-only (no parameter attachments)
    attackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    attackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    attackSlider.setRange(0.1, 1.0, 0.1);
    addAndMakeVisible(attackSlider);

    decaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    decaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    decaySlider.setRange(0.1, 1.0, 0.1);
    addAndMakeVisible(decaySlider);

    sustainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    sustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    sustainSlider.setRange(0.1, 1.0, 0.1);
    addAndMakeVisible(sustainSlider);

    releaseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    releaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    releaseSlider.setRange(0.1, 3.0, 0.1);
    addAndMakeVisible(releaseSlider);

    // Setup labels
    attackLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    attackLabel.setFont(15.0f);
    attackLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(attackLabel);

    decayLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    decayLabel.setFont(15.0f);
    decayLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(decayLabel);

    sustainLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    sustainLabel.setFont(15.0f);
    sustainLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(sustainLabel);

    releaseLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    releaseLabel.setFont(15.0f);
    releaseLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(releaseLabel);

    // NOTE: Attachments are NOT created here - they will be created by switchToOscillator()
    // in PluginEditor to ensure proper parameter routing
}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText(componentName, labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);
}

void AdsrComponent::resized()
{
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getHeight() - 45;
    const auto sliderStartX = padding + 5;
    const auto sliderStartY = 55;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    const auto labelStart = sliderStartY - labelYOffset;

    attackSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    attackLabel.setBounds(attackSlider.getX(), labelStart, sliderWidth, labelHeight);

    decaySlider.setBounds(attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    decayLabel.setBounds(decaySlider.getX(), labelStart, sliderWidth, labelHeight);

    sustainSlider.setBounds(decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    sustainLabel.setBounds(sustainSlider.getX(), labelStart, sliderWidth, labelHeight);

    releaseSlider.setBounds(sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    releaseLabel.setBounds(releaseSlider.getX(), labelStart, sliderWidth, labelHeight);
}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void AdsrComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);

    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);

    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}

void AdsrComponent::attachToParameters(juce::AudioProcessorValueTreeState& apvts,
                                       const juce::String& attackId,
                                       const juce::String& decayId,
                                       const juce::String& sustainId,
                                       const juce::String& releaseId)
{
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    attackAttachment = std::make_unique<SliderAttachment>(apvts, attackId, attackSlider);
    decayAttachment = std::make_unique<SliderAttachment>(apvts, decayId, decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(apvts, sustainId, sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(apvts, releaseId, releaseSlider);
}

void AdsrComponent::detachParameters()
{
    attackAttachment.reset();
    decayAttachment.reset();
    sustainAttachment.reset();
    releaseAttachment.reset();
}
