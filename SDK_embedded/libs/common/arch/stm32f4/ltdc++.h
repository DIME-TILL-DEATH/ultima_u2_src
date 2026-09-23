/*
 * can++.h
 *
 *  Created on: 07 сен. 2017 г.
 *      Author: klen
 */

#ifndef __LTDC++_H__
#define __LTDC++_H__

#include "types++.h"

// TODO доделать до конца



namespace stm32f4
{


struct ltdc_t
  {

    struct synchronization_size_configuration_t : public read_write_32_t
      {
        struct vertical_synchronization_height_t   { enum enum_t { offset=0,  mask=0b11111111111 } ; } ;
        struct horizontal_synchronization_width_t { enum enum_t { offset=16, mask=0b111111111111 } ; } ;

      } ;

    inline  void vertical_synchronization_height( uint16_t val){  synchronization_size_configuration.rmw((synchronization_size_configuration_t::vertical_synchronization_height_t::enum_t)val) ;}
    inline  auto vertical_synchronization_height() const {  return (uint16_t) synchronization_size_configuration.rd<synchronization_size_configuration_t::synchronization_size_configuration_t::vertical_synchronization_height_t> ();}

    inline  void horizontal_synchronization_width( uint16_t val){  synchronization_size_configuration.rmw((synchronization_size_configuration_t::horizontal_synchronization_width_t::enum_t)val) ;}
    inline  auto horizontal_synchronization_width() const {  return (uint16_t) synchronization_size_configuration.rd<synchronization_size_configuration_t::synchronization_size_configuration_t::horizontal_synchronization_width_t> ();}


    struct back_porch_configuration_t : public read_write_32_t
      {

      } ;

    struct active_width_configuration_t : public read_write_32_t
      {

      } ;

    struct total_width_configuration_t : public read_write_32_t
      {

      } ;

    struct global_control_t : public read_write_32_t
      {

      } ;

    struct shadow_reload_configuration_t : public read_write_32_t
    {

    } ;

  struct background_color_configuration_t : public read_write_32_t
    {

    } ;

  struct interrupt_enable_t : public read_write_32_t
    {

    } ;

  struct interrupt_status_t : public read_write_32_t
    {

    } ;

  struct interrupt_clear_t : public read_write_32_t
     {

     } ;

  struct line_interrupt_position_configuration_t : public read_write_32_t
     {

     } ;

  struct current_position_status_t : public read_write_32_t
     {

     } ;

  struct current_display_status_t : public read_write_32_t
     {

     } ;



    uint32_t      reserved0[2];  /*!< Reserved, 0x00-0x04 */
    synchronization_size_configuration_t synchronization_size_configuration; // SSCR;          /*!< LTDC Synchronization Size Configuration Register,    Address offset: 0x08 */
    back_porch_configuration_t back_porch_configuration;                     // BPCR;          /*!< LTDC Back Porch Configuration Register,              Address offset: 0x0C */
    active_width_configuration_t active_width_configuration; // AWCR;          /*!< LTDC Active Width Configuration Register,            Address offset: 0x10 */
    total_width_configuration_t total_width_configuration; // TWCR;          /*!< LTDC Total Width Configuration Register,             Address offset: 0x14 */
    global_control_t global_control; //GCR;           /*!< LTDC Global Control Register,                        Address offset: 0x18 */
    uint32_t      reserved1[2];  /*!< Reserved, 0x1C-0x20 */
    shadow_reload_configuration_t shadow_reload_configuration; //SRCR;          /*!< LTDC Shadow Reload Configuration Register,           Address offset: 0x24 */
    uint32_t      reserved2[1];  /*!< Reserved, 0x28 */
    background_color_configuration_t background_color_configuration ; //BCCR;          /*!< LTDC Background Color Configuration Register,        Address offset: 0x2C */
    uint32_t      reserved4[1];  /*!< Reserved, 0x30 */
    interrupt_enable_t interrupt_enable; //IER;           /*!< LTDC Interrupt Enable Register,                      Address offset: 0x34 */
    interrupt_status_t interrupt_status; //ISR;           /*!< LTDC Interrupt Status Register,                      Address offset: 0x38 */
    interrupt_clear_t interrupt_clear ; //ICR;           /*!< LTDC Interrupt Clear Register,                       Address offset: 0x3C */
    line_interrupt_position_configuration_t line_interrupt_position_configuration; //LIPCR;         /*!< LTDC Line Interrupt Position Configuration Register, Address offset: 0x40 */
    current_position_status_t current_position_status; //CPSR;          /*!< LTDC Current Position Status Register,               Address offset: 0x44 */
    current_display_status_t current_display_status; //CDSR;         /*!< LTDC Current Display Status Register,                       Address offset: 0x48 */


