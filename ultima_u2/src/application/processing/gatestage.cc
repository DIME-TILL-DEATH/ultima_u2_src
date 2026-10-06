#include "gatestage.h"

#include "math.h"
#include <vdt/vdt.h>

#include "init.h"

GateStage::GateStage()
{
	env = 0.0f;
	gate = 0.0f;

	state = CLOSED;
	int presets[3] = { -50, 1, 100 };
	for(int n = 0; n < 3; n++)
		gate_par(n | presets[n] << 8);
}

GateStage::~GateStage()
{
}

void GateStage::updateParams(const TModuleDescriptor* module)
{
	m_enabled = module->parameter[GateStage::ENABLED].value;

	for(uint8_t i = 0; i < 3; i++)
		gate_par(i | (module->parameter[i+1].value << 8));
}

void GateStage::process(float* sampleL, float* sampleR)
{
	if(!m_enabled) return;

	for(uint8_t i=0; i<audioBlockSize; i++)
	{
		sampleL[i] *= reductionData[i];

		if(sampleR != nullptr) sampleR[i] *= reductionData[i];
	}
}

void GateStage::gate_par(uint32_t val)
{
	uint32_t va = val >> 8;
	val &= 0xff;
	switch(val & 0xff)
	{
	case 0:
		Pthreshold = -((127 - va) * (70.0f / 127.0f) + 17.0f);
		t_level = dB2rap((float) Pthreshold);
		break;
	case 1:
		Pattack = va * 10 + 1;
		a_rate = 1000.0f / ((float) Pattack * fs);
		break;
	case 2:
		Pdecay = va * 10 + 10;
		d_rate = 1000.0f / ((float) Pdecay * fs);
		break;
	}
}

void GateStage::sense(float* sample)
{
	for(uint8_t i=0; i<audioBlockSize; i++)
	{
		float sum = dcBlock(sample[i]);
		sum = fabsf(sum);
		if(sum > env)
			env = sum;
		else
			env = 0.0f;
		//------------------------------------------------------------------
		if(state == CLOSED)
		{
			if(env >= t_level)
				state = OPENING;
		}
		else
		{
			if(state == OPENING)
			{
				gate += a_rate;
				if(gate >= 1.0f)
				{
					gate = 1.0f;
					state = OPEN;
				}
			}
			else
			{
				if(state == OPEN)
				{
					if(env < t_level)
						state = CLOSING;
				}
				else
				{
					if(state == CLOSING)
					{
						gate -= d_rate;
						if(env >= t_level)
							state = OPENING;
						else
						{
							if(gate <= 0.0f)
							{
								gate = 0.0f;
								state = CLOSED;
							}
						}
					}
				}
			}
		}
		reductionData[i] = gate;
	}
}
