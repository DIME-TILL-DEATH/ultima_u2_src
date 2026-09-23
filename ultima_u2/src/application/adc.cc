/*
 * adc.cc
 *
 *  Created on: 7 января 2019 г.
 *      Author: klen
 */

#include "adc.h"
#include "gui.h"
#include "init.h"
#include "filt.h"

float maschtab = 1.0f/127.0f;

volatile uint16_t adc_val ;


uint16_t adc_get_val()
{
  return  adc_val ;
}
void adc_contr_init(void)
{
	syscfg.clock_enable();
	syscfg.exti0_pb();
	syscfg.exti1_pb();

	gpiob.clock_enable();
	gpiob.pin0_mode_input();
	gpiod.pin0_pull_up();
	gpiob.pin1_mode_input();
	gpiod.pin1_pull_up();
	exti.pin0_falling_trigger_enable();
	exti.pin1_falling_trigger_enable();
    adc.converter_1.eoc_interrupt_disable();
    adc.converter_1.power_off();
    nvic.exti0_priority(configMAX_SYSCALL_INTERRUPT_PRIORITY + 2);
    nvic.exti0_enable();
    nvic.exti1_priority(configMAX_SYSCALL_INTERRUPT_PRIORITY + 2);
    nvic.exti1_enable();
    gpioc.clock_enable();
    gpioc.pin5_set();
    gpioc.pin5_mode_output();
    gpioc.pin5_output_type_pull_push();
    gpioc.pin5_pull_no();
    gpioc.pin5_output_speed_high();
    gpioe.clock_enable();
    gpioe.pin11_set();
    gpioe.pin11_mode_output();
    gpioe.pin11_output_type_pull_push();
    gpioe.pin11_pull_no();
    gpioe.pin11_output_speed_high();
}
void adc_init (void)
{
    gpioc.clock_enable();
    gpioc.pin5_reset();
    gpioc.pin5_mode_output();
    gpioc.pin5_output_type_pull_push();
    gpioc.pin5_pull_no();
    gpioc.pin5_output_speed_high();
    gpioe.clock_enable();
    gpioe.pin11_reset();
    gpioe.pin11_mode_output();
    gpioe.pin11_output_type_pull_push();
    gpioe.pin11_pull_no();
    gpioe.pin11_output_speed_high();
	nvic.exti0_disable();
	nvic.exti1_disable();
    nvic.adc_enable();
    nvic.adc_priority(configMAX_SYSCALL_INTERRUPT_PRIORITY + 2);


    gpiob.clock_enable();
    gpiob.pin(  gpio_t::mode_t::pin0_t::analog  );

    gpiob.pin1_mode_output();
    gpiob.pin1_output_type_pull_push();
    gpiob.pin1_pull_no();
    gpiob.pin1_output_speed_very_high();
    gpiob.pin1_set();

    adc.converter_1.clock_enable();
    adc.reset();

    adc.converter_1.power_off();
    adc.converter_1.regular_sequence_1_converion_channel(8);
    adc.converter_1.regular_sequence_length(1);
    adc.converter_1.channel_8_sampling_time_cycles_480();
    adc.converter_1.scan_mode_enable();
    adc.converter_1.continuous_conversion_disable();
    adc.converter_1.eoc_interrupt_enable();
    adc.converter_1.power_on();
    adc.converter_1.conversion_regular_channels_start();
}

extern float p_vol;

float adc_delta;
uint16_t adc_buff[32];
volatile uint8_t adc_po;
volatile uint16_t adc_bu1[2];

uint16_t mediann( uint16_t* array, int length)  // массив и его длина
{
	uint16_t  slit = length/2;
	  for( uint16_t i=0; i < length; i++)
	  {
		uint16_t s1=0, s2=0;
	    uint16_t val = array[i];
	    for( int j=0; j < length; j++)
	    {
	    	if( array[j] < val)
	    	{
	    		if( ++s1 > slit) goto aaa;
	    	}
	    	else if( array[j] > val)
	    	{
	    		if( ++s2 > slit) goto aaa;
	    	}
	    }
	    return val;
aaa:;
	  }
	  return 0;  // чистая формальность, досюда исполнение никогда не доходит
}

