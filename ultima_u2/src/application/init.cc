#include "appdefs.h"
#include "init.h"
#include "gui.h"
#include "fs_browser.h"
#include "msc.h"
#include "allFonts.h"
#include "SN1106.h"
#include "arm_math.h"
#include "adc.h"
#include "Gate.h"
#include "distor.h"
#include "phaser.h"
#include "flanger.h"

__attribute__((section(".dtcm_data"))) ad_data_t adc_data[block_samples * 2];
__attribute__((section(".dtcm_data"))) da_data_t dac_data[block_samples * 2];
__attribute__((section(".itcm_data"))) float phas[14];
__attribute__((section(".itcm_data"))) float memflan[2048];

const int8_t def_expander[] = { -90, 1, 1, 10 };

float pow_temp = 1.0f / (127.0f * 127.0f);
float a_a = -0.5f;
float b_b = 0.5f;
float k1;
float k2;
float k3;
float k4;
uint8_t fs_but_fl;
uint8_t fs_but_fl1;
uint8_t tim2_start = 0;
uint8_t encoder_but_fl = 0;
uint8_t enc_but_fl = 0;
uint8_t foot_sw_fl = 0;
uint8_t foot_but_fl = 0;
uint8_t tap_fs_fl = 0;
uint8_t tap_ext_fl = 0;
uint8_t int_fsw_a1 = 0;
uint8_t ext_fsw_a1 = 0;
uint8_t ext_fsw_a2 = 0;
uint8_t ext_fsw_b1 = 0;
uint8_t ext_fsw_b2 = 0;
uint8_t start_fl = 0;

arm_fir_instance_f32 cab_inst;
arm_fir_instance_f32 amp_inst;
arm_biquad_casd_df1_inst_f32 eq_instance;
arm_biquad_casd_df1_inst_f32 presen_instance;
arm_biquad_casd_df1_inst_f32 preamp_instance;
float coef_cab[num_tab_cab];
float state_cab[num_tab_cab + block_samples - 1];
float coef_amp[num_tab_amp];
float state_amp[num_tab_amp + block_samples - 1];
float coeff_eq[eq_stage * 5];
float stage_eq[eq_stage * 4];
float coeff_presen[presen_stage * 5];
float stage_presen[presen_stage * 4];
float coeff_preamp[preamp_stage * 5];
float stage_preamp[preamp_stage * 4];

