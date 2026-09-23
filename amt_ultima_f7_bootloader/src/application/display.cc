/*
 * display.cc
 *
 *  Created on: Aug 30, 2014
 *      Author: s
 */

#include "display.h"
#include "fonts.h"


display_task_t* display_task ;

void display_task_t::code()
{
	{
      display_task->string(20 , 10, BOOT_LOADER_VER_STR);
      emb_string str ;
      //emb_printf::sprintf(str, "%1", gnu_linker_build_date());
      //display_task->string(8 , str);
	}

  while(1)
    {

      if ( !message_buffer->receive_from_task ( message, max_messagge_size, portMAX_DELAY ))
	 std::__throw_logic_error("display_task_t::code(): message received fail") ;

      nop_rep(10);

      switch( *((request_t*)message) )
      {
	 case rqst_clear:
	   {
	     sh1106_t::clear() ;
	     break ;
	   }
	 case rqst_font:
	   {
	     const rqst_font_t* obj = (rqst_font_t*)message ;
	     sh1106_t::font( obj->font, obj->intersymbol_space );
	     break;
	   }
	 case rqst_string:
	   {
	     const rqst_string_t* obj = (rqst_string_t*)message ;
	     sh1106_t::string( obj->pos.col, obj->pos.row, obj->str ) ;
	     break;
	   }
	 case rqst_string_font:
	   {
	     const rqst_string_font_t* obj = (rqst_string_font_t*)message ;
	     sh1106_t::font( obj->font, obj->font );
	     sh1106_t::string( obj->pos.col, obj->pos.row, obj->str ) ;
	     break;
	   }
	 default:
	   {
	     std::__throw_logic_error("display_task_t::code(): invalid message received") ;
	   }
      }
    }
}


void display_task_t::clear()
{
  rqst_clear_t rqst_clear ;
  request<rqst_clear_t>(rqst_clear) ;
}

void display_task_t::font(const uint8_t font, const uint8_t intersymbol_space )
{
  rqst_font_t obj ;
  obj.font = font ;
  obj.intersymbol_space = intersymbol_space ;
  request<rqst_font_t>(obj) ;
}

void display_task_t::string(uint8_t row, uint8_t col , const char* val)
{
  rqst_string_t obj ;
  obj.pos.col = col ;
  obj.pos.row = row ;
  strlcpy ( obj.str , val, max_string_length );
  request<rqst_string_t>(obj) ;
}

// добавляет текст с текущей колонки
void display_task_t::string(uint8_t row, const char* val)
{
  string(row, sh1106_t::cols, val);
}

void display_task_t::string_font(uint8_t row, uint8_t col, const char* val, const uint8_t font, const uint8_t intersymbol_space=255 )
{
  rqst_string_font_t obj ;
  obj.pos.col = col ;
  obj.pos.row = row ;
  obj.font = font ;
  obj.intersymbol_space = intersymbol_space ;
  strlcpy ( obj.str , val, max_string_length );
  request<rqst_string_font_t>(obj) ;
}

// добавляет текст с текущей колонки
void display_task_t::string_font(uint8_t row, const char* val, const uint8_t font, const uint8_t intersymbol_space=255 )
{
  display_task_t::string_font(row, sh1106_t::cols, val, font, intersymbol_space);
}


void display_task_t::progress( const uint8_t val )
{

}

static void display_io_init()
{
  gpioa.clock_enable();
  gpiod.clock_enable();
  gpioc.clock_enable();

  gpioa.pin15_mode_output();
  gpioa.pin15_output_type_pull_push();
  gpioa.pin15_pull_no();
  gpioa.pin15_output_speed_high();
  gpioa.pin15_set();

  gpiod.pin5_mode_output();
  gpiod.pin5_output_type_pull_push();
  gpiod.pin5_pull_no();
  gpiod.pin5_output_speed_high();
  gpiod.pin5_reset();


  gpiod.pin6_mode_output();
  gpiod.pin6_output_type_pull_push();
  gpiod.pin6_pull_no();
  gpiod.pin6_output_speed_high();
  gpiod.pin6_reset();


  gpioc.pin10_mode_alternate_function();
  gpioc.pin10_output_type_pull_push();
  gpioc.pin10_pull_no();
  gpioc.pin10_output_speed_very_high();
  gpioc.pin10_af_spi3_sck_i2s3_ck();

  gpioc.pin12_mode_alternate_function();
  gpioc.pin12_output_type_pull_push();
  gpioc.pin12_pull_no();
  gpioc.pin12_output_speed_very_high();
  gpioc.pin12_af_spi3_mosi_i2s3_sd();


  spi3.clock_enable();
  spi3.reset();
  spi3.boud_rate_fpclk_div_2();
  spi3.clock_polarity_hight();
  spi3.clock_phase_second_clock();
  spi3.frame_first_msb();
  spi3.mode_selection_master();
  spi3.fifo_reception_threshold_1div4();
  spi3.data_size_8_bits();
  spi3.ss_output_enable();
  spi3.nss_pulse_management_enable();
  spi3.crc_polynomial=7;
  spi3.enable();
}


static void display_write (const uint8_t data)
{
  spi3.wait_tx_empty();
  spi3.byte_data = data ;
  spi3.wait_not_busy();
}

static void display_select()
{
  gpioa.pin15_reset();
}

static void display_deselect()
{
  gpioa.pin15_set();
}

static void display_command_mode()
{
  gpiod.pin6_reset();
}

static void display_data_mode()
{
  gpiod.pin6_set();
}

static void display_reset_state_active()
{
  gpiod.pin5_reset();
}

static void display_reset_state_deactive()
{
  gpiod.pin5_set();
}

static void display_delay_ms(uint32_t val)
{

}

const sh1106_t::io_t display_io =
    {
	.reset_state_active = display_reset_state_active,
	.reset_state_deactive = display_reset_state_deactive,
	.init = display_io_init,
	.write = display_write,
	.select = display_select,
	.deselect = display_deselect,
	.delay_ms = display_delay_ms,
	.command_mode = display_command_mode,
	.data_mode = display_data_mode
    } ;
