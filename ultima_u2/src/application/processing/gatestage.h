#ifndef _GATESTAGE_H_
#define _GATESTAGE_H_

#include "abstractstage.h"

class GateStage : public AbstractStage
{

public:
	GateStage();
	~GateStage();

	enum Parameters
	{
		ENABLED = 0,
		THRESHOLD,
		ATTACK,
		DECAY
	};

	void sense(float* sample);
	void updateParams(const TModuleDescriptor* module) override;
	void process(float* sampleL, float* sampleR) override;


	void gate_par(uint32_t val);


private:

	typedef enum{
		CLOSED = 1,
		OPENING,
		OPEN,
		CLOSING
	}TGateState;

	static constexpr float ENV_TR = 0.0001f;

	TGateState state;

	float t_level;
	float a_rate;
	float d_rate;
	float env;
	float gate;

	int Pthreshold;		// attack time  (ms)
	int Pattack;			// release time (ms)
	int Ohold;
	int Pdecay;
	int Prange;
	int Plpf;
	int Phpf;
	int Phold;

	float reductionData[audioBlockSize];

//	void Gate_Change(int np, int value);
};

#endif /* _GATESTAGE_H_ */
