/*
 * ltc6803.h

 *
 *  Created on: 17 июля 2017 г.
 *      Author: klen
 */
#ifndef __LTC6803_H__
#define __LTC6803_H__

#include "types++.h"
#include <vector>

typedef void (*init_t)() ;
typedef uint8_t (*xfer_t)(uint8_t val) ;
typedef void (*select_t)() ;
typedef void (*deselect_t)();
typedef uint8_t (crc8_t)(uint8_t crc,  uint8_t *buf, size_t len);


template <init_t init, xfer_t xfer, select_t select, deselect_t deselect, crc8_t crc8, const size_t stack_size >
class ltc6803_t
{
   public:


      enum comparator_duty_cycle_t
      {//UVOV compartor period
       //     Vref power down between mesurenment
       //            cell voltage mesurenment time
          cdc_off_yes_off=0,
  	  cdc_off_no_13ms,
  	  cdc_13ms_no_13ms,
  	  cdc_130ms_no_13ms,
  	  cdc_500ms_no_13ms,
  	  cdc_130ms_yes_21ms,
  	  cdc_500ms_yes_21ms,
  	  cdc_2000ms_yes_21ms,
      } ;


      struct configuration_register_group_t
      {
	  // CFGR0
	  comparator_duty_cycle_t CDC    : 3 ;
	  uint8_t CELL10 : 1 ;
	  uint8_t LVLPL  : 1 ;
	  uint8_t GPIO_1 : 1 ;
	  uint8_t GPIO_2 : 1 ;
	  uint8_t WDT    : 1 ;
	  // CFGR1
	  uint8_t DCC1   : 1 ;
	  uint8_t DCC2   : 1 ;
	  uint8_t DCC3   : 1 ;
	  uint8_t DCC4   : 1 ;
	  uint8_t DCC5   : 1 ;
	  uint8_t DCC6   : 1 ;
	  uint8_t DCC7   : 1 ;
	  uint8_t DCC8   : 1 ;
	  // CFGR2
	  uint8_t DCC9   : 1 ;
	  uint8_t DCC10  : 1 ;
	  uint8_t DCC11  : 1 ;
	  uint8_t DCC12  : 1 ;
	  uint8_t MC1I   : 1 ;
	  uint8_t MC2I   : 1 ;
	  uint8_t MC3I   : 1 ;
	  uint8_t MC4I   : 1 ;
	  // CFGR3
	  uint8_t MC5I   : 1 ;
	  uint8_t MC6I   : 1 ;
	  uint8_t MC7I   : 1 ;
	  uint8_t MC8I   : 1 ;
	  uint8_t MC9I   : 1 ;
	  uint8_t MC10I  : 1 ;
	  uint8_t MC11I  : 1 ;
	  uint8_t MC12I  : 1 ;
	  // CFGR4
	  uint8_t VUV;
	  // CFGR5
	  uint8_t VOV ;

          uint8_t pec ;
          inline void crc()   { pec =  crc8(0x41, (uint8_t*)this, offsetof (configuration_register_group_t, pec) ) ; }
          inline void check() { pec -= crc8(0x41, (uint8_t*)this, offsetof (configuration_register_group_t, pec) ) ; }
          inline void clear() { *((uint16_t*)this) = 0 ; }
      } __PACKED__ ;

      struct cell_voltage_register_group_t
      {
	  // CFGR0
	  uint16_t C1V  : 12 ;
	  uint16_t C2V  : 12 ;
	  uint16_t C3V  : 12 ;
	  uint16_t C4V  : 12 ;
	  uint16_t C5V  : 12 ;
	  uint16_t C6V  : 12 ;
	  uint16_t C7V  : 12 ;
	  uint16_t C8V  : 12 ;
	  uint16_t C9V  : 12 ;
	  uint16_t C10V : 12 ;
	  uint16_t C11V : 12 ;
	  uint16_t C12V : 12 ;

          uint8_t pec ;
          inline void crc()   { pec =  crc8(0x41, (uint8_t*)this, offsetof (configuration_register_group_t, pec) ) ; }
          inline void check() { pec -= crc8(0x41, (uint8_t*)this, offsetof (configuration_register_group_t, pec) ) ; }
      } __PACKED__ ;

