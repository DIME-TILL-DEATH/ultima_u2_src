/*
 * dcmi++.h
 *
 *  Created on: 28 дек. 2018 г.
 *      Author: klen
 */

#ifndef __DCMI++_H__
#define __DCMI++_H__

#include "types++.h"

namespace stm32
{

struct dcmi_t
{

  struct control_t : public read_write_32_t
  {
    struct capture_t                            { enum enum_t { offset=0, mask=1, disable=0 , enable }; } ;
    struct capture_mode_t                       { enum enum_t { offset=1, mask=1, continuous_grab=0 , single_frame }; } ;
    struct crop_feature_t                       { enum enum_t { offset=2, mask=1, disable=0 , enable }; } ;
    struct jpeg_format_t                        { enum enum_t { offset=3, mask=1, disable=0 , enable }; } ;
    struct synchronization_select_t             { enum enum_t { offset=4, mask=1, hardware=0 , data_flow_embedded }; } ;
    struct pixel_clock_polarity_t               { enum enum_t { offset=5, mask=1, falling_edge=0 , rising_edge }; } ;
    struct horizontal_synchronization_polarity_t{ enum enum_t { offset=6, mask=1, low=0 , high }; } ;
    struct vertical_synchronization_polarity_t  { enum enum_t { offset=7, mask=1, low=0 , high }; } ;
    struct frame_capture_rate_control_t         { enum enum_t { offset=8, mask=0b11, all=0 , frame_1_of_2, frame_1_of_4 }; } ;
    struct extended_data_mode_t                 { enum enum_t { offset=10, mask=0b11, data_8_bit=0 , data_10_bit, data_12_bit, data_14_bit }; } ;
    struct state_t                              { enum enum_t { offset=14, mask=1, disable=0 , enable }; } ;
    struct byte_select_mode_t                   { enum enum_t { offset=16, mask=0b11, data_all=0, data_1_of_2,  data_1_of_4, data_2_of_4 }; } ;
    struct data_select_start_t                  { enum enum_t { offset=18, mask=1, first=0, second }; } ;
    struct line_select_mode_t                   { enum enum_t { offset=19, mask=1, lines_all=0, lines_1_of_2 }; } ;
    struct line_select_start_t                  { enum enum_t { offset=20, mask=1, first=0, second }; } ;
  } ;

  inline void capture(const control_t::capture_t::enum_t val) {  control.rmw( val );}
  inline void capture_enable() { control.rmw( control_t::capture_t::enable );}
  inline void capture_disable() { control.rmw( control_t::capture_t::disable );}
  inline auto capture() const { return control.rd<control_t::capture_t>();}

  inline void capture_mode(const control_t::capture_mode_t::enum_t val) {  control.rmw( val );}
  inline void capture_mode_continuous_grab() { control.rmw( control_t::capture_mode_t::continuous_grab );}
  inline void capture_mode_single_frame() { control.rmw( control_t::capture_mode_t::single_frame );}
  inline auto capture_mode() const { return control.rd<control_t::capture_mode_t>();}

  inline void crop_feature(const control_t::crop_feature_t::enum_t val) {  control.rmw( val );}
  inline void crop_feature_disable() { control.rmw( control_t::crop_feature_t::disable );}
  inline void crop_feature_enable() { control.rmw( control_t::crop_feature_t::enable );}
  inline auto crop_feature() const { return control.rd<control_t::crop_feature_t>();}

  inline void jpeg_format(const control_t::jpeg_format_t::enum_t val) {  control.rmw( val );}
  inline void jpeg_format_disable() { control.rmw( control_t::jpeg_format_t::disable );}
  inline void jpeg_format_enable() { control.rmw( control_t::jpeg_format_t::enable );}
  inline auto jpeg_format() const { return control.rd<control_t::jpeg_format_t>();}

  inline void synchronization_select(const control_t::synchronization_select_t::enum_t val) {  control.rmw( val );}
  inline void synchronization_select_hardware() { control.rmw( control_t::synchronization_select_t::hardware );}
  inline void synchronization_select_data_flow_embedded() { control.rmw( control_t::synchronization_select_t::data_flow_embedded );}
  inline auto synchronization_select() const { return control.rd<control_t::synchronization_select_t>();}

