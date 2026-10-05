#ifndef SRC_APPLICATION_INIT_H_
#define SRC_APPLICATION_INIT_H_

#include "appdefs.h"
#include "math.h"
#include "gui.h"
#include <vdt/vdt.h>

#include "Reverb/reverb.h"

#include "tasks/display_task.h"

#define FILT_PI    3.14159265358979323846f

#define num_tab_cab 1024
#define num_tab_amp 128
#define eq_stage 5
#define presen_stage 1
#define preamp_stage 6
#define rev_size  65536
#define pre_size  31488

using namespace vdt;
using namespace vdt::details;

inline float dB2rap(float dB)
{
	const float DB_2_LOG = 0.1151292546497022f;
	return fast_expf(dB * DB_2_LOG);
}
inline float rap2dB(float rap)
{
	const float LOG_2_DB = 8.6858896380650365f;
	return fast_logf(rap) * LOG_2_DB;
}

typedef union
{
	uint64_t val;
	struct
	{
		uint32_t left;
		uint32_t right;
	};
} ad_data_t;

typedef union
{
	int64_t val;
	struct
	{
		uint32_t left;
		uint32_t right;
	};
} da_data_t;

extern float pow_temp;
extern ad_data_t adc_data[];
extern da_data_t dac_data[];
extern float *rev_pre_buf;
extern uint8_t prog_data[];
extern uint8_t prog_data_t[];
extern uint8_t controller[];
extern uint8_t prog;
extern uint8_t prog_old;
extern uint8_t encoder_fl;
extern uint8_t encoder_fl1;
extern uint8_t encoder_but;
extern uint8_t encoder_but_dub_short;
extern uint8_t encoder_but_dub_long;
extern uint8_t edit_but;
extern uint8_t enc_but_fl;
extern float coef_amp[];
extern float pream_vol;
extern float amp_vol;
extern float amp_sla;
extern float p_vol;
extern float rev_vol;
extern float mute_mas;
extern uint8_t fs_but;
extern uint8_t fs_fl;
extern volatile uint8_t m_vol_fl;
extern uint8_t condish;
extern float cab_volume;
extern const uint8_t eq_list[][10];
extern uint32_t ind_in_p[];
extern uint32_t ind_out_l[];
extern uint32_t ind_out_r[];
extern uint8_t sys_data[];
extern const uint8_t prog_init[];
extern float coef_cab[];
extern int16_t *del_buf;
extern float tail_vol;
extern uint16_t delay_time;
extern float mas_v;
extern uint32_t ear_point;
extern float ear_mem[];
extern float rev_n;
extern float ear_vol;
extern volatile int presets_compress[];
extern uint8_t proc_run;
extern float rev_fb_val;
extern float rev_nopr;
extern volatile uint8_t impulse_flag;
extern uint8_t tap_fs_fl;
extern uint32_t tap_temp;
extern uint32_t tap_temp1;
extern uint32_t tap_temp2;
extern uint32_t tap_global;
extern uint8_t eq_num;
extern uint8_t foot_but_fl;
//extern uint32_t metronom_start;
//extern uint8_t metronom_fl;
//extern uint16_t metronom_counter;
//extern uint16_t temp_counter;
//extern uint32_t metronom_int;
//extern uint8_t metronom_vol;
extern uint8_t f_sw_sel;
extern uint8_t tap_ext_fl;
extern uint8_t int_fsw_a1;
extern uint8_t ext_fsw_a1;
extern uint8_t ext_fsw_a2;
extern uint8_t ext_fsw_b1;
extern uint8_t ext_fsw_b2;
extern uint8_t tuner_use;
extern uint8_t start_fl;
extern float c3[];
extern volatile uint8_t ind_flag;
extern float pr_ga;

void init_ext_fs(void);
void start_irq(void);
void del_param(uint32_t val);
void SetHPF_d(float fCut);
void SetLPF_d(float fCut);
void rever_par(uint32_t val);
void rev_init(void);
void Compressor_Change_Preset(int dgui, int npreset);
void Compressor_init(void);
void comp_par(uint32_t val);
void Compressor_Change(int np, int value);
void comp_par(uint32_t val);
float compr_out(float efxout);
float gate_out(float efxout);
void gate_par(uint32_t val);
void path_fold(emb_string &path);
void para_com(uint8_t num, int8_t val);
void adc_init(void);
void adc_contr_init(void);
void adc_proc(void);
uint8_t tap_temp_global(void);

