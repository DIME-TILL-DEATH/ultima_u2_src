#include "abstractstage.h"

float __attribute__((section(".dtcm_data"), aligned(32))) AbstractStage::dsp_scratch[AbstractStage::audioBlockSize];

float AbstractStage::dcBlock(float in)
{
	float a = in - in_dc_old + 0.995f * out_dc_old;
	in_dc_old = in;
	out_dc_old = a;
	return a;
}