void init_ext_fs(void)
{
	if(system_file.fs_inver < 2 || system_file.fs_inver > 2)
	{
		syscfg.exti12_pb();

		gpiob.clock_enable();
		gpiob.pin12_mode_input();
		gpiob.pin12_pull_no();
		exti.pin12_falling_trigger_enable();
		exti.pin12_rising_trigger_enable();
		exti.pin10_falling_trigger_enable();
		exti.pin10_rising_trigger_enable();
	}
	else
	{
		exti.pin12_falling_trigger_disable();
		exti.pin12_rising_trigger_disable();
		exti.pin10_falling_trigger_disable();
		exti.pin10_rising_trigger_disable();

		gpiob.pin12_mode_alternate_function();
		gpiob.pin12_output_type_pull_push();
		gpiob.pin12_pull_no();
		gpiob.pin12_output_speed_very_high();
		gpiob.pin12_af_uart5_rx();
		gpiob.pin13_mode_alternate_function();
		gpiob.pin13_output_type_pull_push();
		gpiob.pin13_pull_no();
		gpiob.pin13_output_speed_very_high();
		gpiob.pin13_af_uart5_tx();
	}
}
const uint8_t exp_init[4] =
{ 100, 0, 5, 10 };
void init(void)
{

	arm_fir_init_f32(&cab_inst, num_tab_cab, coef_cab, state_cab, block_samples);
	arm_fir_init_f32(&amp_inst, num_tab_amp, coef_amp, state_amp, block_samples);
	arm_biquad_cascade_df1_init_f32(&eq_instance, eq_stage, coeff_eq, stage_eq);
	arm_biquad_cascade_df1_init_f32(&presen_instance, presen_stage, coeff_presen, stage_presen);
	arm_biquad_cascade_df1_init_f32(&preamp_instance, preamp_stage, coeff_preamp, stage_preamp);
//-----------------------------------------------config pins SAI1-----------------------
	gpioe.clock_enable();
	gpioe.pin2_mode_alternate_function();
	gpioe.pin2_output_type_pull_push();
	gpioe.pin2_pull_no();
	gpioe.pin2_output_speed_very_high();
	gpioe.pin2_af_sai1_mclk_a();

	gpioe.pin3_mode_alternate_function();
	gpioe.pin3_output_type_pull_push();
	gpioe.pin3_pull_no();
	gpioe.pin3_output_speed_very_high();
	gpioe.pin3_af_sai1_sd_b();

	gpioe.pin4_mode_alternate_function();
	gpioe.pin4_output_type_pull_push();
	gpioe.pin4_pull_no();
	gpioe.pin4_output_speed_very_high();
	gpioe.pin4_af_sai1_fs_a();

	gpioe.pin5_mode_alternate_function();
	gpioe.pin5_output_type_pull_push();
	gpioe.pin5_pull_no();
	gpioe.pin5_output_speed_very_high();
	gpioe.pin5_af_sai1_sck_a();

	gpioe.pin6_mode_alternate_function();
	gpioe.pin6_output_type_pull_push();
	gpioe.pin6_pull_no();
	gpioe.pin6_output_speed_very_high();
	gpioe.pin6_af_sai1_sd_a();
//----------------------------------------------------LEDS-----------------------------------------
	gpioa.clock_enable();
	gpioa.pin0_set();
	gpioa.pin0_mode_output();
	gpioa.pin0_output_type_open_drain();
	gpioa.pin0_pull_no();
	gpioa.pin0_output_speed_very_high();

	gpioa.pin1_set();
	gpioa.pin1_mode_output();
	gpioa.pin1_output_type_open_drain();
	gpioa.pin1_pull_no();
	gpioa.pin1_output_speed_very_high();

	gpioe.pin0_set();
	gpioe.pin0_mode_output();
	gpioe.pin0_output_type_open_drain();
	gpioe.pin0_pull_no();
	gpioe.pin0_output_speed_very_high();

	gpioe.pin1_set();
	gpioe.pin1_mode_output();
	gpioe.pin1_output_type_open_drain();
	gpioe.pin1_pull_no();
	gpioe.pin1_output_speed_very_high();

//  gpiod.pin4_mode_output();
//  gpiod.pin4_output_type_pull_push();
//  gpiod.pin4_pull_no();
//  gpiod.pin4_output_speed_very_high();

	gpiob.clock_enable();
//  gpiob.pin7_mode_output();
//  gpiob.pin7_output_type_pull_push();
//  gpiob.pin7_pull_no();
//  gpiob.pin7_output_speed_high();
//-------------------------------------------------conf pins codec SPI6--------------------------
	gpiob.pin3_mode_alternate_function();
	gpiob.pin3_output_type_pull_push();
	gpiob.pin3_pull_no();
	gpiob.pin3_output_speed_very_high();
	gpiob.pin3_af_spi6_sck();

	gpiob.pin5_mode_alternate_function();
	gpiob.pin5_output_type_pull_push();
	gpiob.pin5_pull_no();
	gpiob.pin5_output_speed_very_high();
	gpiob.pin5_af_spi6_mosi();

	gpioa.pin4_set();
	gpioa.pin4_mode_output();
	gpioa.pin4_output_type_pull_push();
	gpioa.pin4_pull_no();
	gpioa.pin4_output_speed_very_high();                        // Codec CS*/
//------------------------------------------------------------------------------------------
	gpiod.clock_enable();
	gpiod.pin7_reset();                // codec PDN
	gpiod.pin7_mode_output();
	gpiod.pin7_output_type_pull_push();
	gpiod.pin7_pull_no();
	gpiod.pin7_output_speed_high();

	gpioc.clock_enable();
	gpioc.pin14_set();                 // Bypass L Mute
	gpioc.pin14_mode_output();
	gpioc.pin14_output_type_open_drain();
	gpioc.pin14_pull_up();
	gpioc.pin14_output_speed_high();

	gpioc.pin15_mode_output();
	gpioc.pin15_set();                // Bypass R Mute
	gpioc.pin15_output_type_open_drain();
	gpioc.pin15_pull_up();
	gpioc.pin15_output_speed_high();

	gpioc.pin13_mode_output();
	gpioc.pin13_set();                // eff swith
	gpioc.pin13_output_type_open_drain();
	gpioc.pin13_pull_no();
	gpioc.pin13_output_speed_high();

	gpioc.pin2_reset();                 // OwerDrive mute
	gpioc.pin2_mode_output();
	gpioc.pin2_output_type_pull_push();
	gpioc.pin2_pull_no();
	gpioc.pin2_output_speed_high();

	gpioc.pin3_reset();                 // OwerDrive type
	gpioc.pin3_mode_output();
	gpioc.pin3_output_type_pull_push();
	gpioc.pin3_pull_no();
	gpioc.pin3_output_speed_high();

	//------------------------------------------------------------display pins init----------------------------------
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

	gpioa.pin15_mode_output();
	gpioa.pin15_output_type_pull_push();
	gpioa.pin15_pull_no();
	gpioa.pin15_output_speed_high();
	gpioa.pin15_set();                            // display CS

	gpiod.pin5_mode_output();
	gpiod.pin5_output_type_pull_push();
	gpiod.pin5_pull_no();
	gpiod.pin5_output_speed_high();
	gpiod.pin5_reset();                          // display Reset

	gpiod.pin6_mode_output();
	gpiod.pin6_output_type_pull_push();
	gpiod.pin6_pull_no();
	gpiod.pin6_output_speed_high();
	gpiod.pin6_reset();                         // display DC

	gpiod.pin13_mode_output();
	gpiod.pin13_output_type_open_drain();
	gpiod.pin13_pull_no();
	gpiod.pin13_output_speed_high();            // TAP LED
//-------------------------------------------------------------------SAI1 init----------------------------------

	rcc.pll_sai_on();
	rcc.pll_sai_q();
	rcc.pll_sai_q_div1();
	rcc.sai1_clock_selection_pllsai();
	rcc.pll_sai_config.write(0x24003100);

	sai1.clock_enable();
	sai1.block_a.data_size_bits32();
	sai1.block_a.output_drive_when_sai_enable();
	sai1.block_a.clock_strobing_edge_fall();
	sai1.block_a.master_clock_divider_div4();
	sai1.block_a.master_clock_divider_state_enable();
	sai1.block_a.frame_configuration.write(0x51f3f);
	sai1.block_a.slots.write(0xffff0180);
	sai1.block_a.mode_master_tx();
	sai1.block_a.synchronization_async();
	sai1.block_a.state_disable();
	sai1.block_a.state_enable();
	sai1.block_a.dma_enable();

	sai1.block_b.data_size_bits32();
	sai1.block_b.output_drive_when_sai_enable();
	sai1.block_b.clock_strobing_edge_fall();
	sai1.block_b.master_clock_divider_div4();
	sai1.block_b.frame_configuration.write(0x51f3f);
	sai1.block_b.slots.write(0xffff0180);
	sai1.block_b.mode_slave_rx();
	sai1.block_b.synchronization_internal_audio();
	sai1.block_b.state_disable();
	sai1.block_b.state_enable();
	sai1.block_b.dma_enable();

	//ind_clean = 1;
	dma2.clock_enable();

	dma2_stream5.channel_sai1_b();
	dma2_stream5.number_of_data = block_samples * 4;
	dma2_stream5.peripheral_address = ((uint32_t) &sai1.block_b.data);
	dma2_stream5.memory0_address = ((uint32_t) adc_data);
	dma2_stream5.direction_peripheral_to_memory();
	dma2_stream5.peripheral_increment_mode_disable();
	dma2_stream5.memory_increment_mode_enable();
	dma2_stream5.peripheral_data_size_word();
	dma2_stream5.memory_data_size_word();
	dma2_stream5.circular_mode_enable();
	dma2_stream5.disable();
	dma2_stream5.enable();
	dma2_stream5.half_transfer_interrupt_enable();
	dma2_stream5.transfer_complete_interrupt_enable();
	nvic.dma2_stream5_priority(configMAX_SYSCALL_INTERRUPT_PRIORITY);
	nvic.dma2_stream5_enable();

	dma2_stream1.channel_sai1_a();
	dma2_stream1.number_of_data = block_samples * 4;
	dma2_stream1.peripheral_address = ((uint32_t) &sai1.block_a.data);
	dma2_stream1.memory0_address = ((uint32_t) dac_data);
	dma2_stream1.direction_memory_to_peripheral();
	dma2_stream1.peripheral_increment_mode_disable();
	dma2_stream1.memory_increment_mode_enable();
	dma2_stream1.peripheral_data_size_word();
	dma2_stream1.memory_data_size_word();
	dma2_stream1.circular_mode_enable();
	dma2_stream1.disable();
	dma2_stream1.enable();

//-------------------------------------------------------------conf codec SPI6-----------------------------------------
	spi6.clock_enable();
	spi6.reset();
	spi6.boud_rate_fpclk_div_128();
	spi6.clock_polarity_hight();
	spi6.clock_phase_second_clock();
	spi6.frame_first_msb();
	spi6.mode_selection_master();
	spi6.fifo_reception_threshold_1div4();
	spi6.data_size_16_bits();
	spi6.ss_output_enable();
	spi6.nss_pulse_management_enable();
	spi6.crc_polynomial = 7;
	spi6.enable();
//-------------------------------------------------------------config display SPI3--------------------------------------
	spi3.clock_enable();
	spi3.reset();
	spi3.boud_rate_fpclk_div_16();
	spi3.clock_polarity_hight();
	spi3.clock_phase_second_clock();
	spi3.frame_first_msb();
	spi3.mode_selection_master();
	spi3.fifo_reception_threshold_1div4();
	spi3.data_size_8_bits();
	spi3.ss_output_enable();
	spi3.nss_pulse_management_enable();
	spi3.crc_polynomial = 7;
	spi3.enable();
//------------------------------------------------------------config timers---------------------------------------
	tim4.clock_enable();
	tim4.auto_reload_preload_enable();
	tim4.update_interrupt_enable();
	tim4.auto_reload = 0xffff;
	tim4.prescaler = 0x200;
	tim4.enable();

	tim6.clock_enable();
	tim6.one_pulse_mode_enable();
	tim6.update_interrupt_enable();
	tim6.auto_reload_preload_enable();
	tim6.auto_reload = 0xffff;
	tim6.prescaler = 0xff;
	tim6.counter = 0;
	tim6.update_interrupt_flag_clear();
	tim6.enable();

	tim2.clock_enable();
	tim2.one_pulse_mode_enable();
	tim2.auto_reload_preload_enable();
	tim2.update_interrupt_enable();
	tim2.auto_reload = 0xffff;
	tim2.counter = 0xfffffff0;
	tim2.prescaler = 0x200;

	tim9.clock_enable();
	tim9.one_pulse_mode_enable();
	tim9.update_interrupt_enable();
	tim9.auto_reload_preload_enable();
	tim9.auto_reload = 0xffff;
	tim9.prescaler = 0x500;
	tim9.counter = 0;
	tim9.update_interrupt_flag_clear();
	tim9.enable();
//------------------------------------------------------------contpol init-----------------------------------------
	syscfg.clock_enable();
	syscfg.exti8_pd();
	syscfg.exti11_pd();
	syscfg.exti10_pb();
	syscfg.exti7_pa();

	gpiod.clock_enable();
	gpiod.pin11_mode_input();
	gpiod.pin11_pull_up();
	exti.pin11_falling_trigger_enable();

	gpiod.clock_enable();
	gpiod.pin8_mode_input();
	gpiod.pin8_pull_up();
	exti.pin8_falling_trigger_enable();

	gpioa.clock_enable();
	gpioa.pin7_mode_input();
	gpioa.pin7_pull_up();
	exti.pin7_falling_trigger_enable();

	gpioa.pin3_mode_input();
	gpioa.pin3_pull_no();

	gpiob.clock_enable();
	gpiob.pin10_mode_input();
	gpiob.pin10_pull_no();
	exti.pin10_falling_trigger_enable();

	gpioc.clock_enable();
	gpioc.pin6_mode_alternate_function();
	gpioc.pin6_pull_up();
	gpioc.pin6_af_tim3_ch1();

	gpioc.pin7_mode_alternate_function();
	gpioc.pin7_pull_up();
	gpioc.pin7_af_tim3_ch2();

	tim3.clock_enable();
	tim3.cc1_selection_inpit_capture_internal_trigger_1();
	tim3.ic1_filter_fck_n8();
	tim3.cc2_selection_inpit_capture_internal_trigger_2();
	tim3.ic2_filter_fck_n8();
	tim3.slave_mode_encoder_mode_3();
	tim3.auto_reload = 0xffff;
	tim3.update_event_enable();
	tim3.cc1_enable();
	tim3.cc2_enable();
	tim3.cc1_interrupt_enable();
	tim3.enable();

	tim10.clock_enable();
	tim10.one_pulse_mode_enable();
	tim10.auto_reload_preload_enable();
	tim10.update_interrupt_enable();
	tim10.auto_reload = 0xffff;
	tim10.prescaler = 0x7f;
	tim10.enable();

	tim11.clock_enable();
	tim11.one_pulse_mode_enable();
	tim11.auto_reload_preload_enable();
	tim11.update_interrupt_enable();
	tim11.auto_reload = 0xffff;
	tim11.prescaler = 0x7f;
	tim11.enable();

	tim13.clock_enable();
	tim13.one_pulse_mode_enable();
	tim13.auto_reload_preload_enable();
	tim13.update_interrupt_enable();
	tim13.auto_reload = 0xffff;
	tim13.prescaler = 0x7f;
	tim13.enable();

	tim14.clock_enable();
	tim14.one_pulse_mode_enable();
	tim14.auto_reload_preload_enable();
	tim14.update_interrupt_enable();
	tim14.auto_reload = 0xffff;
	tim14.prescaler = 0x7f;
	tim14.enable();

	tim2.clock_enable();
	tim2.one_pulse_mode_enable();
	tim2.auto_reload_preload_enable();
	tim2.update_interrupt_enable();
	tim2.auto_reload = 0xffff;
	tim2.counter = 0xfffffff0;
	tim2.prescaler = 0x400;
//-------------------------------------------------------USART------------------------------------------------
	uart5.clock_enable();
	uart5.receiver_enable();
	uart5.transmitter_enable();
	uart5.baud_rate.write(rcc.apb1_clock_freq() / 31250);
	uart5.enable();
	uart5.rx_not_empty_interupt_enable();
//------------------------------------------------------------init codec-------------------------------------------
	prog_data[fx_type] = 1;
	prog_data[er_on] = 1;
	prog_data[od_on] = 1;

	m_vol_fl = 1;
	while(m_vol_fl != 2)
		;
	proc_run = 0;

	nop_while(0xffff);
	gpiod.pin7_set();
	nop_while(0xff);

	const uint16_t fff[4] =
	{ 0xa007, 0xa103, 0xa265, 0xa82f };
	for(int i = 0;i < 4;i++)
	{
		gpioa.pin4_reset();
		spi6.wait_tx_empty();
		spi6.half_data = fff[i];
		spi6.wait_not_busy();
		gpioa.pin4_set();
		nop_while(0xff);
	}
	nop_while(0xfff);
//------------------------------------------------------------unused pin--------------------------------------------
	select_unused_pin(0);
//------------------------------------------------------------init display-------------------------------------------
	void disp_init(void);
	disp_init();

}
void start_irq(void)
{
	nvic.tim2_priority(configMAX_SYSCALL_INTERRUPT_PRIORITY + 2);
	nvic.tim2_enable();
	tim2.enable();
	nvic.tim4_priority(configMAX_SYSCALL_INTERRUPT_PRIORITY + 2);
	nvic.tim4_enable();
	nvic.tim3_priority(configMAX_SYSCALL_INTERRUPT_PRIORITY + 2);
	nvic.tim3_enable();
	exti.pin11_interrupt_unmasked();
	exti.pin12_interrupt_unmasked();
	exti.pin10_interrupt_unmasked();
	exti.pin8_interrupt_unmasked();
	exti.pin7_interrupt_unmasked();
	exti.pin0_interrupt_unmasked();
	exti.pin1_interrupt_unmasked();
	nvic.exti15_10_priority(configMAX_SYSCALL_INTERRUPT_PRIORITY);
	nvic.exti15_10_enable();
	nvic.uart5_priority(configMAX_SYSCALL_INTERRUPT_PRIORITY + 2);
	nvic.uart5_enable();
}
IRQ_HANDLER(tim3)
{
	tim3.cc1_interrupt_flag_clear();
	encoder_fl1 = 1;
	if(tim3.direction())
		encoder_fl = 2;
	else
		encoder_fl = 1;
	gui_task->update();
}
IRQ_HANDLER(exti9_5)
{
	if(exti.pin9_pending())
	{
		exti.pin9_pending_clear();
		m_vol_fl = 1;
		fs_browser_task->stop();
		msc_task->start();
	}
	if(exti.pin7_pending())
	{
		exti.pin7_pending_clear();
		tim11.disable();
		if(exti.pin7_falling_trigger())
		{
			if(tim11.update_interrupt_flag())
			{
				foot_sw_fl = 1;
				tim2.counter = 0;
				tim2.enable();
				exti.pin7_falling_trigger_disable();
				exti.pin7_rising_trigger_enable();
			}
		}
		else
		{
			if(tim11.update_interrupt_flag())
			{
				tim2.disable();
				tim2.update_interrupt_flag_clear();
				foot_sw_fl = 0;
				if(foot_but_fl)
				{
					foot_but_fl = 0;
				}
				else
				{
					if(tap_fs_fl && prog_data[ifs_type] == 1)
					{
						if(tap_temp_global())
						{
							del_p1 = tap_global;
							del_param(8 | prog_data[dp_d] << 8);
						}
					}
					else
					{
						if(prog_data[ifs_type] != 3)
						{
							if(int_fsw_a1)
							{
								int_fsw_a1 = 0;
								fs_but = 0;
								f_sw_sel = 1;
								gpioc.pin13_set();
								foot_sw_dub_short = 1;
								gui_task->update();
							}
							else
							{
								int_fsw_a1 = 1;
								fs_but = 1;
								f_sw_sel = 1;
								gpioc.pin13_reset();
								foot_sw_dub_short = 1;
								gui_task->update();
							}
						}
					}
				}
				exti.pin7_rising_trigger_disable();
				exti.pin7_falling_trigger_enable();
			}
		}
		tim11.update_interrupt_flag_clear();
		tim11.counter = 0;
		tim11.enable();
	}
	if(exti.pin8_pending())
	{
		exti.pin8_pending_clear();
		tim14.disable();
		if(exti.pin8_falling_trigger())
		{
			if(tim14.update_interrupt_flag())
			{
				if(edit_but)
					edit_but = 0;
				else
					edit_but = 1;
				exti.pin8_falling_trigger_disable();
				exti.pin8_rising_trigger_enable();
				gui_task->update();
			}
		}
		else
		{
			if(tim14.update_interrupt_flag())
			{
				exti.pin8_rising_trigger_disable();
				exti.pin8_falling_trigger_enable();
			}
		}
		tim14.update_interrupt_flag_clear();
		tim14.counter = 0;
		tim14.enable();
	}
}
IRQ_HANDLER(exti15_10)
{
	if(exti.pin11_pending())
	{
		exti.pin11_pending_clear();
		tim13.disable();
		if(exti.pin11_falling_trigger())
		{
			if(tim13.update_interrupt_flag())
			{
				encoder_but = 1;
				enc_but_fl = 1;
				exti.pin11_falling_trigger_disable();
				exti.pin11_rising_trigger_enable();
				gui_task->update();
				tim2.counter = 0;
				tim2.enable();
			}
		}
		else
		{
			if(tim13.update_interrupt_flag())
			{
				tim2.disable();
				tim2.update_interrupt_flag_clear();
				enc_but_fl = 0;
				if(encoder_but_fl)
					encoder_but_fl = 0;
				else
				{
					encoder_but_dub_short = 1;
					tim2.disable();
					gui_task->update();
				}
				exti.pin11_rising_trigger_disable();
				exti.pin11_falling_trigger_enable();
			}
		}
		tim13.update_interrupt_flag_clear();
		tim13.counter = 0;
		tim13.enable();
	}
	if(exti.pin10_pending())
	{
		exti.pin10_pending_clear();
		tim10.disable();
		if(exti.pin10_falling_trigger())
		{
			if(tim10.update_interrupt_flag())
			{
				if(system_file.fs_inver == 3)
				{
					if(condish == start_screen)
					{
						m_vol_fl = 1;
						prog1 = prog_old;
						encoder_but = 1;
						gui_task->update();
					}
				}
				else
				{
					fs_but_fl = 1;
					tim2.counter = 0;
					tim2.enable();
				}
				exti.pin10_falling_trigger_disable();
				exti.pin10_rising_trigger_enable();
			}
		}
		else
		{
			if(tim10.update_interrupt_flag())
			{
				tim2.disable();
				tim2.update_interrupt_flag_clear();
				if(tap_ext_fl && prog_data[del_ex_tap] == 2)
				{
					if(tap_temp_global())
					{
						del_p1 = tap_global;
						del_param(8 | prog_data[dp_d] << 8);
					}
				}
				else
				{
					if(system_file.fs_inver != 3)
					{
						fs_but_fl = 0;
						if(fs_but_fl1)
							fs_but_fl1 = 0;
						else
						{
							if(system_file.fs_inver != 4)
							{
								if(condish == start_screen)
								{
									encoder_fl1 = 1;
									if(!system_file.fs_inver)
										encoder_fl = 2;
									else
										encoder_fl = 1;
									gui_task->right_ind();
									gui_task->left_ind_cl();
									gui_task->update();
								}
							}
							else
							{
								f_sw_sel = 3;
								if(ext_fsw_a2 == 1)
								{
									ext_fsw_a2 = 0;
									gpioa.pin0_set();
									fs_but = 0;
									foot_sw_dub_short = 1;
								}
								else
								{
									ext_fsw_a2 = 1;
									gpioa.pin0_reset();
									fs_but = 1;
									foot_sw_dub_short = 1;
								}
								gui_task->update();
							}
						}
					}
				}
				exti.pin10_rising_trigger_disable();
				exti.pin10_falling_trigger_enable();
			}
		}
		tim10.update_interrupt_flag_clear();
		tim10.counter = 0;
		tim10.enable();
	}
	if(exti.pin12_pending())
	{
		exti.pin12_pending_clear();
		tim10.disable();
		if(exti.pin12_falling_trigger())
		{
			if(tim10.update_interrupt_flag())
			{
				if(system_file.fs_inver != 3)
				{
					fs_but_fl = 1;
					tim2.counter = 0;
					tim2.enable();
				}
				exti.pin12_falling_trigger_disable();
				exti.pin12_rising_trigger_enable();
			}
		}
		else
		{
			if(tim10.update_interrupt_flag())
			{
				tim2.disable();
				tim2.update_interrupt_flag_clear();
				if(tap_ext_fl && prog_data[del_ex_tap] == 1)
				{
					if(tap_temp_global())
					{
						del_p1 = tap_global;
						del_param(8 | prog_data[dp_d] << 8);
					}
				}
				else
				{
					if(system_file.fs_inver != 3)
					{
						fs_but_fl = 0;
						if(fs_but_fl1)
							fs_but_fl1 = 0;
						else
						{
							if(system_file.fs_inver != 4)
							{
								if(condish == start_screen)
								{
									encoder_fl1 = 1;
									if(!system_file.fs_inver)
										encoder_fl = 1;
									else
										encoder_fl = 2;
									gui_task->left_ind();
									gui_task->right_ind_cl();
									gui_task->update();
								}
							}
							else
							{
								f_sw_sel = 2;
								if(ext_fsw_a1)
								{
									ext_fsw_a1 = 0;
									gpioa.pin1_set();
									fs_but = 0;
									foot_sw_dub_short = 1;
								}
								else
								{
									ext_fsw_a1 = 1;
									gpioa.pin1_reset();
									fs_but = 1;
									foot_sw_dub_short = 1;
								}
								gui_task->update();
							}
						}
					}
				}
				exti.pin12_rising_trigger_disable();
				exti.pin12_falling_trigger_enable();
			}
		}
		tim10.update_interrupt_flag_clear();
		tim10.counter = 0;
		tim10.enable();
	}
}
IRQ_HANDLER(tim2)
{
	tim2.update_interrupt_flag_clear();
	if(!tim2_start)
		tim2_start = 1;
	else
	{
		if(enc_but_fl)
		{
			encoder_but_fl = 1;
			enc_but_fl = 0;
			encoder_but_dub_long = 1;
			gui_task->update();
		}
		if(fs_but_fl)
		{
			fs_but_fl = 0;
			fs_but_fl1 = 1;
			if(condish == start_screen && system_file.fs_inver != 4)
			{
				ext_but_long_fl = 1;
				gui_task->left_ind_cl();
				gui_task->right_ind_cl();
				gui_task->update();
			}
		}
		if(foot_sw_fl)
		{
			foot_sw_fl = 0;
			foot_but_fl = 1;
			foot_sw_dub_long = 1;
			gui_task->update();
		}
	}
}
const uint8_t prog_init[256] =
{/*od on*/0,/*preamp on*/0,/*amp on*/0,/*cab on*/1,/*eq on*/0,/*eq pos*/1,/*early on*/0,/*eq*/15, 15, 15, 15, 15,
/*preamp_12*/127, 0, 0, 0, 1,/*amp*/0, 0, 110, 0,/*rev_vol*/41,/*rev type*/0,/*rev time*/52,/*rev size*/60,/*rev dump*/25,
/*rev lp_26*/0,/*rev hp*/0,/*rev detune*/30,/*rev diffuse*/0,/*rev predelay*/0,/*rev tail*/0, /*delay vol*/47,/*nop*/0,
/*del fedb_34*/37,/*del lp*/0,/*del hp*/0,/*del pan*/63,/*del2 vol*/0,/*del2 pan*/63,/*del2 delay*/63,/*del det white*/0,
/*del det rate_42*/0,/*del direct*/0,/*del tim hi*/0,/*del tim lo*/0xfa,/*del type tap*/0,/*del tail*/1,/*ear del vol*/0,
/*ear del size49*/64,/*preset volume*/127,/*cab vol*/110,/*od type*/0,/*od vol*/64,/*comp on*/0,/*com th*/50,
/*comp rat*/127,/*comp vol*/84,/*comp att*/0,/*comp rel*/10,/*def*/0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

