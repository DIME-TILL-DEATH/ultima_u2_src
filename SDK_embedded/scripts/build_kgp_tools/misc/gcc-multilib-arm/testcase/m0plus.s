	.cpu cortex-m0plus
	.eabi_attribute 23, 1
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 2
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"a.cc"
	.text
	.global	__aeabi_dadd
	.global	__aeabi_ddiv
	.global	__aeabi_d2iz
	.section	.text.startup,"ax",%progbits
	.align	1
	.p2align 2,,3
	.global	main
	.arch armv6s-m
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L3
	push	{r4, r5, r6, lr}
	ldr	r3, [r3]
	@ sp needed
	ldr	r4, [r3]
	ldr	r5, [r3, #4]
	movs	r1, r5
	movs	r0, r4
	bl	sqrt
	movs	r3, r5
	movs	r2, r4
	bl	__aeabi_dadd
	movs	r2, r0
	movs	r3, r1
	movs	r0, r4
	movs	r1, r5
	bl	__aeabi_ddiv
	movs	r2, #0
	ldr	r3, .L3+4
	bl	__aeabi_dadd
	bl	__aeabi_d2iz
	pop	{r4, r5, r6, pc}
.L4:
	.align	2
.L3:
	.word	.LANCHOR0
	.word	1072693248
	.size	main, .-main
	.global	ptr
	.data
	.align	2
	.set	.LANCHOR0,. + 0
	.type	ptr, %object
	.size	ptr, 4
ptr:
	.word	291
	.ident	"GCC: (Klen's GNU package (KGP) for target::arm-kgp-eabi @ host::x86_64-kgp-linux-gnu, << PLANTAGO >>) 9.0.0 20181201 (experimental)"
