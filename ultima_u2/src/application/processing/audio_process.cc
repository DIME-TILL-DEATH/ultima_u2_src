#include <processing/compressorstage.h>
#include <processing/gatestage.h>
#include "audio_process.h"

#include "init.h"
#include "gui.h"
#include "filt.h"
#include "arm_math.h"
#include "vdt/vdt.h"
#include "metronome.h"
#include "spectrum.h"

#include "distor.h"
#include "phaser.h"
#include "flanger.h"
#include "Reverb/reverb.h"
#include "FirststFilt.h"
#include "fpv4-sp-d16-instr.h"

#include "tasks/display_task.h"
#include "tasks/dsp_task.h"

#define DSP_DTCM static __attribute__((section(".dtcm_data"), aligned(32)))

DSP_DTCM int32_t ccl[AbstractStage::audioBlockSize];
DSP_DTCM int32_t ccr[AbstractStage::audioBlockSize];

DSP_DTCM float inp_sampleL[AbstractStage::audioBlockSize];
DSP_DTCM float inp_sampleR[AbstractStage::audioBlockSize];

float c3[AbstractStage::audioBlockSize];


TModuleRuntime moduleRuntime[MAX_PRESET_MODULES];

GateStage gate_pres;
GateStage gate_glob;
Expander expan;
CompressorStage compr;
Distor dist;
PassFilt hpFilt;
PassFilt lpFilt;
Phaser phaser;
Flanger flanger;
extern FirststFilt rev_lp;
extern FirststFilt rev_hp;

uint8_t dma_ht_fl = 0;

float *rev_pre_buf = (float*) ear_mem;
uint16_t rev_pre = 0;
uint16_t rev_pre_po = 0;
uint8_t proc_run = 1;


uint8_t eq_preamp_fl;
uint8_t fir_amp_fl;
uint8_t eq_fl;

float in_l;
uint8_t down_fl = 0;
volatile uint8_t sai_start = 0;
float pream_vol;
float amp_vol;
float amp_sla;
volatile uint8_t m_vol_fl = 0;
float p_vol = 1.0;
float mute_mas = 1.0f;
float cab_volume = 0.0f;
float od_volume;
uint16_t clip_ind = 22000;
float del_outL;
float del_outR;
float od_cross = 0.0f;
float rev_vo;
float rev_vol;
float mas_v = 0.0f;
float rev_fb;
float rev_fb_val;
float rev_nopr;
float pr_ga = 1;

extern uint32_t ind_in_p[];
extern uint32_t ind_out_l[];
extern uint32_t ind_out_r[];
extern uint16_t ind_poin;
void del_proc(float *ls, float *rs);

uint8_t light_per;
uint16_t light_per_po;
uint16_t light_per_po1;
uint32_t tap_temp;
uint32_t tap_temp1;
uint32_t tap_temp2;
uint32_t del_tim_ind;

uint8_t tuner_use = 0;
uint8_t gate_fl = 0;

arm_fir_instance_f32 cab_inst;
arm_fir_instance_f32 amp_inst;
arm_biquad_casd_df1_inst_f32 eq_instance;
arm_biquad_casd_df1_inst_f32 presen_instance;
arm_biquad_casd_df1_inst_f32 preamp_instance;
float coef_cab[num_tab_cab];
float state_cab[num_tab_cab + AbstractStage::audioBlockSize  - 1];
float coef_amp[num_tab_amp];
float state_amp[num_tab_amp + AbstractStage::audioBlockSize  - 1];
float coeff_eq[eq_stage * 5];
float stage_eq[eq_stage * 4];
float coeff_presen[presen_stage * 5];
float stage_presen[presen_stage * 4];
float coeff_preamp[preamp_stage * 5];
float stage_preamp[preamp_stage * 4];

void audioProcessInit()
{
	arm_fir_init_f32(&cab_inst, num_tab_cab, coef_cab, state_cab, AbstractStage::audioBlockSize );
	arm_fir_init_f32(&amp_inst, num_tab_amp, coef_amp, state_amp, AbstractStage::audioBlockSize );
	arm_biquad_cascade_df1_init_f32(&eq_instance, eq_stage, coeff_eq, stage_eq);
	arm_biquad_cascade_df1_init_f32(&presen_instance, presen_stage, coeff_presen, stage_presen);
	arm_biquad_cascade_df1_init_f32(&preamp_instance, preamp_stage, coeff_preamp, stage_preamp);
}

