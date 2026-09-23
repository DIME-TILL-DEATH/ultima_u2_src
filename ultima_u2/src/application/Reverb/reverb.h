#ifndef REVERB__H_
#define REVERB__H_

#include "appdefs.h"
#include "FirststFilt.h"

#define FILT_PI    3.14159265358979323846f

extern FirststFilt rev_lp;
extern FirststFilt rev_hp;

extern float memrev[];
extern float* rev_pre_buf;
extern float ear_mem[];
extern float phase_rev;
extern float ph_rev_in;
extern float ch_r_w;
extern float rev_outL;
extern float rev_outR;
extern float rev_time;
extern float accumul;
extern float accumul1;
extern float filt_fed1;
extern float filt_fed2;

extern uint32_t mem_plan[];
extern uint32_t mem_outL[];
extern uint32_t mem_outR[];

extern uint32_t mem_d11_shift[];
extern uint32_t alp1_1 , alp2 , alp2_1 , alp3 , alp3_1 , chor_m1 , chor_m1_1 , dela1 , dela1_1 , dela2 , dela2_1 ;
extern uint32_t dela3 , dela3_1 , dela4 , dela4_1 , dela5 , dela5_1 , chor_m2 , chor_m2_1 , dela6 , dela6_1 ;
extern uint32_t dela7 , dela7_1 , dela8 , dela8_1 , dela9 , dela9_1 , dela10 , dela10_1 , dela11 ;
extern uint32_t chor_shift;
extern uint32_t chor_shift1;
extern uint32_t reverb_point;
extern float rev_diff;
extern uint8_t rev_typ;
extern float rv_wet;
extern uint8_t prog_data[];
extern float kapi;
extern float kap;
extern float krt;
extern float kfh;
extern float kfl;
extern float kdiff;
extern float kdiff_t1;
extern float lapout;
extern float rapout;
extern float lup;

void reverb();
void hall();
void room();
void plate();
void spring();
void reve();
void early_par(float val);
void early_refl(void);
void early1 (void);
void early_init(float val);
void rev_adr_init_hall(float val);
void rev_adr_init_room(float val);
void rev_adr_init_plate(float val);
void rev_adr_init_reve(float val);
void spring_tim(int i);
void hall_1(void);

inline void reverb(void)
{
	switch(rev_typ){
	case 0:early1();break;
	case 1:hall();break;
	case 2:room();break;
	case 3:plate();break;
	case 4:spring();break;
	case 5:reve();break;
	case 6:reve();break;
	}
	phase_rev += ph_rev_in;
	if(phase_rev > 2.0f)phase_rev = 0.0f;
	if(!reverb_point)reverb_point = 65536;
	reverb_point -= 1;
}

inline void chor(uint32_t adr)
{
	float a = phase_rev;
	if(a > 1.0f)a = 2.0f - a;
	a *= ch_r_w;
	uint32_t  poschor = a;
	float frac = a - poschor;
	poschor = (reverb_point + poschor + adr) & 0xffff;
	accumul = (1.0f - frac )*memrev[poschor] + frac * memrev[(poschor + 1) & 0xffff];
}
inline void SetLPF_r(float fCut)
{
	rev_lp.SetLPF(fCut);
}
inline void SetHPF_r(float fCut)
{
	rev_hp.SetHPF(fCut);
}
#endif /* REVERB__H_ */
