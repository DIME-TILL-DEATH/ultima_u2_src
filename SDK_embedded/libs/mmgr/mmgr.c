#include "tlsf.h"
#include "mmgr.h"
#include <string.h>

#if defined __USE_FREERTOS__



  void heap_take_stub() {}
  void heap_give_stub() {}

  static heap_sync_fn_t heap_take = heap_take_stub;
  static heap_sync_fn_t heap_give = heap_give_stub;

  void heap_sync_reset ()
   {
          heap_take = heap_take_stub ;
          heap_give = heap_give_stub ;
   }

  void  heap_sync_set ( heap_sync_fn_t take, heap_sync_fn_t give)
   {
      if ( take && give )
         {
            heap_take = take ;
            heap_give = give ;
         }
   }

#endif

void __attribute__((weak)) heap_error_handler()
{
    while(1)
      {
	__asm__ volatile ("nop");
      }
}

static tlsf_t tlsf = NULL ;

// ---------------    POOLS DESCRIPTIONS ------------------
#if defined (CCM_SRAM_POOL_SIZE)
   __attribute__ ((section(".ccm_bss"))) static char ccm_sram_pool[CCM_SRAM_POOL_SIZE] ;
#endif

#if defined (INTERNAL_SRAM_POOL_SIZE)
   static char  internal_sram_pool[INTERNAL_SRAM_POOL_SIZE] ;
#endif

#if defined (EXT_MEM_BANK0_POOL_SIZE)
   __attribute__ ((section(".ext_mem_bank0_bss")))  static char ext_mem_bank0_pool[EXT_MEM_BANK0_POOL_SIZE] ;
#endif

#if defined (EXT_MEM_BANK1_POOL_SIZE)
   __attribute__ ((section(".ext_mem_bank1_bss")))  static char ext_mem_bank1_pool[EXT_MEM_BANK1_POOL_SIZE] ;
#endif

#if defined (EXT_MEM_BANK2_POOL_SIZE)
   __attribute__ ((section(".ext_mem_bank2_bss")))  static char ext_mem_bank2_pool[EXT_MEM_BANK2_POOL_SIZE] ;
#endif

#if defined (EXT_MEM_BANK3_POOL_SIZE)
   __attribute__ ((section(".ext_mem_bank3_bss")))  static char ext_mem_bank3_pool[EXT_MEM_BANK3_POOL_SIZE] ;
#endif

   typedef enum {
                    // if not user defined internal sram area, used a default  INTERNAL_SRAM_POOL_SIZE = 0 heap dummy
                    #if defined (CCM_SRAM_POOL_SIZE)
                        hpiCcmSram,
                    #endif

                    #if defined (INTERNAL_SRAM_POOL_SIZE)
                        hpiInternalSram,
                    #endif

                    #if defined (EXT_MEM_BANK0_POOL_SIZE)
   		     hpiExtMemBank0,
                    #endif

                    #if defined (EXT_MEM_BANK1_POOL_SIZE)
   		     hpiExtMemBank1,
                    #endif

                    #if defined (EXT_MEM_BANK2_POOL_SIZE)
   		     hpiExtMemBank2,
                    #endif

                    #if defined (EXT_MEM_BANK3_POOL_SIZE)
   		     hpiExtMemBank3,
                    #endif

   		 hpiHeapPoolsCount
                } heap_pool_id_t ;

pool_t* heap_pools[ hpiHeapPoolsCount ] ;

size_t  heap_get_pools(void*** ptr) { *ptr = (void**)heap_pools ; return hpiHeapPoolsCount ; }



#if defined __USE_FREERTOS__

  void heap_sync_init ( heap_sync_fn_t take, heap_sync_fn_t give)
   {
    if ( take && give )
       {
          heap_take = take ;
          heap_give = give ;
       }

    heap_init();

   }
#endif


