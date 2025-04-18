/*
  ==============================================================================

    SynthVoice.cpp
    Created: 22 Feb 2025 5:08:21pm
    Author:  soatm

  ==============================================================================
*/

#include "SynthVoice.h"


bool::SynthVoice::canPlaySound(juce::SynthesiserSound* sound) {
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) {
  
        osc.reset();
        osc.setWaveFrequency(midiNoteNumber);
        adsr.noteOn();
    


}

void SynthVoice::stopNote(float velocity, bool allowTailOff) {
    adsr.noteOff();

    if (!allowTailOff || !adsr.isActive()) {
        clearCurrentNote();
    }
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue) {

}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue) {


}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels) {
    adsr.setSampleRate(sampleRate);
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    osc.prepare(spec);
    mGain.prepare(spec);

    mGain.setGainLinear(0.03f);

    isPrepared = true;
}

void SynthVoice::update(const float attack, const float decay, const float sustain, const float release, const float mGainLinear) {
    adsr.updateADSR(attack, decay, sustain, release);
    mGain.updateMGain(mGainLinear);

}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) {

    jassert(isPrepared);

    if (!isVoiceActive()) {
        return;
    }

    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();



    juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };
    osc.getNextAudioBlock(audioBlock);
    mGain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());


    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel) {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);

        if (!adsr.isActive()) {
            clearCurrentNote();
        }
    }
}