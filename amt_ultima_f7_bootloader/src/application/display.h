/*
 * display.h
 *
 *  Created on: 12 дек 2018
 *      Author: klen_s@mail.ru
 */

#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "appdefs.h"
#include "display/sh1106.h"



class display_task_t : public task_t, public sh1106_t
{
  constexpr static size_t max_string_length = 64 ;

  enum request_t
    {
       rqst_clear,
       rqst_font,
       rqst_string,
       rqst_string_font
    } ;

  struct pos_t
    {
      uint8_t col ;
      uint8_t row ;
    };

  struct rqst_clear_t
    {
      const request_t request = rqst_clear ;
    } ;

  struct rqst_font_t
    {
      const request_t request = rqst_font ;
      uint8_t font ;
      uint8_t intersymbol_space ;
    } ;

  struct rqst_string_t
    {
      const request_t request = rqst_string ;
      pos_t pos ;
      char str[max_string_length];
    } ;

  struct rqst_string_font_t
    {
      const request_t request = rqst_string_font ;
      pos_t pos ;
      uint8_t font ;
      uint8_t intersymbol_space ;
      char str[max_string_length];
    } ;


  constexpr static size_t max_messagge_size = sizeof(request_t) + sizeof(pos_t) + sizeof(rqst_string_font_t) ;
  constexpr static size_t max_messagge_buffer_depth = 16 ;
  constexpr static size_t messagge_buffer_size = max_messagge_buffer_depth * max_messagge_size  ;



  public:
     inline display_task_t (const char* name , const int stack_size , const int priority, const sh1106_t::io_t& io, const sh1106_t::font_t* fonts)
     : task_t(name , stack_size , priority , false), sh1106_t(io, fonts)

     {
        message_buffer = new message_buffer_t( messagge_buffer_size ) ;
        if ( !((bool)message_buffer & message_buffer->is_created()) )
          std::__throw_memmgr_error("display_task_t::display_task_t(...): message_buffer allocation fail") ;

        message = new char[max_messagge_size] ;
     }



     void clear();
     void font(const uint8_t font, const uint8_t intersymbol_space = 255 );

     void string(uint8_t row, uint8_t col, const char* str);
     inline void string(uint8_t row, uint8_t col, const emb_string& str) { string(row,col,str.c_str()); }
     void string_font(uint8_t row, uint8_t col, const char* val, const uint8_t font, const uint8_t intersymbol_space );
     inline void string_font(uint8_t row, uint8_t col, const emb_string& str, const uint8_t font, const uint8_t intersymbol_space )
       {
    	 string_font(row, col, str.c_str(), font, intersymbol_space );
       }

     // добавляет текст с текущей колонки
     void string(uint8_t row, const char* str);
     inline void string(uint8_t row, const emb_string& str) { string(row,str.c_str()); }
     void string_font(uint8_t row, const char* val, const uint8_t font, const uint8_t intersymbol_space );
     inline void string_font(uint8_t row, const emb_string& str, const uint8_t font, const uint8_t intersymbol_space )
       {
    	 string_font(row, str.c_str(), font, intersymbol_space );
       }


     void progress( const uint8_t val );


  protected:

     template< typename T >
     void request(T& message) { message_buffer->send_from_task( (void*)&message, sizeof(T), 0); }

  private:
     void code() ;
     message_buffer_t* message_buffer ;
     char* message ;





};

extern display_task_t* display_task ;
extern const sh1106_t::io_t display_io ;

#include "fonts.h"

#endif /* __DISPLAY_H__ */
