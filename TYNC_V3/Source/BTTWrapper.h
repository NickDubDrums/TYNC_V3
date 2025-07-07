#pragma once

#include "External/BTT.h"
#include <vector>
#include <numeric>

class BTTWrapper
{
public:
    BTTWrapper(float sampleRate);
    ~BTTWrapper();

    void process(const float* input, int numSamples);

    float getBPM() const;
    const std::vector<int>& getHistogram() const;

    void setThreshold(float t) { threshold = t; }
    void setDecay(float d) { decay = d; }
    void setWidth(int w) { width = w; histogram.resize(width); }
    void init(float sampleRate);


private:
    BTT* btt = nullptr;

    float threshold = 0.001f;
    float decay = 0.9f;
    int width = 20;

    float sampleRate = 44100.0f;
    float currentBPM = 0.0f;

    std::vector<int> histogram;
    std::vector<float> peakTimes;
};
