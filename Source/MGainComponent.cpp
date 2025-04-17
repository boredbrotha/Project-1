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
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    mSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(mSlider);
    
    mSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts,"MGAIN", mSlider);

}

MGainComponent::~MGainComponent()
{
}

void MGainComponent::paint(juce::Graphics& g)
{
}

void MGainComponent::resized()
{

    mSlider.setBounds(0, 0, getWidth(), getHeight());
}