inline int16_t enc_speed_inc(int16_t data, int16_t max)
{
	tim6.disable();
	if(tim6.update_interrupt_flag())
		data = data + 1;
	else
	{
		if(tim6.counter > 0x3fff)
			data += 1;
		else
		{
			if(tim6.counter > 0x1fff)
			{
				if(data < (max - 1))
					data += 2;
				else
					data += 1;
			}
			else
			{
				if(tim6.counter > 0xfff)
				{
					if(data < (max - 3))
						data += 4;
					else
						data += 1;
				}
				else
				{
					if(tim6.counter > 0x7ff)
					{
						if(data < (max - 7))
							data += 8;
						else
							data += 1;
					}
					else
					{
						if(data < (max - 9))
							data += 10;
						else
							data += 1;
					}
				}
			}
		}
	}
	tim6.counter = 0;
	tim6.update_interrupt_flag_clear();
	tim6.enable();
	return data;
}

inline uint16_t enc_speed_dec(int16_t data, int16_t min)
{
	tim6.disable();
	if(tim6.update_interrupt_flag())
		data -= 1;
	else
	{
		if(tim6.counter > 0x3fff)
			data -= 1;
		else
		{
			if(tim6.counter > 0x1fff)
			{
				if(data > (min + 1))
					data -= 2;
				else
					data -= 1;
			}
			else
			{
				if(tim6.counter > 0xfff)
				{
					if(data > (min + 3))
						data -= 4;
					else
						data -= 1;
				}
				else
				{
					if(tim6.counter > 0x7ff)
					{
						if(data > (min + 7))
							data -= 8;
						else
							data -= 1;
					}
					else
					{
						if(data > (min + 9))
							data -= 10;
						else
							data -= 1;
					}
				}
			}
		}
	}
	tim6.counter = 0;
	tim6.update_interrupt_flag_clear();
	tim6.enable();
	return data;
}

inline void del_time_inc(void)
{
	if(delay_time < 2730)
	{
		if(tim6.update_interrupt_flag())
			delay_time++;
		else
		{
			if(tim6.counter > 0x1fff)
			{
				if(delay_time < 2720)
					delay_time += 10;
				else
					delay_time++;
			}
			else
			{
				if(tim6.counter > 0xfff)
				{
					if(delay_time < 2700)
						delay_time += 30;
					else
						delay_time++;
				}
				else
				{
					if(tim6.counter > 0x7ff)
					{
						if(delay_time < 2670)
							delay_time += 60;
						else
							delay_time++;
					}
					else
					{
						if(delay_time < 2610)
							delay_time += 100;
						else
							delay_time++;
					}
				}
			}
		}
		display_task->del_time_ind(60, 1, delay_time, 1);
		tim6.counter = 0;
		tim6.update_interrupt_flag_clear();
		tim6.enable();
		prog_data[d_tim_lo] = delay_time & 0xff;
		prog_data[d_tim_hi] = delay_time >> 8;
		del_param(12 | prog_data[d_tim_hi] << 8);
		del_param(13 | prog_data[d_tim_lo] << 8);
	}
}

inline void del_time_dec(void)
{
	if(delay_time > 10)
	{
		if(tim6.update_interrupt_flag())
			delay_time--;
		else
		{
			if(tim6.counter > 0x1fff)
			{
				if(delay_time > 20)
					delay_time -= 10;
				else
					delay_time--;
			}
			else
			{
				if(tim6.counter > 0xfff)
				{
					if(delay_time > 40)
						delay_time -= 30;
					else
						delay_time--;
				}
				else
				{
					if(tim6.counter > 0x7ff)
					{
						if(delay_time > 70)
							delay_time -= 60;
						else
							delay_time--;
					}
					else
					{
						if(delay_time > 110)
							delay_time -= 100;
						else
							delay_time--;
					}
				}
			}
		}
		display_task->del_time_ind(60, 1, delay_time, 1);
		tim6.counter = 0;
		tim6.update_interrupt_flag_clear();
		tim6.enable();
		prog_data[d_tim_lo] = delay_time & 0xff;
		prog_data[d_tim_hi] = delay_time >> 8;
		del_param(12 | prog_data[d_tim_hi] << 8);
		del_param(13 | prog_data[d_tim_lo] << 8);
	}
}

