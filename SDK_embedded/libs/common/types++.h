/*
 * types++.h
 *
 *  Created on: 30 янв. 2017 г.
 *      Author: klen
 */
#ifndef __TYPES++_H__
#define __TYPES++_H__

#include <stdint.h>

#define __inline_static__ __attribute__((always_inline)) static inline
#define __inline_         __attribute__((always_inline)) inline

#define __reg_attr__  __attribute__((packed))


// отключение предупреждения -Wuninitialized
//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wuninitialized"
//  class {}
//#pragma GCC diagnostic pop

// запрещение оптимизации трасс ассембленрных инструкций в инлайн вызовах по их границам.
// данная мера необходима для исключения "мержа" трасс вызовов, что может нарушать
// логику W/R операций в регистры периферии
// данный барьер необходим в каждом вызове с обращением к переферии
struct nro_t  // "NO call asm ROUTE gcc OPTIMIZE
{
	nro_t ()  { asm volatile ("") ; }
	~nro_t () { asm volatile ("" : : : "memory") ; }
}  ;

#define NRO nro_t nro ;


template<typename T, typename Y>
struct read_t
{
  inline read_t() {}

  // read 32bit. версия для атомарного чтения через переферийеый регистр,  функция c барьера памяти (NRO)
  T inline read()   const  { NRO return (*((volatile T*)this)) ; }

  template <typename U> typename U::enum_t inline rd(const size_t offset) const { NRO return static_cast<typename U::enum_t>(((*((volatile T*)this)) >>    offset) & U::mask) ; }
  template <typename U> typename U::enum_t inline rd()                    const { NRO return static_cast<typename U::enum_t>(((*((volatile T*)this)) >> U::offset) & U::mask) ; }

  union
     {
       T reg_value ;
       struct
         {
	   Y reg_low_value  ;
	   Y reg_high_value ;
         };
     };
};

template<typename T, typename Y>
struct read_write_t : public read_t<T,Y>
{
  inline read_write_t():read_t<T,Y>() {}
  inline read_write_t( const T val):read_t<T,Y>() {*((volatile T*)this) = val ;}

  // write 32bit. версия для атомарной записи через переферийеый регистр,  функция c барьера памяти (NRO)
  void inline write( const T val) { NRO *(((volatile T*)this))  = val; }

  // read-modify-write 32bit. версия для атомарного доступа через периферийеый регистр,  функция c барьера памяти (NRO)
  template <typename U> void inline rmw( const U val )                     { NRO *((volatile T*)this) = ((*(((volatile T*)this))) & (~(U::mask << U::offset ))) | ((val & U::mask) << U::offset) ; }
  template <typename U> void inline rmw( const U val, const size_t offset) { NRO *((volatile T*)this) = ((*(((volatile T*)this))) & (~(U::mask << offset )))    | ((val & U::mask) <<    offset) ; }

  // read-or(args)-write 32bit. версия для доступа через временную переменную, функция без барьера памяти (NRO). использовать при оптимизации множественной записи в регистр переферии
  template <typename U> void inline rmw_or( T& dest ,  const U val )                      const { dest = (dest & (~(U::mask << U::offset ))) | ((val & U::mask) << U::offset ); }
  template <typename U> void inline rmw_or( T& dest ,  const U val, const size_t offset ) const { dest = (dest & (~(U::mask <<    offset ))) | ((val & U::mask) <<    offset ); }


  // write 32bit. версия для атомарного доступа через периферийеый регистр,  функция c барьера памяти (NRO)
  template <typename U> void inline wr( const U val )                     { NRO *((volatile T*)this) = ((val & U::mask) << U::offset) ; }
  template <typename U> void inline wr( const U val, const size_t offset) { NRO *((volatile T*)this) = ((val & U::mask) <<    offset) ; }

  // or(args)-write 32bit. версия для доступа через временную переменную, функция без барьера памяти (NRO). использовать при оптимизации множественной записи в регистр переферии
  template <typename U> void inline wr_or( T& dest ,  const U val )                      const { dest |= ((val & U::mask) << U::offset ); }
  template <typename U> void inline wr_or( T& dest ,  const U val, const size_t offset ) const { dest |= ((val & U::mask) <<    offset ); }

  // read-and 32bit. версия для атомарного доступа через периферийеый регистр,  функция c барьера памяти (NRO)
  template <typename U> auto inline operator & ( const U val )                     { NRO return (*(volatile T*)this) & ((val & U::mask) << U::offset) ; }
                        auto inline operator & ( const uint32_t val )                { NRO return (*(volatile T*)this) & val ; }
  //template <typename U> auto inline and( const U val, const size_t offset) { NRO return (*(volatile T*)this) & ((val & U::mask) <<    offset) ; }

  // доступ по списку параметров. тебуется определения набора функций  inline void modify(T& tmp, XYZ_t arg) {  }
  template<typename... Args> inline T modify(const Args... args) { NRO T tmp = read_t<T,Y>::read() ; modify( tmp , args...);  write(tmp) ; return tmp ; }
  template<typename U, typename... Args> inline T modify(T& tmp , const U arg, const Args... args) { modify( tmp, arg); modify( tmp, args...); return tmp ; }

  // шаблонная функция доступа через значения перечислений
  template<typename U>  inline T modify(T& tmp, const U arg) { rmw_or<U> (tmp, arg) ; return tmp ; }
  inline T modify(const T& tmp) { return tmp ; } // завершающая версия



  // запись по списку параметров. тебуется определения набора функций  inline void modify(T& tmp, XYZ_t arg) {  }
  template<typename... Args> inline T write_or(const Args... args) { NRO T tmp = 0 ; write_or( tmp , args...); return (this->reg_value = tmp) ; }
  template<typename U, typename... Args> inline T write_or(T& tmp , const U arg, const Args... args) { write_or( tmp, arg); write_or( tmp, args...); return tmp ; }

  // шаблонная функция доступа через значения перечислений
  template<typename U> inline T write_or(T& tmp, const U arg) { wr_or<U> (tmp, arg) ; return tmp ; }
  inline T write_or(const T& tmp) { return tmp ; } // завершающая версия

  // оператор присваивания, необходим для исключения оптимизации трассы типа { type_t z = u ; u = z ; }
  // используется для чтения флагов переферии с доступом rc_w1 в локальную структуру а потом их сброса
  inline read_write_t& operator = ( const read_write_t& val ) { NRO (*(volatile T*)this) = val.reg_value ; return *this ; }
};

// перегруженный оператор | с функционалом полей описания полей регистров переферии
// используется для формирования значения аргумента read_write_t::operator & ( const uint32_t val )
// пример :
//    if ( status & ( eth_t::dma_t::status_t::receive_status_t::occured | eth_t::dma_t::status_t::receive_buffer_unavailable_status_t::occured ))
//         {
//           ...
//         }

//template <typename U1, typename U2> uint32_t static inline operator | ( const U1 val1 , const U2 val2) { NRO return (uint32_t)(((val1 & U1::mask) << U1::offset) | ((val2 & U2::mask) << U2::offset))  ; }



typedef read_t<uint16_t,uint8_t> read_16_t ; // фиктивный тип ( подполя объединения не являются потомками read_t), необходим для плонофункционального read_32_t
typedef read_t<uint32_t,read_16_t> read_32_t ;
typedef read_t<uint64_t,read_32_t> read_64_t ;

typedef read_write_t<uint16_t,uint8_t> read_write_16_t ; // фиктивный тип ( подполя объединения не являются потомками write_t), необходим для плонофункционального write_32_t
typedef read_write_t<uint32_t,read_write_16_t> read_write_32_t ;
typedef read_write_t<uint64_t,read_write_32_t> read_write_64_t ;

union data_8bit_t
    {
     enum bit_state_t    { low=0, high }  ;
     enum bit_index_t { bi0=0 , bi1, bi2, bi3, bi4, bi5, bi6, bi7, bi_count }  ;
     enum bit_mask_t { bm0= 1 << bi0 ,
                     bm1= 1 << bi1,
	             bm2= 1 << bi2,
	             bm3= 1 << bi3,
	             bm4= 1 << bi4,
	             bm5= 1 << bi5,
	             bm6= 1 << bi6,
	             bm7= 1 << bi7 }  ;
     struct
      {
	bit_state_t bit0 : 1  ;
	bit_state_t bit1 : 1  ;
	bit_state_t bit2 : 1  ;
	bit_state_t bit3 : 1  ;
	bit_state_t bit4 : 1  ;
	bit_state_t bit5 : 1  ;
	bit_state_t bit6 : 1  ;
	bit_state_t bit7 : 1  ;
      } __reg_attr__ ;
      char    cval ;
      uint8_t uval ;
      int8_t  sval ;

      // bit set operation
      inline void set_bit ( bit_index_t bit_index ) { uval |= (1 << bit_index) ; } ;
      inline void set_bit ( bit_mask_t bit_mask )   { uval |=  bit_mask  ; } ;
      inline void set_bit0() { uval |= bm0 ; } ;
      inline void set_bit1() { uval |= bm1 ; } ;
      inline void set_bit2() { uval |= bm2 ; } ;
      inline void set_bit3() { uval |= bm3 ; } ;
      inline void set_bit4() { uval |= bm4 ; } ;
      inline void set_bit5() { uval |= bm5 ; } ;
      inline void set_bit6() { uval |= bm6 ; } ;
      inline void set_bit7() { uval |= bm7 ; } ;
      inline void set_bits(char val)    { uval |= val ; } ;
      inline void set_bits(uint8_t val) { uval |= val ; } ;
      inline void set_bits(int8_t val)  { uval |= val ; } ;

      // bit clear operation
      inline void clear_bit ( bit_index_t bit_index ) { uval &= ~(1 << bit_index) ; } ;
      inline void clear_bit ( bit_mask_t bit_mask )   { uval &= ~bit_mask  ; } ;
      inline void clear_bit0() { uval &= ~bm0 ; } ;
      inline void clear_bit1() { uval &= ~bm1 ; } ;
      inline void clear_bit2() { uval &= ~bm2 ; } ;
      inline void clear_bit3() { uval &= ~bm3 ; } ;
      inline void clear_bit4() { uval &= ~bm4 ; } ;
      inline void clear_bit5() { uval &= ~bm5 ; } ;
      inline void clear_bit6() { uval &= ~bm6 ; } ;
      inline void clear_bit7() { uval &= ~bm7 ; } ;
      inline void clear_bits(char val)    { uval &= ~val ; } ;
      inline void clear_bits(uint8_t val) { uval &= ~val ; } ;
      inline void clear_bits(int8_t val)  { uval &= ~val ; } ;


      // bit toggle operation
      inline void toggle_bit ( bit_index_t bit_index ) { uval ^= (1 << bit_index) ; } ;
      inline void toggle_bit ( bit_mask_t bit_mask )   { uval ^=  bit_mask  ; } ;
      inline void toggle_bit0() { uval ^= bm0 ; } ;
      inline void toggle_bit1() { uval ^= bm1 ; } ;
      inline void toggle_bit2() { uval ^= bm2 ; } ;
      inline void toggle_bit3() { uval ^= bm3 ; } ;
      inline void toggle_bit4() { uval ^= bm4 ; } ;
      inline void toggle_bit5() { uval ^= bm5 ; } ;
      inline void toggle_bit6() { uval ^= bm6 ; } ;
      inline void toggle_bit7() { uval ^= bm7 ; } ;
      inline void toggle_bits(char val)    { uval ^= val ; } ;
      inline void toggle_bits(uint8_t val) { uval ^= val ; } ;
      inline void toggle_bits(int8_t val)  { uval ^= val ; } ;

      inline static data_8bit_t& from(const int8_t& val) {return *((data_8bit_t*)(&val)) ; }
      inline static data_8bit_t& from(const uint8_t& val) {return *((data_8bit_t*)(&val)) ; }

    }  ;

