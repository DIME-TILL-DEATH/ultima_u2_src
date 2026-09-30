#include "appdefs.h"
#include "math.h"
#include <vdt/vdt.h>

#define ENV_TR 0.0001f
#define CLOSED  1
#define OPENING 2
#define OPEN    3
#define CLOSING 4

float dB2rap(float dB);
float rap2dB(float rap);

class Gate
{

public:

	inline Gate()
	{
		Gate_Change_Preset();
	}

	inline ~Gate()
	{
	}

	inline void Gate_Change(int np, int value)
	{
		switch(np)
		{
		case 0:
			Pthreshold = value;
			t_level = dB2rap((float) Pthreshold);
			break;
		case 1:
			Pattack = value;
			a_rate = 1000.0f / ((float) Pattack * fs);
			break;
		case 2:
			Pdecay = value;
			d_rate = 1000.0f / ((float) Pdecay * fs);
			break;
		}
	}
	inline void Gate_Change_Preset(void)
	{
		env = 0.0f;
		gate = 0.0f;
		fs = 48000.0f;
		state = CLOSED;
		int presets[3] =
		{ -50, 1, 100 };
		for(int n = 0;n < 3;n++)
			Gate_Change(n, presets[n]);
	}
	inline void gate_par(uint32_t val)
	{
		uint32_t va = val >> 8;
		val &= 0xff;
		switch(val & 0xff)
		{
		case 0:
			Gate_Change(0, -((127 - va) * (70.0f / 127.0f) + 17.0f));
			break;
		case 1:
			Gate_Change(1, va * 10 + 1);
			break;
		case 2:
			Gate_Change(2, va * 10 + 10);
			break;
		}
	}
	inline float gate_out(float efxout)
	{
		float sum;
		sum = fabsf(efxout);
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
		return gate;
	}
	inline float dc_block(float in)
	{
		float a = in - in_dc_old + 0.995f * out_dc_old;
		in_dc_old = in;
		out_dc_old = a;
		return a;
	}

	int Pthreshold;		// attack time  (ms)
	int Pattack;			// release time (ms)
	int Ohold;
	int Pdecay;
	int Prange;
	int Plpf;
	int Phpf;
	int Phold;

private:

	int state;
	float t_level;
	float a_rate;
	float d_rate;
	float env;
	float gate;
	float fs;
	float in_dc_old;
	float out_dc_old;
};
