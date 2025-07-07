#pragma once
#include <JuceHeader.h>

class HistogramView : public juce::Component, private juce::Timer
{
public:
    HistogramView();

    void paint(juce::Graphics&) override;
    void resized() override;

    void updateData(const std::vector<float>& histogram, float bpm);
    void setDecay(float d) { decay = d; }
    void setThreshold(float t) { threshold = t; }
    void setWidth(float w) { width = w; }

private:
    void timerCallback() override;

    std::vector<float> histogramData;
    float currentBPM = 0.0f;
    float decay = 0.9f;
    float threshold = 0.5f;
    float width = 0.3f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HistogramView)
};