union volatile_data_8bit_t
        {
         enum bit_state_t    { low=0, high }  ;
         enum bit_index_t { bi0=0 , bi1, bi2, bi3, bi4, bi5, bi6, bi7, bi_count }  ;
         enum bit_mask_t { bm0= 1 << bi0 ,
                         bm1= 1 << bi1,
    	                 bm2= 1 << bi2,
    	                 bm3= 1 << bi3,
    	                 bm4= 1 << bi4,
    	                 bm5= 1 << bi5,
    	                 bm6= 1 << bi6,
    	                 bm7= 1 << bi7 }  ;
         struct
          {
    	    volatile bit_state_t bit0 : 1  ;
    	    volatile bit_state_t bit1 : 1  ;
    	    volatile bit_state_t bit2 : 1  ;
    	    volatile bit_state_t bit3 : 1  ;
    	    volatile bit_state_t bit4 : 1  ;
    	    volatile bit_state_t bit5 : 1  ;
    	    volatile bit_state_t bit6 : 1  ;
    	    volatile bit_state_t bit7 : 1  ;
          } __reg_attr__ ;
          volatile char    cval ;
          volatile uint8_t uval ;
          volatile int8_t  sval ;

          // bit set operation
          inline void set_bit ( bit_index_t bit_index ) { NRO uval |= (1 << bit_index) ; } ;
          inline void set_bit ( bit_mask_t bit_mask )   { NRO uval |=  bit_mask  ; } ;
          inline void set_bit0() { NRO uval |= bm0 ; } ;
          inline void set_bit1() { NRO uval |= bm1 ; } ;
          inline void set_bit2() { NRO uval |= bm2 ; } ;
          inline void set_bit3() { NRO uval |= bm3 ; } ;
          inline void set_bit4() { NRO uval |= bm4 ; } ;
          inline void set_bit5() { NRO uval |= bm5 ; } ;
          inline void set_bit6() { NRO uval |= bm6 ; } ;
          inline void set_bit7() { NRO uval |= bm7 ; } ;
          inline void set_bits(char val)    { NRO uval |= val ; } ;
          inline void set_bits(uint8_t val) { NRO uval |= val ; } ;
          inline void set_bits(int8_t val)  { NRO uval |= val ; } ;

          // bit clear operation
          inline void clear_bit ( bit_index_t bit_index ) { NRO uval &= ~(1 << bit_index) ; } ;
          inline void clear_bit ( bit_mask_t bit_mask )   { NRO uval &= ~bit_mask  ; } ;
          inline void clear_bit0() { NRO uval &= ~bm0 ; } ;
          inline void clear_bit1() { NRO uval &= ~bm1 ; } ;
          inline void clear_bit2() { NRO uval &= ~bm2 ; } ;
          inline void clear_bit3() { NRO uval &= ~bm3 ; } ;
          inline void clear_bit4() { NRO uval &= ~bm4 ; } ;
          inline void clear_bit5() { NRO uval &= ~bm5 ; } ;
          inline void clear_bit6() { NRO uval &= ~bm6 ; } ;
          inline void clear_bit7() { NRO uval &= ~bm7 ; } ;
          inline void clear_bits(char val)    { NRO uval &= ~val ; } ;
          inline void clear_bits(uint8_t val) { NRO uval &= ~val ; } ;
          inline void clear_bits(int8_t val)  { NRO uval &= ~val ; } ;


          // bit toggle operation
          inline void toggle_bit ( bit_index_t bit_index ) { NRO uval ^= (1 << bit_index) ; } ;
          inline void toggle_bit ( bit_mask_t bit_mask )   { NRO uval ^=  bit_mask  ; } ;
          inline void toggle_bit0() { NRO uval ^= bm0 ; } ;
          inline void toggle_bit1() { NRO uval ^= bm1 ; } ;
          inline void toggle_bit2() { NRO uval ^= bm2 ; } ;
          inline void toggle_bit3() { NRO uval ^= bm3 ; } ;
          inline void toggle_bit4() { NRO uval ^= bm4 ; } ;
          inline void toggle_bit5() { NRO uval ^= bm5 ; } ;
          inline void toggle_bit6() { NRO uval ^= bm6 ; } ;
          inline void toggle_bit7() { NRO uval ^= bm7 ; } ;
          inline void toggle_bits(char val)    { NRO uval ^= val ; } ;
          inline void toggle_bits(uint8_t val) { NRO uval ^= val ; } ;
          inline void toggle_bits(int8_t val)  { NRO sval ^= val ; } ;

          inline static data_8bit_t& from(const int8_t& val) {NRO return *((data_8bit_t*)(&val)) ; }
          inline static data_8bit_t& from(const uint8_t& val) {NRO return *((data_8bit_t*)(&val)) ; }
        }  ;

union data_16bit_t
    {
     enum bit_state_t    { low=0, high }  ;
     enum bit_index_t { bi0=0 , bi1, bi2, bi3, bi4, bi5, bi6, bi7, bi8, bi9, bi10, bi11, bi12, bi13, bi14, bi15, bi_count }  ;
     enum bit_mask_t { bm0= 1 << bi0 ,
                     bm1= 1 << bi1,
	             bm2= 1 << bi2,
	             bm3= 1 << bi3,
	             bm4= 1 << bi4,
	             bm5= 1 << bi5,
	             bm6= 1 << bi6,
	             bm7= 1 << bi7,
		     bm8= 1 << bi8,
		     bm9= 1 << bi9,
		     bm10=1 << bi10,
		     bm11=1 << bi11,
		     bm12=1 << bi12,
		     bm13=1 << bi13,
		     bm14=1 << bi14,
		     bm15=1 << bi15,
                    }  ;
      struct
      {
	bit_state_t bit0 : 1  ;
	bit_state_t bit1 : 1  ;
	bit_state_t bit2 : 1  ;
	bit_state_t bit3 : 1  ;
	bit_state_t bit4 : 1  ;
	bit_state_t bit5 : 1  ;
	bit_state_t bit6 : 1  ;
	bit_state_t bit7 : 1  ;
	bit_state_t bit8 : 1  ;
	bit_state_t bit9 : 1  ;
	bit_state_t bit10 : 1 ;
	bit_state_t bit11 : 1 ;
	bit_state_t bit12 : 1 ;
	bit_state_t bit13 : 1 ;
	bit_state_t bit14 : 1 ;
	bit_state_t bit15 : 1 ;
      } __reg_attr__ ;
      struct
      {
	data_8bit_t low_byte ;
	data_8bit_t high_byte ;
      };
      uint16_t uval ;
      int16_t  sval ;

      // bit set operation
      inline void set_bit ( bit_index_t bit_index ) { uval |= (1 << bit_index) ; } ;
      inline void set_bit ( bit_mask_t bit_mask )   { uval |=  bit_mask  ; } ;
      inline void set_bit0() { uval |= bm0  ; } ;
      inline void set_bit1() { uval |= bm1  ; } ;
      inline void set_bit2() { uval |= bm2  ; } ;
      inline void set_bit3() { uval |= bm3  ; } ;
      inline void set_bit4() { uval |= bm4  ; } ;
      inline void set_bit5() { uval |= bm5  ; } ;
      inline void set_bit6() { uval |= bm6  ; } ;
      inline void set_bit7() { uval |= bm7  ; } ;
      inline void set_bit8() { uval |= bm8  ; } ;
      inline void set_bit9() { uval |= bm9  ; } ;
      inline void set_bit10(){ uval |= bm10 ; } ;
      inline void set_bit11(){ uval |= bm11 ; } ;
      inline void set_bit12(){ uval |= bm12 ; } ;
      inline void set_bit13(){ uval |= bm13 ; } ;
      inline void set_bit14(){ uval |= bm14 ; } ;
      inline void set_bit15(){ uval |= bm15 ; } ;
      inline void set_bits(uint16_t val) { uval |= val ; } ;
      inline void set_bits(int16_t val)  { uval |= val ; } ;

      // bit clear operation
      inline void clear_bit ( bit_index_t bit_index ) { uval &= ~(1 << bit_index) ; } ;
      inline void clear_bit ( bit_mask_t bit_mask )   { uval &= ~bit_mask  ; } ;
      inline void clear_bit0() { uval &= ~bm0  ; } ;
      inline void clear_bit1() { uval &= ~bm1  ; } ;
      inline void clear_bit2() { uval &= ~bm2  ; } ;
      inline void clear_bit3() { uval &= ~bm3  ; } ;
      inline void clear_bit4() { uval &= ~bm4  ; } ;
      inline void clear_bit5() { uval &= ~bm5  ; } ;
      inline void clear_bit6() { uval &= ~bm6  ; } ;
      inline void clear_bit7() { uval &= ~bm7  ; } ;
      inline void clear_bit8() { uval &= ~bm8  ; } ;
      inline void clear_bit9() { uval &= ~bm9  ; } ;
      inline void clear_bit10(){ uval &= ~bm10 ; } ;
      inline void clear_bit11(){ uval &= ~bm11 ; } ;
      inline void clear_bit12(){ uval &= ~bm12 ; } ;
      inline void clear_bit13(){ uval &= ~bm13 ; } ;
      inline void clear_bit14(){ uval &= ~bm14 ; } ;
      inline void clear_bit15(){ uval &= ~bm15 ; } ;
      inline void clear_bits(uint16_t val) { uval &= ~val ; } ;
      inline void clear_bits(int16_t val)  { uval &= ~val ; } ;

      // bit toggle operation
      inline void toggle_bit ( bit_index_t bit_index ) { NRO uval ^= ~(1 << bit_index) ; } ;
      inline void toggle_bit ( bit_mask_t bit_mask )   { NRO uval ^= ~bit_mask  ; } ;
      inline void toggle_bit0()  { uval ^= bm0 ;  } ;
      inline void toggle_bit1()  { uval ^= bm1 ;  } ;
      inline void toggle_bit2()  { uval ^= bm2 ;  } ;
      inline void toggle_bit3()  { uval ^= bm3 ;  } ;
      inline void toggle_bit4()  { uval ^= bm4 ;  } ;
      inline void toggle_bit5()  { uval ^= bm5 ;  } ;
      inline void toggle_bit6()  { uval ^= bm6 ;  } ;
      inline void toggle_bit7()  { uval ^= bm7 ;  } ;
      inline void toggle_bit8()  { uval ^= bm8 ;  } ;
      inline void toggle_bit9()  { uval ^= bm9 ;  } ;
      inline void toggle_bit10() { uval ^= bm10 ; } ;
      inline void toggle_bit11() { uval ^= bm11 ; } ;
      inline void toggle_bit12() { uval ^= bm12 ; } ;
      inline void toggle_bit13() { uval ^= bm13 ; } ;
      inline void toggle_bit14() { uval ^= bm14 ; } ;
      inline void toggle_bit15() { uval ^= bm15 ; } ;
      inline void toggle_bits(uint16_t val) { uval ^= val ; } ;
      inline void toggle_bits(int16_t  val) { sval ^= val ; } ;

      inline static data_16bit_t& from(const int16_t& val) {return *((data_16bit_t*)(&val)) ; }
      inline static data_16bit_t& from(const uint16_t& val) {return *((data_16bit_t*)(&val)) ; }

    } ;


union volatile_data_16bit_t
        {
         enum bit_state_t    { low=0, high }  ;
         enum bit_index_t { bi0=0 , bi1, bi2, bi3, bi4, bi5, bi6, bi7, bi8, bi9, bi10, bi11, bi12, bi13, bi14, bi15, bi_count }  ;
         enum bit_mask_t { bm0= 1 << bi0 ,
                         bm1= 1 << bi1,
    	             bm2= 1 << bi2,
    	             bm3= 1 << bi3,
    	             bm4= 1 << bi4,
    	             bm5= 1 << bi5,
    	             bm6= 1 << bi6,
    	             bm7= 1 << bi7,
    		     bm8= 1 << bi8,
    		     bm9= 1 << bi9,
    		     bm10=1 << bi10,
    		     bm11=1 << bi11,
    		     bm12=1 << bi12,
    		     bm13=1 << bi13,
    		     bm14=1 << bi14,
    		     bm15=1 << bi15,
                        }  ;
          struct
          {
             volatile bit_state_t bit0 : 1  ;
    	     volatile bit_state_t bit1 : 1  ;
    	     volatile bit_state_t bit2 : 1  ;
    	     volatile bit_state_t bit3 : 1  ;
    	     volatile bit_state_t bit4 : 1  ;
    	     volatile bit_state_t bit5 : 1  ;
    	     volatile bit_state_t bit6 : 1  ;
    	     volatile bit_state_t bit7 : 1  ;
    	     volatile bit_state_t bit8 : 1  ;
    	     volatile bit_state_t bit9 : 1  ;
    	     volatile bit_state_t bit10 : 1 ;
    	     volatile bit_state_t bit11 : 1 ;
    	     volatile bit_state_t bit12 : 1 ;
    	     volatile bit_state_t bit13 : 1 ;
    	     volatile bit_state_t bit14 : 1 ;
    	     volatile bit_state_t bit15 : 1 ;
          } __reg_attr__ ;
          struct
          {
            volatile_data_8bit_t low_byte ;
    	    volatile_data_8bit_t high_byte ;
          };
          uint16_t uval ;
          int16_t  sval ;

          // bit set operation
          inline void set_bit ( bit_index_t bit_index ) { NRO uval |= (1 << bit_index) ; } ;
          inline void set_bit ( bit_mask_t bit_mask )   { NRO uval |=  bit_mask  ; } ;
          inline void set_bit0() { NRO uval |= bm0  ; } ;
          inline void set_bit1() { NRO uval |= bm1  ; } ;
          inline void set_bit2() { NRO uval |= bm2  ; } ;
          inline void set_bit3() { NRO uval |= bm3  ; } ;
          inline void set_bit4() { NRO uval |= bm4  ; } ;
          inline void set_bit5() { NRO uval |= bm5  ; } ;
          inline void set_bit6() { NRO uval |= bm6  ; } ;
          inline void set_bit7() { NRO uval |= bm7  ; } ;
          inline void set_bit8() { NRO uval |= bm8  ; } ;
          inline void set_bit9() { NRO uval |= bm9  ; } ;
          inline void set_bit10(){ NRO uval |= bm10 ; } ;
          inline void set_bit11(){ NRO uval |= bm11 ; } ;
          inline void set_bit12(){ NRO uval |= bm12 ; } ;
          inline void set_bit13(){ NRO uval |= bm13 ; } ;
          inline void set_bit14(){ NRO uval |= bm14 ; } ;
          inline void set_bit15(){ NRO uval |= bm15 ; } ;
          inline void set_bits(uint16_t val) { NRO uval |= val ; } ;
          inline void set_bits(int16_t val)  { NRO uval |= val ; } ;

          // bit clear operation
          inline void clear_bit ( bit_index_t bit_index ) { NRO uval &= ~(1 << bit_index) ; } ;
          inline void clear_bit ( bit_mask_t bit_mask )   { NRO uval &= ~bit_mask  ; } ;
          inline void clear_bit0() { NRO uval &= ~bm0  ; } ;
          inline void clear_bit1() { NRO uval &= ~bm1  ; } ;
          inline void clear_bit2() { NRO uval &= ~bm2  ; } ;
          inline void clear_bit3() { NRO uval &= ~bm3  ; } ;
          inline void clear_bit4() { NRO uval &= ~bm4  ; } ;
          inline void clear_bit5() { NRO uval &= ~bm5  ; } ;
          inline void clear_bit6() { NRO uval &= ~bm6  ; } ;
          inline void clear_bit7() { NRO uval &= ~bm7  ; } ;
          inline void clear_bit8() { NRO uval &= ~bm8  ; } ;
          inline void clear_bit9() { NRO uval &= ~bm9  ; } ;
          inline void clear_bit10(){ NRO uval &= ~bm10 ; } ;
          inline void clear_bit11(){ NRO uval &= ~bm11 ; } ;
          inline void clear_bit12(){ NRO uval &= ~bm12 ; } ;
          inline void clear_bit13(){ NRO uval &= ~bm13 ; } ;
          inline void clear_bit14(){ NRO uval &= ~bm14 ; } ;
          inline void clear_bit15(){ NRO uval &= ~bm15 ; } ;
          inline void clear_bits(uint16_t val) { NRO uval &= ~val ; } ;
          inline void clear_bits(int16_t val)  { NRO uval &= ~val ; } ;

          // bit toggle operation
          inline void toggle_bit ( bit_index_t bit_index ) { NRO uval ^= ~(1 << bit_index) ; } ;
          inline void toggle_bit ( bit_mask_t bit_mask )   { NRO uval ^= ~bit_mask  ; } ;
          inline void toggle_bit0()  { NRO uval ^= bm0 ;  } ;
          inline void toggle_bit1()  { NRO uval ^= bm1 ;  } ;
          inline void toggle_bit2()  { NRO uval ^= bm2 ;  } ;
          inline void toggle_bit3()  { NRO uval ^= bm3 ;  } ;
          inline void toggle_bit4()  { NRO uval ^= bm4 ;  } ;
          inline void toggle_bit5()  { NRO uval ^= bm5 ;  } ;
          inline void toggle_bit6()  { NRO uval ^= bm6 ;  } ;
          inline void toggle_bit7()  { NRO uval ^= bm7 ;  } ;
          inline void toggle_bit8()  { NRO uval ^= bm8 ;  } ;
          inline void toggle_bit9()  { NRO uval ^= bm9 ;  } ;
          inline void toggle_bit10() { NRO uval ^= bm10 ; } ;
          inline void toggle_bit11() { NRO uval ^= bm11 ; } ;
          inline void toggle_bit12() { NRO uval ^= bm12 ; } ;
          inline void toggle_bit13() { NRO uval ^= bm13 ; } ;
          inline void toggle_bit14() { NRO uval ^= bm14 ; } ;
          inline void toggle_bit15() { NRO uval ^= bm15 ; } ;
          inline void toggle_bits(uint16_t val) { NRO uval ^= val ; } ;
          inline void toggle_bits(int16_t  val) { NRO sval ^= val ; } ;

          inline static data_16bit_t& from(const int16_t& val) {NRO return *((data_16bit_t*)(&val)) ; }
          inline static data_16bit_t& from(const uint16_t& val) {NRO return *((data_16bit_t*)(&val)) ; }

        }  ;


