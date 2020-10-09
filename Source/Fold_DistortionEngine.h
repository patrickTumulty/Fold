/*
  ==============================================================================

    Fold_DistortionEngine.h
    Created: 6 Oct 2020 10:09:13pm
    Author:  Patrick Tumulty

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

enum mode { SINE, LINEAR }; // different distortion modes.

class DistortionEngine
{
public:
    DistortionEngine();
    ~DistortionEngine();
    
    float wfSine(float sample);
    float wfSineSat(float sample, float saturation);
    float wfLin(float sample);
    float wfLinSat(float sample, float saturation);
    
    float processDistortion(float sample, float saturation, mode distMode);
    
private:
    mode mDistortionMode;
    
    
};
