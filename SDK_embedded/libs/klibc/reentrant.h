#ifndef __REENTRANT_H__
#define __REENTRANT_H__

#include <stdint.h>

#ifdef __cplusplus
    extern "C" {
#endif


#ifdef __USE_REENTRANT__

//-----------------------------------------------------------------------
typedef struct
{
   int          errno_val ;
   unsigned int rand_state ;
   char *       strtok_pos ;
} reentrant_t;
//-----------------------------------------------------------------------
extern reentrant_t* reentrant ;

void reentrant_deinit (void* val);
void reentrant_init   (void* val);

#endif


#ifdef __cplusplus
     }
#endif


#endif /*__REENTRANT_H__*/
