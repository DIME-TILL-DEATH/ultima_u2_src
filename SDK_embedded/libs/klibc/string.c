#include "string.h"

#define __expect(foo,bar) __builtin_expect((long)(foo),bar)
#define __likely(foo)   __expect((foo),1)
#define __unlikely(foo) __expect((foo),0)

#define likely(x)	__builtin_expect(!!(x), 1)
#define unlikely(x)	__builtin_expect(!!(x), 0)


//-------------------------------------------------------------------
void* memcpy (void* dst0 , const void* src0 , size_t len0)
{

  char  *dst = (char *) dst0;
  char  *src = (char *) src0;

  char  *save =  (char *)dst0;

  while (len0--)
    {
      *dst++ = *src++;
    }

  return save ;
}
//-----------------------------------------------------------
void* memccpy(void* dst, const void* src, int c, size_t count)
{
  char *a = dst;
  const char *b = src;
  while (count--)
  {
    *a++ = *b;
    if (*b==c)
    {
      return (void *)a;
    }
    b++;
  }
  return 0;
}

//-----------------------------------------------------------
void* memchr (const void* src_void, int c , size_t length)
{
  const unsigned char *src = (const unsigned char *) src_void;
  unsigned char d = c;
  while (length--)
    {
      if (*src == d)
        return (void *) src;
      src++;
    }

  return NULL;
}
//-----------------------------------------------------------
void* memset (void* m , int c , size_t n)
{
  volatile char *s = (char *) m;
  while (n--)
     *s++ = (char) c;

   return m;
}
//-----------------------------------------------------------
int memcmp(const void* m1, const void* m2, size_t n)
{
  unsigned char *s1 = (unsigned char *) m1;
  unsigned char *s2 = (unsigned char *) m2;

  while (n--)
    {
      if (*s1 != *s2)
	{
	  return *s1 - *s2;
	}
      s1++;
      s2++;
    }
  return 0;
}
//-----------------------------------------------------------
void *memmove(void* dst_void, const void* src_void, size_t length)
{
  char* dst = dst_void;
  const char* src = src_void;

  if (src < dst && dst < src + length)
    {
      // Have to copy backwards
      src += length;
      dst += length;
      while (length--)
	{
	  *--dst = *--src;
	}
    }
  else
    {
      while (length--)
	{
	  *dst++ = *src++;
	}
    }

  return dst_void;
}
//-----------------------------------------------------------

size_t strlen(const char* str)
{
  const char *start = str;

while (*str)
    str++;
  return str - start;

  }
//-----------------------------------------------------------
char* strncpy(char* __restrict dst0, const char* __restrict src0, size_t count)

{
  char *dscan;
  const char *sscan;

  dscan = dst0;
  sscan = src0;
  while (count > 0)
    {
      --count;
      if ((*dscan++ = *sscan++) == '\0')
	break;
    }
  while (count-- > 0)
    *dscan++ = '\0';

  return dst0;
}
//-----------------------------------------------------------
char* strcpy (char* dst0, const char* src0)
{
  char *s = dst0;

  while ( (*dst0++ = *src0++) ) ;

  return s;
  }
//-----------------------------------------------------------
size_t strlcpy(char *dst, const char *src, size_t dsize)
{
	const char *osrc = src;
	size_t nleft = dsize;

	/* Copy as many bytes as will fit. */
	if (nleft != 0) {
		while (--nleft != 0) {
			if ((*dst++ = *src++) == '\0')
				break;
		}
	}

	/* Not enough room in dst, add NUL and traverse rest of src. */
	if (nleft == 0) {
		if (dsize != 0)
			*dst = '\0';		/* NUL-terminate dst */
		while (*src++)
			;
	}

	return(src - osrc - 1);	/* count does not include NUL */
}
//-----------------------------------------------------------
int strcmp (const char* s1 , const char* s2)
{
  while (*s1 != '\0' && *s1 == *s2)
    {
      s1++;
      s2++;
    }
  return (*(unsigned char *) s1) - (*(unsigned char *) s2);
  }
//-----------------------------------------------------------
int strncmp(const char* s1, const char* s2, size_t n)
{
  if (n == 0)
    return 0;

  while (n-- != 0 && *s1 == *s2)
    {
      if (n == 0 || *s1 == '\0')
        break;
      s1++;
      s2++;
    }

  return (*(unsigned char *) s1) - (*(unsigned char *) s2);
}
//-----------------------------------------------------------
int  strcasecmp ( const char* s1, const char* s2 )
{
    register unsigned int  x2;
    register unsigned int  x1;

    while (1) {
        x2 = *s2 - 'A'; if (__unlikely(x2 < 26u)) x2 += 32;
        x1 = *s1 - 'A'; if (__unlikely(x1 < 26u)) x1 += 32;
	s1++; s2++;
        if ( __unlikely(x2 != x1) )
            break;
        if ( __unlikely(x1 == (unsigned int)-'A') )
            break;
    }

    return x1 - x2;
}
//-----------------------------------------------------------
char* strchr(const char* s1 , int i)
{
  const unsigned char *s = (const unsigned char *)s1;
  unsigned char c = i;

  while (*s && *s != c)
      s++;
    if (*s == c)
      return (char *)s;
    return NULL;
}
//-----------------------------------------------------------
size_t strspn(const char* s1, const char* s2)
{
    const char *s = s1;
    const char *c;

    while (*s1)
      {
        for (c = s2; *c; c++)
  	{
  	  if (*s1 == *c)
  	    break;
  	}
        if (*c == '\0')
  	break;
        s1++;
      }

    return s1 - s;
  }