IRQ_HANDLER(dma2_stream5)
{
	if(ind_flag && !system_file.f_sw_exp)
	{
		light_per++;
		light_per &= 0x3f;
		if(light_per > light_per_po)
			gpioe.pin0_set();
		else
			gpioe.pin0_reset();
		light_per_po1 = 63 - light_per_po;
		if(light_per > light_per_po1)
			gpioe.pin1_set();
		else
			gpioe.pin1_reset();
	}
	else
	{
		if(!ind_flag)
		{
			gpioe.pin0_set();
			gpioe.pin1_set();
		}
	}
//-----------------------------------------------tap select-------------------------------
	if(tap_temp < 8191)
		tap_temp += 1;

	if(tap_fs_fl || tap_ext_fl || (prog_data[FX] && prog_data[FX_typ]))
	{
		uint32_t temp = del_p1 * 0.0625f;
		if(del_tim_ind)
			del_tim_ind--;
		else
			del_tim_ind = temp;
		if(!del_tim_ind)
			gpiod.pin13_set();
		if(del_tim_ind == (temp >> 3))
			gpiod.pin13_reset();
	}
//---------------------------------------------------Fade IN OUT-----------------------------------
	if(m_vol_fl == 1)
	{
		if(mute_mas > 0.0f)
			mute_mas -= 0.05f;
		else
		{
			m_vol_fl = 2;
			mute_mas = 0.0f;
		}
	}
	else
	{
		if(!m_vol_fl)
		{
			if(mute_mas < 1.0f)
				mute_mas += 0.05f;
			else
			{
				mute_mas = 1.0f;
				m_vol_fl = 2;
			}
		}
	}
//-----------------------------------------------------DMA point----------------------------------------------
	if(dma2.stream5_half_transfer_interrupt_flag())
	{
		dma2.stream5_half_transfer_interrupt_clear();
		dma_ht_fl = 0;
	}
	else
	{
		dma2.stream5_transfer_complete_interrupt_clear();
		dma_ht_fl = 1;
	}

	if(dsp_task)
		dsp_task->trigger();

	audioCaptureBlock();
}

void audioCaptureBlock()
{
	for(uint8_t i = 0;i < AbstractStage::audioBlockSize ;i++)
	{
		uint8_t a = i + dma_ht_fl * AbstractStage::audioBlockSize ;
		ccl[i] = adc_data[a].left;
		ccl[i] = ccl[i] >> 8;
		ccr[i] = adc_data[a].right;
		ccr[i] = ccr[i] >> 8;
		inp_sampleL[i] = ccl[i] * 0.000000119f;
		inp_sampleR[i] = ccr[i] * 0.000000119f;

		//-------------clip ind-------
		ind_in_p[0] = abs(ccl[i]);
		if(ind_in_p[0] > ind_in_p[1])
			ind_in_p[1] = ind_in_p[0];

		if(!tap_fs_fl && !tap_ext_fl)
		{
			if(ind_in_p[0] > 7600000)
			{
				gpiod.pin13_reset();
				clip_ind = 10000;
			}
			else
			{
				if(!clip_ind)
					gpiod.pin13_set();
				else
					clip_ind--;
			}
		}
		//--------------------------------
	}
}

