/*
 * syscfg++.h
 *
 *  Created on: 30 окт. 2017 г.
 *      Author: klen
 */

#ifndef __SYSCFG++_H__
#define __SYSCFG++_H__

#if    defined( STM32F405xx ) || defined( STM32F407xx ) || defined( STM32F415xx ) || defined( STM32F417xx )
   #include "syscfg++_405.h"
#elif  defined( STM32F429xx ) || defined( STM32F43xxx )
   #include "syscfg++_42x.h"
#else
   #error "chip famaly not defined"
#endif

#endif /* __SYSCFG++_H__ */
