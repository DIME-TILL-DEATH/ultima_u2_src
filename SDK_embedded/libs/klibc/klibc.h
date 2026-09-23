#ifndef __KLIBC_H__
#define __KLIBC_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" 
  {
#endif



#define __expect(foo,bar) (foo)
#define __expect(foo,bar) __builtin_expect((long)(foo),bar)
#define __likely(foo)   __expect((foo),1)
#define __unlikely(foo) __expect((foo),0)



#ifdef __cplusplus
  }
#endif



#endif  __KLIBC_H__