union data_32bit_t
    {
     enum bit_state_t    { low=0, high }  ;
     enum bit_index_t { bi0=0 , bi1, bi2, bi3, bi4, bi5, bi6, bi7, bi8, bi9, bi10,
                     bi11, bi12, bi13, bi14, bi15, bi16, bi17, bi18, bi19,
		     bi20, bi21, bi22, bi23, bi24, bi25, bi26, bi27, bi28,
		     bi29, bi30, bi31,bi_count }  ;
     enum bit_mask_t { bm0= 1 << bi0 ,
                     bm1= 1 << bi1,
	             bm2= 1 << bi2,
	             bm3= 1 << bi3,
	             bm4= 1 << bi4,
	             bm5= 1 << bi5,
	             bm6= 1 << bi6,
	             bm7= 1 << bi7,
		     bm8= 1 << bi8,
		     bm9= 1 << bi9,
		     bm10=1 << bi10,
		     bm11=1 << bi11,
		     bm12=1 << bi12,
		     bm13=1 << bi13,
		     bm14=1 << bi14,
		     bm15=1 << bi15,
		     bm16=1 << bi16,
		     bm17=1 << bi17,
		     bm18=1 << bi18,
		     bm19=1 << bi19,
		     bm20=1 << bi20,
		     bm21=1 << bi21,
		     bm22=1 << bi22,
		     bm23=1 << bi23,
		     bm24=1 << bi24,
		     bm25=1 << bi25,
		     bm26=1 << bi26,
		     bm27=1 << bi27,
		     bm28=1 << bi28,
		     bm29=1 << bi29,
		     bm30=1 << bi30,
		     bm31=1 << bi31,
                 }  ;
      struct
      {
	bit_state_t bit0 : 1  ;
	bit_state_t bit1 : 1  ;
	bit_state_t bit2 : 1  ;
	bit_state_t bit3 : 1  ;
	bit_state_t bit4 : 1  ;
	bit_state_t bit5 : 1  ;
	bit_state_t bit6 : 1  ;
	bit_state_t bit7 : 1  ;
	bit_state_t bit8 : 1  ;
	bit_state_t bit9 : 1  ;
	bit_state_t bit10 : 1  ;
	bit_state_t bit11 : 1  ;
	bit_state_t bit12 : 1  ;
	bit_state_t bit13 : 1  ;
	bit_state_t bit14 : 1  ;
	bit_state_t bit15 : 1  ;
	bit_state_t bit16 : 1  ;
	bit_state_t bit17 : 1  ;
	bit_state_t bit18 : 1  ;
	bit_state_t bit19 : 1  ;
	bit_state_t bit20 : 1  ;
	bit_state_t bit21 : 1  ;
	bit_state_t bit22 : 1  ;
	bit_state_t bit23 : 1  ;
	bit_state_t bit24 : 1  ;
	bit_state_t bit25 : 1  ;
	bit_state_t bit26 : 1  ;
	bit_state_t bit27 : 1  ;
	bit_state_t bit28 : 1  ;
	bit_state_t bit29 : 1  ;
	bit_state_t bit30 : 1  ;
	bit_state_t bit31 : 1  ;
      } __reg_attr__ ;
      struct
      {
	data_16bit_t low_half_word ;
	data_16bit_t high_half_word ;
      } __reg_attr__ ;
      uint32_t uval ;
      int32_t  sval ;
      float    fval ;

      // bit set operation
      inline void set_bit ( bit_index_t bit_index ) { uval |= (1 << bit_index) ; } ;
      inline void set_bit ( bit_mask_t bit_mask )   { uval |=  bit_mask  ; } ;
      inline void set_bit0() { uval |= bm0  ; } ;
      inline void set_bit1() { uval |= bm1  ; } ;
      inline void set_bit2() { uval |= bm2  ; } ;
      inline void set_bit3() { uval |= bm3  ; } ;
      inline void set_bit4() { uval |= bm4  ; } ;
      inline void set_bit5() { uval |= bm5  ; } ;
      inline void set_bit6() { uval |= bm6  ; } ;
      inline void set_bit7() { uval |= bm7  ; } ;
      inline void set_bit8() { uval |= bm8  ; } ;
      inline void set_bit9() { uval |= bm9  ; } ;
      inline void set_bit10(){ uval |= bm10 ; } ;
      inline void set_bit11(){ uval |= bm11 ; } ;
      inline void set_bit12(){ uval |= bm12 ; } ;
      inline void set_bit13(){ uval |= bm13 ; } ;
      inline void set_bit14(){ uval |= bm14 ; } ;
      inline void set_bit15(){ uval |= bm15 ; } ;
      inline void set_bit16(){ uval |= bm16 ; } ;
      inline void set_bit17(){ uval |= bm17 ; } ;
      inline void set_bit18(){ uval |= bm18 ; } ;
      inline void set_bit19(){ uval |= bm19 ; } ;
      inline void set_bit20(){ uval |= bm20 ; } ;
      inline void set_bit21(){ uval |= bm21 ; } ;
      inline void set_bit22(){ uval |= bm22 ; } ;
      inline void set_bit23(){ uval |= bm23 ; } ;
      inline void set_bit24(){ uval |= bm24 ; } ;
      inline void set_bit25(){ uval |= bm25 ; } ;
      inline void set_bit26(){ uval |= bm26 ; } ;
      inline void set_bit27(){ uval |= bm27 ; } ;
      inline void set_bit28(){ uval |= bm28 ; } ;
      inline void set_bit29(){ uval |= bm29 ; } ;
      inline void set_bit30(){ uval |= bm30 ; } ;
      inline void set_bit31(){ uval |= bm31 ; } ;
      inline void set_bits(uint32_t val) { uval |= val ; } ;
      inline void set_bits(int32_t val)  { uval |= val ; } ;

      // bit clear operation
      inline void clear_bit ( bit_index_t bit_index ) { uval &=~ (1 << bit_index) ; } ;
      inline void clear_bit ( bit_mask_t bit_mask )   { uval &=~  bit_mask  ; } ;
      inline void clear_bit0() { uval &=~ bm0  ; } ;
      inline void clear_bit1() { uval &=~ bm1  ; } ;
      inline void clear_bit2() { uval &=~ bm2  ; } ;
      inline void clear_bit3() { uval &=~ bm3  ; } ;
      inline void clear_bit4() { uval &=~ bm4  ; } ;
      inline void clear_bit5() { uval &=~ bm5  ; } ;
      inline void clear_bit6() { uval &=~ bm6  ; } ;
      inline void clear_bit7() { uval &=~ bm7  ; } ;
      inline void clear_bit8() { uval &=~ bm8  ; } ;
      inline void clear_bit9() { uval &=~ bm9  ; } ;
      inline void clear_bit10(){ uval &=~ bm10 ; } ;
      inline void clear_bit11(){ uval &=~ bm11 ; } ;
      inline void clear_bit12(){ uval &=~ bm12 ; } ;
      inline void clear_bit13(){ uval &=~ bm13 ; } ;
      inline void clear_bit14(){ uval &=~ bm14 ; } ;
      inline void clear_bit15(){ uval &=~ bm15 ; } ;
      inline void clear_bit16(){ uval &=~ bm16 ; } ;
      inline void clear_bit17(){ uval &=~ bm17 ; } ;
      inline void clear_bit18(){ uval &=~ bm18 ; } ;
      inline void clear_bit19(){ uval &=~ bm19 ; } ;
      inline void clear_bit20(){ uval &=~ bm20 ; } ;
      inline void clear_bit21(){ uval &=~ bm21 ; } ;
      inline void clear_bit22(){ uval &=~ bm22 ; } ;
      inline void clear_bit23(){ uval &=~ bm23 ; } ;
      inline void clear_bit24(){ uval &=~ bm24 ; } ;
      inline void clear_bit25(){ uval &=~ bm25 ; } ;
      inline void clear_bit26(){ uval &=~ bm26 ; } ;
      inline void clear_bit27(){ uval &=~ bm27 ; } ;
      inline void clear_bit28(){ uval &=~ bm28 ; } ;
      inline void clear_bit29(){ uval &=~ bm29 ; } ;
      inline void clear_bit30(){ uval &=~ bm30 ; } ;
      inline void clear_bit31(){ uval &=~ bm31 ; } ;
      inline void clear_bits(uint32_t val) { uval &=~ val ; } ;
      inline void clear_bits(int32_t val)  { uval &=~ val ; } ;

      inline void toggle_bit ( bit_index_t bit_index ) { uval ^= (1 << bit_index) ; } ;
      inline void toggle_bit ( bit_mask_t bit_mask )   { uval ^=  bit_mask  ; } ;
      inline void toggle_bit0()  { uval ^= bm0 ; } ;
      inline void toggle_bit1()  { uval ^= bm1 ; } ;
      inline void toggle_bit2()  { uval ^= bm2 ; } ;
      inline void toggle_bit3()  { uval ^= bm3 ; } ;
      inline void toggle_bit4()  { uval ^= bm4 ; } ;
      inline void toggle_bit5()  { uval ^= bm5 ; } ;
      inline void toggle_bit6()  { uval ^= bm6 ; } ;
      inline void toggle_bit7()  { uval ^= bm7 ; } ;
      inline void toggle_bit8()  { uval ^= bm8 ; } ;
      inline void toggle_bit9()  { uval ^= bm9 ; } ;
      inline void toggle_bit10() { uval ^= bm10 ; } ;
      inline void toggle_bit11() { uval ^= bm11 ; } ;
      inline void toggle_bit12() { uval ^= bm12 ; } ;
      inline void toggle_bit13() { uval ^= bm13 ; } ;
      inline void toggle_bit14() { uval ^= bm14 ; } ;
      inline void toggle_bit15() { uval ^= bm15 ; } ;
      inline void toggle_bit16() { uval ^= bm16 ; } ;
      inline void toggle_bit17() { uval ^= bm17 ; } ;
      inline void toggle_bit18() { uval ^= bm18 ; } ;
      inline void toggle_bit19() { uval ^= bm19 ; } ;
      inline void toggle_bit20() { uval ^= bm20 ; } ;
      inline void toggle_bit21() { uval ^= bm21 ; } ;
      inline void toggle_bit22() { uval ^= bm22 ; } ;
      inline void toggle_bit23() { uval ^= bm23 ; } ;
      inline void toggle_bit24() { uval ^= bm24 ; } ;
      inline void toggle_bit25() { uval ^= bm25 ; } ;
      inline void toggle_bit26() { uval ^= bm26 ; } ;
      inline void toggle_bit27() { uval ^= bm27 ; } ;
      inline void toggle_bit28() { uval ^= bm28 ; } ;
      inline void toggle_bit29() { uval ^= bm29 ; } ;
      inline void toggle_bit30() { uval ^= bm30 ; } ;
      inline void toggle_bit31() { uval ^= bm31 ; } ;
      inline void toggle_bits(uint32_t val) { uval ^= val ; } ;
      inline void toggle_bits(int32_t  val) { sval ^= val ; } ;

      inline static data_32bit_t& from(const int32_t& val) {NRO return *((data_32bit_t*)(&val)) ; }
      inline static data_32bit_t& from(const uint32_t& val) {NRO return *((data_32bit_t*)(&val)) ; }

    } ;