  inline void pixel_clock_polarity(const control_t::pixel_clock_polarity_t::enum_t val) {  control.rmw( val );}
  inline void pixel_clock_polarity_falling_edge() { control.rmw( control_t::pixel_clock_polarity_t::falling_edge );}
  inline void pixel_clock_polarity_rising_edge() { control.rmw( control_t::pixel_clock_polarity_t::rising_edge );}
  inline auto pixel_clock_polarity() const { return control.rd<control_t::pixel_clock_polarity_t>();}

  inline void horizontal_synchronization_polarity(const control_t::horizontal_synchronization_polarity_t::enum_t val) {  control.rmw( val );}
  inline void horizontal_synchronization_polarity_low() { control.rmw( control_t::horizontal_synchronization_polarity_t::low );}
  inline void horizontal_synchronization_polarity_high() { control.rmw( control_t::horizontal_synchronization_polarity_t::high );}
  inline auto horizontal_synchronization_polarity() const { return control.rd<control_t::horizontal_synchronization_polarity_t>();}

  inline void vertical_synchronization_polarity(const control_t::vertical_synchronization_polarity_t::enum_t val) {  control.rmw( val );}
  inline void vertical_synchronization_polarity_low() { control.rmw( control_t::vertical_synchronization_polarity_t::low );}
  inline void vertical_synchronization_polarity_high() { control.rmw( control_t::vertical_synchronization_polarity_t::high );}
  inline auto vertical_synchronization_polarity() const { return control.rd<control_t::vertical_synchronization_polarity_t>();}

  inline void frame_capture_rate_control(const control_t::frame_capture_rate_control_t::enum_t val) {  control.rmw( val );}
  inline void frame_capture_rate_control_all() { control.rmw( control_t::frame_capture_rate_control_t::all );}
  inline void frame_capture_rate_control_1_of_2() { control.rmw( control_t::frame_capture_rate_control_t::frame_1_of_2 );}
  inline void frame_capture_rate_control_1_of_4() { control.rmw( control_t::frame_capture_rate_control_t::frame_1_of_4 );}
  inline auto frame_capture_rate_control() const { return control.rd<control_t::frame_capture_rate_control_t>();}

  inline void extended_data_mode(const control_t::extended_data_mode_t::enum_t val) {  control.rmw( val );}
  inline void extended_data_mode_data_8_bit()  { control.rmw( control_t::extended_data_mode_t::data_8_bit );}
  inline void extended_data_mode_data_10_bit() { control.rmw( control_t::extended_data_mode_t::data_10_bit );}
  inline void extended_data_mode_data_12_bit() { control.rmw( control_t::extended_data_mode_t::data_12_bit );}
  inline void extended_data_mode_data_14_bit() { control.rmw( control_t::extended_data_mode_t::data_14_bit );}
  inline auto extended_data_mode() const { return control.rd<control_t::extended_data_mode_t>();}

  inline void state(const control_t::state_t::enum_t val) {  control.rmw( val );}
  inline void state_disable() { control.rmw( control_t::state_t::disable );}
  inline void state_enable() { control.rmw( control_t::state_t::enable );}
  inline auto state() const { return control.rd<control_t::state_t>();}

  inline void byte_select_mode(const control_t::byte_select_mode_t::enum_t val) {  control.rmw( val );}
  inline void byte_select_mode_data_all()    { control.rmw( control_t::byte_select_mode_t::data_all );}
  inline void byte_select_mode_data_1_of_2() { control.rmw( control_t::byte_select_mode_t::data_1_of_2 );}
  inline void byte_select_mode_data_1_of_4() { control.rmw( control_t::byte_select_mode_t::data_1_of_4 );}
  inline void byte_select_mode_data_2_of_4() { control.rmw( control_t::byte_select_mode_t::data_2_of_4 );}
  inline auto byte_select_mode() const { return control.rd<control_t::byte_select_mode_t>();}

  inline void data_select_start(const control_t::data_select_start_t::enum_t val) {  control.rmw( val );}
  inline void data_select_start_first() { control.rmw( control_t::data_select_start_t::first );}
  inline void data_select_start_second() { control.rmw( control_t::data_select_start_t::second );}
  inline auto data_select_start() const { return control.rd<control_t::data_select_start_t>();}

  inline void line_select_mode(const control_t::line_select_mode_t::enum_t val) {  control.rmw( val );}
  inline void line_select_mode_all() { control.rmw( control_t::line_select_mode_t::lines_all );}
  inline void line_select_mode_1_of_2() { control.rmw( control_t::line_select_mode_t::lines_1_of_2 );}
  inline auto line_select_mode() const { return control.rd<control_t::line_select_mode_t>();}

