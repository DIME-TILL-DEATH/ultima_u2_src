#ifndef __KLIBC_STDINT_H__
#define __KLIBC_STDINT_H__

#include <stddef.h>

#ifdef __cplusplus
  /*namespace std {*/ extern "C" {
#endif

// implement subset LIBC API for C++ support (see cstring)

void*  memchr (const void* src_void, int c , size_t length);
int    memcmp(const void *m1, const void *m2, size_t n);
void*  memcpy (void* dst0 , const void* src0 , size_t len0);
void*  memmove(void *dst_void, const void *src_void, size_t length);
void*  memset (void* m , int c , size_t n);

char*  strcat(char* s,const char* t);
size_t strlcat(char* dst, const char* src, size_t siz);
char*  strchr(const char* s1 , int i);
int    strcmp (const char* s1 , const char* s2);
size_t strlcpy(char *dst, const char *src, size_t dsize);
int    strcasecmp ( const char* s1, const char* s2 );
int    strcoll(const char* a , const char* b);
char*  strcpy (char* dst0, const char* src0);
size_t strcspn(const char* s, const char* reject);
char*  strerror(int errnum);
size_t strlen(const char* str);
char*  strncat(char* s, const char* t, size_t n);
int    strncmp(const char* s1, const char* s2, size_t n);
char*  strncpy(char* __restrict dst0, const char* __restrict src0, size_t count);
char*  strpbrk( const char* s1 , const char* s2);
char*  strrchr(const char* t, int c);
size_t strspn(const char* s1, const char* s2);
char*  strstr(const char* searchee, const char* lookfor);
char*  strtok(char* s, const char* delim);
size_t strxfrm(char* dest, const char* src, size_t n);
char*  strdup(const char* src);
char*  strndup(const char* src, size_t n);

// other standart LIBC API (unused C++)

size_t strlcat(char* dst, const char* src, size_t siz);

char*  rindex(const char* t,int c);
void*  memccpy(void* dst, const void* src, int c, size_t count);


#if __GNU_VISIBLE && defined(__GNUC__)
#define strdupa(__s) \
	(__extension__ ({const char *__in = (__s); \
			 size_t __len = strlen (__in) + 1; \
			 char * __out = (char *) __builtin_alloca (__len); \
			 (char *) memcpy (__out, __in, __len);}))
#define strndupa(__s, __n) \
	(__extension__ ({const char *__in = (__s); \
			 size_t __len = strnlen (__in, (__n)) + 1; \
			 char *__out = (char *) __builtin_alloca (__len); \
			 __out[__len-1] = '\0'; \
			 (char *) memcpy (__out, __in, __len-1);}))
#endif /* __GNU_VISIBLE && __GNUC__ */

//-------------------------------------------------------------------

#ifdef __cplusplus
 /* }*/ }
#endif

#endif /*__KLIBC_STDINT_H__*/

