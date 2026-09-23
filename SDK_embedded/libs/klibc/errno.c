#include "errno.h"

#ifdef __USE_REENTRANT__

#include "reentrant.h"

   int* __attribute__((used)) __errno(void)
     {
        return &( ((reentrant_t*)reentrant)->errno_val) ;
     }
#else
   static int errno_val ;

   int* __attribute__((used)) __errno(void)
     {
        return (int*)&errno_val ;
     }
#endif