  inline void line_select_start(const control_t::line_select_start_t::enum_t val) {  control.rmw( val );}
  inline void line_select_start_first() { control.rmw( control_t::line_select_start_t::first );}
  inline void line_select_start_second() { control.rmw( control_t::line_select_start_t::second );}
  inline auto line_select_start() const { return control.rd<control_t::line_select_start_t>();}

  struct status_t : public read_write_32_t
  {
    struct hsync_flag_t       { enum enum_t { offset=0, mask=1, active_line=0 , between_lines }; } ;
    struct vsync_flag_t       { enum enum_t { offset=1, mask=1, active_frame=0 , between_frame }; } ;
    struct fifo_flag_t        { enum enum_t { offset=2, mask=1, empty=0 , not_empty }; } ;
  } ;

  inline auto hsync_flag() const { return status.rd<status_t::hsync_flag_t>();}
  inline auto vsync_flag() const { return status.rd<status_t::vsync_flag_t>();}
  inline auto fifo_flag()  const { return status.rd<status_t::fifo_flag_t>();}

  struct raw_interrupt_status_t : public read_write_32_t
  {
    struct capture_complete_interrupt_flag_t      { enum enum_t { offset=0, mask=1, not_occured=0 , occured }; } ;
    struct overrun_interrupt_flag_t               { enum enum_t { offset=1, mask=1, not_occured=0 , occured }; } ;
    struct synchronization_error_interrupt_flag_t { enum enum_t { offset=2, mask=1, not_occured=0 , occured }; } ;
    struct vsync_interrupt_flag_t                 { enum enum_t { offset=3, mask=1, not_occured=0 , occured }; } ;
    struct hsync_interrupt_flag_t                 { enum enum_t { offset=4, mask=1, not_occured=0 , occured }; } ;
  } ;

  inline auto raw_capture_complete_interrupt_flag() const { return raw_interrupt_status.rd<raw_interrupt_status_t::capture_complete_interrupt_flag_t>();}
  inline void raw_capture_complete_interrupt_flag_clear() {  raw_interrupt_status.rmw( raw_interrupt_status_t::capture_complete_interrupt_flag_t::occured );}

  inline auto raw_overrun_interrupt_flag() const { return raw_interrupt_status.rd<raw_interrupt_status_t::overrun_interrupt_flag_t>();}
  inline void raw_overrun_interrupt_flag_clear() {  raw_interrupt_status.rmw( raw_interrupt_status_t::overrun_interrupt_flag_t::occured );}

  inline auto raw_synchronization_error_interrupt_flag() const { return raw_interrupt_status.rd<raw_interrupt_status_t::synchronization_error_interrupt_flag_t>();}
  inline void raw_synchronization_error_interrupt_flag_clear() {  raw_interrupt_status.rmw( raw_interrupt_status_t::synchronization_error_interrupt_flag_t::occured );}

  inline auto raw_vsync_interrupt_flag() const { return raw_interrupt_status.rd<raw_interrupt_status_t::vsync_interrupt_flag_t>();}
  inline void raw_vsync_interrupt_flag_clear() {  raw_interrupt_status.rmw( raw_interrupt_status_t::vsync_interrupt_flag_t::occured );}

  inline auto raw_hsync_interrupt_flag() const { return raw_interrupt_status.rd<raw_interrupt_status_t::hsync_interrupt_flag_t>();}
  inline void raw_hsync_interrupt_flag_clear() {  raw_interrupt_status.rmw( raw_interrupt_status_t::hsync_interrupt_flag_t::occured );}

  struct interrupt_t : public read_write_32_t
  {
    struct capture_complete_interrupt_t      { enum enum_t { offset=0, mask=1, disable=0 , enable }; } ;
    struct overrun_interrupt_t               { enum enum_t { offset=1, mask=1, disable=0 , enable }; } ;
    struct synchronization_error_interrupt_t { enum enum_t { offset=2, mask=1, disable=0 , enable }; } ;
    struct vsync_interrupt_t                 { enum enum_t { offset=3, mask=1, disable=0 , enable }; } ;
    struct hsync_interrupt_t                 { enum enum_t { offset=4, mask=1, disable=0 , enable }; } ;
  } ;

