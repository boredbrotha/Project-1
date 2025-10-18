/*
  ==============================================================================

    OscComponent.cpp
    Created: 19 Feb 2025 7:05:12pm
    Author:  soatm

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    juce::StringArray choices{ "Sine", "Saw", "Square", "Triangle"};
    oscWaveSelector.addItemList(choices, 1);

    addAndMakeVisible(oscWaveSelector);

    // NOTE: Attachment is NOT created here - it will be created by switchToOscillator()
    // in PluginEditor to ensure proper parameter routing

    oscLabel.setText("Oscillator", juce::dontSendNotification);
    oscLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    oscLabel.setFont(20.0f);
    oscLabel.setJustificationType(juce::Justification::left);
    addAndMakeVisible(oscLabel);

}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void OscComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    const auto labelHeight = 25;

    oscLabel.setBounds(5, 5, getWidth() - 10, labelHeight);
    oscWaveSelector.setBounds(10, 35, 90, 20);

}

void OscComponent::attachToParameters(juce::AudioProcessorValueTreeState& apvts, const juce::String& waveSelectorId)
{
    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveSelectorId, oscWaveSelector);
}

void OscComponent::detachParameters()
{
    oscWaveSelectorAttachment.reset();
}
