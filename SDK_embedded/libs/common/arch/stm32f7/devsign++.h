/*
 * devsign++.h
 *
 *  Created on: 20 фев. 2018 г.
 *      Author: klen
 */

#ifndef __DEVSIGN++_H__
#define __DEVSIGN++_H__

#include "types++.h"

namespace stm32f7
{

struct devsign_t
  {
    const uint32_t unuque_id_0 ;
    const uint32_t unuque_id_1 ;
    const uint32_t unuque_id_2 ;
    const uint32_t : 32;
    const uint32_t : 32;
    const uint32_t : 32;
    const uint32_t : 32;
    const uint32_t : 32;

    const uint16_t : 16;
    const uint16_t flash_size  ;


    inline const uint8_t* unuque_id() const
      {
        return (const uint8_t*) &unuque_id_0 ;
      }

    inline void unuque_id( char* str, size_t len ) const
      {
      	const char hex[] = "0123456789ABCDEF";

      	len = (len >= 25) ? 24 : len - 1;
        size_t i = 0 ;

      	do
      	  {
      	     str[i]   = hex[(unuque_id()[i/2] >> 4) & 0x0F];
      	     i++ ;
      	     if ( i == len ) break ;
      	     str[i]   = hex[(unuque_id()[i/2] >> 0) & 0x0F];
      	     i++;
      	  }
      	while ( i < len ) ;

        str[i] = '\0' ;
      }

    inline void unuque_id_fdu( char* str ) const
      {
      	const char hex[] = "0123456789ABCDEF";

        uint8_t serial[6];
      	serial[0] = unuque_id()[11];
      	serial[1] = unuque_id()[10] + unuque_id()[2];
      	serial[2] = unuque_id()[9];
      	serial[3] = unuque_id()[8]  + unuque_id()[0];
      	serial[4] = unuque_id()[7];
      	serial[5] = unuque_id()[6];

      	uint8_t *ser = &serial[0];
      	uint8_t *end = &serial[6];

      	for (; ser < end; ser++)
           {
      	      *str++ = hex[(*ser >> 4) & 0x0f];
              *str++ = hex[(*ser >> 0) & 0x0f];
      	   }
      	*str = '\0';
      }



    // TODO
    /* ref manual 77x 76x  01926/1939  DocID028270 Rev 3
    0x111: STM32F767 and STM32F777 LQFP208 and TFBGA216 package
    0x110: STM32F769 and STM32F779 LQFP208 and TFBGA216 package
    0x101: STM32F767 and STM32F777 LQFP176 package
    0x100: STM32F769 and STM32F779 LQFP176 package
    0x011: WLCSP180 package
    0x010: LQFP144 package
    0x001: LQFP100 package
    0x000: Reserved
*/

    enum package_t { lqfp100=1, lqfp144, wlcsp180, lqfp176_for_769_779, lqfp176_for_767_777, lqfp208_or_tfbga216_for_769_779, lqfp208_or_tfbga216_for_767_777 } ;
    inline package_t package() const
      {
        return (package_t)(*((const uint16_t*)package_addr) >> 8 & 0b111) ;
      }

  };

static devsign_t& devsign   = *((devsign_t*) devsign_addr);

}  // stm32f7

using namespace stm32f7 ;

#endif /* __DEVSIGN++_H__ */