  inline void capture_complete_interrupt(const interrupt_t::capture_complete_interrupt_t::enum_t val) {  interrupt.rmw( val );}
  inline void capture_complete_interrupt_disable() { interrupt.rmw( interrupt_t::capture_complete_interrupt_t::disable );}
  inline void capture_complete_interrupt_enable() { interrupt.rmw( interrupt_t::capture_complete_interrupt_t::enable );}
  inline auto capture_complete_interrupt() const { return interrupt.rd<interrupt_t::capture_complete_interrupt_t>();}

  inline void overrun_interrupt(const interrupt_t::overrun_interrupt_t::enum_t val) {  interrupt.rmw( val );}
  inline void overrun_interrupt_disable() { interrupt.rmw( interrupt_t::overrun_interrupt_t::disable );}
  inline void overrun_interrupt_enable() { interrupt.rmw( interrupt_t::overrun_interrupt_t::enable );}
  inline auto overrun_interrupt() const { return interrupt.rd<interrupt_t::overrun_interrupt_t>();}

  inline void synchronization_error_interrupt(const interrupt_t::synchronization_error_interrupt_t::enum_t val) {  interrupt.rmw( val );}
  inline void synchronization_error_interrupt_disable() { interrupt.rmw( interrupt_t::synchronization_error_interrupt_t::disable );}
  inline void synchronization_error_interrupt_enable() { interrupt.rmw( interrupt_t::synchronization_error_interrupt_t::enable );}
  inline auto synchronization_error_interrupt() const { return interrupt.rd<interrupt_t::synchronization_error_interrupt_t>();}

  inline void vsync_interrupt(const interrupt_t::vsync_interrupt_t::enum_t val) {  interrupt.rmw( val );}
  inline void vsync_interrupt_disable() { interrupt.rmw( interrupt_t::vsync_interrupt_t::disable );}
  inline void vsync_interrupt_enable() { interrupt.rmw( interrupt_t::vsync_interrupt_t::enable );}
  inline auto vsync_interrupt() const { return interrupt.rd<interrupt_t::vsync_interrupt_t>();}

  inline void hsync_interrupt(const interrupt_t::hsync_interrupt_t::enum_t val) {  interrupt.rmw( val );}
  inline void hsync_interrupt_disable() { interrupt.rmw( interrupt_t::hsync_interrupt_t::disable );}
  inline void hsync_interrupt_enable() { interrupt.rmw( interrupt_t::hsync_interrupt_t::enable );}
  inline auto hsync_interrupt() const { return interrupt.rd<interrupt_t::hsync_interrupt_t>();}

  struct masked_interrupt_status_t : public read_write_32_t
  {
    struct capture_complete_interrupt_flag_t      { enum enum_t { offset=0, mask=1, not_occured=0 , occured }; } ;
    struct overrun_interrupt_flag_t               { enum enum_t { offset=1, mask=1, not_occured=0 , occured }; } ;
    struct synchronization_error_interrupt_flag_t { enum enum_t { offset=2, mask=1, not_occured=0 , occured }; } ;
    struct vsync_interrupt_flag_t                 { enum enum_t { offset=3, mask=1, not_occured=0 , occured }; } ;
    struct hsync_interrupt_flag_t                 { enum enum_t { offset=4, mask=1, not_occured=0 , occured }; } ;
  } ;

  inline auto masked_capture_complete_interrupt_flag() const { return masked_interrupt_status.rd<masked_interrupt_status_t::capture_complete_interrupt_flag_t>();}
  inline auto masked_overrun_interrupt_flag()          const { return masked_interrupt_status.rd<masked_interrupt_status_t::overrun_interrupt_flag_t>();}
  inline auto masked_synchronization_error_interrupt_flag() const { return masked_interrupt_status.rd<masked_interrupt_status_t::synchronization_error_interrupt_flag_t>();}
  inline auto masked_vsync_interrupt_flag()            const { return masked_interrupt_status.rd<masked_interrupt_status_t::vsync_interrupt_flag_t>();}
  inline auto masked_hsync_interrupt_flag()            const { return masked_interrupt_status.rd<masked_interrupt_status_t::hsync_interrupt_flag_t>();}

  struct interrupt_clear_t : public read_write_32_t
  {
    struct capture_complete_interrupt_clear_t      { enum enum_t { offset=0, mask=1, no_action=0 , clear }; } ;
    struct overrun_interrupt_clear_t               { enum enum_t { offset=1, mask=1, no_action=0 , clear }; } ;
    struct synchronization_error_interrupt_clear_t { enum enum_t { offset=2, mask=1, no_action=0 , clear }; } ;
    struct vsync_interrupt_clear_t                 { enum enum_t { offset=3, mask=1, no_action=0 , clear }; } ;
    struct hsync_interrupt_clear_t                 { enum enum_t { offset=4, mask=1, no_action=0 , clear }; } ;
  } ;

