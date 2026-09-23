/*
 * __aeabi_impl.h
 *
 *  Created on: 28 янв. 2016 г.
 *      Author: klen
 */

#ifndef __AEABI_IMPL_H__
#define __AEABI_IMPL_H__

// KGP tools embedded SDK
// Chernov S.A. aka klen
// klen_s@mail.ru


#include "__cxa_impl.h"

#ifdef __cplusplus
 extern "C" {
#endif

     inline __attribute__((used)) int __aeabi_atexit(void* object, void (*destroyer)(void*), void* dso_handle)
      {
          // atexit(f) should call __aeabi_atexit (NULL, f, NULL)
          // The meaning of this function is given by the following model implementation...
          return __cxa_atexit(destroyer, object, dso_handle);
          // 0 ⇒ OK; non - 0 ⇒ failed
      }

#ifdef __cplusplus
  }
#endif


#endif /* __AEABI_IMPL_H__ */