union volatile_data_32bit_t
        {
         enum bit_state_t    { low=0, high }  ;
         enum bit_index_t { bi0=0 , bi1, bi2, bi3, bi4, bi5, bi6, bi7, bi8, bi9, bi10,
                            bi11, bi12, bi13, bi14, bi15, bi16, bi17, bi18, bi19,
    		            bi20, bi21, bi22, bi23, bi24, bi25, bi26, bi27, bi28,
    		            bi29, bi30, bi31,bi_count }  ;
         enum bit_mask_t { bm0= 1 << bi0 ,
                         bm1= 1 << bi1,
    	             bm2= 1 << bi2,
    	             bm3= 1 << bi3,
    	             bm4= 1 << bi4,
    	             bm5= 1 << bi5,
    	             bm6= 1 << bi6,
    	             bm7= 1 << bi7,
    		     bm8= 1 << bi8,
    		     bm9= 1 << bi9,
    		     bm10=1 << bi10,
    		     bm11=1 << bi11,
    		     bm12=1 << bi12,
    		     bm13=1 << bi13,
    		     bm14=1 << bi14,
    		     bm15=1 << bi15,
    		     bm16=1 << bi16,
    		     bm17=1 << bi17,
    		     bm18=1 << bi18,
    		     bm19=1 << bi19,
    		     bm20=1 << bi20,
    		     bm21=1 << bi21,
    		     bm22=1 << bi22,
    		     bm23=1 << bi23,
    		     bm24=1 << bi24,
    		     bm25=1 << bi25,
    		     bm26=1 << bi26,
    		     bm27=1 << bi27,
    		     bm28=1 << bi28,
    		     bm29=1 << bi29,
    		     bm30=1 << bi30,
    		     bm31=1 << bi31,
                     }  ;
          struct
          {
            volatile bit_state_t bit0  : 1  ;
	    volatile bit_state_t bit1  : 1  ;
	    volatile bit_state_t bit2  : 1  ;
	    volatile bit_state_t bit3  : 1  ;
	    volatile bit_state_t bit4  : 1  ;
	    volatile bit_state_t bit5  : 1  ;
	    volatile bit_state_t bit6  : 1  ;
	    volatile bit_state_t bit7  : 1  ;
	    volatile bit_state_t bit8  : 1  ;
	    volatile bit_state_t bit9  : 1  ;
	    volatile bit_state_t bit10 : 1  ;
	    volatile bit_state_t bit11 : 1  ;
	    volatile bit_state_t bit12 : 1  ;
	    volatile bit_state_t bit13 : 1  ;
	    volatile bit_state_t bit14 : 1  ;
	    volatile bit_state_t bit15 : 1  ;
	    volatile bit_state_t bit16 : 1  ;
	    volatile bit_state_t bit17 : 1  ;
	    volatile bit_state_t bit18 : 1  ;
	    volatile bit_state_t bit19 : 1  ;
	    volatile bit_state_t bit20 : 1  ;
	    volatile bit_state_t bit21 : 1  ;
	    volatile bit_state_t bit22 : 1  ;
	    volatile bit_state_t bit23 : 1  ;
	    volatile bit_state_t bit24 : 1  ;
	    volatile bit_state_t bit25 : 1  ;
	    volatile bit_state_t bit26 : 1  ;
	    volatile bit_state_t bit27 : 1  ;
	    volatile bit_state_t bit28 : 1  ;
    	    volatile bit_state_t bit29 : 1  ;
    	    volatile bit_state_t bit30 : 1  ;
    	    volatile bit_state_t bit31 : 1  ;
          } __reg_attr__ ;
          struct
          {
            volatile_data_16bit_t low_half_word ;
            volatile_data_16bit_t high_half_word ;
          } __reg_attr__ ;
          volatile uint32_t uval ;
          volatile int32_t  sval ;
          volatile float    fval ;

          // read
          inline bit_state_t bit(const bit_index_t val) const { NRO return uval & (1 << val)  ? high : low ; } ;
          inline bit_state_t bit(const bit_mask_t  val) const { NRO return uval & val ? high : low ; } ;
          inline bit_state_t bit(const volatile_data_16bit_t::bit_index_t val) const { NRO return uval & (1 << val)  ? high : low ; } ;
          inline bit_state_t bit(const volatile_data_16bit_t::bit_mask_t  val) const { NRO return uval & val ? high : low ; } ;

          // bit set operation
          inline void set_bit ( bit_index_t bit_index ) { NRO uval |= (1 << bit_index) ; } ;
          inline void set_bit ( bit_mask_t bit_mask )   { NRO uval |=  bit_mask  ; } ;
          inline void set_bit ( volatile_data_16bit_t::bit_index_t bit_index ) { NRO uval |= (1 << bit_index) ; } ;
          inline void set_bit ( volatile_data_16bit_t::bit_mask_t bit_mask )   { NRO uval |=  bit_mask  ; } ;
          inline void set_bit0() { NRO uval |= bm0  ; } ;
          inline void set_bit1() { NRO uval |= bm1  ; } ;
          inline void set_bit2() { NRO uval |= bm2  ; } ;
          inline void set_bit3() { NRO uval |= bm3  ; } ;
          inline void set_bit4() { NRO uval |= bm4  ; } ;
          inline void set_bit5() { NRO uval |= bm5  ; } ;
          inline void set_bit6() { NRO uval |= bm6  ; } ;
          inline void set_bit7() { NRO uval |= bm7  ; } ;
          inline void set_bit8() { NRO uval |= bm8  ; } ;
          inline void set_bit9() { NRO uval |= bm9  ; } ;
          inline void set_bit10(){ NRO uval |= bm10 ; } ;
          inline void set_bit11(){ NRO uval |= bm11 ; } ;
          inline void set_bit12(){ NRO uval |= bm12 ; } ;
          inline void set_bit13(){ NRO uval |= bm13 ; } ;
          inline void set_bit14(){ NRO uval |= bm14 ; } ;
          inline void set_bit15(){ NRO uval |= bm15 ; } ;
          inline void set_bit16(){ NRO uval |= bm16 ; } ;
          inline void set_bit17(){ NRO uval |= bm17 ; } ;
          inline void set_bit18(){ NRO uval |= bm18 ; } ;
          inline void set_bit19(){ NRO uval |= bm19 ; } ;
          inline void set_bit20(){ NRO uval |= bm20 ; } ;
          inline void set_bit21(){ NRO uval |= bm21 ; } ;
          inline void set_bit22(){ NRO uval |= bm22 ; } ;
          inline void set_bit23(){ NRO uval |= bm23 ; } ;
          inline void set_bit24(){ NRO uval |= bm24 ; } ;
          inline void set_bit25(){ NRO uval |= bm25 ; } ;
          inline void set_bit26(){ NRO uval |= bm26 ; } ;
          inline void set_bit27(){ NRO uval |= bm27 ; } ;
          inline void set_bit28(){ NRO uval |= bm28 ; } ;
          inline void set_bit29(){ NRO uval |= bm29 ; } ;
          inline void set_bit30(){ NRO uval |= bm30 ; } ;
          inline void set_bit31(){ NRO uval |= bm31 ; } ;
          inline void set_bits(uint32_t val) { NRO uval |= val ; } ;
          inline void set_bits(int32_t val)  { NRO uval |= val ; } ;

          // bit clear operation
          inline void clear_bit ( bit_index_t bit_index ) { NRO uval &=~ (1 << bit_index) ; } ;
          inline void clear_bit ( bit_mask_t bit_mask )   { NRO uval &=~  bit_mask  ; } ;
          inline void clear_bit ( volatile_data_16bit_t::bit_index_t bit_index ) { NRO uval &=~ (1 << bit_index) ; } ;
          inline void clear_bit ( volatile_data_16bit_t::bit_mask_t bit_mask )   { NRO uval &=~  bit_mask  ; } ;
          inline void clear_bit0() { NRO uval &=~ bm0  ; } ;
          inline void clear_bit1() { NRO uval &=~ bm1  ; } ;
          inline void clear_bit2() { NRO uval &=~ bm2  ; } ;
          inline void clear_bit3() { NRO uval &=~ bm3  ; } ;
          inline void clear_bit4() { NRO uval &=~ bm4  ; } ;
          inline void clear_bit5() { NRO uval &=~ bm5  ; } ;
          inline void clear_bit6() { NRO uval &=~ bm6  ; } ;
          inline void clear_bit7() { NRO uval &=~ bm7  ; } ;
          inline void clear_bit8() { NRO uval &=~ bm8  ; } ;
          inline void clear_bit9() { NRO uval &=~ bm9  ; } ;
          inline void clear_bit10(){ NRO uval &=~ bm10 ; } ;
          inline void clear_bit11(){ NRO uval &=~ bm11 ; } ;
          inline void clear_bit12(){ NRO uval &=~ bm12 ; } ;
          inline void clear_bit13(){ NRO uval &=~ bm13 ; } ;
          inline void clear_bit14(){ NRO uval &=~ bm14 ; } ;
          inline void clear_bit15(){ NRO uval &=~ bm15 ; } ;
          inline void clear_bit16(){ NRO uval &=~ bm16 ; } ;
          inline void clear_bit17(){ NRO uval &=~ bm17 ; } ;
          inline void clear_bit18(){ NRO uval &=~ bm18 ; } ;
          inline void clear_bit19(){ NRO uval &=~ bm19 ; } ;
          inline void clear_bit20(){ NRO uval &=~ bm20 ; } ;
          inline void clear_bit21(){ NRO uval &=~ bm21 ; } ;
          inline void clear_bit22(){ NRO uval &=~ bm22 ; } ;
          inline void clear_bit23(){ NRO uval &=~ bm23 ; } ;
          inline void clear_bit24(){ NRO uval &=~ bm24 ; } ;
          inline void clear_bit25(){ NRO uval &=~ bm25 ; } ;
          inline void clear_bit26(){ NRO uval &=~ bm26 ; } ;
          inline void clear_bit27(){ NRO uval &=~ bm27 ; } ;
          inline void clear_bit28(){ NRO uval &=~ bm28 ; } ;
          inline void clear_bit29(){ NRO uval &=~ bm29 ; } ;
          inline void clear_bit30(){ NRO uval &=~ bm30 ; } ;
          inline void clear_bit31(){ NRO uval &=~ bm31 ; } ;
          inline void clear_bits(uint32_t val) { NRO uval &=~ val ; } ;
          inline void clear_bits(int32_t val)  { NRO uval &=~ val ; } ;

          inline void toggle_bit ( bit_index_t bit_index ) { NRO uval ^= (1 << bit_index) ; } ;
          inline void toggle_bit ( bit_mask_t bit_mask )   { NRO uval ^=   bit_mask  ; } ;
          inline void toggle_bit ( volatile_data_16bit_t::bit_index_t bit_index ) { NRO uval ^=  (1 << bit_index) ; } ;
          inline void toggle_bit ( volatile_data_16bit_t::bit_mask_t bit_mask )   { NRO uval ^=   bit_mask  ; } ;
          inline void toggle_bit0()  { NRO uval ^= bm0 ; } ;
          inline void toggle_bit1()  { NRO uval ^= bm1 ; } ;
          inline void toggle_bit2()  { NRO uval ^= bm2 ; } ;
          inline void toggle_bit3()  { NRO uval ^= bm3 ; } ;
          inline void toggle_bit4()  { NRO uval ^= bm4 ; } ;
          inline void toggle_bit5()  { NRO uval ^= bm5 ; } ;
          inline void toggle_bit6()  { NRO uval ^= bm6 ; } ;
          inline void toggle_bit7()  { NRO uval ^= bm7 ; } ;
          inline void toggle_bit8()  { NRO uval ^= bm8 ; } ;
          inline void toggle_bit9()  { NRO uval ^= bm9 ; } ;
          inline void toggle_bit10() { NRO uval ^= bm10 ; } ;
          inline void toggle_bit11() { NRO uval ^= bm11 ; } ;
          inline void toggle_bit12() { NRO uval ^= bm12 ; } ;
          inline void toggle_bit13() { NRO uval ^= bm13 ; } ;
          inline void toggle_bit14() { NRO uval ^= bm14 ; } ;
          inline void toggle_bit15() { NRO uval ^= bm15 ; } ;
          inline void toggle_bit16() { NRO uval ^= bm16 ; } ;
          inline void toggle_bit17() { NRO uval ^= bm17 ; } ;
          inline void toggle_bit18() { NRO uval ^= bm18 ; } ;
          inline void toggle_bit19() { NRO uval ^= bm19 ; } ;
          inline void toggle_bit20() { NRO uval ^= bm20 ; } ;
          inline void toggle_bit21() { NRO uval ^= bm21 ; } ;
          inline void toggle_bit22() { NRO uval ^= bm22 ; } ;
          inline void toggle_bit23() { NRO uval ^= bm23 ; } ;
          inline void toggle_bit24() { NRO uval ^= bm24 ; } ;
          inline void toggle_bit25() { NRO uval ^= bm25 ; } ;
          inline void toggle_bit26() { NRO uval ^= bm26 ; } ;
          inline void toggle_bit27() { NRO uval ^= bm27 ; } ;
          inline void toggle_bit28() { NRO uval ^= bm28 ; } ;
          inline void toggle_bit29() { NRO uval ^= bm29 ; } ;
          inline void toggle_bit30() { NRO uval ^= bm30 ; } ;
          inline void toggle_bit31() { NRO uval ^= bm31 ; } ;
          inline void toggle_bits(uint32_t val) { NRO uval ^= val ; } ;
          inline void toggle_bits(int32_t  val) { NRO sval ^= val ; } ;

          inline static data_32bit_t& from(const int32_t& val) {NRO return *((data_32bit_t*)(&val)) ; }
          inline static data_32bit_t& from(const uint32_t& val) {NRO return *((data_32bit_t*)(&val)) ; }
        } ;