void heap_init()
    {
                    #if defined (CCM_SRAM_POOL_SIZE)

                        if ( !(tlsf = tlsf_create_with_pool(ccm_sram_pool, CCM_SRAM_POOL_SIZE)))  heap_error_handler();
                        if ( !(heap_pools[hpiCcmSram] = tlsf_get_pool(tlsf)))                     heap_error_handler();

                    #endif

                    #if defined (INTERNAL_SRAM_POOL_SIZE)
                        if(tlsf)
                           {
                              if (!(heap_pools[hpiInternalSram] = tlsf_add_pool(tlsf, internal_sram_pool, INTERNAL_SRAM_POOL_SIZE))) heap_error_handler();
                           }
                        else
                           {
                              if(!(tlsf = tlsf_create_with_pool(internal_sram_pool, INTERNAL_SRAM_POOL_SIZE))) heap_error_handler();
                              if(!(heap_pools[hpiInternalSram] = tlsf_get_pool(tlsf)))             heap_error_handler();
                           }


                    #endif

                    #if defined (EXT_MEM_BANK0_POOL_SIZE)
                        if(tlsf)
                          {
                              if (!(heap_pools[hpiExtMemBank0] = tlsf_add_pool(tlsf, ext_mem_bank0_pool, EXT_MEM_BANK0_POOL_SIZE))) heap_error_handler();
                          }
                        else
                          {
                              if(!(tlsf = tlsf_create_with_pool(ext_mem_bank0_pool, EXT_MEM_BANK0_POOL_SIZE))) heap_error_handler();
                              if(!(heap_pools[hpiExtMemBank0] = tlsf_get_pool(tlsf)))             heap_error_handler();
                          }
                    #endif

                    #if defined (EXT_MEM_BANK1_POOL_SIZE)
                        if(tlsf)
                          {
                              if (!(heap_pools[hpiExtMemBank1] = tlsf_add_pool(tlsf, ext_mem_bank1_pool, EXT_MEM_BANK1_POOL_SIZE))) heap_error_handler();
                          }
                        else
                          {
                              if(!(tlsf = tlsf_create_with_pool(ext_mem_bank1_pool, EXT_MEM_BANK1_POOL_SIZE))) heap_error_handler();
                              if(!(heap_pools[hpiExtMemBank1] = tlsf_get_pool(tlsf)))             heap_error_handler();
                          }
                   #endif

                   #if defined (EXT_MEM_BANK2_POOL_SIZE)
                        if(tlsf)
                          {
                              if (!(heap_pools[hpiExtMemBank2] = tlsf_add_pool(tlsf, ext_mem_bank2_pool, EXT_MEM_BANK2_POOL_SIZE))) heap_error_handler();
                          }
                        else
                          {
                              if(!(tlsf = tlsf_create_with_pool(ext_mem_bank2_pool, EXT_MEM_BANK2_POOL_SIZE))) heap_error_handler();
                              if(!(heap_pools[hpiExtMemBank2] = tlsf_get_pool(tlsf)))             heap_error_handler();
                          }
                   #endif

                   #if defined (EXT_MEM_BANK3_POOL_SIZE)
                        if(tlsf)
                          {
                              if (!(heap_pools[hpiExtMemBank3] = tlsf_add_pool(tlsf, ext_mem_bank3_pool, EXT_MEM_BANK3_POOL_SIZE))) heap_error_handler();
                          }
                        else
                          {
                              if(!(tlsf = tlsf_create_with_pool(ext_mem_bank3_pool, EXT_MEM_BANK3_POOL_SIZE))) heap_error_handler();
                              if(!(heap_pools[hpiExtMemBank3] = tlsf_get_pool(tlsf)))             heap_error_handler();
                          }
                   #endif
        }

void heap_deinit() { tlsf_destroy(tlsf) ; }
void*  heap_ptr()  { return  tlsf ; }

size_t heap_size()
{
   size_t size = 0 ;

   #if defined (CCM_SRAM_POOL_SIZE)
      size +=CCM_SRAM_POOL_SIZE ;
   #endif

   #if defined (INTERNAL_SRAM_POOL_SIZE)
      size +=INTERNAL_SRAM_POOL_SIZE ;
   #endif

   #if defined (EXT_MEM_BANK0_POOL_SIZE)
      size +=EXT_MEM_BANK0_POOL_SIZE ;
  #endif

  #if defined (EXT_MEM_BANK1_POOL_SIZE)
      size +=EXT_MEM_BANK1_POOL_SIZE ;
  #endif

  #if defined (EXT_MEM_BANK2_POOL_SIZE)
      size +=EXT_MEM_BANK2_POOL_SIZE ;
  #endif

  #if defined (EXT_MEM_BANK3_POOL_SIZE)
      size +=EXT_MEM_BANK3_POOL_SIZE ;
  #endif

   return size ;
}

