#include "led.h"
#include "stm32++.h"


static void led_timer_handler( TimerHandle_t pxTimer )
{
  const led_config_t& conf  = *(( led_config_t* ) pvTimerGetTimerID( pxTimer ));

  if ( conf.pin_config.port.output & _BV(conf.pin_config.pin) )
    {
      conf.pin_config.port.pin_reset(conf.pin_config.bit);

      if ( conf.coupled==led_config_t::coupled_t::gnd )
	{
          xTimerChangePeriod( pxTimer, conf.low_ticks, 0 ) ;
          if ( conf.user_handler_high ) conf.user_handler_high(conf) ;
	}
      else
	{
	  xTimerChangePeriod( pxTimer, conf.hight_ticks, 0 ) ;
	  if ( conf.user_handler_low ) conf.user_handler_low(conf) ;
	}


    }
  else
    {
      conf.pin_config.port.pin_set(conf.pin_config.bit);

      if ( conf.coupled==led_config_t::coupled_t::gnd )
      	{
	  xTimerChangePeriod( pxTimer, conf.hight_ticks, 0 ) ;
	  if ( conf.user_handler_low ) conf.user_handler_low(conf) ;
      	}
      else
      	{
          xTimerChangePeriod( pxTimer, conf.low_ticks, 0 ) ;
          if ( conf.user_handler_high ) conf.user_handler_high(conf) ;
      	}
    }
}


static led_config_t led_config[LED_COUNT] = LED_DESC ;


void led_set_on_ticks(size_t index, size_t val)
{
  nop_rep(10);
  if (led_config[index].coupled == led_config_t::coupled_t::gnd)
    led_config[index].hight_ticks = val ;
  else
    led_config[index].low_ticks = val ;
}

void led_set_off_ticks(size_t index, size_t val)
{
  if (led_config[index].coupled == led_config_t::coupled_t::gnd)
    led_config[index].low_ticks = val ;
  else
    led_config[index].hight_ticks = val ;
}

size_t led_get_on_ticks(size_t index)
{
  if (led_config[index].coupled == led_config_t::coupled_t::gnd)
    return led_config[index].hight_ticks ;
  else
    return led_config[index].low_ticks ;
}

size_t led_get_off_ticks(size_t index)
{
  if (led_config[index].coupled == led_config_t::coupled_t::gnd)
    return led_config[index].low_ticks ;
  else
    return led_config[index].hight_ticks ;
}

void led_init()
{
    for (size_t index = 0 ; index < LED_COUNT ; index++)
      {
	 gpio_t::pin_configure( led_config[index].pin_config ) ;

	 led_config[index].timer = xTimerCreate  ( ( const char *) "led_tim", led_config[index].hight_ticks , pdTRUE, (void*) &led_config[index] , led_config[index].fnc  );
         if (led_config[index].active)
        	 xTimerStart( led_config[index].timer, 0 ) ;
      }
}

bool led_timer_state(size_t index)
{
  if ( index >= LED_COUNT )
        __throw_invalid_argument("invalid led index") ;
  return  xTimerIsTimerActive( led_config[index].timer ) ;
}

void led_timer_state(const size_t index, const bool val)
{
  if ( index >= LED_COUNT )
          __throw_invalid_argument("invalid led index") ;
  val ? xTimerStart( led_config[index].timer, 0 ) : xTimerStop( led_config[index].timer, 0 ) ;
}

void led_state(const size_t index, const bool val)
{
  if ( index >= LED_COUNT )
            __throw_invalid_argument("invalid led index") ;

  (led_config[index].coupled==led_config_t::coupled_t::gnd ? val : !val) ?
      led_config[index].pin_config.port.pin_set  (led_config[index].pin_config.pin) :
      led_config[index].pin_config.port.pin_reset(led_config[index].pin_config.pin) ;

}

bool led_state(size_t index)
{
  if ( index >= LED_COUNT )
              __throw_invalid_argument("invalid led index") ;

  bool led_state = led_config[index].pin_config.port.output & _BV(led_config[index].pin_config.pin) ? true : false ;
  return led_config[index].coupled==led_config_t::coupled_t::gnd ? led_state : !led_state ;
}


void led_user_handler_high( size_t index, led_user_handler_t handler )
{
  if ( index >= LED_COUNT )
                __throw_invalid_argument("invalid led index") ;
  led_config[index].user_handler_high = handler ;
}
void led_user_handler_low( size_t index, led_user_handler_t handler )
{
  if ( index >= LED_COUNT )
                __throw_invalid_argument("invalid led index") ;
  led_config[index].user_handler_low = handler ;
}
