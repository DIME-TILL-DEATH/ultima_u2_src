#ifndef __LTC3300_H__
#define __LTC3300_H__

#include "types++.h"

typedef void (*init_t)() ;
typedef uint8_t (*xfer_t)(uint8_t val) ;
typedef void (*select_t)() ;
typedef void (*deselect_t)();
//typedef uint8_t (crc4_t)(uint8_t crc,  uint8_t *buf, size_t len);

template <init_t init, xfer_t xfer, select_t select, deselect_t deselect, /*crc4_t crc4,*/ const size_t stack_size >
class ltc3300_t
{
public:


  enum command_id_t { ciWrite=0b10101001, ciRead=0b10101010, ciStatus=0b10101100, ciExecute=0b10101111 } ;
  enum cell_ctl_t { ccNone=0b00, ccDischargeCellNoSync=0b01, ccDischargeCellSync=0b10, ccChargeCell=0b11 }  ;

  struct read_balance_status_t // Read Balance Status Data Bit
  {
    uint16_t crc : 4 ;
    uint16_t reserved : 3 ;
    uint16_t temp_ok : 1 ;
    uint16_t sec_not_ov : 1 ;
    uint16_t cells_not_ov : 1 ;
    uint16_t gate_drive_6_ok : 1 ;
    uint16_t gate_drive_5_ok : 1 ;
    uint16_t gate_drive_4_ok : 1 ;
    uint16_t gate_drive_3_ok : 1 ;
    uint16_t gate_drive_2_ok : 1 ;
    uint16_t gate_drive_1_ok : 1 ;

  } __PACKED__ ;


  union  ctrl_t // Write Balance Command Data Bit
  {
    struct bits_t {
    uint16_t crc0 : 1 ;
    uint16_t crc1 : 1 ;
    uint16_t crc2 : 1 ;
    uint16_t crc3 : 1 ;
    uint16_t D6B  : 1 ;
    uint16_t D6A  : 1 ;
    uint16_t D5B  : 1 ;
    uint16_t D5A  : 1 ;
    uint16_t D4B  : 1 ;
    uint16_t D4A  : 1 ;
    uint16_t D3B  : 1 ;
    uint16_t D3A  : 1 ;
    uint16_t D2B  : 1 ;
    uint16_t D2A  : 1 ;
    uint16_t D1B  : 1 ;
    uint16_t D1A  : 1 ;
    } bits ;
    struct
      {
        uint16_t          crc : 4 ;
        cell_ctl_t cell_ctl_6 : 2 ;
        cell_ctl_t cell_ctl_5 : 2 ;
        cell_ctl_t cell_ctl_4 : 2 ;
        cell_ctl_t cell_ctl_3 : 2 ;
        cell_ctl_t cell_ctl_2 : 2 ;
        cell_ctl_t cell_ctl_1 : 2 ;
      } volatile ;

      volatile uint16_t val ;

      struct {
	       uint8_t lb ;
	       uint8_t hb ;
             };

    void crc4()
          {





    	  bool a0 , b0 , c0 , d0 ;
    	  a0 = bits.D3B ^ bits.D1B ;
    	  b0 = bits.D3A ^ bits.D1A ;
    	  c0 = bits.D1A ^ bits.D2B ;
    	  d0 = bits.D2A ^ bits.D4A ;

    	  bool a1 , b1 , c1 , d1 ;
              a1 = a0 ^ bits.D2A ;
              b1 = bits.D1B ^ b0 ;
              c1 = bits.D4B ^ c0 ;
              d1 = c0 ^ d0  ;

    	  bool a2 , b2 , c2 , d2 ;
              a2 = bits.D5B ^ a1 ;
              b2 = bits.D5A ^ b1 ;
              c2 = b1 ^ c1  ;
              d2 = d1 ^ bits.D6A ;

    	  bool a3 , b3 , c3 , d3 ;
              a3 = a2 ^ d1 ;
              b3 = a1 ^ b2 ;
              c3 = bits.D6B ^ c2 ;
              d3 = c2 ^ d2  ;

    	  bool a4 , b4 , c4 , d4 ;
              a4 =  0 ^ a3 ;
              b4 =  0 ^ b3 ;
              c4 =  b3 ^ c3;
              d4 =  d3 ^ 0 ;

              bits.crc3 = ! ( a3 ^ b4 ) ;
              bits.crc2 = ! ( a4 ^ d3 ) ;
              bits.crc1 = ! ( c4 ^ d4 ) ;
              bits.crc0 = ! ( c4 ^ 0 ) ;
          }

     inline void check()
         {

         }
     inline void clear() { val=0; }

  } __PACKED__  ;

  ltc3300_t ()  { init(); }

  inline size_t stack() { return stack_size ; }

  void inline read_balance_status (read_balance_status_t* group)
   {
     cs_t cs ;
     xfer(ciStatus);
     read <read_balance_status_t> (group);
   }

  void inline write_balance_command ( ctrl_t* group )
   {
     cs_t cs ;
     xfer(ciWrite);
     write <ctrl_t> (group);
   }

  void inline read_balance_command ( ctrl_t* group )
   {
     cs_t cs ;
     // запись команды
     xfer(ciRead);
     read <ctrl_t> (group);
   }

  void inline execute_command ()
   {
     cs_t cs ;
     // запись команды
     xfer(ciExecute);
   }

protected:
private:

       struct cs_t
         {
           inline cs_t() { select(); }
           inline ~cs_t(){ deselect(); }
         };


         template <typename T>
         inline void write ( T* groups )
         {
  	    // запись данных !! В ОБРАТНОМ ПОРЯДКЕ !!
  	    size_t index = stack_size ;

            do
  	       {
  	          index-- ;
  	          // вычисление контрольной суммы

 	          groups[index].crc4();
                  data_16bit_t* stream = (data_16bit_t*) groups ;

                  //for(size_t i = 0 ; i < stack_size ; i++)
         	  //   {
         	       xfer(stream[index].high_byte.uval);
         	       xfer(stream[index].low_byte.uval);
         	  //   }

  	      } while (index) ;
         }

         template <typename T>
         inline void read ( T* groups)
         {
           data_16bit_t* stream = (data_16bit_t*) groups ;

  	   for(size_t i = 0 ; i < stack_size ; i++)
  	     {
  	       stream[i].high_byte.uval = xfer(0xff);
  	       stream[i].low_byte.uval = xfer(0xff);
  	     }

  	   // проверка контрольной суммы
  	   //for(size_t i = 0 ; i < stack_size; i++)
  	   //    groups[i].check();

         }


} ;

#endif __LTC3300_H__

