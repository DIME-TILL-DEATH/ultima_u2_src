#include <setjmp.h>





 void	__attribute__ (( naked )) longjmp(jmp_buf jmpb, int retval)
{
   #if defined(__ARM_ARCH_6M__)

       __asm__ volatile ("add	r0, r0, #16               \n");
       __asm__ volatile ("ldmia	r0!, {r2, r3, r4, r5, r6} \n");
       __asm__ volatile ("mov	r8, r2                    \n");
       __asm__ volatile ("mov	r9, r3                    \n");
       __asm__ volatile ("mov	r10, r4                   \n");
       __asm__ volatile ("mov	fp, r5                    \n");
       __asm__ volatile ("mov	sp, r6                    \n");
       __asm__ volatile ("ldmia	r0!, {r3}                 \n"); /* lr */
   	/* Restore low regs.  */
       __asm__ volatile ("sub	r0, r0, #40               \n");
       __asm__ volatile ("ldmia	r0!, {r4, r5, r6, r7}     \n");
        /* Return the result argument, or 1 if it is zero.  */
       __asm__ volatile ("mov	r0, r1                    \n");
       __asm__ volatile ("bne	1f                        \n");
       __asm__ volatile ("mov	r0, #1                    \n");
       __asm__ volatile ("      1:                            \n");
       __asm__ volatile ("bx	r3                        \n");

   #else

  	/* If we have stack extension code it ought to be handled here.  */

  	/* Restore the registers, retrieving the state when setjmp() was called.  */
  #ifdef __thumb2__
  	__asm__ volatile ("ldmfd a1!, { v1-v7, fp, ip, lr }");
  	__asm__ volatile ("mov sp, ip");
  #else
  	__asm__ volatile ("ldmfd a1!, { v1-v7, fp, ip, sp, lr }");
  #endif

  	/* Put the return value into the integer result register.
  	   But if it is zero then return 1 instead.  */
  	__asm__ volatile ("movs a1, a2");
  #ifdef __thumb2__
  	__asm__ volatile ("it eq");
  #endif
  	__asm__ volatile ("moveq a1, #1");

  #ifdef __APCS_26__
	__asm__ volatile ("movs pc, lr");
  #elif defined(__thumb2__)
	__asm__ volatile ("bx lr");
  #else
	__asm__ volatile ("tst		lr, #1");
	__asm__ volatile ("moveq		pc, lr");
	__asm__ volatile (".word           0xe12fff1e	/* bx lr */");
  #endif

  #endif // __ARM_ARCH_6M__
}

 int __attribute__ (( naked )) setjmp(jmp_buf jmpb)
{
	//FUNC_START setjmp

#if defined(__ARM_ARCH_6M__)
	/* Save registers in jump buffer.  */
       __asm__ volatile ("stmia r0!, {r4, r5, r6, r7}          \n");
       __asm__ volatile ("mov   r1, r8                         \n");
       __asm__ volatile ("mov   r2, r9                         \n");
       __asm__ volatile ("mov   r3, r10                        \n");
       __asm__ volatile ("mov   r4, fp                         \n");
       __asm__ volatile ("mov   r5, sp                         \n");
       __asm__ volatile ("mov   r6, lr                         \n");
       __asm__ volatile ("stmia r0!, {r1, r2, r3, r4, r5, r6}  \n");
       __asm__ volatile ("sub   r0, r0, #40                    \n");
       /* Restore callee-saved low regs.  */
       __asm__ volatile ("ldmia r0!, {r4, r5, r6, r7}          \n");
       /* Return zero.  */
       __asm__ volatile ("mov   r0, #0                         \n");
       __asm__ volatile ("bx    lr                             \n");

#else

	/* Save all the callee-preserved registers into the jump buffer.  */
#ifdef __thumb2__
	__asm__ volatile ("mov ip, sp") ;
	__asm__ volatile ("stmea a1!, { v1-v7, fp, ip, lr }") ;
#else
	__asm__ volatile ("stmea a1!, { v1-v7, fp, ip, sp, lr }");
#endif

	/* When setting up the jump buffer return 0.  */
	__asm__ volatile ("mov a1, #0");

#ifdef __APCS_26__
	__asm__ volatile ("movs pc, lr");
#elif defined(__thumb2__)
	__asm__ volatile ("bx lr");
#else
	__asm__ volatile ("tst		lr, #1");
	__asm__ volatile ("moveq		pc, lr");
	__asm__ volatile (".word           0xe12fff1e	/* bx lr */");
#endif

#endif // __ARM_ARCH_6M__
}

