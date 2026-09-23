/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PLATFORM_CONFIG_H
#define __PLATFORM_CONFIG_H

#define LED_COUNT 3
#define LED_RED {  gpiob, \
		 gpio_t::mode_t::output, \
                 gpio_t::output_type_t::pull_push, \
		 gpio_t::output_speed_t::very_high, \
	         gpio_t::pull_t::enum_t::no, \
		 (gpio_t::af_t::enum_t)0, \
		 gpio_t::i14, \
		 gpio_t::b14, \
		 gpio_t::output_t::enum_t::reset, \
	      }

#define LED_BLUE {  gpiob, \
		 gpio_t::mode_t::output, \
                 gpio_t::output_type_t::pull_push, \
		 gpio_t::output_speed_t::very_high, \
	         gpio_t::pull_t::enum_t::no, \
		 (gpio_t::af_t::enum_t)0, \
		 gpio_t::i7, \
		 gpio_t::b7, \
		 gpio_t::output_t::enum_t::reset, \
	      }

#define LED_GREEN {  gpiob, \
		 gpio_t::mode_t::output, \
                 gpio_t::output_type_t::pull_push, \
		 gpio_t::output_speed_t::very_high, \
	         gpio_t::pull_t::enum_t::no, \
		 (gpio_t::af_t::enum_t)0, \
		 gpio_t::i0, \
		 gpio_t::b0, \
		 gpio_t::output_t::enum_t::reset, \
	      }

#define LED_DESC  {{ LED_RED,   led_config_t::vdd, 10, 990, false, led_timer_handler, 0, 0, 0},\
                   { LED_BLUE,  led_config_t::vdd, 10, 990, false, led_timer_handler, 0, 0, 0},\
                   { LED_GREEN, led_config_t::vdd, 10, 990, false, led_timer_handler, 0, 0, 0}}

#define ENCODER_BUTTON {  gpiod, \
		 gpio_t::mode_t::input, \
                 gpio_t::output_type_t::pull_push, \
		         gpio_t::output_speed_t::low, \
	              gpio_t::pull_t::enum_t::no, \
		        (gpio_t::af_t::enum_t)0, \
		 gpio_t::i11, \
		 gpio_t::b11, \
		 gpio_t::output_t::enum_t::reset, \
	      }


#define      DEBUG_OUT_PORT  GPIOC
#define      DEBUG_OUT_RCC   RCC_GPIOC
#define      DEBUG_OUT_PIN   GPIO14

#define      SD_DETECT_PORT  GPIOA
#define      SD_DETECT_RCC   RCC_GPIOA
#define      SD_DETECT_PIN   GPIO8

#define      SD_CMD_PORT     GPIOD
#define      SD_CMD_RCC      RCC_GPIOD
#define      SD_CMD_PIN      GPIO2


#define      SD_DATA_PORT    GPIOC
#define      SD_DATA_RCC     RCC_GPIOC
#define      SD_D0_PIN       GPIO8
#define      SD_D1_PIN       GPIO9
#define      SD_D2_PIN       GPIO10
#define      SD_D3_PIN       GPIO11
#define      SD_CLK_PIN      GPIO12
#define      SD_DATA_PINS    SD_D0_PIN | SD_D1_PIN | SD_D2_PIN | SD_D3_PIN

const char fw_name[] = "0:firmware" ;
const uint32_t header_offset = 0x40000 ;
const uint32_t header_flash_sector = 5 ;
const uint32_t app_offset =    0x80000 ;
const uint32_t app_flash_sector =  6 ;

#define SD_MULTIPLAYER_AES128_CRYPT_KEY "y0ßhÏU ¹Ìjµ&¢z"
#define SD_MULTIPLAYER_AES128_CRYPT_IV  "r^ÃV·Ú¯Ô1"

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

#define BOOT_LOADER_VER_STR "   AMT bootloader ver0.2.0 "

#endif /* __PLATFORM_CONFIG_H */

