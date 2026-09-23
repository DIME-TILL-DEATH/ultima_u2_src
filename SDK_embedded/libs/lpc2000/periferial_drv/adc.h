#ifndef __ADC_H__
#define __ADC_H__


void set_adc0( char channals , unsigned int sample_freq  );
void start_adc0();
void stop_adc0();
unsigned int get_adc0_val(unsigned int chanal);
unsigned int get_adc1_val(unsigned int chanal);

#endif /*_ADC_H__*/
