/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FoldAudioProcessorEditor::FoldAudioProcessorEditor (FoldAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{

    
    setSize (500, 350);
    
    // ============ GAIN SLIDER ============
        
    gainSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    gainSlider.setTextValueSuffix(" dB");
    gainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);

    gainSlider.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::red);
    gainSlider.setColour(Slider::ColourIds::rotarySliderOutlineColourId, Colours::ghostwhite);
    gainSlider.setColour(Slider::ColourIds::thumbColourId, Colours::darkgrey);
    gainSlider.setColour(Slider::ColourIds::textBoxTextColourId, Colours::black);
    
    gainLabel.setText("GAIN", dontSendNotification);
    gainLabel.setJustificationType(Justification::verticallyCentred);
    gainLabel.setJustificationType(Justification::horizontallyCentred);
    
    gainLabel.setFont(20.0f);
    gainLabel.setColour(Label::ColourIds::textColourId, Colours::ghostwhite);
    
    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "GAIN", gainSlider);
    
    addAndMakeVisible(gainLabel);
    addAndMakeVisible(gainSlider);
   
    
    // ========== SATURATION SLIDER ===========
    
    saturationSlider.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::deepskyblue);
    saturationSlider.setColour(Slider::ColourIds::rotarySliderOutlineColourId, Colours::ghostwhite);
    saturationSlider.setColour(Slider::ColourIds::thumbColourId, Colours::darkgrey);
    saturationSlider.setColour(Slider::ColourIds::textBoxTextColourId, Colours::black);
    
    saturationSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    saturationSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
    
    saturationLabel.setText("SATURATION", dontSendNotification);
    saturationLabel.setJustificationType(Justification::verticallyCentred);
    saturationLabel.setJustificationType(Justification::horizontallyCentred);
    
    saturationLabel.setFont(20.0f);
    saturationLabel.setColour(Label::ColourIds::textColourId, Colours::ghostwhite);
    
    saturationAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "SATURATION", saturationSlider);
    
    addAndMakeVisible(saturationLabel);
    addAndMakeVisible(saturationSlider);
    
    // ===== DISTORTION MODE SELECTOR =====
    
    // Note to self COMBOBOX doesn't pull in parameters from AudioParameterChoice
    distortionSelector.addItemList(StringArray { "Sine","Linear" }, 1); // Remember 0 will throw error. Index + 1
    distortionSelector.setColour(ComboBox::ColourIds::backgroundColourId, Colours::ghostwhite);
    distortionSelector.setColour(ComboBox::ColourIds::textColourId, Colours::black);
    distortionSelector.setColour(ComboBox::ColourIds::arrowColourId, Colours::limegreen);
    
    distortionSelector.setJustificationType(Justification::centred);
    
    distortionSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(processor.getAPVTS(), "MODE", distortionSelector);
    
    addAndMakeVisible(distortionSelector);
    
    // ===== TITLE =======
    
    title.setText("- F O L D -", dontSendNotification);
    title.setFont(26.0f);
    title.setJustificationType(Justification::centred);
    title.setColour(Label::ColourIds::textColourId, Colours::ghostwhite);
    addAndMakeVisible(title);
}

FoldAudioProcessorEditor::~FoldAudioProcessorEditor()
{
}

//==============================================================================
void FoldAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::lightgrey);
    
//    g.setColour (Colours::tan);

}

void FoldAudioProcessorEditor::resized()
{
    Rectangle<int> totalArea = getLocalBounds();
    Rectangle<int> titleBounds = totalArea.removeFromTop(50);
    Rectangle<int> selectorBounds = totalArea.removeFromBottom(50);
    
    Rectangle<int> area = totalArea;
    Rectangle<int> textArea = area.removeFromBottom(30);
    gainSlider.setBounds(area.removeFromLeft(getLocalBounds().getWidth()/2));
    saturationSlider.setBounds(area);
    
    gainLabel.setBounds(textArea.removeFromLeft(getLocalBounds().getWidth()/2));
    saturationLabel.setBounds(textArea);
    title.setBounds(titleBounds);
    distortionSelector.setBounds(selectorBounds.reduced(200, 10));
}


