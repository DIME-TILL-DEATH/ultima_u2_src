#include "appdefs.h"
#include "DSP_inst.h"
#include "stdint.h"
#include "reverb.h"

uint32_t mem_plan_init_hall[15] = {214,342,105,644,4715,1246,3449,2360,2326,711,3976,1256,3429,1571,2442};// -------------------|
uint32_t mem_outL_init_hall[15] = {1807,3803,5882,7444,9423,11159,13095,14882,17276,18738,20469,26293,22163,24705,28323};//---| hall4
uint32_t mem_outR_init_hall[15] = {1046,2948,4901,6462,8393,10361,12074,14128,16273,17938,19526,21313,24961,23508,27336};//-----|
uint32_t mem_d11_shift_init_hall[8] = {1000,3324,1338,2153,1124,3933,1635,2907};//---------------------------------------------|

void rev_adr_init_hall(float val)
{
	chor_shift = 195 * val;
	chor_shift1 = 228 * val;

	for(int i = 0 ; i < 15 ; i++)
	{
		mem_plan[i] = mem_plan_init_hall[i] * val;
		mem_outL[i] =  mem_outL_init_hall[i] * val;
		mem_outR[i] =  mem_outR_init_hall[i] * val;
	}
	for(int i = 0 ; i < 8 ; i++)
	{
		mem_d11_shift[i] = mem_d11_shift_init_hall[i] * val;
	}
	volatile int i = 0;
	alp1_1 =  alp1 + mem_plan[i++];
	alp2 = alp1_1 + 1;
	alp2_1 =  alp2 + mem_plan[i++];
	alp3 = alp2_1 + 1;
	alp3_1 =  alp3 + mem_plan[i++];
	chor_m1 = alp3_1 + 1;
	chor_m1_1 = chor_m1 + mem_plan[i++];
	dela1 = chor_m1_1 + 1;
	dela1_1 = dela1 + mem_plan[i++];
	dela2 = dela1_1 + 1;
	dela2_1 = dela2 + mem_plan[i++];
	dela3 = dela2_1 + 1;
	dela3_1 = dela3 + mem_plan[i++];
	dela4 = dela3_1 + 1;
	dela4_1 = dela4 + mem_plan[i++];
	dela5 = dela4_1 + 1;
	dela5_1 = dela5 + mem_plan[i++];
	chor_m2 = dela5_1 + 1;
	chor_m2_1 = chor_m2 + mem_plan[i++];
	dela6 = chor_m2_1 + 1;
	dela6_1 = dela6 + mem_plan[i++];
	dela7 = dela6_1 + 1;
	dela7_1 = dela7 + mem_plan[i++];
	dela8 = dela7_1 + 1;
	dela8_1 = dela8 + mem_plan[i++];
	dela9 = dela8_1 + 1;
	dela9_1 = dela9 + mem_plan[i++];
	dela10 = dela9_1 + 1;
	dela10_1 = dela10 + mem_plan[i++];
	dela11 = dela10_1 + 1;
}
volatile float ch_rat = 0.000145f;
void hall(void)
{
	   uint32_t* mem_d11_shif = mem_d11_shift;
	   volatile int i = 0;

	   RAP(filt1_2, 0.574803149606299f);
	   WZP(filt1_1, 0.992125984251969f);
	   RAP(filt1_2, -0.992125984251969f);
	   RAP(filt1_3, 0.984251968503937f);
	   WAP(filt1_2, 1.0f);
//----------------------------------------------------
	   RAP(alp1_1, -rev_diff);
	   WZP(alp1, rev_diff);
	   RAP(alp1_1, 1.0f);
	   RAP(alp2_1, -rev_diff);
	   WZP(alp2, rev_diff);
	   RAP(alp2_1, 1.0f);
	   RAP(alp3_1, -rev_diff);
	   WZP(alp3, rev_diff);
	   RAP(alp3_1, 1.0f);

	   WZP(dela11,0.0f);
//-------------------------------------------------------
	   RZP(dela11+mem_d11_shift[i++], 0.362204724409449f);
	   RAP(dela11+mem_d11_shift[i++], 0.440944881889764f);
	   RAP(dela10_1, rev_time);
	   WZP(filt2_1, filt_fed1);
	   RAP(filt2_2, filt_fed2);
	   WAPC(filt2_1,0.0f);
	   chor(chor_m1 + chor_shift);
	   WCP(temp_rev, -rev_diff);
	   WZP(chor_m1, rev_diff);
	   RAP(temp_rev, 1.0f);
//-----------------------------------------------------
	   WZP(dela1,0.0f);
	   RZP(dela11+mem_d11_shift[i++], 0.440944881889764f);
	   RAP(dela1_1, rev_time);
	   RAP(dela2_1, -rev_diff);
	   WZP(dela2, rev_diff);
	   RAP(dela2_1, 1.0f);
//-----------------------------------------------------------
	   WZP(dela3,0.0f);
	   RZP(dela11+mem_d11_shift[i++], 0.440944881889764f);
	   RAP(dela3_1, rev_time);
	   RAP(dela4_1, -rev_diff);
	   WZP(dela4, rev_diff);
	   RAP(dela4_1, 1.0f);
//-------------------------------------------------------------
	   WZP(dela5,0.0f);
	   RZP(dela11+mem_d11_shift[i++], 0.362204724409449f);
	   RAP(dela11+mem_d11_shift[i++], 0.440944881889764f);
	   RAP(dela5_1, rev_time);
	   WZP(filt3_1, filt_fed1);
	   RAP(filt3_2, filt_fed2);
	   WAPC(filt3_1,0.0f);
	   chor(chor_m2 + chor_shift1);
	   WCP(temp_rev, -rev_diff);
	   WZP(chor_m2, rev_diff);
	   RAP(temp_rev, 1.0f);
//----------------------------------------------------------------
	   WZP(dela6,0.0f);
	   RZP(dela6_1, 0.031496062992126f);
	   RAP(filt4_2, 0.968503937007874f);
	   WZP(filt4_1, -0.149606299212598f);
	   RAP(dela11+mem_d11_shift[i++], 0.440944881889764f);
	   RAP(dela6_1, rev_time);
	   RAP(dela7_1, -rev_diff);
	   WZP(dela7, rev_diff);
	   RAP(dela7_1, 1.0f);
//----------------------------------------------------------------
	   WZP(dela8,0.0f);
	   RZP(dela11+mem_d11_shift[i++], 0.440944881889764f);
	   RAP(dela8_1, rev_time);
	   RAP(dela9_1, -rev_diff);
	   WZP(dela9, rev_diff);
	   RAP(dela9_1, 1.0f);
//----------------------------------------------------------------
	   WZP(dela10,0.0f);

	   uint32_t* mem_out_l = mem_outL;
	   RZP(*mem_out_l++, 0.503937007874016f);
	   RAP(*mem_out_l++, -0.503937007874016f);
	   RAP(*mem_out_l++, 0.377952755905512f);
	   RAP(*mem_out_l++, -0.503937007874016f);
	   RAP(*mem_out_l++, 0.377952755905512f);
	   RAP(*mem_out_l++, 0.503937007874016f);
	   RAP(*mem_out_l++, -0.503937007874016f);
	   RAP(*mem_out_l++, 0.377952755905512f);
	   RAP(*mem_out_l++, -0.503937007874016f);
	   RAP(*mem_out_l++, 0.377952755905512f);
	   RAP(*mem_out_l++, 0.503937007874016f);
	   RAP(*mem_out_l++, -0.503937007874016f);
	   RAP(*mem_out_l++, -0.503937007874016f);
	   RAP(*mem_out_l++, 0.377952755905512f);
	   RAP(*mem_out_l++, 0.385826771653543f);
	   rev_outL = accumul;

	   uint32_t* mem_out_r = mem_outR;
	   RZP(*mem_out_r++, 0.503937007874016f);
	   RAP(*mem_out_r++, -0.503937007874016f);
	   RAP(*mem_out_r++, 0.377952755905512f);
	   RAP(*mem_out_r++, 0.503937007874016f);
	   RAP(*mem_out_r++, -0.503937007874016f);
	   RAP(*mem_out_r++, 0.377952755905512f);
	   RAP(*mem_out_r++, -0.503937007874016f);
	   RAP(*mem_out_r++, 0.377952755905512f);
	   RAP(*mem_out_r++, -0.503937007874016f);
	   RAP(*mem_out_r++, 0.503937007874016f);
	   RAP(*mem_out_r++, 0.377952755905512f);
	   RAP(*mem_out_r++, -0.503937007874016f);
	   RAP(*mem_out_r++, 0.503937007874016f);
	   RAP(*mem_out_r++, 0.377952755905512f);
	   RAP(*mem_out_r++, -0.503937007874016f);
	   rev_outR = accumul;
}