size_t heap_control_stuct_size() { return tlsf_size()           ;}
size_t heap_align_size()         { return tlsf_align_size()     ;}
size_t heap_block_size_min()     { return tlsf_block_size_min() ;}
size_t heap_block_size_max()     { return tlsf_block_size_max() ;}
size_t heap_pool_overhead()      { return tlsf_pool_overhead()  ;}

#if defined __USE_FREERTOS__

#include "FreeRTOS.h"
#include "task.h"


/*-----------------------------------------------------------*/

void* malloc( const size_t size )
{
        void *pvReturn;

        heap_take();
	{
		pvReturn = tlsf_malloc( tlsf , size);
		traceMALLOC( pvReturn, size );
	}
	heap_give();

	#if( configUSE_MALLOC_FAILED_HOOK == 1 )
	{
		if( pvReturn == NULL )
		{
			extern void vApplicationMallocFailedHook( void );
			vApplicationMallocFailedHook();
		}
	}
	#endif

	return pvReturn;
}
/*-----------------------------------------------------------*/
void* calloc(const size_t nelem, const size_t elem_size)
{
  void *pvReturn;

        heap_take();
	{
		pvReturn = tlsf_malloc( tlsf , nelem * elem_size);
		if (pvReturn)
		  __builtin_memset(pvReturn,0, nelem * elem_size);
		traceMALLOC( pvReturn, size );
	}
	heap_give();

	#if( configUSE_MALLOC_FAILED_HOOK == 1 )
	{
		if( pvReturn == NULL )
		{
			extern void vApplicationMallocFailedHook( void );
			vApplicationMallocFailedHook();
		}
	}
	#endif

	return pvReturn;
}
/*-----------------------------------------------------------*/
void* realloc(void *ptr, const size_t size)
{
  void *pvReturn;

        heap_take();
  	{
  		pvReturn = tlsf_realloc(tlsf , ptr, size);
  		traceMALLOC( pvReturn, size );
  	}
  	heap_give();

  	#if( configUSE_MALLOC_FAILED_HOOK == 1 )
  	{
  		if( pvReturn == NULL )
  		{
  			extern void vApplicationMallocFailedHook( void );
  			vApplicationMallocFailedHook();
  		}
  	}
  	#endif

  	return pvReturn;
}
/*-----------------------------------------------------------*/
void free( void *pv )
{
	if( pv )
	{
	        heap_take();
		{
			tlsf_free( tlsf , pv );
			traceFREE( pv, 0 );
		}
		heap_give();
	}
}


void* pvPortMalloc( size_t size ) __attribute__ ((nothrow, malloc, alloc_size(1), leaf, alias ("malloc"))) ;
void vPortFree( void* pv ) __attribute__ ((nothrow, leaf, alias ("free")));

size_t heap_block_size(const void* ptr)
{
  size_t size ;
  heap_take();
  size = tlsf_block_size(ptr) ;
  heap_give();
  return size ;
}

void heap_walk_pool( const void* pool,  heap_walker_fnc_t walker,  const void* user)
{
  heap_take();
  tlsf_walk_pool((pool_t)pool, (tlsf_walker)walker, user);
  heap_give();
}

#else

void* malloc(size_t size)                    { return tlsf_malloc(tlsf , size); }
void* calloc(size_t nelem, size_t elem_size) { return tlsf_malloc(tlsf , nelem * elem_size); }
void* realloc(void *ptr, size_t size)        { return tlsf_realloc(tlsf , ptr, size); }
void  free(void *ptr)                  { tlsf_free( tlsf , ptr ); }

size_t heap_block_size(const void* ptr)            { return tlsf_block_size(ptr) ; }
void heap_walk_pool(const void* pool, heap_walker_fnc_t walker, const void* user)
{
  tlsf_walk_pool((pool_t)pool, (tlsf_walker)walker, user);
}

#endif
