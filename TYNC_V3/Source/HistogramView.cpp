#include "HistogramView.h"

HistogramView::HistogramView()
{
    startTimerHz(30); // refresh 30 fps
}

void HistogramView::resized() {}

void HistogramView::timerCallback()
{
    repaint();
}

void HistogramView::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);

    const int w = getWidth();
    const int h = getHeight();

    g.setColour(juce::Colours::white);
    g.drawText("BPM: " + juce::String(currentBPM, 1), 10, 10, 100, 20, juce::Justification::left);

    g.setColour(juce::Colours::green);

    if (!histogramData.empty())
    {
        auto barWidth = static_cast<float>(w) / histogramData.size();
        for (size_t i = 0; i < histogramData.size(); ++i)
        {
            float barHeight = histogramData[i] * static_cast<float>(h);
            g.fillRect(static_cast<int>(i * barWidth), h - barHeight, static_cast<int>(barWidth), barHeight);
        }
    }

    // Draw decay curve
    g.setColour(juce::Colours::red);
    for (int x = 0; x < w; ++x)
    {
        float relative = static_cast<float>(x) / w;
        float yVal = std::exp(-relative / width);
        int y = static_cast<int>((1.0f - yVal) * h);
        g.setPixelAt(x, y);
    }

    // Draw threshold line
    g.setColour(juce::Colours::yellow);
    int threshY = static_cast<int>((1.0f - threshold) * h);
    g.drawLine(0.0f, (float)threshY, (float)w, (float)threshY, 1.0f);
}

void HistogramView::updateData(const std::vector<float>& newHistogram, float bpm)
{
    histogramData = newHistogram;
    currentBPM = bpm;
}