union volatile_half_const_data_32bit_t
                {
                  enum bit_state_t    { low=0, high }  ;
                  struct
                  {
                    volatile bit_state_t bit0  : 1  ;
        	    volatile bit_state_t bit1  : 1  ;
        	    volatile bit_state_t bit2  : 1  ;
        	    volatile bit_state_t bit3  : 1  ;
        	    volatile bit_state_t bit4  : 1  ;
        	    volatile bit_state_t bit5  : 1  ;
        	    volatile bit_state_t bit6  : 1  ;
        	    volatile bit_state_t bit7  : 1  ;
        	    volatile bit_state_t bit8  : 1  ;
        	    volatile bit_state_t bit9  : 1  ;
        	    volatile bit_state_t bit10 : 1  ;
        	    volatile bit_state_t bit11 : 1  ;
        	    volatile bit_state_t bit12 : 1  ;
        	    volatile bit_state_t bit13 : 1  ;
        	    volatile bit_state_t bit14 : 1  ;
        	    volatile bit_state_t bit15 : 1  ;
        	    const uint32_t : 16 ;
                  } __attribute__ ((packed)) ;
                  struct
                  {
                    volatile data_16bit_t low_half_word ;
            	    const uint16_t placeholder ;
                  } __attribute__ ((packed)) ;

                  // read
                  inline bit_state_t bit(const volatile_data_16bit_t::bit_index_t val) const { NRO return low_half_word.uval & (1 << val)  ? high : low ; } ;
                  inline bit_state_t bit(const volatile_data_16bit_t::bit_mask_t  val) const { NRO return low_half_word.uval & val ? high : low ; } ;

                  // bit set operation
                  inline void set_bit ( volatile_data_16bit_t::bit_index_t bit_index ) { NRO low_half_word.uval |= (1 << bit_index) ; } ;
                  inline void set_bit ( volatile_data_16bit_t::bit_mask_t bit_mask )   { NRO low_half_word.uval |=  bit_mask  ; } ;
                  inline void set_bit0() { NRO low_half_word.uval |= volatile_data_16bit_t::bm0  ; } ;
                  inline void set_bit1() { NRO low_half_word.uval |= volatile_data_16bit_t::bm1  ; } ;
                  inline void set_bit2() { NRO low_half_word.uval |= volatile_data_16bit_t::bm2  ; } ;
                  inline void set_bit3() { NRO low_half_word.uval |= volatile_data_16bit_t::bm3  ; } ;
                  inline void set_bit4() { NRO low_half_word.uval |= volatile_data_16bit_t::bm4  ; } ;
                  inline void set_bit5() { NRO low_half_word.uval |= volatile_data_16bit_t::bm5  ; } ;
                  inline void set_bit6() { NRO low_half_word.uval |= volatile_data_16bit_t::bm6  ; } ;
                  inline void set_bit7() { NRO low_half_word.uval |= volatile_data_16bit_t::bm7  ; } ;
                  inline void set_bit8() { NRO low_half_word.uval |= volatile_data_16bit_t::bm8  ; } ;
                  inline void set_bit9() { NRO low_half_word.uval |= volatile_data_16bit_t::bm9  ; } ;
                  inline void set_bit10(){ NRO low_half_word.uval |= volatile_data_16bit_t::bm10 ; } ;
                  inline void set_bit11(){ NRO low_half_word.uval |= volatile_data_16bit_t::bm11 ; } ;
                  inline void set_bit12(){ NRO low_half_word.uval |= volatile_data_16bit_t::bm12 ; } ;
                  inline void set_bit13(){ NRO low_half_word.uval |= volatile_data_16bit_t::bm13 ; } ;
                  inline void set_bit14(){ NRO low_half_word.uval |= volatile_data_16bit_t::bm14 ; } ;
                  inline void set_bit15(){ NRO low_half_word.uval |= volatile_data_16bit_t::bm15 ; } ;
                  inline void set_bits(uint16_t val) { NRO low_half_word.uval |= val ; } ;
                  inline void set_bits(int16_t val)  { NRO low_half_word.uval |= val ; } ;

                  // bit clear operation
                  inline void clear_bit ( volatile_data_16bit_t::bit_index_t bit_index ) { NRO low_half_word.uval &=~ (1 << bit_index) ; } ;
                  inline void clear_bit ( volatile_data_16bit_t::bit_mask_t bit_mask )   { NRO low_half_word.uval &=~  bit_mask  ; } ;
                  inline void clear_bit0() { NRO low_half_word.uval &=~ volatile_data_16bit_t::bm0  ; } ;
                  inline void clear_bit1() { NRO low_half_word.uval &=~ volatile_data_16bit_t::bm1  ; } ;
                  inline void clear_bit2() { NRO low_half_word.uval &=~ volatile_data_16bit_t::bm2  ; } ;
                  inline void clear_bit3() { NRO low_half_word.uval &=~ volatile_data_16bit_t::bm3  ; } ;
                  inline void clear_bit4() { NRO low_half_word.uval &=~ volatile_data_16bit_t::bm4  ; } ;
                  inline void clear_bit5() { NRO low_half_word.uval &=~ volatile_data_16bit_t::bm5  ; } ;
                  inline void clear_bit6() { NRO low_half_word.uval &=~ volatile_data_16bit_t::bm6  ; } ;
                  inline void clear_bit7() { NRO low_half_word.uval &=~ volatile_data_16bit_t::bm7  ; } ;
                  inline void clear_bit8() { NRO low_half_word.uval &=~ volatile_data_16bit_t::bm8  ; } ;
                  inline void clear_bit9() { NRO low_half_word.uval &=~ volatile_data_16bit_t::bm9  ; } ;
                  inline void clear_bit10(){ NRO low_half_word.uval &=~ volatile_data_16bit_t::bm10 ; } ;
                  inline void clear_bit11(){ NRO low_half_word.uval &=~ volatile_data_16bit_t::bm11 ; } ;
                  inline void clear_bit12(){ NRO low_half_word.uval &=~ volatile_data_16bit_t::bm12 ; } ;
                  inline void clear_bit13(){ NRO low_half_word.uval &=~ volatile_data_16bit_t::bm13 ; } ;
                  inline void clear_bit14(){ NRO low_half_word.uval &=~ volatile_data_16bit_t::bm14 ; } ;
                  inline void clear_bit15(){ NRO low_half_word.uval &=~ volatile_data_16bit_t::bm15 ; } ;
                  inline void clear_bits(uint16_t val) { NRO low_half_word.uval &=~ val ; } ;
                  inline void clear_bits(int16_t val)  { NRO low_half_word.uval &=~ val ; } ;

                  inline void toggle_bit ( volatile_data_16bit_t::bit_index_t bit_index ) { NRO low_half_word.uval ^= (1 << bit_index) ; } ;
                  inline void toggle_bit ( volatile_data_16bit_t::bit_mask_t bit_mask )   { NRO low_half_word.uval ^=  bit_mask  ; } ;
                  inline void toggle_bit0()  { NRO low_half_word.uval ^= volatile_data_16bit_t::bm0 ; } ;
                  inline void toggle_bit1()  { NRO low_half_word.uval ^= volatile_data_16bit_t::bm1 ; } ;
                  inline void toggle_bit2()  { NRO low_half_word.uval ^= volatile_data_16bit_t::bm2 ; } ;
                  inline void toggle_bit3()  { NRO low_half_word.uval ^= volatile_data_16bit_t::bm3 ; } ;
                  inline void toggle_bit4()  { NRO low_half_word.uval ^= volatile_data_16bit_t::bm4 ; } ;
                  inline void toggle_bit5()  { NRO low_half_word.uval ^= volatile_data_16bit_t::bm5 ; } ;
                  inline void toggle_bit6()  { NRO low_half_word.uval ^= volatile_data_16bit_t::bm6 ; } ;
                  inline void toggle_bit7()  { NRO low_half_word.uval ^= volatile_data_16bit_t::bm7 ; } ;
                  inline void toggle_bit8()  { NRO low_half_word.uval ^= volatile_data_16bit_t::bm8 ; } ;
                  inline void toggle_bit9()  { NRO low_half_word.uval ^= volatile_data_16bit_t::bm9 ; } ;
                  inline void toggle_bit10() { NRO low_half_word.uval ^= volatile_data_16bit_t::bm10 ; } ;
                  inline void toggle_bit11() { NRO low_half_word.uval ^= volatile_data_16bit_t::bm11 ; } ;
                  inline void toggle_bit12() { NRO low_half_word.uval ^= volatile_data_16bit_t::bm12 ; } ;
                  inline void toggle_bit13() { NRO low_half_word.uval ^= volatile_data_16bit_t::bm13 ; } ;
                  inline void toggle_bit14() { NRO low_half_word.uval ^= volatile_data_16bit_t::bm14 ; } ;
                  inline void toggle_bit15() { NRO low_half_word.uval ^= volatile_data_16bit_t::bm15 ; } ;
                  inline void toggle_bits(uint16_t val) { NRO low_half_word.uval ^= val ; } ;
                  inline void toggle_bits(int16_t  val) { NRO low_half_word.uval ^= val ; } ;

                  inline void write(uint16_t val) { NRO low_half_word.uval = val ; }
                  inline void write(int16_t val)  { NRO low_half_word.uval = val ; }

                  inline uint16_t  read() { NRO return low_half_word.uval ; }


                } __attribute__ ((packed));




