#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct STFT STFT;

STFT* new_STFT(int windowSize, float hopFactor);
void free_STFT(STFT*);

void process_STFT(STFT* stft, const float* input, int numSamples);

#ifdef __cplusplus
}
#endif
