/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <math.h>

//==============================================================================
FoldAudioProcessor::FoldAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), mAPVTS(*this, nullptr, "PARAMETERS", createParameters())
#endif
{
    mAPVTS.state.addListener (this);
    foldDistortionProcessor = std::make_unique<DistortionEngine>();

}

FoldAudioProcessor::~FoldAudioProcessor()
{
}

//==============================================================================



const String FoldAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FoldAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FoldAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FoldAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FoldAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FoldAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FoldAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FoldAudioProcessor::setCurrentProgram (int index)
{
}

const String FoldAudioProcessor::getProgramName (int index)
{
    return {};
}

void FoldAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void FoldAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    linGain = getLinGain(); // otherwise no audio before knobs get moved
    saturation = getSaturation();
    distortionMode = getMode();
    
}

void FoldAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FoldAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void FoldAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        for (int sample = 0; sample < buffer.getNumSamples(); sample++)
        {
            channelData[sample] *= linGain;
            channelData[sample] = foldDistortionProcessor->processDistortion(channelData[sample], saturation, distortionMode);
        }
    }
}

//==============================================================================
bool FoldAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* FoldAudioProcessor::createEditor()
{
    return new FoldAudioProcessorEditor (*this);
}

//==============================================================================
void FoldAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    

}

void FoldAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{


}

void FoldAudioProcessor::valueTreePropertyChanged (juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property)
{
    linGain = getLinGain();
    saturation = getSaturation();
    distortionMode = getMode();
}

mode FoldAudioProcessor::getMode()
{
    int temp = mAPVTS.getRawParameterValue ("MODE")->load();
    if (temp == 0)
        return SINE;
    else if (temp == 1)
        return LINEAR;
}

float FoldAudioProcessor::getLinGain()
{
    return juce::Decibels::decibelsToGain (mAPVTS.getRawParameterValue ("GAIN")->load());
}

float FoldAudioProcessor::getSaturation()
{
    return mAPVTS.getRawParameterValue ("SATURATION")->load();
}


float FoldAudioProcessor::db_to_lin(float db)
{
    return juce::Decibels::decibelsToGain(db);
}


juce::AudioProcessorValueTreeState::ParameterLayout FoldAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;
        
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("GAIN", "Gain", 0.0f, 40.0f, 0.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("SATURATION", "Saturation", 0.0f, 1.0f, 0.01f));
    parameters.push_back(std::make_unique<juce::AudioParameterChoice>("MODE", "Mode", StringArray { "Sine", "Linear" }, 0));
    
    return { parameters.begin(), parameters.end() };
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FoldAudioProcessor();
}
