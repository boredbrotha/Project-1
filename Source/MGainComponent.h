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
    MGainComponent();
    ~MGainComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    juce::Slider mSlider;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MGainComponent)
};
