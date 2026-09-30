#include "appdefs.h"
#include "init.h"
#include "math.h"
#include "fx_sin.h"
#include "vdt/vdt.h"
#include "gui.h"
#include "FirststFilt.h"

extern float del_in_contr;
int16_t *del_buf = (int16_t*) memrev;
float del_accL;
float del_accR;
float del_acc1;
float del_acc2;
float del_acc_fed;
float del_rev_acc1;
float del_fe = 0.5f;
float del_vo = 0.5f;
float tail_vol = 1.0f;
float del_vo1 = 0.5f;
int32_t del_p;
int32_t del_p_rev;
int32_t del_p1 = 40000;
int32_t del_p2 = 20000;
float del_ph;
float del_wh = 0.0f;
float del_ra = 0.00001f;
float delay_outl;
float delay_outr;
uint8_t d_on_off = 0;

FirststFilt del_lp1;
FirststFilt del_lp2;
FirststFilt del_lp3;
FirststFilt del_hp1;
FirststFilt del_hp2;
FirststFilt del_hp3;

float panL1 = 1.0f;
float panL2 = 1.0f;
float panR1 = 1.0f;
float panR2 = 1.0f;
float dl_dry;
float dl_wet;

void SetLPF_d(float fCut)
{
	del_lp1.SetLPF(fCut);
	del_lp2.SetLPF(fCut);
	del_lp3.SetLPF(fCut);
}
void SetHPF_d(float fCut)
{
	del_hp1.SetHPF(fCut);
	del_hp2.SetHPF(fCut);
	del_hp3.SetHPF(fCut);
}

uint32_t direc;
uint8_t hpf_fl = 0;
uint8_t lpf_fl = 0;

float del_in_contr1;
float wh;
uint32_t d_p;
float fr;
void del_proc(float *ls, float *rs)
{
	float in = *ls;
	del_ph += del_ra;
	if(del_ph > 1.0f)
		del_ph = 0.0f;
	wh = vector_sin[(uint32_t) (del_ph * 16384.0f)] * 0.00006103515625f;
	wh *= del_wh;
	fr = del_p;
	wh = wh + fr;
	d_p = wh;
	fr = wh - d_p;

	if(!ind_clean)
	{

		float swell = (del_p - del_p_rev) & 0x7fffffff;
//--------------------------------------------------------------------------------------------
		if(swell <= 128.0f)
			del_rev_acc1 = del_buf[del_p_rev] * swell * 0.0078125f;
		else
			del_rev_acc1 = del_buf[del_p_rev];
//-----------------------------------------------------------------------------------------------
		del_acc_fed = del_acc1 = del_buf[d_p % del_p1] * (1.0f - fr) + del_buf[(d_p + 1) % del_p1] * fr;
//----------------------------------------------------------------------------------------------------
		if(direc)
			del_acc1 = del_rev_acc1;
		if(hpf_fl)
		{
			del_acc_fed = del_hp3.filt(del_acc_fed);
			del_acc1 = del_hp1.filt(del_acc1);
		}
		if(lpf_fl)
		{
			del_acc_fed = del_lp3.filt(del_acc_fed);
			del_acc1 = del_lp1.filt(del_acc1);
		}
//---------------------------------------------------------------------------------------------------------
		del_accL = del_acc1 * panL1;
		del_accR = del_acc1 * panR1;

		d_p = del_p2 + d_p;
//----------------------------------------------------------------------------------------------------------
		del_acc2 = del_buf[d_p % del_p1] * (1.0f - fr) + del_buf[(d_p + 1) % del_p1] * fr;
//------------------------------------------------------------------------------------------------------------
		if(hpf_fl)
			del_acc2 = del_hp2.filt(del_acc2);
		if(lpf_fl)
			del_acc2 = del_lp2.filt(del_acc2);
		if((!del_p2) || (del_p2 == del_p1))
			del_acc2 = 0.0f;
//------------------------------------------------------------------------------------------------------------
		del_accL += del_acc2 * panL2 * del_vo1;
		del_accR += del_acc2 * panR2 * del_vo1;

		del_acc_fed = (del_acc_fed * del_fe) * 3.051850947599719e-5;

		del_acc_fed = soft_clip_v2(del_acc_fed);
		del_acc_fed *= 32767.0f;

		del_buf[del_p] = in * del_vo * del_in_contr1 + del_acc_fed;

		if(++del_p >= del_p1)
			del_p = 0;
		if(!del_p_rev)
			del_p_rev = del_p1;
		del_p_rev--;

	}

	*ls = del_accL * dl_wet * tail_vol;
	*rs = del_accR * dl_wet * tail_vol;

	if(del_in_contr1 < del_in_contr)
		del_in_contr1 += 0.001f;
	else
	{
		if(del_in_contr1 > del_in_contr)
			del_in_contr1 -= 0.001f;
	}

	if(prog_data[er_on])
	{
		if(del_vo < 1.0f)
			del_vo += 0.001f;
		tail_vol = 1.0f;
	}
	else
	{
		if(del_vo > 0.0f)
			del_vo -= 0.001f;
		if(del_vo < 0.0f)
		{
			del_vo = 0.0f;
			if(!prog_data[d_tail])
				revmem_clean();
		}
		if(!prog_data[d_tail])
		{
			if(tail_vol > 0.0f)
				tail_vol -= 0.01f;
			if(tail_vol < 0.0f)
				tail_vol = 0.0f;
		}
	}
}
volatile uint32_t del_p2_temp;

