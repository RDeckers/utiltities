#include <stdint.h>
#ifndef _UTIL_INT_H
#define _UTIL_INT_H
#ifdef __cplusplus
extern "C"{
#endif

inline unsigned iabs(int x){return x>0?x:-x;}
inline int signOf(int x){return x<0?-1:1;}

void generatePrimes(unsigned *primes, unsigned N_PRIMES);
int isqrt(int n);
unsigned usqrt(unsigned x); //fails on x= UINT_MAX, gives 0.
unsigned triag_nr(unsigned x){
  return (x*x+x)/2;
}

#ifdef __cplusplus
}
#endif
#endif
