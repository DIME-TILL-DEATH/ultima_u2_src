/*
 * __cxa_impl.h
 *
 *  Created on: 28 янв. 2016 г.
 *      Author: klen
 */

#ifndef __CXA_IMPL_H__
#define __CXA_IMPL_H__

// KGP tools embedded SDK
// Chernov S.A. aka klen
// klen_s@mail.ru

#ifdef __cplusplus
 extern "C" {
#endif

   __extension__ typedef int __guard __attribute__((mode (__DI__)));

   inline __attribute__((noreturn,used)) int __cxa_atexit(void (*func) (void *), void * arg, void * dso_handle)
      {
          throw_exeption_catcher();
      }

   inline __attribute__((noreturn,used)) int __cxa_guard_acquire(__guard* g)
      {
          throw_exeption_catcher();
          //return !*g;
      }

   inline __attribute__((noreturn,used)) void __cxa_guard_release (__guard* g)
      {
          throw_exeption_catcher();
          //*g = 1;
      }

   inline  __attribute__((noreturn,used)) void __cxa_guard_abort (__guard*)
      {
          throw_exeption_catcher();
      }

   inline __attribute__((noreturn,used)) void __cxa_pure_virtual()
      {
        throw_exeption_catcher();
      }

#ifdef __cplusplus
 }
#endif



#endif


