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
            
        // I have to reset so that the synth doesn't tweak out.
        osc1.reset();
        osc2.reset();

        // I guess here I have to figure out how to modulate the semitone and octave. This is where it happens!! Or maybe not. maybe I should do it in the processor.
        // Modulating the frequency depending on what the pitch and semitone knobs are at in the front-end. (Doing this for both oscillators)
        float baseFreq1 = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        baseFreq1 = (baseFreq1)*std::pow(2.0f, pRack1.getOctave() + pRack1.getSemitone() / 12.0f);
        float baseFreq2 = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        baseFreq2 = (baseFreq2)*std::pow(2.0f, pRack2.getOctave() + pRack2.getSemitone() / 12.0f);


        //Setting the frequency of the oscillators
        osc1.setWaveFrequency(baseFreq1);
        osc2.setWaveFrequency(baseFreq2);
   
        //Turning notes on
        adsr1.noteOn();
        adsr2.noteOn();
    


}

void SynthVoice::stopNote(float velocity, bool allowTailOff) {
    adsr1.noteOff();
    adsr2.noteOff();

    if ((!allowTailOff || !adsr1.isActive()) && (!allowTailOff || !adsr2.isActive())) {
        clearCurrentNote();
    }
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue) {

}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue) {


}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels) {
    adsr1.setSampleRate(sampleRate);
    adsr2.setSampleRate(sampleRate);

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    osc1.prepare(spec);
    osc2.prepare(spec);
    filter1.prepareToPlay(sampleRate, samplesPerBlock, outputChannels);
    filter2.prepareToPlay(sampleRate, samplesPerBlock, outputChannels);
    mGain1.prepare(spec);
    mGain2.prepare(spec);

    // I need to test this line of code..... Note for future me.
    mGain1.setGainLinear(0.03f); 
    mGain2.setGainLinear(0.03f);

    isPrepared = true;
}

void SynthVoice::update(const float attack1, const float attack2,
                        const float decay1, const float decay2,
                        const float sustain1, const float sustain2,
                        const float release1, const float release2,
                        const float mGainLinear1, const float mGainLinear2,
                        const float pRackO1, const float pRackO2,
                        const float pRackS1, const float pRackS2){

    adsr1.updateADSR(attack1, decay1, sustain1, release1);
    adsr2.updateADSR(attack2, decay2, sustain2, release2);

    mGain1.updateMGain(mGainLinear1);
    mGain2.updateMGain(mGainLinear2);


    pRack1.setOctave(pRackO1);
    pRack2.setOctave(pRackO2);


    pRack1.setSemitone(pRackS1);
    pRack2.setSemitone(pRackS2);

}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) {

    jassert(isPrepared);

    if (!isVoiceActive()) {
        return;
    }

    // Create separate buffers for each oscillator chain
    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    osc2Buffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);

    synthBuffer.clear();
    osc2Buffer.clear();

    // ===== OSC 1 CHAIN =====
    juce::dsp::AudioBlock<float> audioBlock1{ synthBuffer };

    osc1.getNextAudioBlock(audioBlock1);
    mGain1.process(juce::dsp::ProcessContextReplacing<float>(audioBlock1));
    filter1.process(synthBuffer);
    adsr1.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());

    // ===== OSC 2 CHAIN =====
    juce::dsp::AudioBlock<float> audioBlock2{ osc2Buffer };

    osc2.getNextAudioBlock(audioBlock2);
    mGain2.process(juce::dsp::ProcessContextReplacing<float>(audioBlock2));
    filter2.process(osc2Buffer);
    adsr2.applyEnvelopeToBuffer(osc2Buffer, 0, osc2Buffer.getNumSamples());

    // ===== MIX BOTH OSCILLATORS =====
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel) {
        // Add osc1 to output
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);

        // Add osc2 to output (mixing with osc1)
        outputBuffer.addFrom(channel, startSample, osc2Buffer, channel, 0, numSamples);
    }

    // Check if voice should be cleared (when both ADSRs are done)
    if (!adsr1.isActive() && !adsr2.isActive()) {
        clearCurrentNote();
    }
}

void SynthVoice::updateFilter(const int filterType1, const float frequency1, const float resonance1,
                               const int filterType2, const float frequency2, const float resonance2)
{
    filter1.updateParameters(filterType1, frequency1, resonance1);
    filter2.updateParameters(filterType2, frequency2, resonance2);
}