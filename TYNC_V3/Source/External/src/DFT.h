#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DFT DFT;

DFT* new_DFT(int size);
void free_DFT(DFT* dft);

void compute_DFT(DFT* dft, const float* input);

#ifdef __cplusplus
}
#endif
