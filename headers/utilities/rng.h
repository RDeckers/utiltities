#ifndef _RNG_INT_H
#define _RNG_INT_H
#ifdef __cplusplus
extern "C"{
#endif
#include <stdint.h>

uint32_t fast_rng(){
  static uint64_t state = 0xdeadbeef;
  return (state = state*6364136223846793005UL+1442695040888963407UL); //Knuth, https://en.wikipedia.org/wiki/Linear_congruential_generator#Parameters_in_common_use
}

float fast_rngf(float min, float max){
  return min+((float)rng()/0xFFFFFFFF)*(max-min);
}

#ifdef __cplusplus
}
#endif
#endif