//-----------------------------------------------------------
char* strpbrk( const char* s1 , const char* s2)
{
  const char *c = s2;
  if (!*s1)
    return (char *) NULL;

  while (*s1)
    {
      for (c = s2; *c; c++)
	{
	  if (*s1 == *c)
	    break;
	}
      if (*c)
	break;
      s1++;
    }

  if (*c == '\0')
    s1 = ((void *)0);

  return (char *) s1;
}
//----------------------------------------------------------
int strcoll(const char* a , const char* b)
{
  return strcmp (a, b);
}
//----------------------------------------------------------
char* strstr(const char* searchee, const char* lookfor)
{
  /* Less code size, but quadratic performance in the worst case.  */
  if (*searchee == 0)
    {
      if (*lookfor)
	return (char *) 0;
      return (char *) searchee;
    }

  while (*searchee)
    {
      size_t i;
      i = 0;

      while (1)
	{
	  if (lookfor[i] == 0)
	    {
	      return (char *) searchee;
	    }

	  if (lookfor[i] != searchee[i])
	    {
	      break;
	    }
	  i++;
	}
      searchee++;
    }

  return (char *) 0;
}
//-------------------------------------------------------------------
char* strcat(register char* s,register const char* t)
{
  char *dest=s;
  s+=strlen(s);
  for (;;)
    {
     if (!(*s = *t))
       break;
     ++s;
     ++t;
    }
  return dest;
}
//-------------------------------------------------------------------
size_t strlcat(char* dst, const char* src, size_t siz)
{
	register char *d = dst;
	register const char *s = src;
	register size_t n = siz;
	size_t dlen;

	/* Find the end of dst and adjust bytes left but don't go past end */
	while (*d != '\0' && n-- != 0)
		d++;
	dlen = d - dst;
	n = siz - dlen;

	if (n == 0)
		return(dlen + strlen(s));
	while (*s != '\0') {
		if (n != 1) {
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = '\0';

	return(dlen + (s - src));	/* count does not include NUL */
}
//-------------------------------------------------------------------
size_t strcspn(const char* s, const char* reject)
{
  size_t l=0;
  int i;

  for (; *s; ++s) {
    for (i=0; reject[i]; ++i)
      if (*s==reject[i]) return l;
    ++l;
  }
  return l;
}
//-------------------------------------------------------------------
char* strerror(int errnum)
{
  while (1)
    {
      __asm__ volatile ("nop");
    }
  return "Not implement, see errno.c";
}
//-------------------------------------------------------------------
char *strncat(char* s, const char* t, size_t n)
{
  char *dest=s;
  register char *max;
  s+=strlen(s);
  if (__unlikely((max=s+n)==s)) goto fini;
  for (;;)
    {
      if (__unlikely(!(*s = *t)))
        break;
      if (__unlikely(++s==max))
        break;
      ++t;
    }
  *s=0;
 fini:
  return dest;
}
//-------------------------------------------------------------------

#include "reentrant.h"

char *strtok(char* s,const char* delim)
{
  char*tmp=0;

  #ifdef __USE_REENTRANT__
     char* pos  = ((reentrant_t*)reentrant)->strtok_pos;
  #else
     static char* pos  = 0;
  #endif

  if (s==0)
    s=pos;
  s+=strspn(s,delim);		/* overread leading delimiter */
  if (__likely(*s))
    {
      tmp=s;
      s+=strcspn(s,delim);
      if (__likely(*s)) *s++=0;	/* not the end ? => terminate it */
    }
  pos=s;
  return tmp;
}
//-------------------------------------------------------------------
size_t strxfrm(char* dest, const char* src, size_t n)
{
    memset(dest,0,n);
    memccpy(dest,src,0,n);
    return strlen(dest);
}
//-------------------------------------------------------------------
char *strrchr(const char* t, int c) {
  register char ch;
  register const char *l=0;

  ch = c;
  for (;;) {
    if (__unlikely(*t == ch))
      l=t;
    if (__unlikely(!*t))
      return (char*)l;
    ++t;
  }
  return (char*)l;
}

char *rindex(const char *t,int c)	__attribute__((weak,alias("strrchr")));