void adc_proc(void)
{
	float temp = adc_val * 0.0078740157480315f;
	float temp_lo;
	float temp_hi;
	float temp1;
	for(uint8_t i = 0 ; i < 6 ; i++)
	{
		temp_lo = prog_data[ex_pr_lo + i * 2];
		temp_hi = prog_data[ex_pr_hi + i * 2];
		temp1 = (temp_lo + (temp_hi - temp_lo) * temp) * maschtab;
		switch(i){
		case 0:if(temp_lo || temp_hi)p_vol = (temp1 * temp1);break;
		case 1:if(temp_lo || temp_hi)pream_vol = (temp1 * temp1);break;
		case 2:if(temp_lo || temp_hi)od_volume = (temp1 * temp1);break;
		case 3:if(temp_lo || temp_hi)amp_vol = (temp1 * temp1) * 20.0f + 1.0f;break;
		case 4:if(temp_lo || temp_hi)amp_sla = amp_sla = (temp1*temp1*temp1*temp1) * 0.99f + 0.01f;break;
		case 5:if(temp_lo || temp_hi)set_shelf(temp1 * 31.0f);break;
		}
	}

}
volatile uint8_t adc_old;
extern uint8_t adcinv_fl;
extern uint16_t light_per_po;
IRQ_HANDLER(adc)
{
  adc.converter_1.regular_channel_eoc_clear();
  int16_t a = adc.converter_1.regular_data - system_file.exp_calib_lo;
  if(a < 0)a = 0;
  adc_val = a * adc_delta;
  if(adc_val > 127)adc_val = 127;
  if(adcinv_fl)adc_val = 127 - adc_val;
  adc_buff[adc_po++] = adc_val;
  if(adc_po == 32)adc_po = 0;
  adc_val = mediann(adc_buff,32);
  if(adc_val != adc_bu1[0])
  {
	  if((adc_val != adc_bu1[1]))
	  {
		  if(system_file.exp_On_Off && (adc_val != adc_old))
		  {
			  adc_proc();
			  adc_old = adc_val;
			  light_per_po = adc_val >> 1;
		  }
	  }
  }
  adc.converter_1.conversion_regular_channels_start();
}
IRQ_HANDLER(exti0)
{
	exti.pin0_pending_clear();
	tim14.disable();
	if(exti.pin0_falling_trigger())
	{
		if(tim14.update_interrupt_flag())
		{
			if(tap_fs_fl == 1 && prog_data[del_ex_tap] == 3)
			{
				if(tap_temp_global())
				{
					del_p1 = tap_global;
					del_param( 8 | prog_data[dp_d] << 8);
				}
			}
			else {
				f_sw_sel = 4;
				if(ext_fsw_b1)
				{
					ext_fsw_b1 = 0;
					gpioe.pin1_set();
					fs_but = 0;
					foot_sw_dub_short = 1;
				}
				else {
					ext_fsw_b1 = 1;
					gpioe.pin1_reset();
					fs_but = 1;
					foot_sw_dub_short = 1;
				}
			}
			exti.pin0_falling_trigger_disable();
			exti.pin0_rising_trigger_enable();
			gui_task->update();
		}
	}
	else {
		if(tim14.update_interrupt_flag())
		{
			exti.pin0_rising_trigger_disable();
			exti.pin0_falling_trigger_enable();
		}
	}
	tim14.update_interrupt_flag_clear();
    tim14.counter = 0;
    tim14.enable();
}
IRQ_HANDLER(exti1)
{
	exti.pin1_pending_clear();
	tim14.disable();
	if(exti.pin1_falling_trigger())
	{
		if(tim14.update_interrupt_flag())
		{
			if(tap_fs_fl == 1 && prog_data[del_ex_tap] == 4)
			{
				if(tap_temp_global())
				{
					del_p1 = tap_global;
					del_param( 8 | prog_data[dp_d] << 8);
				}
			}
			else {
				f_sw_sel = 5;
				if(ext_fsw_b2)
				{
					ext_fsw_b2 = 0;
					gpioe.pin0_set();
					fs_but = 0;
					foot_sw_dub_short = 1;
				}
				else {
					fs_but = 1;
					foot_sw_dub_short = 1;
					ext_fsw_b2 = 1;
					gpioe.pin0_reset();
				}
			}
			exti.pin1_falling_trigger_disable();
			exti.pin1_rising_trigger_enable();
			gui_task->update();
		}
	}
	else {
		if(tim14.update_interrupt_flag())
		{
			exti.pin1_rising_trigger_disable();
			exti.pin1_falling_trigger_enable();
		}
	}
	tim14.update_interrupt_flag_clear();
    tim14.counter = 0;
    tim14.enable();
}
