/*
 * apptypes.h
 *
 *  Created on: 17.07.2011
 *      Author: klen
 */

#ifndef __APPTYPES_H__
#define __APPTYPES_H__


#define FW_HEADER_DATA_MAGIC 0x12345678

typedef struct
{
  uint32_t       magic ;
  uint32_t       size  ;   // image.bin size
  uint_least32_t crc   ;   // image.bin CRC32
} __attribute__ ((packed)) firmware_header_data_t ;

typedef union
{
  char plaseholder[512] ; // use for set a 512 bytes size. reqared for STM32 VTOR value aligning
  firmware_header_data_t header_data ;
} __attribute__ ((packed)) firmware_header_t ;

#endif /* APPTYPES_H_ */
