#ifndef __SPECTRUM_H__
#define __SPECTRUM_H__

#include "appdefs.h"
//TODO #include "display.h"
#include "dsp/fft.h"
#include "math/window.h"

class spectrum_task_t: public task_t
{
public:

	spectrum_task_t(const char *name, const int stack_size, const int priority);
	inline virtual ~spectrum_task_t()
	{

	}
	;

	inline kgp_math::fft& get_fft_0()
	{
		return fft_0;
	}
	;
	inline kgp_math::fft& get_fft_1()
	{
		return fft_1;
	}
	;

	inline bool ready_to_write() const
	{
		return !busy;
	}

private:
	void code();

	inline void process()
	{
		resume();
	}

#if DEBUG
     void PrintNoteTable();
     void PrintBassGuitarTable();
     void PrintSpertrum(vec* in, size_t N);
     void PrintSpertrumDB(float* in, float low_level, size_t N );
     void Sinus( float Fin, float Fs, size_t N, vec* in, size_t offset = 0 );
     void SinusRepos( kgp_math::fft& fft, float f, float Fs, size_t N, size_t offset = 0 );
#endif

	inline void tone_meter();
	inline void tone_table();

	float inline half_tone(float index, const float ref_freq = 440.0f)
	{
		return ref_freq * vdt::fast_powf(2.0f, (index - 57.0f) / 12.0f);
	}

	void inline tone2note_and_diff(float tone, size_t &note, float &freq_diff, const float ref_freq = 440.0f)
	{
		note = 0.5f + 57 + 12 * vdt::fast_logf(tone / ref_freq) / vdt::fast_logf(2.0f);
		//      ^ round trip

		extern volatile float Fswe;
		Fswe = tone;

		freq_diff = tone - half_tone(note);
	}

	size_t guitar_classic_index_table[6];
	size_t guitar_bass_index_table[6];

	kgp_math::fft fft_0;
	kgp_math::fft fft_1;

	float Kmes;            // измеренный индекс отсчета спектра
	float tone;
	char const *note_name;
	float freq_diff;

	float ffts_x2_uS, uS_find_tone, note_and_diff_uS;

	bool busy;
};

extern spectrum_task_t *spectrum_task;

void SpectrumBuffsUpdate(float u);

#endif /*__SPECTRUM_H__*/