  inline void capture_complete_interrupt_clear() { interrupt_clear.rmw( interrupt_clear_t::capture_complete_interrupt_clear_t::clear );}
  inline void overrun_interrupt_clear()          { interrupt_clear.rmw( interrupt_clear_t::overrun_interrupt_clear_t::clear );}
  inline void synchronization_error_interrupt_clear() { interrupt_clear.rmw( interrupt_clear_t::synchronization_error_interrupt_clear_t::clear );}
  inline void vsync_interrupt_clear()            { interrupt_clear.rmw( interrupt_clear_t::vsync_interrupt_clear_t::clear );}
  inline void hsync_interrupt_clear()            { interrupt_clear.rmw( interrupt_clear_t::hsync_interrupt_clear_t::clear );}



  struct embedded_synchronization_code_t : public read_write_32_t
  {
    struct frame_start_delimiter_code_t   { enum enum_t { offset=0,  mask=0xff }; } ;
    struct line_start_delimiter_code_t    { enum enum_t { offset=8,  mask=0xff }; } ;
    struct line_end_delimiter_code_t      { enum enum_t { offset=16, mask=0xff }; } ;
    struct frame_end_delimiter_code_t     { enum enum_t { offset=24, mask=0xff }; } ;
  } ;

  inline void frame_start_delimiter_code(const uint8_t val) {  embedded_synchronization_code.rmw( (embedded_synchronization_code_t::frame_start_delimiter_code_t::enum_t)val );}
  inline auto frame_start_delimiter_code() const { return (uint8_t)embedded_synchronization_code.rd<embedded_synchronization_code_t::frame_start_delimiter_code_t>();}

  inline void line_start_delimiter_code(const uint8_t val) {  embedded_synchronization_code.rmw( (embedded_synchronization_code_t::line_start_delimiter_code_t::enum_t)val );}
  inline auto line_start_delimiter_code() const { return (uint8_t)embedded_synchronization_code.rd<embedded_synchronization_code_t::line_start_delimiter_code_t>();}

  inline void line_end_delimiter_code(const uint8_t val) {  embedded_synchronization_code.rmw( (embedded_synchronization_code_t::line_end_delimiter_code_t::enum_t)val );}
  inline auto line_end_delimiter_code() const { return (uint8_t)embedded_synchronization_code.rd<embedded_synchronization_code_t::line_end_delimiter_code_t>();}

  inline void frame_end_delimiter_code(const uint8_t val) {  embedded_synchronization_code.rmw( (embedded_synchronization_code_t::frame_end_delimiter_code_t::enum_t)val );}
  inline auto frame_end_delimiter_code() const { return (uint8_t)embedded_synchronization_code.rd<embedded_synchronization_code_t::frame_end_delimiter_code_t>();}

  struct embedded_synchronization_unmask_t : public read_write_32_t
  {
    struct frame_start_delimiter_unmask_t   { enum enum_t { offset=0,  mask=0xff }; } ;
    struct line_start_delimiter_unmask_t    { enum enum_t { offset=8,  mask=0xff }; } ;
    struct line_end_delimiter_unmask_t      { enum enum_t { offset=16, mask=0xff }; } ;
    struct frame_end_delimiter_unmask_t     { enum enum_t { offset=24, mask=0xff }; } ;
  } ;

  inline void frame_start_delimiter_unmask(const uint8_t val) {  embedded_synchronization_unmask.rmw( (embedded_synchronization_unmask_t::frame_start_delimiter_unmask_t::enum_t)val );}
  inline auto frame_start_delimiter_unmask() const { return (uint8_t)embedded_synchronization_unmask.rd<embedded_synchronization_unmask_t::frame_start_delimiter_unmask_t>();}

  inline void line_start_delimiter_unmask(const uint8_t val) {  embedded_synchronization_unmask.rmw( (embedded_synchronization_unmask_t::line_start_delimiter_unmask_t::enum_t)val );}
  inline auto line_start_delimiter_unmask() const { return (uint8_t)embedded_synchronization_unmask.rd<embedded_synchronization_unmask_t::line_start_delimiter_unmask_t>();}

