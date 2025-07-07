/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class TYNC_V3AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    TYNC_V3AudioProcessorEditor (TYNC_V3AudioProcessor&);
    ~TYNC_V3AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TYNC_V3AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TYNC_V3AudioProcessorEditor)
};
