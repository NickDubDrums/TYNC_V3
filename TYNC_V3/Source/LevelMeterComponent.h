#pragma once
#include <JuceHeader.h>

class LevelMeterComponent : public juce::Component
{
public:
    LevelMeterComponent();

    void setLevel(float newLevel);
    void setThreshold(float newThreshold);
    void paint(juce::Graphics& g) override;

private:
    std::atomic<float> level{ 0.0f };       // valore tra 0.0 e 1.0
    std::atomic<float> threshold{ 0.5f };   // valore tra 0.0 e 1.0
};
