#include "reentrant.h"
#include "stddef.h"

#ifdef __USE_REENTRANT__

   reentrant_t* reentrant ;

   void reentrant_deinit (void* val)
      {
         void free(void*);
         free(val);
      }

   /*void reentrant_init   (void** val)
      {
         void* malloc (size_t);
         (*val) = malloc ( sizeof(reentrant_t) ) ;
         ((reentrant_t*)(*val))->errno_val = 0 ;
         ((reentrant_t*)(*val))->rand_state = 0 ;
         ((reentrant_t*)(*val))->strtok_pos = 0 ;
      }*/

   void reentrant_init   (void* val)
      {
         ((reentrant_t*)(val))->errno_val = 0 ;
         ((reentrant_t*)(val))->rand_state = 0 ;
         ((reentrant_t*)(val))->strtok_pos = 0 ;
      }

#else

#endif
