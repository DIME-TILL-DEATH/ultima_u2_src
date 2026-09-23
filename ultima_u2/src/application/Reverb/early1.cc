#include "appdefs.h"
#include "DSP_inst.h"
#include "stdint.h"
#include "reverb.h"
const int early_ind_def[30]= {98,767,1226,1307,1530,1927,2210,2379,2724,2807,2930,3143,3248,3508,3638,
		                  543,862,1029,1593,1731,1852,2215,2229,2461,2676,2893,3010,3149,3431,3523};
uint32_t early_ind1[30];
void early_init(float val)
{
	for(int i = 0 ; i < 30 ; i++)early_ind1[i] = early_ind_def[i] * val;
}

void early1 (void)
{
	uint32_t* earl_index = early_ind1;

	accumul *= 4.0f;

	  RAP (16240, -0.700787401574803f);
	  WZP (16137, 0.700787401574803f);
	  RAP (16240, 1.0f);
	  RAP (16320, -0.700787401574803f);
	  WZP (16241, 0.700787401574803f);
	  RAP (16320, 1.0f);
	  RAP (16370, -0.700787401574803f);
	  WZP (16321, 0.700787401574803f);
	  RAP (16370, 1.0f);
	  WZP (2, 0.0f);

	  RZP (*earl_index++, 0.133858267716535f);
	  RAP (*earl_index++, 0.110236220472441f);
	  RAP (*earl_index++, 0.0551181102362205f);
	  RAP (*earl_index++, 0.0866141732283465f);
	  RAP (*earl_index++, 0.0866141732283465f);
	  RAP (*earl_index++, 0.047244094488189f);
	  RAP (*earl_index++, 0.0393700787401575f);
	  RAP (*earl_index++, 0.062992125984252f);
	  RAP (*earl_index++, 0.031496062992126f);
	  RAP (*earl_index++, 0.031496062992126f);
	  RAP (*earl_index++, 0.0551181102362205f);
	  RAP (*earl_index++, 0.031496062992126f);
	  RAP (*earl_index++, 0.031496062992126f);
	  RAP (*earl_index++, 0.0236220472440945f);
	  RAP (*earl_index++, 0.0236220472440945f);
	  WZP (16377, 0.307086614173228f);
	  RAP (16372, 0.771653543307087f);
	  WAP (16371, 1.0f);
	  WAP (16377, 0.503937007874016f);

	  rev_outL = accumul;

      RZP (*earl_index++, 0.118110236220472f);
      RAP (*earl_index++, 0.102362204724409f);
      RAP (*earl_index++, 0.094488188976378f);
      RAP (*earl_index++, 0.047244094488189f);
      RAP (*earl_index++, 0.078740157480315f);
      RAP (*earl_index++, 0.047244094488189f);
      RAP (*earl_index++, 0.062992125984252f);
      RAP (*earl_index++, 0.0393700787401575f);
      RAP (*earl_index++, 0.0393700787401575f);
      RAP (*earl_index++, 0.031496062992126f);
      RAP (*earl_index++, 0.031496062992126f);
      RAP (*earl_index++, 0.031496062992126f);
      RAP (*earl_index++, 0.031496062992126f);
      RAP (*earl_index++, 0.047244094488189f);
      RAP (*earl_index++, 0.0236220472440945f);
      WZP (16377, 0.307086614173228f);
      RAP (16375, 0.771653543307087f);
      WAP (16374, 1.0f);
      WAP (16377, 0.503937007874016f);

      rev_outR = accumul;
}