union data_64bit_t
  {  enum bit_state_t    { low=0, high }  ;
     enum bit_index_t { bi0=0,bi1,  bi2,  bi3,  bi4,  bi5,  bi6,  bi7,  bi8,  bi9,  bi10, bi11, bi12, bi13, bi14, bi15,
                     bi16, bi17, bi18, bi19, bi20, bi21, bi22, bi23, bi24, bi25, bi26, bi27, bi28, bi29, bi30, bi31,
		     bi32, bi33, bi34, bi35, bi36, bi37, bi38, bi39, bi40, bi41, bi42, bi43, bi44, bi45, bi46, bi47,
		     bi48, bi49, bi50, bi51, bi52, bi53, bi54, bi55, bi56, bi57, bi58, bi59, bi60, bi61, bi62, bi63,
		     bi_count }  ;

		            enum bit_mask_t :  uint64_t { bm0= 1ull << bi0,  bm1= 1ull << bi1,  bm2= 1ull << bi2,  bm3= 1ull << bi3,  bm4= 1ull << bi4,  bm5= 1ull << bi5,  bm6= 1ull << bi6,  bm7= 1ull << bi7,
		                  		       bm8= 1ull << bi8,  bm9= 1ull << bi9,  bm10=1ull << bi10, bm11=1ull << bi11, bm12=1ull << bi12, bm13=1ull << bi13, bm14=1ull << bi14, bm15=1ull << bi15,
		                  		       bm16=1ull << bi16, bm17=1ull << bi17, bm18=1ull << bi18, bm19=1ull << bi19, bm20=1ull << bi20, bm21=1ull << bi21, bm22=1ull << bi22, bm23=1ull << bi23,
		                  		       bm24=1ull << bi24, bm25=1ull << bi25, bm26=1ull << bi26, bm27=1ull << bi27, bm28=1ull << bi28, bm29=1ull << bi29, bm30=1ull << bi30, bm31=1ull << bi31,
		  				       bm32=1ull << bi32, bm33=1ull << bi33, bm34=1ull << bi34, bm35=1ull << bi35, bm36=1ull << bi36, bm37=1ull << bi37, bm38=1ull << bi38, bm39=1ull << bi39,
		  				       bm40=1ull << bi40, bm41=1ull << bi41, bm42=1ull << bi42, bm43=1ull << bi43, bm44=1ull << bi44, bm45=1ull << bi45, bm46=1ull << bi46, bm47=1ull << bi47,
		  				       bm48=1ull << bi48, bm49=1ull << bi49, bm50=1ull << bi50, bm51=1ull << bi51, bm52=1ull << bi52, bm53=1ull << bi53, bm54=1ull << bi54, bm55=1ull << bi55,
		  				       bm56=1ull << bi56, bm57=1ull << bi57, bm58=1ull << bi58, bm59=1ull << bi59, bm60=1ull << bi60, bm61=1ull << bi61, bm62=1ull << bi62, bm63=1ull << bi63,
		                                   }  ;
                      struct
                      {
                	bit_state_t bit0  : 1  ;
                	bit_state_t bit1  : 1  ;
                	bit_state_t bit2  : 1  ;
                	bit_state_t bit3  : 1  ;
                	bit_state_t bit4  : 1  ;
                	bit_state_t bit5  : 1  ;
                	bit_state_t bit6  : 1  ;
                	bit_state_t bit7  : 1  ;
                	bit_state_t bit8  : 1  ;
                	bit_state_t bit9  : 1  ;
                	bit_state_t bit10 : 1  ;
                	bit_state_t bit11 : 1  ;
                	bit_state_t bit12 : 1  ;
                	bit_state_t bit13 : 1  ;
                	bit_state_t bit14 : 1  ;
                	bit_state_t bit15 : 1  ;
                	bit_state_t bit16 : 1  ;
                	bit_state_t bit17 : 1  ;
                	bit_state_t bit18 : 1  ;
                	bit_state_t bit19 : 1  ;
                	bit_state_t bit20 : 1  ;
                	bit_state_t bit21 : 1  ;
                	bit_state_t bit22 : 1  ;
                	bit_state_t bit23 : 1  ;
                	bit_state_t bit24 : 1  ;
                	bit_state_t bit25 : 1  ;
                	bit_state_t bit26 : 1  ;
                	bit_state_t bit27 : 1  ;
                	bit_state_t bit28 : 1  ;
                	bit_state_t bit29 : 1  ;
                	bit_state_t bit30 : 1  ;
                	bit_state_t bit31 : 1  ;
                	bit_state_t bit32 : 1  ;
                	bit_state_t bit33 : 1  ;
                	bit_state_t bit34 : 1  ;
                	bit_state_t bit35 : 1  ;
                	bit_state_t bit36 : 1  ;
                	bit_state_t bit37 : 1  ;
                	bit_state_t bit38 : 1  ;
                	bit_state_t bit39 : 1  ;
                	bit_state_t bit40 : 1  ;
                	bit_state_t bit41 : 1  ;
                	bit_state_t bit42 : 1  ;
                	bit_state_t bit43 : 1  ;
                	bit_state_t bit44 : 1  ;
                	bit_state_t bit45 : 1  ;
                	bit_state_t bit46 : 1  ;
                	bit_state_t bit47 : 1  ;
                	bit_state_t bit48 : 1  ;
                	bit_state_t bit49 : 1  ;
                	bit_state_t bit50 : 1  ;
                	bit_state_t bit51 : 1  ;
                	bit_state_t bit52 : 1  ;
                	bit_state_t bit53 : 1  ;
                	bit_state_t bit54 : 1  ;
                	bit_state_t bit55 : 1  ;
                	bit_state_t bit56 : 1  ;
                	bit_state_t bit57 : 1  ;
                	bit_state_t bit58 : 1  ;
                	bit_state_t bit59 : 1  ;
                	bit_state_t bit60 : 1  ;
                	bit_state_t bit61 : 1  ;
                	bit_state_t bit62 : 1  ;
                	bit_state_t bit63 : 1  ;

                      } __reg_attr__ ;
                      struct
                      {
                	data_32bit_t low_word ;
                	data_32bit_t high_word ;
                      } __reg_attr__ ;
                      uint64_t uval ;
                      int64_t  sval ;
                      double   fval ;

                      // bit set operation
                      inline void set_bit ( bit_index_t bit_index ) { uval |= (1 << bit_index) ; } ;
                      inline void set_bit ( bit_mask_t bit_mask )   { uval |=  bit_mask  ; } ;
                      inline void set_bit0() { uval |= bm0  ; } ;
                      inline void set_bit1() { uval |= bm1  ; } ;
                      inline void set_bit2() { uval |= bm2  ; } ;
                      inline void set_bit3() { uval |= bm3  ; } ;
                      inline void set_bit4() { uval |= bm4  ; } ;
                      inline void set_bit5() { uval |= bm5  ; } ;
                      inline void set_bit6() { uval |= bm6  ; } ;
                      inline void set_bit7() { uval |= bm7  ; } ;
                      inline void set_bit8() { uval |= bm8  ; } ;
                      inline void set_bit9() { uval |= bm9  ; } ;
                      inline void set_bit10(){ uval |= bm10 ; } ;
                      inline void set_bit11(){ uval |= bm11 ; } ;
                      inline void set_bit12(){ uval |= bm12 ; } ;
                      inline void set_bit13(){ uval |= bm13 ; } ;
                      inline void set_bit14(){ uval |= bm14 ; } ;
                      inline void set_bit15(){ uval |= bm15 ; } ;
                      inline void set_bit16(){ uval |= bm16 ; } ;
                      inline void set_bit17(){ uval |= bm17 ; } ;
                      inline void set_bit18(){ uval |= bm18 ; } ;
                      inline void set_bit19(){ uval |= bm19 ; } ;
                      inline void set_bit20(){ uval |= bm20 ; } ;
                      inline void set_bit21(){ uval |= bm21 ; } ;
                      inline void set_bit22(){ uval |= bm22 ; } ;
                      inline void set_bit23(){ uval |= bm23 ; } ;
                      inline void set_bit24(){ uval |= bm24 ; } ;
                      inline void set_bit25(){ uval |= bm25 ; } ;
                      inline void set_bit26(){ uval |= bm26 ; } ;
                      inline void set_bit27(){ uval |= bm27 ; } ;
                      inline void set_bit28(){ uval |= bm28 ; } ;
                      inline void set_bit29(){ uval |= bm29 ; } ;
                      inline void set_bit30(){ uval |= bm30 ; } ;
                      inline void set_bit31(){ uval |= bm31 ; } ;
                      inline void set_bit32(){ uval |= bm32 ; } ;
                      inline void set_bit33(){ uval |= bm33 ; } ;
                      inline void set_bit34(){ uval |= bm34 ; } ;
                      inline void set_bit35(){ uval |= bm35 ; } ;
                      inline void set_bit36(){ uval |= bm36 ; } ;
                      inline void set_bit37(){ uval |= bm37 ; } ;
                      inline void set_bit38(){ uval |= bm38 ; } ;
                      inline void set_bit39(){ uval |= bm39 ; } ;
                      inline void set_bit40(){ uval |= bm40 ; } ;
                      inline void set_bit41(){ uval |= bm41 ; } ;
                      inline void set_bit42(){ uval |= bm42 ; } ;
                      inline void set_bit43(){ uval |= bm43 ; } ;
                      inline void set_bit44(){ uval |= bm44 ; } ;
                      inline void set_bit45(){ uval |= bm45 ; } ;
                      inline void set_bit46(){ uval |= bm46 ; } ;
                      inline void set_bit47(){ uval |= bm47 ; } ;
                      inline void set_bit48(){ uval |= bm48 ; } ;
                      inline void set_bit49(){ uval |= bm49 ; } ;
                      inline void set_bit50(){ uval |= bm50 ; } ;
                      inline void set_bit51(){ uval |= bm51 ; } ;
                      inline void set_bit52(){ uval |= bm52 ; } ;
                      inline void set_bit53(){ uval |= bm53 ; } ;
                      inline void set_bit54(){ uval |= bm54 ; } ;
                      inline void set_bit55(){ uval |= bm55 ; } ;
                      inline void set_bit56(){ uval |= bm56 ; } ;
                      inline void set_bit57(){ uval |= bm57 ; } ;
                      inline void set_bit58(){ uval |= bm58 ; } ;
                      inline void set_bit59(){ uval |= bm59 ; } ;
                      inline void set_bit60(){ uval |= bm60 ; } ;
                      inline void set_bit61(){ uval |= bm61 ; } ;
                      inline void set_bit62(){ uval |= bm62 ; } ;
                      inline void set_bit63(){ uval |= bm63 ; } ;

                      inline void set_bits(uint64_t val) { uval |= val ; } ;
                      inline void set_bits(int64_t val)  { uval |= val ; } ;

                      // bit clear operation
                      inline void clear_bit ( bit_index_t bit_index ) { uval &=~ (1 << bit_index) ; } ;
                      inline void clear_bit ( bit_mask_t bit_mask )   { uval &=~  bit_mask  ; } ;
                      inline void clear_bit0() { uval &=~ bm0  ; } ;
                      inline void clear_bit1() { uval &=~ bm1  ; } ;
                      inline void clear_bit2() { uval &=~ bm2  ; } ;
                      inline void clear_bit3() { uval &=~ bm3  ; } ;
                      inline void clear_bit4() { uval &=~ bm4  ; } ;
                      inline void clear_bit5() { uval &=~ bm5  ; } ;
                      inline void clear_bit6() { uval &=~ bm6  ; } ;
                      inline void clear_bit7() { uval &=~ bm7  ; } ;
                      inline void clear_bit8() { uval &=~ bm8  ; } ;
                      inline void clear_bit9() { uval &=~ bm9  ; } ;
                      inline void clear_bit10(){ uval &=~ bm10 ; } ;
                      inline void clear_bit11(){ uval &=~ bm11 ; } ;
                      inline void clear_bit12(){ uval &=~ bm12 ; } ;
                      inline void clear_bit13(){ uval &=~ bm13 ; } ;
                      inline void clear_bit14(){ uval &=~ bm14 ; } ;
                      inline void clear_bit15(){ uval &=~ bm15 ; } ;
                      inline void clear_bit16(){ uval &=~ bm16 ; } ;
                      inline void clear_bit17(){ uval &=~ bm17 ; } ;
                      inline void clear_bit18(){ uval &=~ bm18 ; } ;
                      inline void clear_bit19(){ uval &=~ bm19 ; } ;
                      inline void clear_bit20(){ uval &=~ bm20 ; } ;
                      inline void clear_bit21(){ uval &=~ bm21 ; } ;
                      inline void clear_bit22(){ uval &=~ bm22 ; } ;
                      inline void clear_bit23(){ uval &=~ bm23 ; } ;
                      inline void clear_bit24(){ uval &=~ bm24 ; } ;
                      inline void clear_bit25(){ uval &=~ bm25 ; } ;
                      inline void clear_bit26(){ uval &=~ bm26 ; } ;
                      inline void clear_bit27(){ uval &=~ bm27 ; } ;
                      inline void clear_bit28(){ uval &=~ bm28 ; } ;
                      inline void clear_bit29(){ uval &=~ bm29 ; } ;
                      inline void clear_bit30(){ uval &=~ bm30 ; } ;
                      inline void clear_bit31(){ uval &=~ bm31 ; } ;
                      inline void clear_bit32(){ uval &=~ bm32 ; } ;
                      inline void clear_bit33(){ uval &=~ bm33 ; } ;
                      inline void clear_bit34(){ uval &=~ bm34 ; } ;
                      inline void clear_bit35(){ uval &=~ bm35 ; } ;
                      inline void clear_bit36(){ uval &=~ bm36 ; } ;
                      inline void clear_bit37(){ uval &=~ bm37 ; } ;
                      inline void clear_bit38(){ uval &=~ bm38 ; } ;
                      inline void clear_bit39(){ uval &=~ bm39 ; } ;
                      inline void clear_bit40(){ uval &=~ bm40 ; } ;
                      inline void clear_bit41(){ uval &=~ bm41 ; } ;
                      inline void clear_bit42(){ uval &=~ bm42 ; } ;
                      inline void clear_bit43(){ uval &=~ bm43 ; } ;
                      inline void clear_bit44(){ uval &=~ bm44 ; } ;
                      inline void clear_bit45(){ uval &=~ bm45 ; } ;
                      inline void clear_bit46(){ uval &=~ bm46 ; } ;
                      inline void clear_bit47(){ uval &=~ bm47 ; } ;
                      inline void clear_bit48(){ uval &=~ bm48 ; } ;
                      inline void clear_bit49(){ uval &=~ bm49 ; } ;
                      inline void clear_bit50(){ uval &=~ bm50 ; } ;
                      inline void clear_bit51(){ uval &=~ bm51 ; } ;
                      inline void clear_bit52(){ uval &=~ bm52 ; } ;
                      inline void clear_bit53(){ uval &=~ bm53 ; } ;
                      inline void clear_bit54(){ uval &=~ bm54 ; } ;
                      inline void clear_bit55(){ uval &=~ bm55 ; } ;
                      inline void clear_bit56(){ uval &=~ bm56 ; } ;
                      inline void clear_bit57(){ uval &=~ bm57 ; } ;
                      inline void clear_bit58(){ uval &=~ bm58 ; } ;
                      inline void clear_bit59(){ uval &=~ bm59 ; } ;
                      inline void clear_bit60(){ uval &=~ bm60 ; } ;
                      inline void clear_bit61(){ uval &=~ bm61 ; } ;
                      inline void clear_bit62(){ uval &=~ bm62 ; } ;
                      inline void clear_bit63(){ uval &=~ bm63 ; } ;
                      inline void clear_bits(uint64_t val) { uval &=~ val ; } ;
                      inline void clear_bits(int64_t val)  { uval &=~ val ; } ;

                      inline void toggle_bit ( bit_index_t bit_index ) { uval ^= (1 << bit_index) ; } ;
                      inline void toggle_bit ( bit_mask_t bit_mask )   { uval ^=  bit_mask  ; } ;
                      inline void toggle_bit0()  { uval ^= bm0 ; } ;
                      inline void toggle_bit1()  { uval ^= bm1 ; } ;
                      inline void toggle_bit2()  { uval ^= bm2 ; } ;
                      inline void toggle_bit3()  { uval ^= bm3 ; } ;
                      inline void toggle_bit4()  { uval ^= bm4 ; } ;
                      inline void toggle_bit5()  { uval ^= bm5 ; } ;
                      inline void toggle_bit6()  { uval ^= bm6 ; } ;
                      inline void toggle_bit7()  { uval ^= bm7 ; } ;
                      inline void toggle_bit8()  { uval ^= bm8 ; } ;
                      inline void toggle_bit9()  { uval ^= bm9 ; } ;
                      inline void toggle_bit10() { uval ^= bm10 ; } ;
                      inline void toggle_bit11() { uval ^= bm11 ; } ;
                      inline void toggle_bit12() { uval ^= bm12 ; } ;
                      inline void toggle_bit13() { uval ^= bm13 ; } ;
                      inline void toggle_bit14() { uval ^= bm14 ; } ;
                      inline void toggle_bit15() { uval ^= bm15 ; } ;
                      inline void toggle_bit16() { uval ^= bm16 ; } ;
                      inline void toggle_bit17() { uval ^= bm17 ; } ;
                      inline void toggle_bit18() { uval ^= bm18 ; } ;
                      inline void toggle_bit19() { uval ^= bm19 ; } ;
                      inline void toggle_bit20() { uval ^= bm20 ; } ;
                      inline void toggle_bit21() { uval ^= bm21 ; } ;
                      inline void toggle_bit22() { uval ^= bm22 ; } ;
                      inline void toggle_bit23() { uval ^= bm23 ; } ;
                      inline void toggle_bit24() { uval ^= bm24 ; } ;
                      inline void toggle_bit25() { uval ^= bm25 ; } ;
                      inline void toggle_bit26() { uval ^= bm26 ; } ;
                      inline void toggle_bit27() { uval ^= bm27 ; } ;
                      inline void toggle_bit28() { uval ^= bm28 ; } ;
                      inline void toggle_bit29() { uval ^= bm29 ; } ;
                      inline void toggle_bit30() { uval ^= bm30 ; } ;
                      inline void toggle_bit31() { uval ^= bm31 ; } ;
                      inline void toggle_bit32() { uval ^= bm32 ; } ;
                      inline void toggle_bit33() { uval ^= bm33 ; } ;
                      inline void toggle_bit34() { uval ^= bm34 ; } ;
                      inline void toggle_bit35() { uval ^= bm35 ; } ;
                      inline void toggle_bit36() { uval ^= bm36 ; } ;
                      inline void toggle_bit37() { uval ^= bm37 ; } ;
                      inline void toggle_bit38() { uval ^= bm38 ; } ;
                      inline void toggle_bit39() { uval ^= bm39 ; } ;
                      inline void toggle_bit40() { uval ^= bm40 ; } ;
                      inline void toggle_bit41() { uval ^= bm41 ; } ;
                      inline void toggle_bit42() { uval ^= bm42 ; } ;
                      inline void toggle_bit43() { uval ^= bm43 ; } ;
                      inline void toggle_bit44() { uval ^= bm44 ; } ;
                      inline void toggle_bit45() { uval ^= bm45 ; } ;
                      inline void toggle_bit46() { uval ^= bm46 ; } ;
                      inline void toggle_bit47() { uval ^= bm47 ; } ;
                      inline void toggle_bit48() { uval ^= bm48 ; } ;
                      inline void toggle_bit49() { uval ^= bm49 ; } ;
                      inline void toggle_bit50() { uval ^= bm50 ; } ;
                      inline void toggle_bit51() { uval ^= bm51 ; } ;
                      inline void toggle_bit52() { uval ^= bm52 ; } ;
                      inline void toggle_bit53() { uval ^= bm53 ; } ;
                      inline void toggle_bit54() { uval ^= bm54 ; } ;
                      inline void toggle_bit55() { uval ^= bm55 ; } ;
                      inline void toggle_bit56() { uval ^= bm56 ; } ;
                      inline void toggle_bit57() { uval ^= bm57 ; } ;
                      inline void toggle_bit58() { uval ^= bm58 ; } ;
                      inline void toggle_bit59() { uval ^= bm59 ; } ;
                      inline void toggle_bit60() { uval ^= bm60 ; } ;
                      inline void toggle_bit61() { uval ^= bm61 ; } ;
                      inline void toggle_bit62() { uval ^= bm62 ; } ;
                      inline void toggle_bit63() { uval ^= bm63 ; } ;
                      inline void toggle_bits(uint64_t val) { uval ^= val ; } ;
                      inline void toggle_bits(int64_t  val) { sval ^= val ; } ;

                      inline static data_64bit_t& from(const int64_t& val) {return *((data_64bit_t*)(&val)) ; }
                      inline static data_64bit_t& from(const uint64_t& val) {return *((data_64bit_t*)(&val)) ; }



  } __reg_attr__ ;

