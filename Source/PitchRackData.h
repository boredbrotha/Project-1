/*
  ==============================================================================

    PitchRackData.h
    Created: 6 May 2025 2:16:02pm
    Author:  soatm

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class PitchRackData {


public:
    void setOctave(const float octaveValue);
    void setSemitone(const float newSemitoneValue);

    float getOctave();

    float getSemitone();



private:

    float octaveValue;

    float semitoneValue;




};