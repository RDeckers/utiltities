#include <stdint.h>
#ifdef __cplusplus
#define EXTERN_C extern "C" {
#define EXTERN_C_END }
#else
#define EXTERN_C
#define EXTERN_C_END
#endif
EXTERN_C
inline unsigned iabs(int x){return x>0?x:-x;}
inline int signOf(int x){return x<0?-1:1;}

void generatePrimes(unsigned *primes, unsigned N_PRIMES);
int isqrt(int n);
unsigned usqrt(unsigned x); //fails on x= UINT_MAX, gives 0.
EXTERN_C_END
