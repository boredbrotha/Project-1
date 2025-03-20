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
MGainComponent::MGainComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    addAndMakeVisible(mSlider);
}

MGainComponent::~MGainComponent()
{
}

void MGainComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);

}

void MGainComponent::resized()
{

  
}
