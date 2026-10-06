#include "compressorstage.h"

#include "math.h"
#include "init.h"
#include <vdt/vdt.h>

void CompressorStage::comp_par(uint32_t val)
{
	uint8_t va = val >> 8;
	val &= 0xff;

	switch(val & 0xff)
	{
		case 1:
			m_thres_db = -(sqrt_f32_main(va) * (36.0f/sqrt_f32_main(127.0f)) + 24.0f); //implicit type cast int to float
			break;
		case 2:
			m_ratio_lin = va * (120.0f/127.0f) + 7.0f;
			m_ratio = (127 - va) * (1.0f/127.0f);
			break;
		case 3:
			m_toutput = va * (20.0f/127.0f);
			break;
		case 4:
			m_coef_at = fast_exp(-1000.0f / ((va * (17.0f/127.0f) + 0.5f) * 48000.0f));
			break;
		case 5:
			m_coef_rel = fast_exp(-1000.0f / ((va * (1000.0f/127.0f) + 100.0f) * 48000.0f));
			break;
	}

	float thres_mx = m_thres_db;  //This is the value of the input when the output is at t+k
	makeup = -m_thres_db + thres_mx/m_ratio_lin;
	float makeuplin = dB2rap(makeup);

	m_outlevel = (dB2rap((float)m_toutput) * makeuplin) * 0.01f;
}

void CompressorStage::process(float* sampleL, float* sampleR)
{
	if(!m_enabled) return;

	for(uint8_t i=0; i<audioBlockSize; i++)
	{
		float bu_sum = fabsf(sampleL[i]);
		bu_sum += m_envelope.DC_OFFSET;
		m_keydB = rap2dB(bu_sum);
		float overdB = m_keydB - m_thres_db;	// delta over threshold
		if(overdB < 0.0f)
			overdB = 0.0f;
		overdB += m_envelope.DC_OFFSET;
		m_envelope.m_envdB = m_envelope.process(overdB, m_coef_at, m_coef_rel);
		overdB = m_envelope.m_envdB - m_envelope.DC_OFFSET;
		float gr = overdB * (m_ratio - 1.0f);
		gr = dB2rap(gr) * m_outlevel;
		sampleL[i] *= gr;

		if(sampleR != nullptr) sampleR[i] *= gr;
	}
}

void CompressorStage::updateParams(const TModuleDescriptor* module)
{
	if(module == nullptr) return;

	m_enabled = module->parameter[CompressorStage::ENABLED].value;

	for(uint8_t i = 1; i < 6; i++)
		comp_par(i | (module->parameter[i].value << 8));
}
