#ifndef __LED_H__
#define __LED_H__

#include "sdk.h"

struct led_config_t ;
typedef void (*led_user_handler_t)(const led_config_t& conf) ;

struct led_config_t
{
  enum coupled_t { gnd = 0 , vdd } ;

  const gpio_t::pin_config_t pin_config ;
  const coupled_t coupled ;
  TickType_t hight_ticks  ;
  TickType_t low_ticks ;
  bool active ;

  TimerCallbackFunction_t fnc ;
  TimerHandle_t timer ;
  led_user_handler_t user_handler_high ;
  led_user_handler_t user_handler_low ;
}  ;


void led_init();
bool led_timer_state(size_t index);
void led_timer_state(size_t index, bool val);

void led_set_on_ticks(size_t index, size_t val);
void led_set_off_ticks(size_t index, size_t val);

size_t led_get_on_ticks(size_t index);
size_t led_get_off_ticks(size_t index);

void led_state(size_t index, bool val);
bool led_state(size_t index) ;

inline void led_state_on(size_t index) {led_state(index,true);}
inline void led_state_off(size_t index) {led_state(index,false);}

void led_user_handler_low( size_t index, led_user_handler_t handler ) ;
void led_user_handler_high( size_t index, led_user_handler_t handler ) ;

#if 0
template <typename module_rcc_T , typename module_gpio_t, typename module_pin_T, uint32_t on, uint32_t off  >
class led_t
{
   public:
      inline led_t() {}
      inline ~led_t() {}

      inline void init()
        {
          //rcc.state_enable</*rcc_t::ahb1_peripheral_clock_t::gpiob_state_t*/module_rcc_T>() ;

	 /* led_gpio_conf[index].port.mode.output( led_gpio_conf[index].gpio);
		 led_gpio_conf[index].port.output_type.bit( led_gpio_conf[index].gpio, led_gpio_conf[index].otype );
		 led_gpio_conf[index].port.output_speed.low(led_gpio_conf[index].gpio);


	         // default led config
	         led_set_on_ticks(index, led_gpio_conf[index].on) ;
	         led_set_off_ticks(index, led_gpio_conf[index].off) ;

	         led_conf[index].fnc = led_timer_handler ;
	         led_conf[index].led_gpio_conf = &led_gpio_conf[index] ;

	         led_conf[index].timer = xTimerCreate  ( ( const char * const) "led_tim", led_conf[index].hight_ticks , pdTRUE, (void*) &led_conf[index] , led_conf[index].fnc  );

	         if (led_gpio_conf[index].active)
	        	 xTimerStart( led_conf[index].timer, 0 ) ;*/
        }

   protected:
   private:

      static void timer_handler( TimerHandle_t pxTimer )
      {
        /*const led_config_t* conf = ( led_config_t* ) pvTimerGetTimerID( pxTimer );
        if ( conf->led_gpio_conf->port.output.bit(conf->led_gpio_conf->gpio))
          {
            conf->led_gpio_conf->port.set_reset.clear(conf->led_gpio_conf->gpio);
            xTimerChangePeriod( pxTimer, conf->low_ticks, 0 ) ;
          }
        else
          {
            conf->led_gpio_conf->port.set_reset.set(conf->led_gpio_conf->gpio);
            xTimerChangePeriod( pxTimer, conf->hight_ticks, 0 ) ;
          }*/
      }

};
#endif
#endif /*__LED_H__*/
