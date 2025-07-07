#include "STFT.h"
#include <cmath>
#include <cstring>
#include <cstdlib>

struct STFT {
    int windowSize;
    int hopSize;
    float* window;
    float* buffer;
};

STFT* new_STFT(int windowSize, float hopFactor) {
    STFT* stft = new STFT;
    stft->windowSize = windowSize;
    stft->hopSize = static_cast<int>(windowSize * hopFactor);
    stft->window = new float[windowSize];
    stft->buffer = new float[windowSize];

    // Simple Hann window
    for (int i = 0; i < windowSize; ++i) {
        stft->window[i] = 0.5f * (1.0f - cosf(2.0f * 3.14159265f * i / (windowSize - 1)));
    }

    std::memset(stft->buffer, 0, sizeof(float) * windowSize);
    return stft;
}

void free_STFT(STFT* stft) {
    if (!stft) return;
    delete[] stft->window;
    delete[] stft->buffer;
    delete stft;
}

void process_STFT(STFT* stft, const float* input, int numSamples) {
    if (!stft || !input || numSamples < stft->windowSize) return;

    // Copy & window input (simplified)
    for (int i = 0; i < stft->windowSize; ++i) {
        stft->buffer[i] = input[i] * stft->window[i];
    }

    // Placeholder: STFT not implemented (just dummy call)
    // Would call FFT or DFT here.
}
