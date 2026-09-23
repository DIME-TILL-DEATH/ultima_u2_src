/*
 * strtof.h
 *
 *  Created on: May 26, 2014
 *      Author: klen
 */

#ifndef __STRTOULL_H__
#define __STRTOULL_H__


#ifdef __cplusplus
extern "C" {
#endif

unsigned long long int strtoull(const char *ptr, char **endptr, int base) ;
long long int strtoll(const char *ptr, char **endptr, int base);

#ifdef __cplusplus
                        }
#endif

#endif /* __STRTOF_H__ */
