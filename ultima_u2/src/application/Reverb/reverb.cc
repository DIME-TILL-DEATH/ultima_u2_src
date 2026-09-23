#include "appdefs.h"
#include "DSP_inst.h"
#include "stdint.h"
#include "init.h"
#include "vdt/vdt.h"
#include "Reverb/reverb.h"

FirststFilt rev_lp;
FirststFilt rev_hp;

float memrev[rev_size];
float rv_wet = 1.0f;
float __attribute__((section(".dtcm_data"))) ear_mem[pre_size];
uint32_t ear_point;

float phase_rev;
float ph_rev_in = 0.00001f;
float ch_r_w = 1.0f;
float rev_outL;
float rev_outR;
float rev_time = 0.5f;
float accumul;
float accumul1;
float B;
float C;
float B1;
float C1;
float rev_diff = 0.5;
float filt_fed1 = 0.5f;
float filt_fed2 = 0.5f;
float pacc;
float lr;
float kapi = 0.5f;
float kap = 0.6f;
float krt = 0.5f;
float kfh = 0.05f;
float kfl = 0.3f;
float kdiff;
float kdiff_t1;
float lapout;
float rapout;
float lup;
uint8_t rev_typ;

uint32_t mem_plan[15];
uint32_t mem_outL[19];
uint32_t mem_outR[19];
uint32_t mem_d11_shift[8];
uint32_t alp1_1 , alp2 , alp2_1 , alp3 , alp3_1 , chor_m1 , chor_m1_1 , dela1 , dela1_1 , dela2 , dela2_1 ;
uint32_t dela3 , dela3_1 , dela4 , dela4_1 , dela5 , dela5_1 , chor_m2 , chor_m2_1 , dela6 , dela6_1 ;
uint32_t dela7 , dela7_1 , dela8 , dela8_1 , dela9 , dela9_1 , dela10 , dela10_1 , dela11 ;
uint32_t chor_shift;
uint32_t chor_shift1;

uint32_t reverb_point;

float rev_n = 1.0f;

void rev_init(void)
{
	if(prog_data[r_typ])rev_n = (powf(prog_data[r_size],2.0f) * (1.709782875368008f/powf(127.0f,2.0f)) + 0.3f);
	else rev_n = (powf(prog_data[r_size],2.0f) * (8.3553f/powf(127.0f,2.0f)) + 0.3f);
	revmem_clean();
	ch_r_w = rev_n * 255.0f;
	switch(rev_typ){
	case 0:early_init(rev_n);break;
	case 1:rev_adr_init_hall(rev_n);break;
	case 2:rev_adr_init_room(rev_n);break;
	case 3:rev_adr_init_plate(rev_n);break;
	case 5:case 6:rev_adr_init_reve(rev_n);ch_r_w = 0.0f;break;
	}
}
void rever_par(uint32_t val)
{
  uint32_t va = (val >> 8) & 0xff;
  switch(val & 0xff){
    case 0:rv_wet = (va * va) * (1.0f/(127.0f * 127.0f));break;
    case 1:rev_typ = va;rev_init();break;
    case 2:rev_time = sound_amp((va + 1) , 0.4f) * (1.0f/sound_amp(128.0f,0.4f));spring_tim(va);break;
    case 3:rev_init();break;
    case 4:filt_fed1 = (127 - va) * (1.0f/127.0f);filt_fed2 = va * (1.0f/127.0f);break;
    case 5:SetLPF_r(powf((127.0f - va),2.0f) * (19000.0f/powf(127.0f,2.0f))+1000.0f);break;
    case 6:SetHPF_r(powf(va,2.0f) * (980.0f/(powf(127.0f,2.0f)))+20.0f);break;
    case 7:ph_rev_in = va * (0.000025f/127.0f) + 0.0000001f;break;
    case 8:rev_diff = (127 - va) * (0.7f/127.0f);break;
    case 9:rev_pre = va * (27391.0f/127.0f);break;
   }
}
