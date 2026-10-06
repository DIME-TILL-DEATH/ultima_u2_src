#include "abstractstage.h"

float AbstractStage::dcBlock(float in)
{
	float a = in - in_dc_old + 0.995f * out_dc_old;
	in_dc_old = in;
	out_dc_old = a;
	return a;
}
