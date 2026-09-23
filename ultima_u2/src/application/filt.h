#ifndef __FILT_H__
#define __FILT_H__
#include "appdefs.h"
#include "init.h"
#include "arm_math.h"
#include "vdt/vdt.h"

#define M_LN2	   0.69314718055994530942f

extern float filt_cos[];
extern float filt_sin[];
extern float filt_alpha[];

extern float fil_lp_in_od[];
extern float fil_lp_out_od[];

extern const float freq[];
extern float freq1[];
extern volatile float filt_q;
extern float w0;
extern float coeff_preamp[];
extern float coeff_od[];

inline void filt_ini(uint8_t num , uint8_t* adr , uint8_t* adr1)
{
  switch (num){
  case 0:case 1:freq1[num] = (int8_t)adr[num] + freq[num];break;
  case 2:freq1[num] = (int8_t)adr[num]*2 + freq[num];break;
  case 3:freq1[num] = (int8_t)adr[num]*10 + freq[num];break;
  case 4:freq1[num] = (int8_t)adr[num]*50 + freq[num];break;
  }
  w0 = 2.0f * FILT_PI * freq1[num] / 48000.0f;
  filt_sin[num] = fast_sinf(w0);
  filt_cos[num] = fast_cosf(w0);
  filt_q =  fast_powf(200 - ((int8_t)adr1[num] + 100) , 3.0f)*(5.0f/fast_powf(200.0f , 3.0f)) + 0.225f;
  filt_alpha[num] = filt_sin[num]/2.0*filt_q;
}
extern float coeff_eq[];
extern float coeff_presen[];
extern float coeff_preamp[];
inline void set_filt (uint8_t num,uint8_t filt_gain)
{
  float gain;
  if(filt_gain < 15)gain = -(15.0f - filt_gain);
  else gain = -(15.0f - filt_gain);
  float A = sound_amp(10.0f, gain /40.0f);
  float a0 = 1.0f + filt_alpha[num]/A;
  coeff_eq[0 + num*5] = (1 + filt_alpha[num] * A)/a0;
  coeff_eq[1 + num*5] = (-2.0 * filt_cos[num])/a0;
  coeff_eq[2 + num*5] = (1 - filt_alpha[num] * A)/a0;
  coeff_eq[3 + num*5] = -coeff_eq[1 + num*5];
  coeff_eq[4 + num*5] = -(1 - filt_alpha[num]/A)/a0;
}
inline void filt_set(float gain , float* adr , float q_fac , float freq)
{
	float w0 = 2.0f*FILT_PI/48000.0f;
	float AA = sound_amp(10.0f , gain/40.0f);
	float w00 = w0 * freq;
	float cos_ = fast_cosf(w00);
	float sin_ = fast_sinf(w00);
	float alfa = sin_/(2.0f*q_fac);
	float a0 = 1.0f + alfa/AA ;
	float gaine = sound_amp(10.0f , 0.0f/20.0f)/a0;
	adr[2] = (1.0f - alfa*AA)*gaine;//--B2
	adr[1] = (-2.0f*cos_)*gaine;    //--B1
	adr[0] = (1.0f + alfa*AA)*gaine;//--B0
	adr[4] = -(1.0f - alfa/AA)/a0;//-A2
	adr[3] = -(-2.0f*cos_)/a0;  //-A1
}
inline void set_shelf(float gain)
{
	float A = sound_amp(10.0f, gain /40.0f);
	float w0 = 2.0f*FILT_PI*5000.0f/48000.0f;
	float cos_ = fast_cosf(w0);
	float sin_ = fast_sinf(w0);
	float alfa = sin_/2.0f * sqrt_f32_main((A+1.0f/A)*(1.0f/0.3f/*slop*/-1.0f)+2.0f);
	float a0 = (A+1.0f) - (A-1.0f)*cos_ + 2.0f*sqrt_f32_main(A)*alfa;
	coeff_presen[0] = (A*((A+1.0f)+(A-1.0f)*cos_ + 2.0f*sqrt_f32_main(A)*alfa))/a0;
	coeff_presen[1] = (-2.0f*A*((A-1.0f)+(A+1.0f)*cos_))/a0;
	coeff_presen[2] = (A*((A+1.0f)+(A-1.0f)*cos_ - 2.0f*sqrt_f32_main(A)*alfa))/a0;
	coeff_presen[3] = -(2.0f*((A-1.0f)-(A+1.0f)*cos_))/a0;
	coeff_presen[4] = -((A+1.0f) - (A-1.0f)*cos_ - 2.0f*sqrt_f32_main(A)*alfa)/a0;
}
inline void set_shelf_hi(float gain , float* adr , float slope , float freq)
{
	float A = sound_amp(10.0f, gain /40.0f);
	float w0 = 2.0f*FILT_PI*freq/48000.0f;
	float cos_ = fast_cosf(w0);
	float sin_ = fast_sinf(w0);
	float alfa = sin_/2.0f * sqrt_f32_main((A+1.0f/A)*(1.0f/slope - 1.0f)+2.0f);
	float a0 = (A+1.0f) - (A-1.0f)*cos_ + 2.0f*sqrt_f32_main(A)*alfa;
	adr[2] = (A*((A+1.0f)+(A-1.0f)*cos_ - 2.0f*sqrt_f32_main(A)*alfa))/a0; // B2
	adr[1] = (-2.0f*A*((A-1.0f)+(A+1.0f)*cos_))/a0;                // B1
	adr[0] = (A*((A+1.0f)+(A-1.0f)*cos_ + 2.0f*sqrt_f32_main(A)*alfa))/a0; // B0
	adr[4] = -((A+1.0f) - (A-1.0f)*cos_ - 2.0f*sqrt_f32_main(A)*alfa)/a0;  // A2
	adr[3] = -(2.0f*((A-1.0f)-(A+1.0f)*cos_))/a0;  // A1
}
inline void pre_param(uint8_t num , float* adr , uint8_t val)
{
	int8_t va = val;
	va += 64;
	switch(num){
	case 0:if(va < 64)filt_set(va * (19.0f/63.0f) - 12.0f , adr , 0.39f , 78.0f);
		   else filt_set((va - 63) * (2.0f/64.0f) + 7.0f , adr , 0.39f , 78.0f);
	break;
	case 1:if(va < 64)
		   {
		       filt_set(0.0f , adr + 20 , 0.49f , 460.0f);
			   filt_set(va * (6.0f/63.0f) - 6.0f, adr + 25 , 1.1f , 604.0f);
		   }
		   else {
			   filt_set((va - 63) * (6.0f/64.0f), adr + 20 , 0.49f , 460.0f);
			   filt_set((va - 63) * (3.0f/64.0f), adr + 25 , 0.44f , 800.0f);
		   }
    break;
	case 2:if(va < 64)
		   {
			   set_shelf_hi(va * (16.11f/63.0f) , adr + 15 , 0.3f , 6000.0f);
			   filt_set(va * -(4.0f/63.0f) , adr + 5 , 0.71f , 602.0f);
			   filt_set(va * (8.0f/63.0f) - 2.0f , adr + 10 , 0.3f , 1920.0f);
		   }
	       else {
	    	   set_shelf_hi((va - 63) * (9.764f/64.0f) + 16.11 , adr + 15 , 0.3f , 6000.0f);
	    	   filt_set((va - 63) * -(1.0f/64.0f) - 4.0f, adr + 5 , 0.71f , (127 - va) * (236.0f/63.0f) + 366.0f);
	    	   filt_set((va - 63) * (2.0f/64.0f) + 6.0f , adr + 10 , 0.3f , 1920.0f);
	       }
	break;
	}
}
#endif /*__FILT_H__*/
