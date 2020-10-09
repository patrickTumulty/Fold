/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

// Macros for Parameter Names and Id's



#include "../JuceLibraryCode/JuceHeader.h"
#include "Fold_DistortionEngine.h"

//==============================================================================
/**
*/
class FoldAudioProcessor  : public juce::AudioProcessor,
                            public juce::ValueTree::Listener
{
public:
    //==============================================================================
    FoldAudioProcessor();
    ~FoldAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    float getLinGain();
    float getSaturation();
    mode getMode();
    
    float db_to_lin(float db);
    
    juce::AudioProcessorValueTreeState& getAPVTS() { return mAPVTS; }
    
private:
    //==============================================================================
    
    juce::AudioProcessorValueTreeState mAPVTS;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();
    
    std::unique_ptr<DistortionEngine> foldDistortionProcessor;
    
    float linGain; // these for use in process block
    float saturation;
    mode distortionMode;
    
    
    void valueTreePropertyChanged (juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property) override;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FoldAudioProcessor)
};
