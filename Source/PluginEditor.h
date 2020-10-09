/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class FoldAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    FoldAudioProcessorEditor (FoldAudioProcessor&);
    ~FoldAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
        
private:
    
    FoldAudioProcessor& processor;
    
    juce::Slider gainSlider;
    juce::Slider saturationSlider;
        
    juce::ComboBox distortionSelector;
    
    juce::Label gainLabel;
    juce::Label saturationLabel;
    
    juce::Label title;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> saturationAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> distortionSelectorAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FoldAudioProcessorEditor)

};
