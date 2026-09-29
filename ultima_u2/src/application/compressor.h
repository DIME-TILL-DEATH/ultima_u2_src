#ifndef SRC_APPLICATION_COMPRESSOR_H_
#define SRC_APPLICATION_COMPRESSOR_H_

#include "appdefs.h"
#include "AttRelEnv.h"
#include <vdt/vdt.h>

#include "init.h"

float dB2rap(float dB);
float rap2dB(float rap);

class Compressor
{

	AttRelEnv envel_comp;

public:

	inline float compr(float efxout)
	{
		float overdB;
		float bu_sum = fabsf(efxout);
	    bu_sum += envel_comp.DC_OFFSET;
		keydB = rap2dB(bu_sum);
		overdB = keydB - thres_db;	// delta over threshold
		if(overdB < 0.0f)overdB = 0.0f;
		overdB += envel_comp.DC_OFFSET;
		envel_comp.envdB_ = envel_comp.attrel(overdB,coef_at,coef_rel);
		overdB = envel_comp.envdB_ - envel_comp.DC_OFFSET;
		float gr = overdB * ( ratio_ - 1.0f );
		gr = dB2rap( gr ) * outlevel;
		efxout *= gr;
		return efxout;
	}
	inline void comp_par(uint32_t val)
	{
		uint8_t va = val >> 8;
		val &= 0xff;
		switch(val & 0xff){
	  	case 1:thres_db = -(sqrt_f32_main(va) * (36.0f/sqrt_f32_main(127.0f)) + 24.0f);break;//implicit type cast int to float
	  	case 2:ratio = va * (120.0f/127.0f) + 7.0f;ratio_ = (127 - va) * (1.0f/127.0f);break;
	  	case 3:toutput = va * (20.0f/127.0f);break;
	  	case 4:coef_at = fast_exp(-1000.0f / ((va * (17.0f/127.0f) + 0.5f) * 48000.0f));break;
	  	case 5:coef_rel = fast_exp(-1000.0f / ((va * (1000.0f/127.0f) + 100.0f) * 48000.0f));break;
		}
		thres_mx = thres_db;  //This is the value of the input when the output is at t+k
		makeup = -thres_db + thres_mx/ratio;
		makeuplin = dB2rap(makeup);
		outlevel = (dB2rap((float)toutput) * makeuplin) * 0.01f;
	}

private:

	float thres_db , thres_mx , ratio , makeup , makeuplin , outlevel , keydB , coef_at , coef_rel;		// threshold
	int tratio , toutput , tthreshold;
	float ratio_ = 1.0f;

};

#endif /* SRC_APPLICATION_COMPRESSOR_H_ */
