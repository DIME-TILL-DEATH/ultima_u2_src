#ifndef __SUPC++_H__
#define __SUPC++_H__

// KGP tools embedded SDK
// Chernov S.A. aka klen
// klen_s@mail.ru

#include <stddef.h> // define size_t
#include <bits/c++config.h> // nedded for _GLIBCXX_NOEXCEPT macro and c++ exception handler redefinition


//------------------------------------------------------------------
// default throw catchers
__attribute__((__noreturn__)) inline void throw_exeption_catcher()
{
  while(1)
       asm volatile("nop") ;
}

__attribute__((__noreturn__)) inline void throw_exeption_catcher(const char* msg)
{
  // save mgs addr to r0 for avoid GCC optimisation
  asm volatile ("ldr r0 , %[msg]" : : [msg]"m" (msg) : ) ;
  while(1)
       asm volatile("nop") ;
}

__attribute__((__noreturn__)) inline void throw_exeption_catcher(const char* msg, int val)
{
  // save mgs addr to r0 for avoid GCC optimisation
  asm volatile ("ldr r0 , %[val]" : : [val]"m" (val) : ) ;
  asm volatile ("ldr r1 , %[msg]" : : [msg]"m" (msg) : ) ;
  while(1)
       asm volatile("nop") ;
}

__attribute__((__noreturn__)) inline void throw_exeption_catcher(const char* msg, unsigned int val)
{
  // save mgs addr to r0 for avoid GCC optimisation
  asm volatile ("ldr r0 , %[val]" : : [val]"m" (val) : ) ;
  asm volatile ("ldr r1 , %[msg]" : : [msg]"m" (msg) : ) ;
  while(1)
       asm volatile("nop") ;
}

__attribute__((__noreturn__)) inline void throw_exeption_catcher(int val)
{
  // save val to r0 for avoid GCC optimisation
  asm volatile ("ldr r0 , %[val]" : : [val]"m" (val) : ) ;
  while(1)
       asm volatile("nop") ;
}


// переопределение обработчиков исключений
#include <bits/exception_defines.h>

#define THROW_CATCHER_ARG1(name,arg_t,arg_v) __attribute__((__noreturn__)) inline void name(arg_t arg_v)   {throw_exeption_catcher(arg_v);}
#define THROW_CATCHER_ARG2(name,arg0_t,arg0_v,arg1_t,arg1_v) __attribute__((__noreturn__)) inline void name(arg0_t arg0_v, arg1_t arg1_v)   {throw_exeption_catcher(arg0_v,arg1_v);}
#define THROW_CATCHER_FMT(name)                   __attribute__((__noreturn__,__format__(__printf__, 1, 2))) \
                                                                                     inline void name(const char* fmt, ...) {throw_exeption_catcher(fmt);}

namespace std _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION

THROW_CATCHER_ARG1(__throw_bad_exception,void,)                // Helper for exception objects in <except>
THROW_CATCHER_ARG1(__throw_bad_alloc,void,)                    // Helper for exception objects in <new>
THROW_CATCHER_ARG1(__throw_bad_cast,void,)                     // Helper for exception objects in <typeinfo>
THROW_CATCHER_ARG1(__throw_bad_typeid,void,)
THROW_CATCHER_ARG1(__throw_logic_error,const char*,msg)        // Helpers for exception objects in <stdexcept>


//THROW_CATCHER_ARG(void,__throw_logic_error,const char*,msg)        // Helpers for exception objects in <stdexcept>
//void __throw_logic_error(const char* msg)
//{
//  throw_exeption_catcher(msg)
//}

THROW_CATCHER_ARG1(__throw_domain_error,const char*,msg)
THROW_CATCHER_ARG1(__throw_invalid_argument,const char*,msg)
THROW_CATCHER_ARG1(__throw_length_error,const char*,msg)
THROW_CATCHER_ARG1(__throw_out_of_range,const char*,msg)
THROW_CATCHER_ARG2(__throw_out_of_range,const char*,msg,int,val)
THROW_CATCHER_ARG1(__throw_runtime_error,const char*,msg)
THROW_CATCHER_ARG1(__throw_range_error,const char*,msg)
THROW_CATCHER_ARG1(__throw_overflow_error,const char*,msg)
THROW_CATCHER_ARG1(__throw_underflow_error,const char*,msg)
THROW_CATCHER_ARG1(__throw_ios_failure,const char*,msg)        // Helpers for exception objects in <ios>
THROW_CATCHER_ARG1(__throw_system_error,int,val)
THROW_CATCHER_ARG1(__throw_future_error,int,val)
THROW_CATCHER_ARG1(__throw_bad_function_call,void,)            // Helpers for exception objects in <functional>
THROW_CATCHER_FMT(__throw_out_of_range_fmt)

// klen's std ecxeption extension
THROW_CATCHER_ARG2(__throw_internal_error,const char*,msg,unsigned int,val)
THROW_CATCHER_ARG2(__throw_hardware_error,const char*,msg,unsigned int,val)
THROW_CATCHER_ARG1(__throw_memmgr_error,const char*,msg)
THROW_CATCHER_ARG1(__throw_unhandled_sycall,int,val)

_GLIBCXX_END_NAMESPACE_VERSION
} // namespace


namespace __gnu_cxx
{
  _GLIBCXX_BEGIN_NAMESPACE_VERSION

  THROW_CATCHER_ARG1(__verbose_terminate_handler,void,)

  _GLIBCXX_END_NAMESPACE_VERSION
};


extern "C" void *malloc( size_t size ) ;
extern "C" void  free( void* pv );


// see referense of 'noexcept' in $TARGET/lib/gcc/$TARGET/X.X.X/include/c++/$TARGET/bits/c++config.h
// _GLIBCXX_NOEXCEPT is macro wrap of noexcept

// размещающие версии new/delete определять не нужно - они как тривиальные inline функции
// определены в include/c++/new

//------------------------------------------------------------------
// определение функции оператор new
inline void* operator new(size_t size) /*_GLIBCXX_NOEXCEPT*/
  {
    return malloc (size) ;
  }
//------------------------------------------------------------------
// определение функции оператор delete
inline void operator delete(void* ptr) _GLIBCXX_NOEXCEPT
  {
    free(ptr) ;
  }
inline void operator delete(void* ptr , size_t size) _GLIBCXX_NOEXCEPT
  {
    free(ptr) ;
  }
//------------------------------------------------------------------
// определение функции оператор new[]
inline void* operator new[] (size_t size) /*_GLIBCXX_NOEXCEPT*/
  {
    return malloc (size) ;
  }
//------------------------------------------------------------------
// определение функции оператор delete[]
inline void operator delete[] (void* ptr) _GLIBCXX_NOEXCEPT
  {
    free(ptr) ;
  }
inline void operator delete[] (void* ptr, size_t size) _GLIBCXX_NOEXCEPT
  {
    free(ptr) ;
  }


#endif /* __SUPC++_H__ */
