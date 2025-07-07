#include "BTT.h"
#include "src/STFT.h"
#include "src/DFT.h"
#include "src/Filter.h"
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>

#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>

struct BTT {
    float sampleRate;
    int bufferSize;
    float estimatedTempo;
    STFT* stft;
    float* inputBuffer;
    int histogram[BTT_NUM_BINS];
};

BTT* new_BTT(float sampleRate) {
    BTT* btt = new BTT;
    btt->sampleRate = sampleRate;
    btt->bufferSize = 44100;
    btt->estimatedTempo = 0.0f;
    btt->inputBuffer = new float[btt->bufferSize];
    std::memset(btt->inputBuffer, 0, sizeof(float) * btt->bufferSize);
    btt->stft = new_STFT(btt->bufferSize, 0.5f); // hopSize = 0.5 * windowSize
    std::fill(btt->histogram, btt->histogram + BTT_NUM_BINS, 0); // <--- istogramma
    return btt;
}

void free_BTT(BTT* btt) {
    if (btt) {
        delete[] btt->inputBuffer;
        free_STFT(btt->stft);
        delete btt;
    }
}

void track(BTT* btt, dft_sample_t* input, int numSamples) {
    if (!btt || !input) return;

    std::vector<float> envelope(numSamples);

    // Calcola energia semplice (rectified signal)
    for (int i = 0; i < numSamples; ++i)
        envelope[i] = std::fabs(input[i]);

    std::cout << "\n--- New block ---\n";
    std::cout << "Envelope sample (first 10): ";
    for (int i = 0; i < std::min(10, numSamples); ++i)
        std::cout << envelope[i] << " ";
    std::cout << "\n";

    // Soglia per picchi
    float threshold = 0.5f;
    std::vector<int> peakPositions;

    float minPeakDistanceSec = 0.2f; // ignora picchi troppo ravvicinati (es. code, risonanze)

    for (int i = 1; i < numSamples - 1; ++i) {
        if (envelope[i] > threshold &&
            envelope[i] > envelope[i - 1] &&
            envelope[i] > envelope[i + 1]) {

            // Controllo distanza minima tra picchi
            if (!peakPositions.empty()) {
                int lastPeak = peakPositions.back();
                float timeSinceLast = (i - lastPeak) / btt->sampleRate;
                if (timeSinceLast < minPeakDistanceSec)
                    continue; // troppo vicino → scartato
            }

            peakPositions.push_back(i);
            std::cout << "  📌 Peak at sample: " << i
                << " (time: " << (i / btt->sampleRate)
                << " s, value: " << envelope[i] << ")\n";
        }
    }

    std::cout << "🔍 Total peaks found: " << peakPositions.size() << "\n";

    if (peakPositions.size() < 2) {
        std::cout << "⚠️  Not enough peaks to calculate BPM.\n";
        btt->estimatedTempo = 0.0f;
        return;
    }

    // Calcola intervalli tra picchi
    std::vector<float> intervals;
    for (size_t i = 1; i < peakPositions.size(); ++i) {
        float dt = (peakPositions[i] - peakPositions[i - 1]) / btt->sampleRate;
        std::cout << "    Δt = " << dt << " s";

        if (dt > 0.05f && dt < 2.0f) {
            intervals.push_back(dt);
            std::cout << " ✅ accepted\n";
        }
        else {
            std::cout << " ❌ rejected\n";
        }
    }

    std::cout << "✅ Valid intervals: " << intervals.size() << "\n";

    if (intervals.empty()) {
        std::cout << "❌ No valid intervals. BPM cannot be calculated.\n";
        btt->estimatedTempo = 0.0f;
        return;
    }

    float meanInterval = std::accumulate(intervals.begin(), intervals.end(), 0.0f) / intervals.size();
    btt->estimatedTempo = 60.0f / meanInterval;

    // Dopo aver calcolato intervals...

// Reset istogramma
    std::fill(btt->histogram, btt->histogram + BTT_NUM_BINS, 0);

    // Popola istogramma
    for (float dt : intervals) {
        float bpm = 60.0f / dt;
        int bin = int((bpm - BTT_MIN_BPM) / ((BTT_MAX_BPM - BTT_MIN_BPM) / float(BTT_NUM_BINS)));
        if (bin >= 0 && bin < BTT_NUM_BINS)
            btt->histogram[bin]++;
    }

    std::cout << "\n📊 BPM Histogram:\n";
    for (int i = 0; i < BTT_NUM_BINS; ++i) {
        float binStart = BTT_MIN_BPM + i * ((BTT_MAX_BPM - BTT_MIN_BPM) / float(BTT_NUM_BINS));
        float binEnd = binStart + ((BTT_MAX_BPM - BTT_MIN_BPM) / float(BTT_NUM_BINS));
        std::cout << "[" << int(binStart) << "-" << int(binEnd) << "]: ";
        for (int k = 0; k < btt->histogram[i]; ++k) std::cout << "|";
        std::cout << " (" << btt->histogram[i] << ")\n";
    }


    std::cout << "🎯 Estimated BPM: " << btt->estimatedTempo << "\n";
}

const int* getHistogram(const BTT* btt) { return btt->histogram; }

float tempo(BTT* btt) {
    return btt ? btt->estimatedTempo : 0.0f;
}
// Dummy histogram: returns a static array for demonstration
float* histogram(BTT* btt) {
    // static (non deallocato mai) per esempio demo
    static float dummyHist[10] = { 0.1f, 0.3f, 0.7f, 0.6f, 0.8f, 0.9f, 0.2f, 0.1f, 0.05f, 0.0f };
    return dummyHist;
}
