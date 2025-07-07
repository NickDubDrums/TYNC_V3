#include "Filter.h"
#include <cstdlib>

struct SimpleFilter {
    float alpha;
    float prev;
};

SimpleFilter* new_SimpleFilter(float alpha) {
    SimpleFilter* f = new SimpleFilter;
    f->alpha = alpha;
    f->prev = 0.0f;
    return f;
}

void free_SimpleFilter(SimpleFilter* f) {
    delete f;
}

float filter_sample(SimpleFilter* f, float input) {
    if (!f) return input;
    float output = f->alpha * input + (1.0f - f->alpha) * f->prev;
    f->prev = output;
    return output;
}
