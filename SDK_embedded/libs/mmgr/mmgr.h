/*
 * mmgr.h
 *
 *  Created on: 15.09.2012
 *      Author: klen
 */

#ifndef MMGR_H_
#define MMGR_H_

#include "stddef.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined __USE_FREERTOS__
  typedef void (*heap_sync_fn_t)();

  void heap_sync_reset ();
  void heap_sync_set ( heap_sync_fn_t take, heap_sync_fn_t give);

  void heap_sync_init( heap_sync_fn_t take, heap_sync_fn_t give);

#endif

  void  heap_init();


  void  heap_error_handler();

  size_t  heap_get_pools(void*** ptr);


  void  heap_deinit();


  size_t heap_block_size(const void* ptr);
  size_t heap_control_stuct_size();
  size_t heap_align_size();
  size_t heap_block_size_min();
  size_t heap_block_size_max();
  size_t heap_pool_overhead();

  void*  heap_ptr();
  size_t heap_size();

void*  malloc(const size_t size);
void*  memalign(const size_t size, size_t align);
void*  realloc(void *ptr, const size_t size);
void*  calloc(const size_t nelem, const size_t elem_size);
void   free(void *ptr);

typedef void (*heap_walker_fnc_t)(const void* ptr, const size_t size, const int used, const void* user);
void heap_walk_pool( const void* pool,  heap_walker_fnc_t walker,  const void* user);

#ifdef __cplusplus
  }
#endif

#endif /* MMGR_H_ */