      struct flag_register_group_t
      {
	  // FLGR0
	  uint8_t C1UV  : 1 ;
	  uint8_t C1OV  : 1 ;
	  uint8_t C2UV  : 1 ;
	  uint8_t C2OV  : 1 ;
	  uint8_t C3UV  : 1 ;
	  uint8_t C3OV  : 1 ;
	  uint8_t C4UV  : 1 ;
	  uint8_t C4OV  : 1 ;
	  // FLGR1
	  uint8_t C5UV  : 1 ;
	  uint8_t C5OV  : 1 ;
	  uint8_t C6UV  : 1 ;
	  uint8_t C6OV  : 1 ;
	  uint8_t C7UV  : 1 ;
	  uint8_t C7OV  : 1 ;
	  uint8_t C8UV  : 1 ;
	  uint8_t C8OV  : 1 ;
	  // FLGR2
	  uint8_t C9UV  : 1 ;
	  uint8_t C9OV  : 1 ;
	  uint8_t C10UV : 1 ;
	  uint8_t C10OV : 1 ;
	  uint8_t C11UV : 1 ;
	  uint8_t C11OV : 1 ;
	  uint8_t C12UV : 1 ;
	  uint8_t C12OV : 1 ;

          uint8_t pec ;
          inline void crc()   { pec =  crc8(0x41, (uint8_t*)this, offsetof (configuration_register_group_t, pec) ) ; }
          inline void check() { pec -= crc8(0x41, (uint8_t*)this, offsetof (configuration_register_group_t, pec) ) ; }
      } __PACKED__ ;

      struct temperature_register_group_t
      {
          // FLGR0
      	  uint16_t ETMP1 : 12 ;
      	  uint16_t ETMP2 : 12 ;
      	  uint16_t ITMP  : 12 ;
      	  uint8_t  THSD  : 1  ;
      	  uint8_t  reserved : 3 ;


      	  uint8_t pec ;
          inline void crc()   { pec =  crc8(0x41, (uint8_t*)this, offsetof (configuration_register_group_t, pec) ) ; }
          inline void check() { pec -= crc8(0x41, (uint8_t*)this, offsetof (configuration_register_group_t, pec) ) ; }
      } __PACKED__ ;

      struct diagnoctic_register_group_t
      {
          // DGNR0/1
      	  uint16_t REF      : 12 ;
      	  uint8_t  reserved : 1  ;
      	  uint16_t MUXFAIL  : 1  ;
      	  uint8_t  REV      : 2  ;

      	  uint8_t pec ;
          inline void crc()   { pec =  crc8(0x41, (uint8_t*)this, offsetof (configuration_register_group_t, pec) ) ; }
          inline void check() { pec -= crc8(0x41, (uint8_t*)this, offsetof (configuration_register_group_t, pec) ) ; }
      } __PACKED__ ;

      inline ltc6803_t()  { init(); }
      inline ~ltc6803_t() {} ;

