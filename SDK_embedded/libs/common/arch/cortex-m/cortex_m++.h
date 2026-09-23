#ifndef __CORTEX_M++_H__
#define __CORTEX_M++_H__

  #define IRQ_HANDLER(name)               extern "C" void __attribute__((noinline)) name##_irq_handler()
  #define IRQ_HANDLER_SECTION(name,place) extern "C" void __attribute__((noinline,section(place))) name##_irq_handler()
  #define IRQ_HANDLER_ITCM(name)          extern "C" void __attribute__((noinline,section(".itcm_data"))) name##_irq_handler()
  #define IRQ_HANDLER_WEAK(name)          extern "C" void __attribute__((weak,noinline,alias("default_exception_handler"))) name##_irq_handler()
  #define IRQ_HANDLER_LINK(linkage,name)  linkage void name()

  // используется при инициализации таблицы векторв прерываний
  #define IRQ_VECTOR(name)                 name##_irq_handler
  #define IRQ_VECTOR_EXTERN(name)          name


namespace cortex_m
{
  typedef void( *irq_handler_t )( void );

   // get a number of Exception
   // result:
   //      [-16...239] - Handler CPU mode, result val is ISR number
   //      0 - a Thread CPU Mode, more than 0 a Handler CPU mode
   inline __attribute__( ( always_inline ) ) static ipsr_t::exception_num_t cpu_exception_num()
     {
       ipsr_t::exception_num_t cpu_exception_num;
       asm volatile ("mrs %[cpu_exception_num], ipsr" : [cpu_exception_num] "=r" (cpu_exception_num) );
       return cpu_exception_num ;
     }

}

using namespace cortex_m ;


/* init value for the stack pointer. defined in linker script */
extern uint32_t __stack_end__;

// объявление символов не лежащих в пространстве имен stm32
int main () ;
extern "C"  void (*__preinit_array_start__ []) (void) ;
extern "C"  void (*__preinit_array_end__ []) (void) ;
extern "C"  void (*__init_array_start__ []) (void) ;
extern "C"  void (*__init_array_end__ []) (void) ;

extern "C"  void (*__fini_array_start__ []) (void);
extern "C"  void (*__fini_array_end__ []) (void);

extern "C" void _init (void);
extern "C" void _fini (void);
extern "C" void __main_exit_handler(int retval);


#endif // __CORTEX_M++_H__



