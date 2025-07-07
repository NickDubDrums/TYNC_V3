#pragma once

#define BTT_NUM_BINS 20
#define BTT_MIN_BPM 40.0f
#define BTT_MAX_BPM 240.0f


#ifdef __cplusplus
extern "C" {
#endif

	typedef float dft_sample_t;

	typedef struct BTT BTT;

	BTT* new_BTT(float sampleRate);
	void free_BTT(BTT*);

	void track(BTT*, dft_sample_t* input, int numSamples);
	float tempo(BTT*);

	// Dummy histogram: returns a static array of 10 values between 0-1
	float* histogram(BTT* btt);

	const int* getHistogram(const BTT* btt);


#ifdef __cplusplus
}
#endif
