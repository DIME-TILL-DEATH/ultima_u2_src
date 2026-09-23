	.cpu cortex-m3
	.eabi_attribute 23, 1
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 2
	.eabi_attribute 34, 1
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
	.arch armv7-m
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, lr}
	ldr	r3, .L4
	ldr	r3, [r3]
	ldrd	r4, [r3]
	mov	r0, r4
	mov	r1, r5
	bl	sqrt
	mov	r2, r4
	mov	r3, r5
	bl	__aeabi_dadd
	mov	r2, r0
	mov	r3, r1
	mov	r0, r4
	mov	r1, r5
	bl	__aeabi_ddiv
	movs	r2, #0
	ldr	r3, .L4+4
	bl	__aeabi_dadd
	bl	__aeabi_d2iz
	pop	{r3, r4, r5, pc}
.L5:
	.align	2
.L4:
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
	.ident	"GCC: (Klen's GNU package (KGP) for x86_64-kgp-linux-gnu platform. << HELLEBORUS >>) 8.0.1 20180316 (experimental)"