  inline void line_end_delimiter_unmask(const uint8_t val) {  embedded_synchronization_unmask.rmw( (embedded_synchronization_unmask_t::line_end_delimiter_unmask_t::enum_t)val );}
  inline auto line_end_delimiter_unmask() const { return (uint8_t)embedded_synchronization_unmask.rd<embedded_synchronization_unmask_t::line_end_delimiter_unmask_t>();}

  inline void frame_end_delimiter_unmask(const uint8_t val) {  embedded_synchronization_unmask.rmw( (embedded_synchronization_unmask_t::frame_end_delimiter_unmask_t::enum_t)val );}
  inline auto frame_end_delimiter_unmask() const { return (uint8_t)embedded_synchronization_unmask.rd<embedded_synchronization_unmask_t::frame_end_delimiter_unmask_t>();}

  struct crop_start_t : public read_write_32_t
  {
    struct horizontal_offset_t   { enum enum_t { offset=0,  mask=0x1ff }; } ;
    struct vertical_start_line_t { enum enum_t { offset=8,  mask=0x3ff }; } ;
  } ;

  inline void crop_horizontal_offset(const uint8_t val) { crop_start.rmw( (crop_start_t::horizontal_offset_t::enum_t)(val - 1) );}
  inline auto crop_horizontal_offset() const { return (uint8_t)crop_start.rd<crop_start_t::horizontal_offset_t>() + 1;}

  inline void crop_vertical_start_line(const uint8_t val) { crop_start.rmw( (crop_start_t::vertical_start_line_t::enum_t)(val - 1));}
  inline auto crop_vertical_start_line() const { return (uint8_t)crop_start.rd<crop_start_t::vertical_start_line_t>() + 1;}

  struct crop_size_t : public read_write_32_t
  {
    struct pixel_count_t   { enum enum_t { offset=0,  mask=0x3ff }; } ;
    struct line_count_t { enum enum_t { offset=8,  mask=0x3ff }; } ;
  } ;

  inline void crop_pixel_count(const uint8_t val) { crop_size.rmw( (crop_size_t::pixel_count_t::enum_t)(val - 1) );}
  inline auto crop_pixel_count() const { return (uint8_t)crop_size.rd<crop_size_t::pixel_count_t>() + 1;}

  inline void line_count(const uint8_t val) { crop_size.rmw( (crop_size_t::line_count_t::enum_t)(val - 1) );}
  inline auto line_count() const { return (uint8_t)crop_size.rd<crop_size_t::line_count_t>() + 1;}

  control_t                         control;                        // CR;       /*!< DCMI control register 1,                       Address offset: 0x00 */
  status_t                          status;                         // SR;       /*!< DCMI status register,                          Address offset: 0x04 */
  raw_interrupt_status_t            raw_interrupt_status;           // RISR;     /*!< DCMI raw interrupt status register,            Address offset: 0x08 */
  interrupt_t                       interrupt;                      // IER;      /*!< DCMI interrupt enable register,                Address offset: 0x0C */
  masked_interrupt_status_t         masked_interrupt_status;        // MISR;     /*!< DCMI masked interrupt status register,         Address offset: 0x10 */
  interrupt_clear_t                 interrupt_clear;                // ICR;      /*!< DCMI interrupt clear register,                 Address offset: 0x14 */
  embedded_synchronization_code_t   embedded_synchronization_code;  // ESCR;     /*!< DCMI embedded synchronization code register,   Address offset: 0x18 */
  embedded_synchronization_unmask_t embedded_synchronization_unmask;// ESUR;     /*!< DCMI embedded synchronization unmask register, Address offset: 0x1C */
  crop_start_t                      crop_start;                     // CWSTRTR;  /*!< DCMI crop window start,                        Address offset: 0x20 */
  crop_size_t                       crop_size;                      // CWSIZER;  /*!< DCMI crop window size,                         Address offset: 0x24 */
  volatile uint32_t                 data ;                          // DR;       /*!< DCMI data register,                            Address offset: 0x28 */

  inline void clock_enable() {  rcc.dcmi_enable() ; }
  inline void clock_disable(){  rcc.dcmi_disable() ; }
  inline void reset()        {  rcc.dcmi_reset() ; }

} ;

static dcmi_t& dcmi  = *((dcmi_t*) dcmi_addr);

}

using namespace stm32 ;

#endif /* __DCMI++_H__ */
