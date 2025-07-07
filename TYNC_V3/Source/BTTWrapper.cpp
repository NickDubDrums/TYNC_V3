#include "BTTWrapper.h"
#include <iostream>
#include <cmath>
#include <numeric>

BTTWrapper::BTTWrapper(float sampleRate)
{
    init(sampleRate);
}

BTTWrapper::~BTTWrapper()
{
    if (btt)
        free_BTT(btt);
}

void BTTWrapper::init(float sampleRate)
{
    if (btt)
        free_BTT(btt);

    btt = new_BTT(sampleRate);
    this->sampleRate = sampleRate;
    currentBPM = 0.0f;

    // Parametri base
    set_peak_threshold(btt, threshold);
    set_gaussian_decay(btt, decay);
    set_gaussian_width(btt, width);

    histogram.clear();
    histogram.resize(width);
}

void BTTWrapper::process(const float* input, int numSamples)
{
    if (!btt)
        return;

    track(btt, (dft_sample_t*)input, numSamples);
    currentBPM = tempo(btt);

    // Aggiorna istogramma
    float* hist = histogram_data(btt);
    for (int i = 0; i < width; ++i)
        histogram[i] = static_cast<int>(hist[i] * 1000.0f);  // Scala per renderlo visibile nel grafico
}

float BTTWrapper::getBPM() const
{
    return currentBPM;
}

const std::vector<int>& BTTWrapper::getHistogram() const
{
    return histogram;
}
