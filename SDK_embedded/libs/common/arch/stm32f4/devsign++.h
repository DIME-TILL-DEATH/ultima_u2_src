/*
 * devsign++.h
 *
 *  Created on: 20 фев. 2018 г.
 *      Author: klen
 */

#ifndef __DEVSIGN++_H__
#define __DEVSIGN++_H__

#include "types++.h"


namespace stm32f4
{

  struct devsign_t
    {
      const uint32_t unuque_id_0 ;
      const uint32_t unuque_id_1 ;
      const uint32_t unuque_id_2 ;
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

      inline void unuque_id_dfu( char* str ) const
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
        	      *str++ = hex[(*ser >> 4) & 0xf];
                      *str++ = hex[(*ser >> 0) & 0xf];
        	   }
        	*str = '\0';
        }

    };

  static devsign_t& devsign   = *((devsign_t*) devsign_addr);

}  // stm32f4

using namespace stm32f4 ;

#endif /* __DEVSIGN++_H__ */