extern float a_a;
extern float b_b;
extern float k1;
extern float k2;
extern float k3;
extern float k4;
inline void clip_init(void)
{
	k1 = a_a * a_a;
	k2 = 1.0f + 2.0f * a_a;
	k3 = b_b * b_b;
	k4 = 1.0f - 2.0f * b_b;
}

inline float soft_clip_v2(float in)
{
	float n;
	if(in < a_a)
		n = (k1 + in) / (k2 - in);
	else
	{
		if(in > b_b)
			n = (in - k3) / (in + k4);
		else
			n = in;
	}
	return n;
}

inline float out_clip(float in)
{
	float a = fabsf(in);
	float b = a - 0.91838997f;
	if(a > 0.9486f)
	{
		a = 0.98f * (b / (fabsf(b) + 0.001f));
		if(in >= 0.0f)
			in = a;
		else
			in = -a;
	}
	return in;
}

inline float soft_clip_amp(float in)
{
	float aaa = fabsf(in);
	if(aaa < 0.1618f)
		aaa *= 4.294115f;
	else
		aaa = 0.81f * ((aaa - 0.11f) / (fabsf(aaa - 0.11f) + 0.033f)) + 0.2f;
	if(in < 0.0f)
		in = -aaa;
	else
		in = aaa;
	return in;
}

inline float sqrt_f32_main(float in)
{
	float out;
	asm("VSQRT.F32 %0,%1" : "=t"(out) : "t"(in));
	return out;
}

inline float sound_amp(const float sample, const float gain)
{
	if(vabsf(sample) <= std::numeric_limits<float>::min())
		return sample;
	if(sample >= 0.0f)
		return fast_expf(gain * vdt::fast_logf(sample));
	else
		return -fast_expf(gain * vdt::fast_logf(-sample));
}

inline void revmem_clean(void)
{
	float *revmembuf;
	for(uint32_t i = 0;i < pre_size;i++)
		ear_mem[i] = 0.0f;
	if(prog_data[r_typ])
	{
		revmembuf = (float*) memrev;
		for(uint32_t i = 0;i < 65536;i++)
			*revmembuf++ = 0.0f;
	}
	else
	{
		int16_t *delmembuf = (int16_t*) del_buf;
		for(uint32_t i = 0;i < 131072;i++)
			*delmembuf++ = 0;
	}
}

