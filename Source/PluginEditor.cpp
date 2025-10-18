/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Project1AudioProcessorEditor::Project1AudioProcessorEditor (Project1AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
    osc(),
    adsr("ADSR"),
    mGain(audioProcessor.apvts),
    pitchR(audioProcessor.apvts),
    filter()
{
    setSize(640, 460);

    addAndMakeVisible(osc1Button);
    addAndMakeVisible(osc2Button);
    addAndMakeVisible(savePresetButton);
    addAndMakeVisible(loadPresetButton);

    osc1Button.setClickingTogglesState(true);
    osc2Button.setClickingTogglesState(true);

    osc1Button.setToggleState(true, juce::dontSendNotification);
    osc2Button.setToggleState(false, juce::dontSendNotification);

    osc1Button.onClick = [this] { switchToOscillator(1); };
    osc2Button.onClick = [this] { switchToOscillator(2); };
    savePresetButton.onClick = [this] { savePresetButtonClicked(); };
    loadPresetButton.onClick = [this] { loadPresetButtonClicked(); };

    osc1Button.setColour(juce::TextButton::buttonColourId, juce::Colours::darkgrey);
    osc1Button.setColour(juce::TextButton::buttonOnColourId, juce::Colours::orange);
    osc1Button.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    osc1Button.setColour(juce::TextButton::textColourOnId, juce::Colours::black);

    osc2Button.setColour(juce::TextButton::buttonColourId, juce::Colours::darkgrey);
    osc2Button.setColour(juce::TextButton::buttonOnColourId, juce::Colours::orange);
    osc2Button.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    osc2Button.setColour(juce::TextButton::textColourOnId, juce::Colours::black);

    savePresetButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkgreen);
    savePresetButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);

    loadPresetButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkblue);
    loadPresetButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);

    addAndMakeVisible(osc);
    addAndMakeVisible(adsr);
    addAndMakeVisible(mGain);
    addAndMakeVisible(pitchR);
    addAndMakeVisible(filter);

    switchToOscillator(1);

}

Project1AudioProcessorEditor::~Project1AudioProcessorEditor()
{
}

//==============================================================================
void Project1AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::black);

    // Draw border around oscillator section
    g.setColour(juce::Colours::white);
    auto oscSectionBounds = juce::Rectangle<int>(10, 10, 310, 220).reduced(5);
    g.drawRoundedRectangle(oscSectionBounds.toFloat(), 5.0f, 2.0f);
}

void Project1AudioProcessorEditor::resized()
{
    const auto padding = 10;
    const auto buttonWidth = 40;
    const auto buttonHeight = 30;
    const auto presetButtonWidth = 60;
    const auto oscSectionWidth = 310;
    const auto oscSectionHeight = 220;
    const auto adsrWidth = 310;
    const auto adsrHeight = 220;
    const auto filterWidth = 310;  // Match oscillator section width
    const auto filterHeight = 220;

    // Top-left: Oscillator section
    osc.setBounds(padding + 5, padding + 10, oscSectionWidth - 30, 70);
    mGain.setBounds(padding + 15, osc.getBottom() + 5, 90, 120);
    pitchR.setBounds(mGain.getRight() + 15, padding + 10, 100, 200);

    // Top-right: ADSR section
    adsr.setBounds(oscSectionWidth + padding, padding, adsrWidth, adsrHeight);

    // Bottom-left: Filter section (now same width as oscillator section)
    filter.setBounds(padding, oscSectionHeight + padding, filterWidth, filterHeight);

    // Bottom-right quadrant: Buttons
    const auto buttonAreaX = oscSectionWidth + padding;
    const auto buttonAreaY = oscSectionHeight + padding;
    const auto buttonSpacing = 5;

    // Oscillator selector buttons (1 and 2)
    osc1Button.setBounds(buttonAreaX + padding, buttonAreaY + padding, buttonWidth, buttonHeight);
    osc2Button.setBounds(osc1Button.getRight() + buttonSpacing, buttonAreaY + padding, buttonWidth, buttonHeight);

    // Save and Load buttons below oscillator selectors
    savePresetButton.setBounds(buttonAreaX + padding, osc1Button.getBottom() + buttonSpacing + 10, presetButtonWidth, buttonHeight);
    loadPresetButton.setBounds(savePresetButton.getRight() + buttonSpacing, osc1Button.getBottom() + buttonSpacing + 10, presetButtonWidth, buttonHeight);

}

void Project1AudioProcessorEditor::switchToOscillator(int oscNum)
{
    if (currentOscillator == oscNum) return;

    currentOscillator = oscNum;

    osc.detachParameters();
    adsr.detachParameters();
    filter.detachParameters();
    pitchR.detachParameters();
    mGain.detachParameters();

    if (oscNum == 1)
    {
        osc.attachToParameters(audioProcessor.apvts, "OSC1WAVETYPE");

        adsr.attachToParameters(audioProcessor.apvts,
                                "ATTACK1", "DECAY1", "SUSTAIN1", "RELEASE1");

        filter.attachToParameters(audioProcessor.apvts,
                                  "FILTERTYPE1", "FILTERFREQ1", "FILTERRES1");

        pitchR.attachToParameters(audioProcessor.apvts,
                                  "OCTAVE1", "SEMITONE1");

        mGain.attachToParameters(audioProcessor.apvts, "MGAIN1");

        osc1Button.setToggleState(true, juce::dontSendNotification);
        osc2Button.setToggleState(false, juce::dontSendNotification);
    }
    else
    {
        osc.attachToParameters(audioProcessor.apvts, "OSC2WAVETYPE");

        adsr.attachToParameters(audioProcessor.apvts,
                                "ATTACK2", "DECAY2", "SUSTAIN2", "RELEASE2");

        filter.attachToParameters(audioProcessor.apvts,
                                  "FILTERTYPE2", "FILTERFREQ2", "FILTERRES2");

        pitchR.attachToParameters(audioProcessor.apvts,
                                  "OCTAVE2", "SEMITONE2");

        mGain.attachToParameters(audioProcessor.apvts, "MGAIN2");

        osc1Button.setToggleState(false, juce::dontSendNotification);
        osc2Button.setToggleState(true, juce::dontSendNotification);
    }

    repaint();
}

void Project1AudioProcessorEditor::savePresetButtonClicked()
{
    auto fileChooser = std::make_shared<juce::FileChooser>(
        "Save Preset",
        juce::File::getSpecialLocation(juce::File::userDocumentsDirectory),
        "*.xml",
        true);

    auto flags = juce::FileBrowserComponent::saveMode | juce::FileBrowserComponent::canSelectFiles;

    fileChooser->launchAsync(flags, [this, fileChooser](const juce::FileChooser& chooser)
    {
        auto file = chooser.getResult();
        if (file != juce::File{})
        {
            // Add .xml extension if not present
            if (!file.hasFileExtension(".xml"))
                file = file.withFileExtension(".xml");

            audioProcessor.savePresetToFile(file);
        }
    });
}

void Project1AudioProcessorEditor::loadPresetButtonClicked()
{
    auto fileChooser = std::make_shared<juce::FileChooser>(
        "Load Preset",
        juce::File::getSpecialLocation(juce::File::userDocumentsDirectory),
        "*.xml",
        true);

    auto flags = juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles;

    fileChooser->launchAsync(flags, [this, fileChooser](const juce::FileChooser& chooser)
    {
        auto file = chooser.getResult();
        if (file != juce::File{} && file.existsAsFile())
        {
            audioProcessor.loadPresetFromFile(file);
        }
    });
}