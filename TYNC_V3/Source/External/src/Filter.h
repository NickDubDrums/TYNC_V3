#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SimpleFilter SimpleFilter;

SimpleFilter* new_SimpleFilter(float alpha);
void free_SimpleFilter(SimpleFilter* f);

float filter_sample(SimpleFilter* f, float input);

#ifdef __cplusplus
}
#endif
