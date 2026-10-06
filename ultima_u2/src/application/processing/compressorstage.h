#ifndef _COMPRESSOR_H_
#define _COMPRESSOR_H_

#include "abstractstage.h"

#include "processing/envelope.h"

class CompressorStage: public AbstractStage
{
public:
	~CompressorStage() {};

	enum Parameters
	{
		ENABLED = 0,
		THRESHOLD,
		RATIO,
		VOLUME,
		ATTACK,
		DECAY
	};

	void comp_par(uint32_t val);

	void process(float* sampleL, float* sampleR) override;
	void updateParams(const TModuleDescriptor *module) override;

private:
	Envelope m_envelope;
	float m_thres_db, makeup, m_ratio_lin, m_outlevel, m_keydB, m_coef_at, m_coef_rel;
	float m_ratio = 1.0f;
	int m_toutput;
};

#endif /* _COMPRESSOR_H_ */