inline void select_unused_pin(uint8_t swd)
{
	gpioa.pin5_mode_output();
	gpioa.pin5_output_type_pull_push();
	gpioa.pin5_pull_no();
	gpioa.pin5_output_speed_low();

	gpioa.pin6_mode_output();
	gpioa.pin6_output_type_pull_push();
	gpioa.pin6_pull_no();
	gpioa.pin6_output_speed_low();

	gpioa.pin8_mode_output();
	gpioa.pin8_output_type_pull_push();
	gpioa.pin8_pull_no();
	gpioa.pin8_output_speed_low();

	gpioa.pin10_mode_output();
	gpioa.pin10_output_type_pull_push();
	gpioa.pin10_pull_no();
	gpioa.pin10_output_speed_low();

	if(swd)
	{
		gpioa.pin13_mode_output();
		gpioa.pin13_output_type_pull_push();
		gpioa.pin13_pull_no();
		gpioa.pin13_output_speed_low();

		gpioa.pin14_mode_output();
		gpioa.pin14_output_type_pull_push();
		gpioa.pin14_pull_no();
		gpioa.pin14_output_speed_low();
	}

	gpiob.pin4_mode_output();
	gpiob.pin4_output_type_pull_push();
	gpiob.pin4_pull_no();
	gpiob.pin4_output_speed_low();

	gpiob.pin6_mode_output();
	gpiob.pin6_output_type_pull_push();
	gpiob.pin6_pull_no();
	gpiob.pin6_output_speed_low();

	gpiob.pin7_mode_output();
	gpiob.pin7_output_type_pull_push();
	gpiob.pin7_pull_no();
	gpiob.pin7_output_speed_low();

	gpiob.pin8_mode_output();
	gpiob.pin8_output_type_pull_push();
	gpiob.pin8_pull_no();
	gpiob.pin8_output_speed_low();

	gpiob.pin9_mode_output();
	gpiob.pin9_output_type_pull_push();
	gpiob.pin9_pull_no();
	gpiob.pin9_output_speed_low();

	gpiob.pin11_mode_output();
	gpiob.pin11_output_type_pull_push();
	gpiob.pin11_pull_no();
	gpiob.pin11_output_speed_low();

	gpiob.pin14_mode_output();
	gpiob.pin14_output_type_pull_push();
	gpiob.pin14_pull_no();
	gpiob.pin14_output_speed_low();

	gpiob.pin15_mode_output();
	gpiob.pin15_output_type_pull_push();
	gpiob.pin15_pull_no();
	gpiob.pin15_output_speed_low();

	gpioc.pin0_mode_output();
	gpioc.pin0_output_type_pull_push();
	gpioc.pin0_pull_no();
	gpioc.pin0_output_speed_low();

	gpioc.pin1_mode_output();
	gpioc.pin1_output_type_pull_push();
	gpioc.pin1_pull_no();
	gpioc.pin1_output_speed_low();

	gpioc.pin8_mode_output();
	gpioc.pin8_output_type_pull_push();
	gpioc.pin8_pull_no();
	gpioc.pin8_output_speed_low();

	gpioc.pin9_mode_output();
	gpioc.pin9_output_type_pull_push();
	gpioc.pin9_pull_no();
	gpioc.pin9_output_speed_low();

	gpiod.pin0_mode_output();
	gpiod.pin0_output_type_pull_push();
	gpiod.pin0_pull_no();
	gpiod.pin0_output_speed_low();

	gpiod.pin1_mode_output();
	gpiod.pin1_output_type_pull_push();
	gpiod.pin1_pull_no();
	gpiod.pin1_output_speed_low();

	gpiod.pin2_mode_output();
	gpiod.pin2_output_type_pull_push();
	gpiod.pin2_pull_no();
	gpiod.pin2_output_speed_low();

	gpiod.pin3_mode_output();
	gpiod.pin3_output_type_pull_push();
	gpiod.pin3_pull_no();
	gpiod.pin3_output_speed_low();

	gpiod.pin4_mode_output();
	gpiod.pin4_output_type_pull_push();
	gpiod.pin4_pull_no();
	gpiod.pin4_output_speed_low();

	gpiod.pin9_mode_output();
	gpiod.pin9_output_type_pull_push();
	gpiod.pin9_pull_no();
	gpiod.pin9_output_speed_low();

	gpiod.pin10_mode_output();
	gpiod.pin10_output_type_pull_push();
	gpiod.pin10_pull_no();
	gpiod.pin10_output_speed_low();

	gpiod.pin12_mode_output();
	gpiod.pin12_output_type_pull_push();
	gpiod.pin12_pull_no();
	gpiod.pin12_output_speed_low();

	gpiod.pin14_mode_output();
	gpiod.pin14_output_type_pull_push();
	gpiod.pin14_pull_no();
	gpiod.pin14_output_speed_low();

	gpiod.pin15_mode_output();
	gpiod.pin15_output_type_pull_push();
	gpiod.pin15_pull_no();
	gpiod.pin15_output_speed_low();

	gpioe.pin12_mode_output();
	gpioe.pin12_output_type_pull_push();
	gpioe.pin12_pull_no();
	gpioe.pin12_output_speed_low();

	gpioe.pin13_mode_output();
	gpioe.pin13_output_type_pull_push();
	gpioe.pin13_pull_no();
	gpioe.pin13_output_speed_low();

	gpioe.pin14_mode_output();
	gpioe.pin14_output_type_pull_push();
	gpioe.pin14_pull_no();
	gpioe.pin14_output_speed_low();
}
#endif /* SRC_APPLICATION_INIT_H_ */
