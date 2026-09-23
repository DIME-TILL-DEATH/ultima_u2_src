#ifndef __RAND_H__
#define __RAND_H__

#ifdef __cplusplus
    extern "C" {
#endif

#include "stdint.h"

//-----------------------------------------------------------------------

void     srand(unsigned seed);
int      rand();
float    randf();
double   randd();

//-----------------------------------------------------------------------

#ifdef __cplusplus
     }
#endif

#endif /*__RAND_H__*/