      inline void write_config_reg_group( configuration_register_group_t* groups ) { cs_t cs ; write_cmd(lcWRCFG); write_group<configuration_register_group_t> ( groups ); }
      inline void read_config_reg_group( configuration_register_group_t* groups )  { cs_t cs ; write_cmd(lcRDCFG); read_group<configuration_register_group_t> ( groups );  }
      inline void read_all_cell_voltage_group(cell_voltage_register_group_t* groups) { cs_t cs ;write_cmd(lcRDCV); read_group<cell_voltage_register_group_t> ( groups );   }
      inline void read_cell_voltage_1_4(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      inline void read_cell_voltage_5_8(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      inline void read_cell_voltage_9_12(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      inline void read_flag_reg_group(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      inline void read_temperature_reg_group(temperature_register_group_t* groups){ cs_t cs ; write_cmd(lcRDTMP); read_group<temperature_register_group_t> ( groups );}
      inline void start_cell_voltage_adc_conversion_and_poll_status_all() { cs_t cs ; write_cmd(lcSTCVAD_ALL); }
      void start_cell_voltage_adc_conversion_and_poll_status_cell_1(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_cell_voltage_adc_conversion_and_poll_status_cell_2(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_cell_voltage_adc_conversion_and_poll_status_cell_3(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_cell_voltage_adc_conversion_and_poll_status_cell_4(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_cell_voltage_adc_conversion_and_poll_status_cell_5(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_cell_voltage_adc_conversion_and_poll_status_cell_6(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_cell_voltage_adc_conversion_and_poll_status_cell_7(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_cell_voltage_adc_conversion_and_poll_status_cell_8(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_cell_voltage_adc_conversion_and_poll_status_cell_9(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_cell_voltage_adc_conversion_and_poll_status_cell_10(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_cell_voltage_adc_conversion_and_poll_status_cell_11(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_cell_voltage_adc_conversion_and_poll_status_cell_12(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_cell_voltage_adc_conversion_and_poll_status_clear(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_cell_voltage_adc_conversion_and_poll_status_selftest_1(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_cell_voltage_adc_conversion_and_poll_status_selftest_2(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }


      void start_open_wire_adc_conversion_and_poll_status_all(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_open_wire_adc_conversion_and_poll_status_cell_1(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_open_wire_adc_conversion_and_poll_status_cell_2(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_open_wire_adc_conversion_and_poll_status_cell_3(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_open_wire_adc_conversion_and_poll_status_cell_4(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_open_wire_adc_conversion_and_poll_status_cell_5(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_open_wire_adc_conversion_and_poll_status_cell_6(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_open_wire_adc_conversion_and_poll_status_cell_7(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_open_wire_adc_conversion_and_poll_status_cell_8(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_open_wire_adc_conversion_and_poll_status_cell_9(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_open_wire_adc_conversion_and_poll_status_cell_10(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_open_wire_adc_conversion_and_poll_status_cell_11(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_open_wire_adc_conversion_and_poll_status_cell_12(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_temperature_adc_conversion_and_poll_status(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void poll_adc_converter_status(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void poll_itrerrupt_status(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_diagnose_and_poll_status() { cs_t cs ; write_cmd(lcDAGN);  }
      void read_diagnose_reg(diagnoctic_register_group_t* groups) { cs_t cs ; write_cmd(lcRDDGNR); read_group<diagnoctic_register_group_t> ( groups ); }
      void start_cell_voltage_adc_conversion_and_poll_status_discarge_permitted_all() { cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_cell_voltage_adc_conversion_and_poll_status_discarge_permitted_cell_1() { cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_cell_voltage_adc_conversion_and_poll_status_discarge_permitted_cell_2() { cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_cell_voltage_adc_conversion_and_poll_status_discarge_permitted_cell_3() { cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_cell_voltage_adc_conversion_and_poll_status_discarge_permitted_cell_4() { cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_cell_voltage_adc_conversion_and_poll_status_discarge_permitted_cell_5() { cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_cell_voltage_adc_conversion_and_poll_status_discarge_permitted_cell_6() { cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_cell_voltage_adc_conversion_and_poll_status_discarge_permitted_cell_7() { cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_cell_voltage_adc_conversion_and_poll_status_discarge_permitted_cell_8() { cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_cell_voltage_adc_conversion_and_poll_status_discarge_permitted_cell_9() { cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_cell_voltage_adc_conversion_and_poll_status_discarge_permitted_cell_10() { cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_cell_voltage_adc_conversion_and_poll_status_discarge_permitted_cell_11() { cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      void start_cell_voltage_adc_conversion_and_poll_status_discarge_permitted_cell_12() { cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }

      inline void start_open_wire_adc_conversion_and_poll_status_discarge_permitted_all()    { cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      inline void start_open_wire_adc_conversion_and_poll_status_discarge_permitted_cell_1() { cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      inline void start_open_wire_adc_conversion_and_poll_status_discarge_permitted_cell_2() { cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      inline void start_open_wire_adc_conversion_and_poll_status_discarge_permitted_cell_3() { cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      inline void start_open_wire_adc_conversion_and_poll_status_discarge_permitted_cell_4() { cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      inline void start_open_wire_adc_conversion_and_poll_status_discarge_permitted_cell_5() { cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      inline void start_open_wire_adc_conversion_and_poll_status_discarge_permitted_cell_6() { cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      inline void start_open_wire_adc_conversion_and_poll_status_discarge_permitted_cell_7() { cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      inline void start_open_wire_adc_conversion_and_poll_status_discarge_permitted_cell_8() { cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      inline void start_open_wire_adc_conversion_and_poll_status_discarge_permitted_cell_9() { cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      inline void start_open_wire_adc_conversion_and_poll_status_discarge_permitted_cell_10(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      inline void start_open_wire_adc_conversion_and_poll_status_discarge_permitted_cell_11(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }
      inline void start_open_wire_adc_conversion_and_poll_status_discarge_permitted_cell_12(){ cs_t cs ;  /*TODO write_cmd ... read_group/write_group*/  }

      inline size_t stack() { return stack_size ; }


      inline void get_cells_voltage( vector<float,KgpAllocator<float>>& vec )
      {
	cell_voltage_register_group_t cvg[stack_size] ;
	read_all_cell_voltage_group( cvg );
	if ( vec.size() != stack_size * 12 )
	        vec.resize(stack_size * 12 );

	for ( size_t stack_index = 0 ; stack_index < stack_size ; stack_index++  )
	  {
             vec[stack_index*12 + 0  ] = (cvg[stack_index].C1V- 512.0f)*0.00150f ;
             vec[stack_index*12 + 1  ] = (cvg[stack_index].C2V- 512.0f)*0.00150f ;
             vec[stack_index*12 + 2  ] = (cvg[stack_index].C3V- 512.0f)*0.00150f ;
             vec[stack_index*12 + 3  ] = (cvg[stack_index].C4V- 512.0f)*0.00150f ;
             vec[stack_index*12 + 4  ] = (cvg[stack_index].C5V- 512.0f)*0.00150f ;
             vec[stack_index*12 + 5  ] = (cvg[stack_index].C6V- 512.0f)*0.00150f ;
             vec[stack_index*12 + 6  ] = (cvg[stack_index].C7V- 512.0f)*0.00150f ;
             vec[stack_index*12 + 7  ] = (cvg[stack_index].C8V- 512.0f)*0.00150f ;
             vec[stack_index*12 + 8  ] = (cvg[stack_index].C9V- 512.0f)*0.00150f ;
             vec[stack_index*12 + 9  ] = (cvg[stack_index].C10V- 512.0f)*0.00150f ;
             vec[stack_index*12 + 10 ] = (cvg[stack_index].C11V- 512.0f)*0.00150f ;
             vec[stack_index*12 + 11 ] = (cvg[stack_index].C12V- 512.0f)*0.00150f ;
	  }
      }

   private:

      enum command_t
       {
         lcWRCFG = 0x01C7, //Write Configuration Register Group
         lcRDCFG = 0x02CE, //Read Configuration Register Group
         lcRDCV  = 0x04DC, //Read All Cell Voltage Group
         lcRDCVA = 0x06D2, //Read Cell Voltages 1-4
         lcRDCVB = 0x08F8, //Read Cell Voltages 5-8
         lcRDCVC = 0x0AF6, //Read Cell Voltages 9-12
         lcRDFLG = 0x0CE4, //Read Flag Register Group
         lcRDTMP = 0x0EEA, //Read Temperature Register Group
         lcSTCVAD_ALL   = 0x10B0 , //Start Cell Voltage ADC Conversions and Poll Status
         lcSTCVAD_CELL1 = 0x11B7 ,
         lcSTCVAD_CELL2 = 0x12BE ,
         lcSTCVAD_CELL3 = 0x13B9 ,
         lcSTCVAD_CELL4 = 0x14AC ,
         lcSTCVAD_CELL5 = 0x15AB ,
         lcSTCVAD_CELL6 = 0x16A2 ,
         lcSTCVAD_CELL7 = 0x17A5 ,
         lcSTCVAD_CELL8 = 0x1888 ,
         lcSTCVAD_CELL9 = 0x198F ,
         lcSTCVAD_CELL10 = 0x1A86 ,
         lcSTCVAD_CELL11 = 0x1B81 ,
         lcSTCVAD_CELL12 = 0x1C94 ,
         lcSTCVAD_CLEAR = 0x1D93 ,
         lcSTCVAD_SELFTEST1 = 0x1E9A ,
         lcSTCVAD_SELFTEST2 = 0x1F9D ,

         lcSTOWAD_ALL = 0x2020 , // Start Open-Wire ADC Conversions and Poll Status
         lcSTOWAD_CELL1 = 0x2127 ,
         lcSTOWAD_CELL2 = 0x222E ,
         lcSTOWAD_CELL3 = 0x2329 ,
         lcSTOWAD_CELL4 = 0x243C ,
         lcSTOWAD_CELL5 = 0x253B ,
         lcSTOWAD_CELL6 = 0x2632 ,
         lcSTOWAD_CELL7 = 0x2735 ,
         lcSTOWAD_CELL8 = 0x2818 ,
         lcSTOWAD_CELL9 = 0x291F ,
         lcSTOWAD_CELL10 = 0x2A16 ,
         lcSTOWAD_CELL11 = 0x2B11 ,
         lcSTOWAD_CELL12 = 0x2C04 ,

         lcSTTMPAD_ALL = 0x3050, // Start Temperature ADC Conversions and Poll Status
         lcSTTMPAD_EXTERNAL1 = 0x3157,
         lcSTTMPAD_EXTERNAL2 = 0x325E,
         lcSTTMPAD_INTERNAL  = 0x3359,
         lcSTTMPAD_SELFTEST1 = 0x3E7A,
         lcSTTMPAD_SELFTEST2 = 0x3F7D,

         lcPLADC = 0x4007, // Poll ADC Converter Status
         lcPLINT = 0x5077, // Poll Interrupt Status
         lcDAGN = 0x5279, // Start Diagnose and Poll Status
         lcRDDGNR = 0x546B, // Read Diagnostic Register
         lcSTCVDC_ALL = 0x60E7, // Start Cell Voltage ADC Conversions and Poll Status, with Discharge Permitted
         lcSTCVDC_CELL1 = 0x61E0 ,
         lcSTCVDC_CELL2 = 0x62E9 ,
         lcSTCVDC_CELL3 = 0x63EE ,
         lcSTCVDC_CELL4 = 0x64FB ,
         lcSTCVDC_CELL5 = 0x65FC ,
         lcSTCVDC_CELL6 = 0x66F5 ,
         lcSTCVDC_CELL7 = 0x67F2 ,
         lcSTCVDC_CELL8 = 0x68DF ,
         lcSTCVDC_CELL9 = 0x69D8 ,
         lcSTCVDC_CELL10 = 0x6AD1 ,
         lcSTCVDC_CELL11 = 0x6BD6 ,
         lcSTCVDC_CELL12 = 0x6CC3 ,

         lcSTOWDC_ALL = 0x7097, // Start Open-Wire ADC Conversions and Poll Status, with Discharge Permitted
         lcSTOWDC_CELL1 = 0x7190 ,
         lcSTOWDC_CELL2 = 0x7299 ,
         lcSTOWDC_CELL3 = 0x739E ,
         lcSTOWDC_CELL4 = 0x748B ,
         lcSTOWDC_CELL5 = 0x758C ,
         lcSTOWDC_CELL6 = 0x7685 ,
         lcSTOWDC_CELL7 = 0x7782 ,
         lcSTOWDC_CELL8 = 0x78AF ,
         lcSTOWDC_CELL9 = 0x79A8 ,
         lcSTOWDC_CELL10 = 0x7AA1 ,
         lcSTOWDC_CELL11 = 0x7BA6 ,
         lcSTOWDC_CELL12 = 0x7CB3 ,
       }  ;


       struct cs_t
       {
         inline cs_t() { select(); }
         inline ~cs_t() { deselect(); }
       };


   protected:

       inline void write_cmd(command_t cmd)
       {
	 xfer ( data_16bit_t::from((uint16_t)cmd).high_byte.uval ) ;
         xfer ( data_16bit_t::from((uint16_t)cmd).low_byte.uval )  ;
       }

       template <typename T>
       inline void write_group ( T* groups )
       {
	 // запись данных !! В ОБРАТНОМ ПОРЯДКЕ !!
	 size_t index = stack_size ;
	 do
	    {
	      index-- ;
	      // вычисление контрольной суммы
	      groups[index].crc();
	      uint8_t* stream =  (uint8_t*) &groups[index] ;
	      for(size_t i = 0 ; i < sizeof(T); i++)
	          xfer( stream[i] );
	    } while (index) ;
       }

       template <typename T>
       inline void read_group ( T* groups)
       {
	 // чтение данных
	 uint8_t* stream =  (uint8_t*)groups ;
	 for(size_t i = 0 ; i < stack_size*sizeof(T); i++)
	     stream[i]=xfer(0xff);

	 // проверка контрольной суммы
	 for(size_t i = 0 ; i < stack_size; i++)
	     groups[i].check();
       }

};



#endif /* __LTC6803_H__ */
