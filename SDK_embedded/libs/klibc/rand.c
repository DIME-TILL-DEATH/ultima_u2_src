#include "reentrant.h"



//-----------------------------------------------------------------------
#ifdef __USE_REENTRANT__
   void  srand(unsigned seed) { ((reentrant_t*)reentrant)->rand_state = seed % (1<<31) ; }
#else
   static unsigned int rand_state ;
   void  srand(unsigned seed) { rand_state = seed % (1<<31) ; }
#endif
//-----------------------------------------------------------------------
#ifdef __USE_REENTRANT__
   int  rand() {  ((reentrant_t*)reentrant)->rand_state = ( 1103515245 * ((reentrant_t*)reentrant)->rand_state + 12345 ) & 0x7fffffff; return ((reentrant_t*)reentrant)->rand_state ; }
#else
   int  rand() { rand_state = ( 1103515245 * rand_state + 12345 ) & 0x7fffffff; return rand_state ; }
#endif


float  randf() { return rand () / ((float)0x7fffffff) ; }
double randd() { return rand () / ((double)0x7fffffffffffffff) ; }
//-----------------------------------------------------------------------


