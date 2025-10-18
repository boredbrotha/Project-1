/*
  ==============================================================================

    PitchRackData.cpp
    Created: 6 May 2025 2:16:02pm
    Author:  soatm

  ==============================================================================
*/

#include "PitchRackData.h"


void PitchRackData::setOctave(const float newOctaveValue) {

    octaveValue = newOctaveValue;
}

void PitchRackData::setSemitone(const float newSemitoneValue) {

    semitoneValue = newSemitoneValue;
}

float PitchRackData::getOctave() {
    return octaveValue;
}

float PitchRackData::getSemitone() {
    return semitoneValue;
}
