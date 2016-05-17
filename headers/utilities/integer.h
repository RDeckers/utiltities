#include <stdint.h>
#ifndef _UTIL_INT_H
#define _UTIL_INT_H
#ifdef __cplusplus
extern "C"{
#endif
317
inline unsigned iabs(int x){return x>0?x:-x;}
inline int signOf(int x){return x<0?-1:1;}

void generatePrimes(unsigned *primes, unsigned N_PRIMES);
int isqrt(int n);
unsigned usqrt(unsigned x); //fails on x= UINT_MAX, gives 0.

#ifdef __cplusplus
}
#endif
#endif
