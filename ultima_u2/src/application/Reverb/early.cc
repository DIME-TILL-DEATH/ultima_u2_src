#include "appdefs.h"
#include "DSP_inst1.h"
#include "stdint.h"
#include "reverb.h"
#include "math.h"
#include "init.h"

const uint32_t early_ind_def[30]= {98,767,1226,1307,1530,1927,2210,2379,2724,2807,2930,3143,3248,3508,3638,
		                  543,862,1029,1593,1731,1852,2215,2229,2461,2676,2893,3010,3149,3431,3523};
__attribute__((section(".itcm_data"))) uint32_t early_ind[30];

void early_refl(void)
{
	  uint32_t* earl_index = early_ind;

	  _RAP (16240, -0.700787401574803f);
	  _WZP (16137, 0.700787401574803f);
	  _RAP (16240, 1.0f);
	  _RAP (16320, -0.700787401574803f);
	  _WZP (16241, 0.700787401574803f);
	  _RAP (16320, 1.0f);
	  _RAP (16370, -0.700787401574803f);
	  _WZP (16321, 0.700787401574803f);
	  _RAP (16370, 1.0f);
	  _WZP (2, 0.0f);

	  _RZP (*earl_index++, 0.133858267716535f);
	  _RAP (*earl_index++, 0.110236220472441f);
	  _RAP (*earl_index++, 0.0551181102362205f);
	  _RAP (*earl_index++, 0.0866141732283465f);
	  _RAP (*earl_index++, 0.0866141732283465f);
	  _RAP (*earl_index++, 0.047244094488189f);
	  _RAP (*earl_index++, 0.0393700787401575f);
	  _RAP (*earl_index++, 0.062992125984252f);
	  _RAP (*earl_index++, 0.031496062992126f);
	  _RAP (*earl_index++, 0.031496062992126f);
	  _RAP (*earl_index++, 0.0551181102362205f);
	  _RAP (*earl_index++, 0.031496062992126f);
	  _RAP (*earl_index++, 0.031496062992126f);
	  _RAP (*earl_index++, 0.0236220472440945f);
	  _RAP (*earl_index++, 0.0236220472440945f);
	  _WZP (19943, 0.307086614173228f);
	  _RAP (19938, 0.771653543307087f);
	  _WAP (19937, 1.0f);
	  _WAP (19943, 0.503937007874016f);

	  rev_outL = accumul;

      _RZP (*earl_index++, 0.118110236220472f);
      _RAP (*earl_index++, 0.102362204724409f);
      _RAP (*earl_index++, 0.094488188976378f);
      _RAP (*earl_index++, 0.047244094488189f);
      _RAP (*earl_index++, 0.078740157480315f);
      _RAP (*earl_index++, 0.047244094488189f);
      _RAP (*earl_index++, 0.062992125984252f);
      _RAP (*earl_index++, 0.0393700787401575f);
      _RAP (*earl_index++, 0.0393700787401575f);
      _RAP (*earl_index++, 0.031496062992126f);
      _RAP (*earl_index++, 0.031496062992126f);
      _RAP (*earl_index++, 0.031496062992126f);
      _RAP (*earl_index++, 0.031496062992126f);
      _RAP (*earl_index++, 0.047244094488189f);
      _RAP (*earl_index++, 0.0236220472440945f);
      _WZP (19943, 0.307086614173228f);
      _RAP (19941, 0.771653543307087f);
      _WAP (19940, 1.0f);
      _WAP (19943, 0.503937007874016f);

      rev_outR = accumul;

      if(!ear_point)ear_point = pre_size;
      ear_point--;
}
void early_par(float val)
{
	for(uint32_t i = 0 ; i < 30 ; i++)early_ind[i] = early_ind_def[i] * val;
}
