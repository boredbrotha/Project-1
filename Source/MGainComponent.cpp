/*
  ==============================================================================

    MGainComponent.cpp
    Created: 5 Mar 2025 6:24:54pm
    Author:  soatm

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MGainComponent.h"

//==============================================================================
MGainComponent::MGainComponent(juce::AudioProcessorValueTreeState& apvts)
{


    //Adding all of my detail methods to the slider
    mSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    mSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    mSlider.setTextValueSuffix(" dB");
    mSlider.setRange(-100.0f, 0.0f);
    // NOTE: Don't call setValue() here - the attachment will sync from APVTS automatically
    addAndMakeVisible(mSlider);


    // NOTE: Attachment is NOT created here - it will be created by switchToOscillator()
    // in PluginEditor to ensure proper parameter routing


    //This little lambda function makes the frontend return "-inf" when the decibels go below -100.
    mSlider.textFromValueFunction = [](double value) {
        if (value <= -99.9) {
            return juce::String("-inf");
        }

        return juce::String(value, 1);

        };




    //Adding the text for the label of this shit
    mLabel.setText("Gain", juce::dontSendNotification);
    mLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(mLabel);


}

MGainComponent::~MGainComponent()
{
}

void MGainComponent::paint(juce::Graphics& g)
{
}

void MGainComponent::resized()
{
    mSlider.setBounds(0, 20, 100, 75);
    mLabel.setBounds(0, 0, 100, 20);
}

void MGainComponent::attachToParameters(juce::AudioProcessorValueTreeState& apvts, const juce::String& gainId)
{
    mSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, gainId, mSlider);
}

void MGainComponent::detachParameters()
{
    mSliderAttachment.reset();
}
