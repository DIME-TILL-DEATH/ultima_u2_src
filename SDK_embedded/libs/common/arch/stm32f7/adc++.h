/*
 * adc++.h
 *
 *  Created on: 12 января 2019 г.
 *      Author: klen
 */

#ifndef __ADC++_H__
#define __ADC++_H__

#include "adc_converter_v1++.h"

namespace stm32f7
{
   static adc_t& adc  = *((adc_t *) adc_addr);
}

using namespace stm32f7 ;

#endif /* __ADC++_H__ */
