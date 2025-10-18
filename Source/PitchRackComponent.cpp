/*
  ==============================================================================

    PitchRackComponent.cpp
    Created: 6 May 2025 2:15:41pm
    Author:  soatm

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PitchRackComponent.h"

//==============================================================================
PitchRackComponent::PitchRackComponent(juce::AudioProcessorValueTreeState& apvts){

    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.


    //Setting the style of the different sliders.
    octaveSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    semitoneSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);


    octaveSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    semitoneSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);

    octaveSlider.setRange(-4.0f, 4.0f);
    semitoneSlider.setRange(-12.f, 12.f);



    addAndMakeVisible(octaveSlider);
    addAndMakeVisible(semitoneSlider);

    // NOTE: Attachments are NOT created here - they will be created by switchToOscillator()
    // in PluginEditor to ensure proper parameter routing

    octaveLabel.setText("Octave", juce::dontSendNotification);
    octaveLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    octaveLabel.setFont(15.0f);
    octaveLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(octaveLabel);

    semitoneLabel.setText("Semi", juce::dontSendNotification);
    semitoneLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    semitoneLabel.setFont(15.0f);
    semitoneLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(semitoneLabel);

}

PitchRackComponent::~PitchRackComponent()
{
}

void PitchRackComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
}

void PitchRackComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    const auto labelHeight = 15;
    const auto labelOffset = 3;
    const auto sliderSize = 70;

    octaveLabel.setBounds(0, 0, 100, labelHeight);
    octaveSlider.setBounds(15, labelHeight + labelOffset, sliderSize, sliderSize);

    semitoneLabel.setBounds(0, octaveSlider.getBottom() + labelOffset, 100, labelHeight);
    semitoneSlider.setBounds(15, semitoneLabel.getBottom() + labelOffset, sliderSize, sliderSize);

}

void PitchRackComponent::attachToParameters(juce::AudioProcessorValueTreeState& apvts,
                                            const juce::String& octaveId,
                                            const juce::String& semitoneId)
{
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    octaveAttachment = std::make_unique<SliderAttachment>(apvts, octaveId, octaveSlider);
    semitoneAttachment = std::make_unique<SliderAttachment>(apvts, semitoneId, semitoneSlider);
}

void PitchRackComponent::detachParameters()
{
    octaveAttachment.reset();
    semitoneAttachment.reset();
}

