/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Project1AudioProcessor::Project1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameters", createParams())
#endif
{
    const int numVoices = 8;

    for (int i = 0; i < numVoices; ++i) {
        synth.addVoice(new SynthVoice());
    }

    synth.addSound(new SynthSound());
}

Project1AudioProcessor::~Project1AudioProcessor()
{
}

//==============================================================================
const juce::String Project1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Project1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Project1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Project1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Project1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Project1AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Project1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Project1AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Project1AudioProcessor::getProgramName (int index)
{
    return {};
}

void Project1AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Project1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    synth.setCurrentPlaybackSampleRate(sampleRate);

    for (int i = 0; i < synth.getNumVoices(); i++) {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i))) {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
}

void Project1AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Project1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Project1AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());


    for (int i = 0; i < synth.getNumVoices(); ++i) {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i))) {

            // OSC 1 parameters
            auto& attack1 = *apvts.getRawParameterValue("ATTACK1");
            auto& decay1 = *apvts.getRawParameterValue("DECAY1");
            auto& sustain1 = *apvts.getRawParameterValue("SUSTAIN1");
            auto& release1 = *apvts.getRawParameterValue("RELEASE1");
            auto& oscWaveChoice1 = *apvts.getRawParameterValue("OSC1WAVETYPE");
            auto& mGain1 = *apvts.getRawParameterValue("MGAIN1");
            auto& pRackO1 = *apvts.getRawParameterValue("OCTAVE1");
            auto& pRackS1 = *apvts.getRawParameterValue("SEMITONE1");
            auto& filterType1 = *apvts.getRawParameterValue("FILTERTYPE1");
            auto& filterCut1 = *apvts.getRawParameterValue("FILTERFREQ1");
            auto& filterRes1 = *apvts.getRawParameterValue("FILTERRES1");

            // OSC 2 parameters
            auto& attack2 = *apvts.getRawParameterValue("ATTACK2");
            auto& decay2 = *apvts.getRawParameterValue("DECAY2");
            auto& sustain2 = *apvts.getRawParameterValue("SUSTAIN2");
            auto& release2 = *apvts.getRawParameterValue("RELEASE2");
            auto& oscWaveChoice2 = *apvts.getRawParameterValue("OSC2WAVETYPE");
            auto& mGain2 = *apvts.getRawParameterValue("MGAIN2");
            auto& pRackO2 = *apvts.getRawParameterValue("OCTAVE2");
            auto& pRackS2 = *apvts.getRawParameterValue("SEMITONE2");
            auto& filterType2 = *apvts.getRawParameterValue("FILTERTYPE2");
            auto& filterCut2 = *apvts.getRawParameterValue("FILTERFREQ2");
            auto& filterRes2 = *apvts.getRawParameterValue("FILTERRES2");

            // Update voice with all parameters
            voice->update(attack1.load(), attack2.load(),
                         decay1.load(), decay2.load(),
                         sustain1.load(), sustain2.load(),
                         release1.load(), release2.load(),
                         mGain1.load(), mGain2.load(),
                         pRackO1.load(), pRackO2.load(),
                         pRackS1.load(), pRackS2.load());

            // Set waveform types for both oscillators
            voice->getOscillator1().setWaveType(oscWaveChoice1.load());
            voice->getOscillator2().setWaveType(oscWaveChoice2.load());

            // Update filters for both oscillators
            voice->updateFilter(filterType1.load(), filterCut1.load(), filterRes1.load(),
                               filterType2.load(), filterCut2.load(), filterRes2.load());

        }

    }

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());


}

//==============================================================================
bool Project1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Project1AudioProcessor::createEditor()
{
    return new Project1AudioProcessorEditor (*this);
}

//==============================================================================
void Project1AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // Save APVTS state to binary (for DAW session save)
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void Project1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // Restore APVTS state from binary (for DAW session load)
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(apvts.state.getType()))
            apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
}

void Project1AudioProcessor::savePresetToFile(const juce::File& file)
{
    // Export APVTS state to XML file
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());

    if (xml != nullptr)
    {
        xml->writeTo(file);
    }
}

void Project1AudioProcessor::loadPresetFromFile(const juce::File& file)
{
    // Import APVTS state from XML file
    std::unique_ptr<juce::XmlElement> xml(juce::XmlDocument::parse(file));

    if (xml != nullptr && xml->hasTagName(apvts.state.getType()))
    {
        apvts.replaceState(juce::ValueTree::fromXml(*xml));
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Project1AudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout Project1AudioProcessor::createParams() {


    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;


    //OSC select
    params.push_back(std::make_unique <juce::AudioParameterChoice>("OSC1WAVETYPE", "Osc 1 Wave Type", juce::StringArray{ "Sine", "Saw", "Square", "Triangle"}, 0));
    params.push_back(std::make_unique <juce::AudioParameterChoice>("OSC2WAVETYPE", "Osc 2 Wave Type", juce::StringArray{ "Sine", "Saw", "Square", "Triangle" }, 0));




    //ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK1", "Attack 2", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK2", "Attack 2", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY1", "Decay 1", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY2", "Decay 2", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN1", "Sustain 1", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN2", "Sustain 2", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 1.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE1", "Release 1", juce::NormalisableRange<float> { 0.1f, 3.0f, 0.1f }, 0.4f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE2", "Release 2", juce::NormalisableRange<float> { 0.1f, 3.0f, 0.1f }, 0.4f));


    //Master Gain Knobs
    params.push_back(std::make_unique<juce::AudioParameterFloat>("MGAIN1", "Master Gain 1", juce::NormalisableRange<float> {-100.0f, 0.0f, 1.0f }, -18.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("MGAIN2", "Master Gain 2", juce::NormalisableRange<float> {-100.0f, 0.0f, 1.0f }, -18.0f));


    //Octave & Semitone Knobs
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OCTAVE1", "Pitch Rack Octave 2", juce::NormalisableRange<float> {-4.0f, 4.0f, 1.0f }, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OCTAVE2", "Pitch Rack Octave 2", juce::NormalisableRange<float> {-4.0f, 4.0f, 1.0f }, 0.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("SEMITONE1", "Pitch Rack Semitone 1", juce::NormalisableRange<float> {-12.0f, 12.0f, 1.0f }, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SEMITONE2", "Pitch Rack Semitone 2", juce::NormalisableRange<float> {-12.0f, 12.0f, 1.0f }, 0.0f));




    //Filter
    params.push_back(std::make_unique<juce::AudioParameterChoice>("FILTERTYPE1", "Filter Type 1", juce::StringArray{ "LowPass", "BandPass", "HighPass" }, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("FILTERTYPE2", "Filter Type 2", juce::StringArray{ "LowPass", "BandPass", "HighPass" }, 0));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERFREQ1", "Filter Freq 1", juce::NormalisableRange<float> { 20.0f, 20000.0f, 0.1f, 0.6f }, 200.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERFREQ2", "Filter Freq 2", juce::NormalisableRange<float> { 20.0f, 20000.0f, 0.1f, 0.6f }, 200.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERRES1", "Filter Resonance 1", juce::NormalisableRange<float> { 1.0f, 10.0f, 0.1f }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERRES2", "Filter Resonance 2", juce::NormalisableRange<float> { 1.0f, 10.0f, 0.1f }, 1.0f));

   

    return { params.begin(), params.end() };
}