    inline void clock_enable()
       {
          rcc.ltdc_enable();
       }

    inline void clock_disable()
       {
           rcc.ltdc_disable();
       }
    inline void reset()
       {
           rcc.ltdc_reset();
       };
  } ;

struct ltdc_layer_t
  {

   struct control_t : public read_write_32_t
     {

     } ;

   struct window_horizontal_position_configuration_t : public read_write_32_t
     {

     } ;

   struct window_vertical_position_configuration_t : public read_write_32_t
     {

     } ;

   struct color_keying_configuration_t : public read_write_32_t
     {

     } ;

   struct pixel_format_configuration_t : public read_write_32_t
     {

     } ;

   struct constant_alpha_configuration_t : public read_write_32_t
     {

     } ;

   struct default_color_configuration_t : public read_write_32_t
     {

     } ;

   struct blending_factors_configuration_t : public read_write_32_t
     {

     } ;

   struct color_frame_buffer_address_t : public read_write_32_t
     {

     } ;
/*
   struct color_frame_buffer_length_t : public read_write_32_t
     {

     } ;

   struct color_frame_buffer_line_number_t : public read_write_32_t
     {

     } ;
*/
   struct clut_write_t : public read_write_32_t
     {

     } ;

   control_t control;            //CR;            /*!< LTDC Layerx Control Register                                  Address offset: 0x84 */
   window_horizontal_position_configuration_t window_horizontal_position_configuration; //WHPCR;         /*!< LTDC Layerx Window Horizontal Position Configuration Register Address offset: 0x88 */
   window_vertical_position_configuration_t window_vertical_position_configuration; //WVPCR;         /*!< LTDC Layerx Window Vertical Position Configuration Register   Address offset: 0x8C */
   color_keying_configuration_t color_keying_configuration; //CKCR;          /*!< LTDC Layerx Color Keying Configuration Register               Address offset: 0x90 */
   pixel_format_configuration_t pixel_format_configuration; //PFCR;          /*!< LTDC Layerx Pixel Format Configuration Register               Address offset: 0x94 */
   constant_alpha_configuration_t constant_alpha_configuration; //CACR;          /*!< LTDC Layerx Constant Alpha Configuration Register             Address offset: 0x98 */
   default_color_configuration_t default_color_configuration_t; //DCCR;          /*!< LTDC Layerx Default Color Configuration Register              Address offset: 0x9C */
   blending_factors_configuration_t blending_factors_configuration; //BFCR;          /*!< LTDC Layerx Blending Factors Configuration Register           Address offset: 0xA0 */
   uint32_t      reserved0[2];  /*!< Reserved */
   color_frame_buffer_address_t color_frame_buffer_address; //CFBAR;         /*!< LTDC Layerx Color Frame Buffer Address Register               Address offset: 0xAC */
   uint32_t color_frame_buffer_length; //CFBLR;         /*!< LTDC Layerx Color Frame Buffer Length Register                Address offset: 0xB0 */
   uint32_t color_frame_buffer_line_number;// CFBLNR;        /*!< LTDC Layerx ColorFrame Buffer Line Number Register            Address offset: 0xB4 */
   uint32_t      reserved1[3];  /*!< Reserved */
   clut_write_t clut_write;         /*!< LTDC Layerx CLUT Write Register                               Address offset: 0x144 */
  };

static ltdc_t&              ltdc = *((ltdc_t*) ltdc_addr);

}  // stm32f4

using namespace stm32f4 ;

#endif /* __LTDC++_H__ */