void del_param(uint32_t val)
{
	uint32_t va = val >> 8;
	val &= 0xff;
	switch(val & 0xff)
	{
	case 0:
		dl_wet = (va * va) * pow_temp;
		break;
	case 1:
		break;
	case 2:
		del_fe = va * (1.0f / 127.0f);
		break;
	case 3:
		if(va)
			lpf_fl = 1;
		else
			lpf_fl = 0;
		SetLPF_d(powf((127.0f - va), 2.0f) * (19000.0f / powf(127.0f, 2.0f)) + 1000.0f);
		break;
	case 4:
		if(va)
			hpf_fl = 1;
		else
			hpf_fl = 0;
		SetHPF_d(powf(va + 0.001, 2.0f) * (980.0f / powf(127.0f, 2.0f)) + 20.0f);
		break;
	case 5:
		if(va < 63)
			panR1 = va * (1.0f / 63.0f);
		else
			panR1 = 1.0f;
		if(va > 63)
			panL1 = (126 - va) * (1.0f / 63.0f);
		else
			panL1 = 1.0f;
		break;
	case 6:
		del_vo1 = (va * va) * pow_temp;
		break;
	case 7:
		if(va < 63)
			panR2 = va * (1.0f / 63.0f);
		else
			panR2 = 1.0f;
		if(va > 63)
			panL2 = (126 - va) * (1.0f / 63.0f);
		else
			panL2 = 1.0f;
		break;
	case 8:
		del_p2_temp = va;
		del_p2 = del_p2_temp * (del_p1 / 127.0f);
		break;
	case 9:
		del_wh = powf(va, 2.0f) * (510.0f / powf(127.0f, 2.0f));
		break;
	case 10:
		del_ra = powf(va, 2.0f) * (0.0002f / powf(127.0f, 2.0f)) + 0.00001f;
		break;
	case 11:
		direc = va;
		break;
	case 12:
		ind_clean = 1;
		del_p1 = va << 8;
		break;
	case 13:
		del_p1 |= va;
		del_p1 *= 48;
		del_p2 = del_p2_temp * (del_p1 / 127.0f);
		if(direc)
			for(int i = 0;i < 131072;i++)
				del_buf[i] = 0;
		del_p_rev = 0;
		ind_clean = 0;
		break;
	}
}

