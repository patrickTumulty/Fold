/*
  ==============================================================================

    Fold_DistortionEngine.cpp
    Created: 6 Oct 2020 10:09:13pm
    Author:  Patrick Tumulty

  ==============================================================================
*/

#include "Fold_DistortionEngine.h"

DistortionEngine::DistortionEngine()
{
    
}

DistortionEngine::~DistortionEngine()
{
    
}


float DistortionEngine::wfSine(float sample)
{
    return std::sin(sample);
}

float DistortionEngine::wfSineSat(float sample, float saturation)
{
    return (std::sin(sample) * (1 - saturation)) + (std::atan(sample) * saturation);
}

float DistortionEngine::wfLin(float sample)
{
    if (sample> 1.0f)
        sample = 1 - (sample - 1);
    else if (sample < -1.0f)
        sample = -1 - (sample + 1);
    return std::atan(sample);
}

float DistortionEngine::wfLinSat(float sample, float saturation)
{
    if (sample> 1.0f)
        sample = 1 - (sample - 1);
    else if (sample < -1.0f)
        sample = -1 - (sample + 1);
    return (std::sin(sample) * (1 - saturation)) + (std::atan(sample) * saturation);
}

float DistortionEngine::processDistortion(float sample, float saturation, mode distMode)
{
    switch (distMode) {
        case SINE :
            sample = wfSineSat(sample, saturation);
            break;
        case LINEAR :
            sample = wfLinSat(sample, saturation);
            break;
    }
    return sample;
}
