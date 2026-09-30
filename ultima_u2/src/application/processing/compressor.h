#ifndef _COMPRESSOR_H_
#define _COMPRESSOR_H_

#include "appdefs.h"
#include "AttRelEnv.h"
#include <vdt/vdt.h>

#include "init.h"
#include "abstractstage.h"

float dB2rap(float dB);
float rap2dB(float rap);

class Compressor : public AbstractStage
{

	AttRelEnv envel_comp;

public:
	~Compressor() {};

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

	void comp_par(uint32_t val);
	void updateParams() override;

private:

	float thres_db , thres_mx , ratio , makeup , makeuplin , outlevel , keydB , coef_at , coef_rel;		// threshold
	int tratio , toutput , tthreshold;
	float ratio_ = 1.0f;

};

#endif /* SRC_APPLICATION_COMPRESSOR_H_ */
