#include <limits.h>
#include "errno.h"

int isspace(int c);

unsigned long
strtoul(const char *nptr, char **endptr, register int base)
{
	register unsigned long acc;
	register unsigned char c;
	register unsigned long cutoff;
	register signed char any;
	unsigned char flag = 0;
#define FL_NEG	0x01		/* number is negative */
#define FL_0X	0x02		/* number has a 0x prefix */
	if (endptr)
		*endptr = (char *)nptr;
	if (base != 0 && (base < 2 || base > 36))
		return 0;
	/*
	 * See strtol for comments as to the logic used.
	 */
	do {
		c = *nptr++;
	} while (isspace(c));
	if (c == '-') {
		flag = FL_NEG;
		c = *nptr++;
	} else if (c == '+')
		c = *nptr++;
	if ((base == 0 || base == 16) &&
	    c == '0' && (*nptr == 'x' || *nptr == 'X')) {
		c = nptr[1];
		nptr += 2;
		base = 16;
		flag |= FL_0X;
	}
	if (base == 0)
		base = c == '0' ? 8 : 10;
	/*
	 * cutoff computation is similar to strtol().
	 *
	 * Description of the overflow detection logic used.
	 *
	 * First, let us assume an overflow.
	 *
	 * Result of `acc_old * base + c' is cut to 32 bits:
	 *  acc_new <-- acc_old * base + c - 0x100000000
	 *
	 *  `acc_old * base' is <= 0xffffffff   (cutoff control)
	 *
	 * then:   acc_new <= 0xffffffff + c - 0x100000000
	 *
	 * or:     acc_new <= c - 1
	 *
	 * or:     acc_new < c
	 *
	 * Second:
	 * if (no overflow) then acc * base + c >= c
	 *                        (or: acc_new >= c)
	 * is clear (alls are unsigned).
	 *
	 */
	switch (base) {
		case 16:    cutoff = ULONG_MAX / 16;  break;
		case 10:    cutoff = ULONG_MAX / 10;  break;
		case 8:     cutoff = ULONG_MAX / 8;   break;
		default:    cutoff = ULONG_MAX / base;
	}
	for (acc = 0, any = 0;; c = *nptr++) {
		if (c >= '0' && c <= '9')
			c -= '0';
		else if (c >= 'A' && c <= 'Z')
			c -= 'A' - 10;
		else if (c >= 'a' && c <= 'z')
			c -= 'a' - 10;
		else
			break;
		if (c >= base)
			break;
		if (any < 0)
			continue;
		if (acc > cutoff) {
			any = -1;
			continue;
		}
		acc = acc * base + c;
		any = (c > acc) ? -1 : 1;
	}
	if (endptr) {
		if (any)
			*endptr = (char *)nptr - 1;
		else if (flag & FL_0X)
			*endptr = (char *)nptr - 2;
	}
	if (flag & FL_NEG)
		acc = -acc;
	if (any < 0) {
		acc = ULONG_MAX;
		errno = ERANGE;
	}
	return (acc);
}