//------------------------------------------------------------------------------
void audioProcessBlock()
{
	if(proc_run)
	{
		gate_pres.sense(inp_sampleL);
		gate_glob.sense(inp_sampleL);

		compr.process(inp_sampleL, nullptr);

		for(uint8_t i = 0;i < AbstractStage::audioBlockSize ;i++)
		{
			c3[i] = inp_sampleL[i];
			if(tuner_use)
			{
				if(fabsf(c3[i]) < 0.0005f)
					c3[i] = 0.0f;
				SpectrumBuffsUpdate(c3[i]);
			}

			if(prog_data[phaz_on] == 1)
				inp_sampleL[i] = phaser.phaser(inp_sampleL[i]);

			if(prog_data[flan_on] == 1)
				flanger.flanger(inp_sampleL + i);
		}

		if(prog_data[od_on])
		{
			for(uint8_t i = 0;i < AbstractStage::audioBlockSize ;i++)
				AbstractStage::dsp_scratch[i] = dist.soft_clip(inp_sampleL[i] * pr_ga * expan.expander(inp_sampleR[i]), prog_data[pr_over_cl + prog_data[preamp_on] - 1])
					* od_volume;
			arm_biquad_cascade_df1_f32(&preamp_instance, AbstractStage::dsp_scratch, inp_sampleL, AbstractStage::audioBlockSize );
		}

		if(!prog_data[eq_po])
		{
			arm_biquad_cascade_df1_f32(&eq_instance, inp_sampleL, AbstractStage::dsp_scratch, AbstractStage::audioBlockSize );
			if(prog_data[eq_on])
				arm_copy_f32(AbstractStage::dsp_scratch, inp_sampleL, AbstractStage::audioBlockSize );
		}

		if(prog_data[preamp_on] && !prog_data[od_on])
		{
			for(uint8_t i = 0;i < AbstractStage::audioBlockSize ;i++)
				AbstractStage::dsp_scratch[i] = dist.soft_clip(inp_sampleL[i] * pr_ga * expan.expander(inp_sampleR[i]), prog_data[pr_over_cl]) * pream_vol;
			arm_biquad_cascade_df1_f32(&preamp_instance, AbstractStage::dsp_scratch, inp_sampleL, AbstractStage::audioBlockSize );
		}

		if(prog_data[amp_on])
		{
			for(uint8_t i = 0;i < AbstractStage::audioBlockSize ;i++)
				inp_sampleL[i] = soft_clip_amp(inp_sampleL[i] * amp_vol) * amp_sla;

			if(prog_data[a_t])
			{
				arm_fir_f32(&amp_inst, inp_sampleL, AbstractStage::dsp_scratch, AbstractStage::audioBlockSize );
				for(uint8_t i = 0;i < AbstractStage::audioBlockSize ;i++)
					inp_sampleL[i] = AbstractStage::dsp_scratch[i] * 0.6f;
			}
		}

		if(prog_data[hip_on])
			for(uint8_t i = 0;i < AbstractStage::audioBlockSize ;i++)
				inp_sampleL[i] = hpFilt.filt(inp_sampleL[i], prog_data[hip_on]);

		if(prog_data[eq_po])
		{
			arm_biquad_cascade_df1_f32(&eq_instance, inp_sampleL, AbstractStage::dsp_scratch, AbstractStage::audioBlockSize );
			if(prog_data[eq_on])
				arm_copy_f32(AbstractStage::dsp_scratch, inp_sampleL, AbstractStage::audioBlockSize );
		}
		if(prog_data[lop_on])
			for(uint8_t i = 0;i < AbstractStage::audioBlockSize ;i++)
				inp_sampleL[i] = lpFilt.filt(inp_sampleL[i], prog_data[lop_on]);

		arm_biquad_cascade_df1_f32(&presen_instance, inp_sampleL, AbstractStage::dsp_scratch, AbstractStage::audioBlockSize );
		if(prog_data[pr_on] || prog_data[amp_on])
			arm_copy_f32(AbstractStage::dsp_scratch, inp_sampleL, AbstractStage::audioBlockSize );

		if(prog_data[phaz_on] == 2)
			for(uint8_t i = 0;i < AbstractStage::audioBlockSize ;i++)
				inp_sampleL[i] = phaser.phaser(inp_sampleL[i]);

		if(prog_data[flan_on] == 2)
			for(uint8_t i = 0;i < AbstractStage::audioBlockSize ;i++)
				flanger.flanger(inp_sampleL + i);

		if(prog_data[cab_on] && impulse_flag && !system_file.glob_cab)
		{
			inp_sampleR[0] = prog_data[ir_mix] * 0.0079365079365079f;
			arm_fir_f32(&cab_inst, inp_sampleL, AbstractStage::dsp_scratch, AbstractStage::audioBlockSize );
			for(uint8_t i = 0;i < AbstractStage::audioBlockSize ;i++)
				inp_sampleL[i] = inp_sampleL[i] * inp_sampleR[0] + AbstractStage::dsp_scratch[i] * 0.3f * cab_volume * (1.0f - inp_sampleR[0]);
		}

		gate_pres.process(inp_sampleL, nullptr);
		gate_glob.process(inp_sampleL, nullptr);

		for(uint8_t i = 0;i < AbstractStage::audioBlockSize ;i++)
		{
			if(!ind_clean)
			{
				if(prog_data[fx_type])
				{
					if(prog_data[er_on])
					{
						if(rev_vo < 1.0f)
							rev_vo += 0.001f;
						tail_vol = 1.0f;
					}
					else
					{
						if(rev_vo > 0.0f)
							rev_vo -= 0.001f;
						if(rev_vo < 0.0f)
						{
							rev_vo = 0.0f;
							if(!prog_data[rev_tail])
								revmem_clean();
						}
						if(!prog_data[rev_tail])
						{
							if(tail_vol > 0.0f)
								tail_vol -= 0.01f;
							if(tail_vol < 0.0f)
								tail_vol = 0.0f;
						}
					}
					if(!ind_clean)
						rev_pre_buf[rev_pre_po] = rev_lp.filt(rev_hp.filt(inp_sampleL[i])) + rev_fb * rev_fb_val;
					else
						rev_pre_buf[rev_pre_po] = 0.0f;
					rev_fb = rev_pre_buf[(rev_pre_po + rev_pre) % pre_size];
					accumul = (rev_pre_buf[rev_pre_po] * rev_nopr + rev_fb) * 0.3f;
					if(!rev_pre_po)
						rev_pre_po = pre_size;
					rev_pre_po--;
					reverb();
					rev_outR *= tail_vol * rv_wet;
					rev_outL *= tail_vol * rv_wet;
				}
				else
				{
					if(prog_data[er_on])
						accumul = inp_sampleL[i] * ear_vol;
					else
						accumul = 0.0f;
					early_refl();
					del_outL = (inp_sampleL[i] + rev_outL) * 32767.0f;
					del_proc(&del_outL, &del_outR);
					del_outL *= 3.051850947599719e-5;
					del_outR *= 3.051850947599719e-5;
				}
			}
			else
				ind_clean1 = 1;

			inp_sampleR[i] = inp_sampleL[i] + rev_outR + del_outR;
			inp_sampleL[i] += rev_outL + del_outL;

			ind_out_l[0] = abs((int32_t) (inp_sampleL[i] * 8388607.0f * p_vol));
			ind_out_r[0] = abs((int32_t) (inp_sampleR[i] * 8388607.0f * p_vol));

			if(ind_out_l[0] > ind_out_l[1])
				ind_out_l[1] = ind_out_l[0];
			if(ind_out_r[0] > ind_out_r[1])
				ind_out_r[1] = ind_out_r[0];
			if((condish == volum || condish == cab_vol_ind) && ind_poin++ == 2000 && !tuner_use)
			{
				ind_poin = 0;
				display_task->VolInd();
			}
		}

		metronome.process(inp_sampleL, inp_sampleR);
	}

	for(uint8_t i = 0;i < AbstractStage::audioBlockSize ;i++)
	{
		uint8_t a = i + dma_ht_fl * AbstractStage::audioBlockSize ; //pointer
		ccl[i] = out_clip(inp_sampleL[i]) * 8388607.0f * mute_mas * p_vol * mas_v;
		ccr[i] = out_clip(inp_sampleR[i]) * 8388607.0f * mute_mas * p_vol * mas_v;
		ccl[i] = ccl[i] << 8;
		ccr[i] = ccr[i] << 8;

		if(mute_mas <= 0.0f)
		{
			dac_data[a].left = 0;
			dac_data[a].right = 0;
		}
		else
		{
			dac_data[a].left = ccl[i];
			dac_data[a].right = ccr[i];
		}
	}
}