union volatile_data_64bit_t
    {
       enum bit_state_t    { low=0, high }  ;
       enum bit_index_t { bi0=0,bi1,  bi2,  bi3,  bi4,  bi5,  bi6,  bi7,  bi8,  bi9,  bi10, bi11, bi12, bi13, bi14, bi15,
                          bi16, bi17, bi18, bi19, bi20, bi21, bi22, bi23, bi24, bi25, bi26, bi27, bi28, bi29, bi30, bi31,
  		          bi32, bi33, bi34, bi35, bi36, bi37, bi38, bi39, bi40, bi41, bi42, bi43, bi44, bi45, bi46, bi47,
  		          bi48, bi49, bi50, bi51, bi52, bi53, bi54, bi55, bi56, bi57, bi58, bi59, bi60, bi61, bi62, bi63,
  		          bi_count }  ;


            enum bit_mask_t :  uint64_t { bm0= 1ull << bi0,  bm1= 1ull << bi1,  bm2= 1ull << bi2,  bm3= 1ull << bi3,  bm4= 1ull << bi4,  bm5= 1ull << bi5,  bm6= 1ull << bi6,  bm7= 1ull << bi7,
                  		       bm8= 1ull << bi8,  bm9= 1ull << bi9,  bm10=1ull << bi10, bm11=1ull << bi11, bm12=1ull << bi12, bm13=1ull << bi13, bm14=1ull << bi14, bm15=1ull << bi15,
                  		       bm16=1ull << bi16, bm17=1ull << bi17, bm18=1ull << bi18, bm19=1ull << bi19, bm20=1ull << bi20, bm21=1ull << bi21, bm22=1ull << bi22, bm23=1ull << bi23,
                  		       bm24=1ull << bi24, bm25=1ull << bi25, bm26=1ull << bi26, bm27=1ull << bi27, bm28=1ull << bi28, bm29=1ull << bi29, bm30=1ull << bi30, bm31=1ull << bi31,
  				       bm32=1ull << bi32, bm33=1ull << bi33, bm34=1ull << bi34, bm35=1ull << bi35, bm36=1ull << bi36, bm37=1ull << bi37, bm38=1ull << bi38, bm39=1ull << bi39,
  				       bm40=1ull << bi40, bm41=1ull << bi41, bm42=1ull << bi42, bm43=1ull << bi43, bm44=1ull << bi44, bm45=1ull << bi45, bm46=1ull << bi46, bm47=1ull << bi47,
  				       bm48=1ull << bi48, bm49=1ull << bi49, bm50=1ull << bi50, bm51=1ull << bi51, bm52=1ull << bi52, bm53=1ull << bi53, bm54=1ull << bi54, bm55=1ull << bi55,
  				       bm56=1ull << bi56, bm57=1ull << bi57, bm58=1ull << bi58, bm59=1ull << bi59, bm60=1ull << bi60, bm61=1ull << bi61, bm62=1ull << bi62, bm63=1ull << bi63,
                                   }  ;

                        struct
                        {
                        volatile bit_state_t bit0  : 1  ;
                        volatile bit_state_t bit1  : 1  ;
                        volatile bit_state_t bit2  : 1  ;
                        volatile bit_state_t bit3  : 1  ;
                  	volatile bit_state_t bit4  : 1  ;
                  	volatile bit_state_t bit5  : 1  ;
                  	volatile bit_state_t bit6  : 1  ;
                  	volatile bit_state_t bit7  : 1  ;
                  	volatile bit_state_t bit8  : 1  ;
                  	volatile bit_state_t bit9  : 1  ;
                  	volatile bit_state_t bit10 : 1  ;
                  	volatile bit_state_t bit11 : 1  ;
                  	volatile bit_state_t bit12 : 1  ;
                  	volatile bit_state_t bit13 : 1  ;
                  	volatile bit_state_t bit14 : 1  ;
                  	volatile bit_state_t bit15 : 1  ;
                  	volatile bit_state_t bit16 : 1  ;
                  	volatile bit_state_t bit17 : 1  ;
                  	volatile bit_state_t bit18 : 1  ;
                  	volatile bit_state_t bit19 : 1  ;
                  	volatile bit_state_t bit20 : 1  ;
                  	volatile bit_state_t bit21 : 1  ;
                  	volatile bit_state_t bit22 : 1  ;
                  	volatile bit_state_t bit23 : 1  ;
                  	volatile bit_state_t bit24 : 1  ;
                  	volatile bit_state_t bit25 : 1  ;
                  	volatile bit_state_t bit26 : 1  ;
                  	volatile bit_state_t bit27 : 1  ;
                  	volatile bit_state_t bit28 : 1  ;
                  	volatile bit_state_t bit29 : 1  ;
                  	volatile bit_state_t bit30 : 1  ;
                  	volatile bit_state_t bit31 : 1  ;
                  	volatile bit_state_t bit32 : 1  ;
                  	volatile bit_state_t bit33 : 1  ;
                  	volatile bit_state_t bit34 : 1  ;
                  	volatile bit_state_t bit35 : 1  ;
                  	volatile bit_state_t bit36 : 1  ;
                  	volatile bit_state_t bit37 : 1  ;
                  	volatile bit_state_t bit38 : 1  ;
                  	volatile bit_state_t bit39 : 1  ;
                  	volatile bit_state_t bit40 : 1  ;
                  	volatile bit_state_t bit41 : 1  ;
                  	volatile bit_state_t bit42 : 1  ;
                  	volatile bit_state_t bit43 : 1  ;
                  	volatile bit_state_t bit44 : 1  ;
                  	volatile bit_state_t bit45 : 1  ;
                  	volatile bit_state_t bit46 : 1  ;
                  	volatile bit_state_t bit47 : 1  ;
                  	volatile bit_state_t bit48 : 1  ;
                  	volatile bit_state_t bit49 : 1  ;
                  	volatile bit_state_t bit50 : 1  ;
                  	volatile bit_state_t bit51 : 1  ;
                  	volatile bit_state_t bit52 : 1  ;
                  	volatile bit_state_t bit53 : 1  ;
                  	volatile bit_state_t bit54 : 1  ;
                  	volatile bit_state_t bit55 : 1  ;
                  	volatile bit_state_t bit56 : 1  ;
                  	volatile bit_state_t bit57 : 1  ;
                  	volatile bit_state_t bit58 : 1  ;
                  	volatile bit_state_t bit59 : 1  ;
                  	volatile bit_state_t bit60 : 1  ;
                  	volatile bit_state_t bit61 : 1  ;
                  	volatile bit_state_t bit62 : 1  ;
                  	volatile bit_state_t bit63 : 1  ;

                        } __reg_attr__ ;
                        struct
                        {
                  	  volatile data_32bit_t low_word ;
                  	  volatile data_32bit_t high_word ;
                        } __reg_attr__ ;
                        volatile uint64_t uval ;
                        volatile int64_t  sval ;
                        volatile double   fval ;

                        // bit set operation
                        inline void set_bit ( bit_index_t bit_index ) { NRO uval |= (1 << bit_index) ; } ;
                        inline void set_bit ( bit_mask_t bit_mask )   { uval |=  bit_mask  ; } ;
                        inline void set_bit0() { NRO uval |= bm0  ; } ;
                        inline void set_bit1() { NRO uval |= bm1  ; } ;
                        inline void set_bit2() { NRO uval |= bm2  ; } ;
                        inline void set_bit3() { NRO uval |= bm3  ; } ;
                        inline void set_bit4() { NRO uval |= bm4  ; } ;
                        inline void set_bit5() { NRO uval |= bm5  ; } ;
                        inline void set_bit6() { NRO uval |= bm6  ; } ;
                        inline void set_bit7() { NRO uval |= bm7  ; } ;
                        inline void set_bit8() { NRO uval |= bm8  ; } ;
                        inline void set_bit9() { NRO uval |= bm9  ; } ;
                        inline void set_bit10(){ NRO uval |= bm10 ; } ;
                        inline void set_bit11(){ NRO uval |= bm11 ; } ;
                        inline void set_bit12(){ NRO uval |= bm12 ; } ;
                        inline void set_bit13(){ NRO uval |= bm13 ; } ;
                        inline void set_bit14(){ NRO uval |= bm14 ; } ;
                        inline void set_bit15(){ NRO uval |= bm15 ; } ;
                        inline void set_bit16(){ NRO uval |= bm16 ; } ;
                        inline void set_bit17(){ NRO uval |= bm17 ; } ;
                        inline void set_bit18(){ NRO uval |= bm18 ; } ;
                        inline void set_bit19(){ NRO uval |= bm19 ; } ;
                        inline void set_bit20(){ NRO uval |= bm20 ; } ;
                        inline void set_bit21(){ NRO uval |= bm21 ; } ;
                        inline void set_bit22(){ NRO uval |= bm22 ; } ;
                        inline void set_bit23(){ NRO uval |= bm23 ; } ;
                        inline void set_bit24(){ NRO uval |= bm24 ; } ;
                        inline void set_bit25(){ NRO uval |= bm25 ; } ;
                        inline void set_bit26(){ NRO uval |= bm26 ; } ;
                        inline void set_bit27(){ NRO uval |= bm27 ; } ;
                        inline void set_bit28(){ NRO uval |= bm28 ; } ;
                        inline void set_bit29(){ NRO uval |= bm29 ; } ;
                        inline void set_bit30(){ NRO uval |= bm30 ; } ;
                        inline void set_bit31(){ NRO uval |= bm31 ; } ;
                        inline void set_bit32(){ NRO uval |= bm32 ; } ;
                        inline void set_bit33(){ NRO uval |= bm33 ; } ;
                        inline void set_bit34(){ NRO uval |= bm34 ; } ;
                        inline void set_bit35(){ NRO uval |= bm35 ; } ;
                        inline void set_bit36(){ NRO uval |= bm36 ; } ;
                        inline void set_bit37(){ NRO uval |= bm37 ; } ;
                        inline void set_bit38(){ NRO uval |= bm38 ; } ;
                        inline void set_bit39(){ NRO uval |= bm39 ; } ;
                        inline void set_bit40(){ NRO uval |= bm40 ; } ;
                        inline void set_bit41(){ NRO uval |= bm41 ; } ;
                        inline void set_bit42(){ NRO uval |= bm42 ; } ;
                        inline void set_bit43(){ NRO uval |= bm43 ; } ;
                        inline void set_bit44(){ NRO uval |= bm44 ; } ;
                        inline void set_bit45(){ NRO uval |= bm45 ; } ;
                        inline void set_bit46(){ NRO uval |= bm46 ; } ;
                        inline void set_bit47(){ NRO uval |= bm47 ; } ;
                        inline void set_bit48(){ NRO uval |= bm48 ; } ;
                        inline void set_bit49(){ NRO uval |= bm49 ; } ;
                        inline void set_bit50(){ NRO uval |= bm50 ; } ;
                        inline void set_bit51(){ NRO uval |= bm51 ; } ;
                        inline void set_bit52(){ NRO uval |= bm52 ; } ;
                        inline void set_bit53(){ NRO uval |= bm53 ; } ;
                        inline void set_bit54(){ NRO uval |= bm54 ; } ;
                        inline void set_bit55(){ NRO uval |= bm55 ; } ;
                        inline void set_bit56(){ NRO uval |= bm56 ; } ;
                        inline void set_bit57(){ NRO uval |= bm57 ; } ;
                        inline void set_bit58(){ NRO uval |= bm58 ; } ;
                        inline void set_bit59(){ NRO uval |= bm59 ; } ;
                        inline void set_bit60(){ NRO uval |= bm60 ; } ;
                        inline void set_bit61(){ NRO uval |= bm61 ; } ;
                        inline void set_bit62(){ NRO uval |= bm62 ; } ;
                        inline void set_bit63(){ NRO uval |= bm63 ; } ;
                        inline void set_bits(uint64_t val) { NRO uval |= val ; } ;
                        inline void set_bits(int64_t val)  { NRO uval |= val ; } ;

                        // bit clear operation
                        inline void clear_bit ( bit_index_t bit_index ) { NRO uval &=~ (1 << bit_index) ; } ;
                        inline void clear_bit ( bit_mask_t bit_mask )   { NRO uval &=~  bit_mask  ; } ;
                        inline void clear_bit0() { NRO uval &=~ bm0  ; } ;
                        inline void clear_bit1() { NRO uval &=~ bm1  ; } ;
                        inline void clear_bit2() { NRO uval &=~ bm2  ; } ;
                        inline void clear_bit3() { NRO uval &=~ bm3  ; } ;
                        inline void clear_bit4() { NRO uval &=~ bm4  ; } ;
                        inline void clear_bit5() { NRO uval &=~ bm5  ; } ;
                        inline void clear_bit6() { NRO uval &=~ bm6  ; } ;
                        inline void clear_bit7() { NRO uval &=~ bm7  ; } ;
                        inline void clear_bit8() { NRO uval &=~ bm8  ; } ;
                        inline void clear_bit9() { NRO uval &=~ bm9  ; } ;
                        inline void clear_bit10(){ NRO uval &=~ bm10 ; } ;
                        inline void clear_bit11(){ NRO uval &=~ bm11 ; } ;
                        inline void clear_bit12(){ NRO uval &=~ bm12 ; } ;
                        inline void clear_bit13(){ NRO uval &=~ bm13 ; } ;
                        inline void clear_bit14(){ NRO uval &=~ bm14 ; } ;
                        inline void clear_bit15(){ NRO uval &=~ bm15 ; } ;
                        inline void clear_bit16(){ NRO uval &=~ bm16 ; } ;
                        inline void clear_bit17(){ NRO uval &=~ bm17 ; } ;
                        inline void clear_bit18(){ NRO uval &=~ bm18 ; } ;
                        inline void clear_bit19(){ NRO uval &=~ bm19 ; } ;
                        inline void clear_bit20(){ NRO uval &=~ bm20 ; } ;
                        inline void clear_bit21(){ NRO uval &=~ bm21 ; } ;
                        inline void clear_bit22(){ NRO uval &=~ bm22 ; } ;
                        inline void clear_bit23(){ NRO uval &=~ bm23 ; } ;
                        inline void clear_bit24(){ NRO uval &=~ bm24 ; } ;
                        inline void clear_bit25(){ NRO uval &=~ bm25 ; } ;
                        inline void clear_bit26(){ NRO uval &=~ bm26 ; } ;
                        inline void clear_bit27(){ NRO uval &=~ bm27 ; } ;
                        inline void clear_bit28(){ NRO uval &=~ bm28 ; } ;
                        inline void clear_bit29(){ NRO uval &=~ bm29 ; } ;
                        inline void clear_bit30(){ NRO uval &=~ bm30 ; } ;
                        inline void clear_bit31(){ NRO uval &=~ bm31 ; } ;
                        inline void clear_bit32(){ NRO uval &=~ bm32 ; } ;
                        inline void clear_bit33(){ NRO uval &=~ bm33 ; } ;
                        inline void clear_bit34(){ NRO uval &=~ bm34 ; } ;
                        inline void clear_bit35(){ NRO uval &=~ bm35 ; } ;
                        inline void clear_bit36(){ NRO uval &=~ bm36 ; } ;
                        inline void clear_bit37(){ NRO uval &=~ bm37 ; } ;
                        inline void clear_bit38(){ NRO uval &=~ bm38 ; } ;
                        inline void clear_bit39(){ NRO uval &=~ bm39 ; } ;
                        inline void clear_bit40(){ NRO uval &=~ bm40 ; } ;
                        inline void clear_bit41(){ NRO uval &=~ bm41 ; } ;
                        inline void clear_bit42(){ NRO uval &=~ bm42 ; } ;
                        inline void clear_bit43(){ NRO uval &=~ bm43 ; } ;
                        inline void clear_bit44(){ NRO uval &=~ bm44 ; } ;
                        inline void clear_bit45(){ NRO uval &=~ bm45 ; } ;
                        inline void clear_bit46(){ NRO uval &=~ bm46 ; } ;
                        inline void clear_bit47(){ NRO uval &=~ bm47 ; } ;
                        inline void clear_bit48(){ NRO uval &=~ bm48 ; } ;
                        inline void clear_bit49(){ NRO uval &=~ bm49 ; } ;
                        inline void clear_bit50(){ NRO uval &=~ bm50 ; } ;
                        inline void clear_bit51(){ NRO uval &=~ bm51 ; } ;
                        inline void clear_bit52(){ NRO uval &=~ bm52 ; } ;
                        inline void clear_bit53(){ NRO uval &=~ bm53 ; } ;
                        inline void clear_bit54(){ NRO uval &=~ bm54 ; } ;
                        inline void clear_bit55(){ NRO uval &=~ bm55 ; } ;
                        inline void clear_bit56(){ NRO uval &=~ bm56 ; } ;
                        inline void clear_bit57(){ NRO uval &=~ bm57 ; } ;
                        inline void clear_bit58(){ NRO uval &=~ bm58 ; } ;
                        inline void clear_bit59(){ NRO uval &=~ bm59 ; } ;
                        inline void clear_bit60(){ NRO uval &=~ bm60 ; } ;
                        inline void clear_bit61(){ NRO uval &=~ bm61 ; } ;
                        inline void clear_bit62(){ NRO uval &=~ bm62 ; } ;
                        inline void clear_bit63(){ NRO uval &=~ bm63 ; } ;
                        inline void clear_bits(uint64_t val) { NRO uval &=~ val ; } ;
                        inline void clear_bits(int64_t val)  { NRO uval &=~ val ; } ;

                        inline void toggle_bit ( bit_index_t bit_index ) { uval ^= (1 << bit_index) ; } ;
                        inline void toggle_bit ( bit_mask_t bit_mask )   { uval ^=  bit_mask  ; } ;
                        inline void toggle_bit0()  { NRO uval ^= bm0 ; } ;
                        inline void toggle_bit1()  { NRO uval ^= bm1 ; } ;
                        inline void toggle_bit2()  { NRO uval ^= bm2 ; } ;
                        inline void toggle_bit3()  { NRO uval ^= bm3 ; } ;
                        inline void toggle_bit4()  { NRO uval ^= bm4 ; } ;
                        inline void toggle_bit5()  { NRO uval ^= bm5 ; } ;
                        inline void toggle_bit6()  { NRO uval ^= bm6 ; } ;
                        inline void toggle_bit7()  { NRO uval ^= bm7 ; } ;
                        inline void toggle_bit8()  { NRO uval ^= bm8 ; } ;
                        inline void toggle_bit9()  { NRO uval ^= bm9 ; } ;
                        inline void toggle_bit10() { NRO uval ^= bm10 ; } ;
                        inline void toggle_bit11() { NRO uval ^= bm11 ; } ;
                        inline void toggle_bit12() { NRO uval ^= bm12 ; } ;
                        inline void toggle_bit13() { NRO uval ^= bm13 ; } ;
                        inline void toggle_bit14() { NRO uval ^= bm14 ; } ;
                        inline void toggle_bit15() { NRO uval ^= bm15 ; } ;
                        inline void toggle_bit16() { NRO uval ^= bm16 ; } ;
                        inline void toggle_bit17() { NRO uval ^= bm17 ; } ;
                        inline void toggle_bit18() { NRO uval ^= bm18 ; } ;
                        inline void toggle_bit19() { NRO uval ^= bm19 ; } ;
                        inline void toggle_bit20() { NRO uval ^= bm20 ; } ;
                        inline void toggle_bit21() { NRO uval ^= bm21 ; } ;
                        inline void toggle_bit22() { NRO uval ^= bm22 ; } ;
                        inline void toggle_bit23() { NRO uval ^= bm23 ; } ;
                        inline void toggle_bit24() { NRO uval ^= bm24 ; } ;
                        inline void toggle_bit25() { NRO uval ^= bm25 ; } ;
                        inline void toggle_bit26() { NRO uval ^= bm26 ; } ;
                        inline void toggle_bit27() { NRO uval ^= bm27 ; } ;
                        inline void toggle_bit28() { NRO uval ^= bm28 ; } ;
                        inline void toggle_bit29() { NRO uval ^= bm29 ; } ;
                        inline void toggle_bit30() { NRO uval ^= bm30 ; } ;
                        inline void toggle_bit31() { NRO uval ^= bm31 ; } ;
                        inline void toggle_bit32() { NRO uval ^= bm32 ; } ;
                        inline void toggle_bit33() { NRO uval ^= bm33 ; } ;
                        inline void toggle_bit34() { NRO uval ^= bm34 ; } ;
                        inline void toggle_bit35() { NRO uval ^= bm35 ; } ;
                        inline void toggle_bit36() { NRO uval ^= bm36 ; } ;
                        inline void toggle_bit37() { NRO uval ^= bm37 ; } ;
                        inline void toggle_bit38() { NRO uval ^= bm38 ; } ;
                        inline void toggle_bit39() { NRO uval ^= bm39 ; } ;
                        inline void toggle_bit40() { NRO uval ^= bm40 ; } ;
                        inline void toggle_bit41() { NRO uval ^= bm41 ; } ;
                        inline void toggle_bit42() { NRO uval ^= bm42 ; } ;
                        inline void toggle_bit43() { NRO uval ^= bm43 ; } ;
                        inline void toggle_bit44() { NRO uval ^= bm44 ; } ;
                        inline void toggle_bit45() { NRO uval ^= bm45 ; } ;
                        inline void toggle_bit46() { NRO uval ^= bm46 ; } ;
                        inline void toggle_bit47() { NRO uval ^= bm47 ; } ;
                        inline void toggle_bit48() { NRO uval ^= bm48 ; } ;
                        inline void toggle_bit49() { NRO uval ^= bm49 ; } ;
                        inline void toggle_bit50() { NRO uval ^= bm50 ; } ;
                        inline void toggle_bit51() { NRO uval ^= bm51 ; } ;
                        inline void toggle_bit52() { NRO uval ^= bm52 ; } ;
                        inline void toggle_bit53() { NRO uval ^= bm53 ; } ;
                        inline void toggle_bit54() { NRO uval ^= bm54 ; } ;
                        inline void toggle_bit55() { NRO uval ^= bm55 ; } ;
                        inline void toggle_bit56() { NRO uval ^= bm56 ; } ;
                        inline void toggle_bit57() { NRO uval ^= bm57 ; } ;
                        inline void toggle_bit58() { NRO uval ^= bm58 ; } ;
                        inline void toggle_bit59() { NRO uval ^= bm59 ; } ;
                        inline void toggle_bit60() { NRO uval ^= bm60 ; } ;
                        inline void toggle_bit61() { NRO uval ^= bm61 ; } ;
                        inline void toggle_bit62() { NRO uval ^= bm62 ; } ;
                        inline void toggle_bit63() { NRO uval ^= bm63 ; } ;
                        inline void toggle_bits(uint64_t val) { NRO uval ^= val ; } ;
                        inline void toggle_bits(int64_t  val) { NRO sval ^= val ; } ;

                        inline static data_64bit_t& from(const int64_t& val) {NRO return *((data_64bit_t*)(&val)) ; }
                        inline static data_64bit_t& from(const uint64_t& val) {NRO return *((data_64bit_t*)(&val)) ; }

    } __reg_attr__ ;


#endif /* __TYPES++_H__ */
