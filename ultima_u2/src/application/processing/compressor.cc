#include "compressor.h"

#include "preset.h"

void Compressor::comp_par(uint32_t val)
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

void Compressor::updateParams(const TModuleDescriptor* module)
{
	if(module == nullptr) return;

	for(uint8_t i = 1; i < 6; i++)
		comp_par(i | (module->parameter[i].value << 8));
}
