#ifndef METRONOME_H_
#define METRONOME_H_

#include "abstractstage.h"

class Metronome : public AbstractStage
{
public:
	Metronome();
	~Metronome() {};

	void process(float* sampleL, float* sampleR) override;
	void updateParams(const TModuleDescriptor* module) override;

private:

	uint32_t metronom_start;
	uint8_t metronom_fl;
	uint8_t metronom_vol;

	uint16_t metronom_counter{0};
	uint16_t temp_counter{0};
	uint32_t metronom_int{0};
};

extern Metronome metronome;
extern TModuleDescriptor metronomeModuleDescriptor;
extern const uint16_t metronom_cod[3935];

#endif /* METRONOME_H_ */
