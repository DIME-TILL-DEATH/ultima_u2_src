#ifndef __PLATFORM_CONFIG_H
#define __PLATFORM_CONFIG_H

#define run_time_counter_irq         nvic_t::irq_num_t::tim7
#define run_time_counter_dbg         dbgmcu_t::apb1_freeze_t::peripheral_t::tim7
#define run_time_counter_tim         tim7
#define run_time_counter_priority    0
#define run_time_timer_irq_handler   tim7_irq_handler

#define LED_COUNT 2
#define LED_EFF { \
                 gpioc, \
		 gpio_t::mode_t::output, \
                 gpio_t::output_type_t::open_drain, \
		 gpio_t::output_speed_t::low, \
	         gpio_t::pull_t::enum_t::no, \
		 (gpio_t::af_t::enum_t)0, \
		 gpio_t::i13, \
		 gpio_t::b13, \
		 gpio_t::output_t::enum_t::reset, \
	      }

#define LED_TAP { \
                 gpiod, \
		 gpio_t::mode_t::output, \
                 gpio_t::output_type_t::open_drain, \
		 gpio_t::output_speed_t::low, \
	         gpio_t::pull_t::enum_t::no, \
		 (gpio_t::af_t::enum_t)0, \
		 gpio_t::i13, \
		 gpio_t::b13, \
		 gpio_t::output_t::enum_t::reset, \
	      }


#define LED_DESC  {{ LED_EFF, led_config_t::coupled_t::vdd, 500, 500, false, led_timer_handler, 0, 0, 0},\
                   { LED_TAP, led_config_t::coupled_t::vdd, 10, 990, false, led_timer_handler, 0, 0, 0}}

enum led_id { led_eff=0, led_tap  } ;


// qspi io
#define QSPI_CS { \
                         gpioc, \
		         gpio_t::mode_t::alternate_function, \
                         gpio_t::output_type_t::pull_push, \
		         gpio_t::output_speed_t::very_high, \
	                 gpio_t::pull_t::enum_t::no, \
		         (gpio_t::af_t::enum_t)gpioc_t::af_t::pin11_t::quadspi_bk2_ncs, \
		         gpio_t::i11, \
		         gpio_t::b11, \
		         gpio_t::output_t::enum_t::set, \
	      }

#define QSPI_CLK { \
                         gpiob, \
		         gpio_t::mode_t::alternate_function, \
                         gpio_t::output_type_t::pull_push, \
		         gpio_t::output_speed_t::very_high, \
	                 gpio_t::pull_t::enum_t::no, \
		         (gpio_t::af_t::enum_t)gpiob_t::af_t::pin2_t::quadspi_clk, \
		         gpio_t::i2, \
		         gpio_t::b2, \
		         gpio_t::output_t::enum_t::reset, \
	      }

#define QSPI_IO0 { \
                         gpioe, \
		         gpio_t::mode_t::alternate_function, \
                         gpio_t::output_type_t::pull_push, \
		         gpio_t::output_speed_t::very_high, \
	                 gpio_t::pull_t::enum_t::no, \
		         (gpio_t::af_t::enum_t)gpioe_t::af_t::pin7_t::quadspi_bk2_io0, \
		         gpio_t::i7, \
		         gpio_t::b7, \
		         gpio_t::output_t::enum_t::reset, \
	            }

#define QSPI_IO1    { \
                         gpioe, \
		         gpio_t::mode_t::alternate_function, \
                         gpio_t::output_type_t::pull_push, \
		         gpio_t::output_speed_t::very_high, \
	                 gpio_t::pull_t::enum_t::no, \
		         (gpio_t::af_t::enum_t)gpioe_t::af_t::pin8_t::quadspi_bk2_io1, \
		         gpio_t::i8, \
		         gpio_t::b8, \
		         gpio_t::output_t::enum_t::reset, \
	             }

#define QSPI_IO2_WP  { \
                         gpioe, \
		         gpio_t::mode_t::alternate_function, \
                         gpio_t::output_type_t::pull_push, \
		         gpio_t::output_speed_t::very_high, \
	                 gpio_t::pull_t::enum_t::up, \
		         (gpio_t::af_t::enum_t)gpioe_t::af_t::pin9_t::quadspi_bk2_io2, \
		         gpio_t::i9, \
		         gpio_t::b9, \
		         gpio_t::output_t::enum_t::reset, \
	            }

#define QSPI_IO3_HOLD { \
                         gpioe, \
		         gpio_t::mode_t::alternate_function, \
                         gpio_t::output_type_t::pull_push, \
		         gpio_t::output_speed_t::very_high, \
	                 gpio_t::pull_t::enum_t::up, \
		         (gpio_t::af_t::enum_t)gpioe_t::af_t::pin10_t::quadspi_bk2_io3, \
		         gpio_t::i10, \
		         gpio_t::b10, \
		         gpio_t::output_t::enum_t::reset, \
	            }

#define QSPI_CHIP      qspi_t::control_t::flash_memory_selection_t::enum_t::chip_2
#define QSPI_PRESCALER 4

#define USER_BUTTON { \
                         gpiod, \
		         gpio_t::mode_t::input, \
                         gpio_t::output_type_t::pull_push, \
		         gpio_t::output_speed_t::very_high, \
	                 gpio_t::pull_t::enum_t::down, \
		         (gpio_t::af_t::enum_t)0, \
		         gpio_t::i9, \
		         gpio_t::b9, \
		         gpio_t::output_t::enum_t::reset, \
	            }

#define FS_PRESETS_COUNT 49

#endif /* __PLATFORM_CONFIG_H */

