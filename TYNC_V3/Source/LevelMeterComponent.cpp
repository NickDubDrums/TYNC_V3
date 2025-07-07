#include "LevelMeterComponent.h"

LevelMeterComponent::LevelMeterComponent() {}

void LevelMeterComponent::setLevel(float newLevel)
{
    level.store(newLevel);
    repaint();
}

void LevelMeterComponent::setThreshold(float newThreshold)
{
    threshold.store(newThreshold);
}

void LevelMeterComponent::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds();

    float levelValue = juce::jlimit(0.0f, 1.0f, level.load());
    float thresholdValue = juce::jlimit(0.0f, 1.0f, threshold.load());

    float levelHeight = (1.0f - levelValue) * bounds.getHeight();
    float thresholdY = (1.0f - thresholdValue) * bounds.getHeight();

    // Sfondo
    g.fillAll(juce::Colours::black);

    // Meter
    g.setColour(juce::Colours::limegreen);
    g.fillRect(juce::Rectangle<float>(0.0f, levelHeight, (float)bounds.getWidth(), (float)(bounds.getHeight() - levelHeight)));

    // Linea Threshold
    g.setColour(juce::Colours::red);
    g.drawLine(0.0f, thresholdY, (float)getWidth(), thresholdY, 1.0f);
}
