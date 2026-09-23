/*
 * eeprom_stuct_storage.h
 *
 *  Created on: Feb 25, 2015
 *      Author: klen
 */

#ifndef __DATA_STUCT_STORAGE_H__
#define __DATA_STUCT_STORAGE_H__

#include "sdk.h"

//#include "sdk.h"
//#include "stm32++.h"

/*  example:
 *
 * 1. add to apptypes.h:
 *
 *
 *  #include "data_struct_storage.h"
 *
 *  // struct for stored data
 *  typedef  struct
 *     {
 *         uint32_t a ;
 *         float    b ;
 *         double   c[32];
 *     } __PACKED__ application_data_t ;
 *
 *   // specifing of template class
 *   typedef data_struct_storage_t<application_data_t, hash_func> storage_t ;
 *   // or not data integrity checking
 *   typedef data_struct_storage_t<application_data_t> storage_t ;
 *
 *
 *    extern storage_t storage ;
 *
 * 2. add to source construct code:
 *
 *   storage_t storage ;
 *
 * 3. use any time and context:
 *
 *    //read from flash sector
 *    int   a = storage.data.a ;
 *    float b = storage.data.b ;
 *    double t = c[6] ;
 *
 *    //write to flash sector
 *    storage.store( &storage.data.a , a ) ;
 *    storage.store( &storage.data.b , b ) ;
 *    // or full struct write
 *    application_data_t data ;
 *    storage.store(data) ;
 */

#if defined (__EEPROM_FLASH_SECTOR_A__) || defined (__EEPROM_FLASH_SECTOR_B__)

typedef /*uint_least32_t*/uint32_t (*hash_fnc_t)(const unsigned char * buf, size_t len) ;


inline uint_least32_t hash_stub(const unsigned char * buf, size_t len)
{
   return 0x55aa55aa ;
}

template <typename T, hash_fnc_t crc32_fnc = hash_stub > class data_struct_storage_t
{

  public:
      data_struct_storage_t() : data (*((const T*)gnu_linker_eeprom_sector_a_start())) {} ;
     ~data_struct_storage_t() {}

     //data_struct_storage_t(uint8_t sector) {}
     data_struct_storage_t(const data_struct_storage_t&) {}

  private:

  public:

     // direct read aaccess
     const T& data /*= *((const T*)gnu_linker_eeprom_sector_a_start())*/ ;
     const uint_least32_t&  crc = *((uint_least32_t*) (((uint32_t)&data + sizeof(T) + 4) & 0xfffffffc ) ); //  __ALIGN_4__ needed for FLASH_TYPEPROGRAM_WORD - 4 byte write operation

     // copy to user
     void inline load(T& val)
       {
          val = data ;
          //memcpy(&val, &data, sizeof(T));
       }

     // direct mass write access
     bool inline store(const T& val)
       {
          #if defined __USE_FREERTOS__
             critical_section_t sc ;
          #endif

          // erase flash sector
          if ( !flash.sector_erase( 1 )) { return false ;}

          // write data
          if ( !flash.program_x8( (uint32_t)&data, &val, sizeof(T)) ) { return false ;}

          // write CRC
          uint32_t crc_sum  = crc32_fnc( (const unsigned char*)&data , sizeof(T)) ;
          if ( !flash.program_x8( (uint32_t)&crc, &crc_sum, sizeof(uint32_t)) ) { return false ;}

          return true ;
       }

     // direct write access
     template <typename V> inline bool store ( const V* var, const V& value )
       {
          T tmp ;

          // value addr
          V* ptr = ( V*)((ptrdiff_t)&tmp + (ptrdiff_t)var - (ptrdiff_t)&data) ;

          // load
          load (tmp) ;

          // modify
          //ptr = value ;
          memcpy ( ptr , &value, sizeof(V) ) ;

          //store
          bool status = store(tmp) ;


          return status ;
       }

     bool inline check_crc() const
       {
          return (crc == crc32_fnc( (const unsigned char*)&data , sizeof(T))) ;
       }

     uint_least32_t inline get_crc() const
       {
          return crc32_fnc( (const unsigned char*)&data , sizeof(T)) ;
       }

};
 #endif /*__EEPROM_FLASH_SECTOR_A__  or/and __EEPROM_FLASH_SECTOR_A__*/

#endif /* __DATA_STUCT_STORAGE_H__ */
