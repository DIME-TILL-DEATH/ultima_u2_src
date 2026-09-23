/*
 * sunset_ui.h
 *
 *  Created on: 18 окт. 2014 г.
 *      Author: klen
 */

#ifndef __LIBSUNSET_SUNSET_UI_H__
#define __LIBSUNSET_SUNSET_UI_H__

#include <stddef.h>

// SunSet Object loader user interface
#ifdef __cplusplus
    extern "C"  {
#endif

 inline const void* SunSet(const char* lib, const char* obj)
{
   extern unsigned long  __FLASH_start__ ;
   extern unsigned long  __sunset_start__ ;
   extern unsigned long  __vec_start__ ;

   typedef const void* (*sunset_entry_t) (const char* , const char*) ;

   return ((sunset_entry_t)((size_t)&__FLASH_start__ + (size_t)&__sunset_start__ - (size_t)&__vec_start__ + 1))(lib,obj) ;
}  

#ifdef __cplusplus
    }
#endif




#endif /* __LIBSUNSET_SUNSET_UI_H__ */
