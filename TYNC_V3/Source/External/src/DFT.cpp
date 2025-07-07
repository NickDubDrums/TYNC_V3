#include "DFT.h"
#include <cmath>
#include <cstdlib>

struct DFT {
    int size;
    float* real;
    float* imag;
};

DFT* new_DFT(int size) {
    DFT* dft = new DFT;
    dft->size = size;
    dft->real = new float[size];
    dft->imag = new float[size];
    return dft;
}

void free_DFT(DFT* dft) {
    if (!dft) return;
    delete[] dft->real;
    delete[] dft->imag;
    delete dft;
}

void compute_DFT(DFT* dft, const float* input) {
    if (!dft || !input) return;

    int N = dft->size;
    for (int k = 0; k < N; ++k) {
        dft->real[k] = 0.0f;
        dft->imag[k] = 0.0f;
        for (int n = 0; n < N; ++n) {
            float angle = 2.0f * 3.14159265f * k * n / N;
            dft->real[k] += input[n] * cosf(angle);
            dft->imag[k] -= input[n] * sinf(angle);
        }
    }
}
