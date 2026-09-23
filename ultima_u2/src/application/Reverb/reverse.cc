#include "appdefs.h"
#include "DSP_inst.h"
#include "stdint.h"
#include "reverb.h"

const uint32_t mem_plan_init_reve[15] = {191,304,93,573,4191,1107,3057,2098,2068,632,3534,1116,3048,1397,2171};// -------------------|
const uint32_t mem_outL_init_reve[15] = {1609,3384,5232,6619,8379,9913,11634,13222,15351,16651,18189,23366,19694,21954,25171};//---| hall4
const uint32_t mem_outR_init_reve[15] = {932,2623,4359,5747,7462,9212,10726,12552,14459,15939,17352,18940,22360,20890,24294};//-----|
const uint32_t mem_d11_shift_init_reve[8] = {29,2277,4277,6900,402,1277,3277,6000};//---------------------------------------------|
uint32_t mem_d11_shift_init_reve1[8] = {290,2277,4277,6900,302,2077,4077,6400};

void rev_adr_init_reve(float val)
{
	chor_shift = 195 * val;
	chor_shift1 = 228 * val;

	for(int i = 0 ; i < 15 ; i++)
	{
		mem_plan[i] = mem_plan_init_reve[i] * val;
		mem_outL[i] =  mem_outL_init_reve[i] * val;
		mem_outR[i] =  mem_outR_init_reve[i] * val;
	}
	for(int i = 0 ; i < 8 ; i++)
	{
		if(rev_typ == 6)mem_d11_shift[i] = mem_d11_shift_init_reve[i] * val;
		else mem_d11_shift[i] = mem_d11_shift_init_reve1[i] * val;
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

void reve(void)
{
	   uint32_t* mem_d11_shif = mem_d11_shift;

	   volatile int i = 0;

	   if(rev_typ == 6)RAP(filt1_2, 0.677165354330709f);
	   else RAP(filt1_2, 0.62992125984252f);
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
	   if(rev_typ == 6)
	   {
		   RZP(dela11 + *mem_d11_shif++, 0.094488188976378f);
		   RAP(dela11 + *mem_d11_shif++, 0.196850393700787f);
		   RAP(dela11 + *mem_d11_shif++, 0.346456692913386f);
		   RAP(dela11 + *mem_d11_shif++, 0.503937007874016f);
	   }
	   else {
		   RZP(dela11 + *mem_d11_shif++, 0.503937007874016f);
		   RAP(dela11 + *mem_d11_shif++, 0.299212598425197f);
		   RAP(dela11 + *mem_d11_shif++, 0.196850393700787f);
		   RAP(dela11 + *mem_d11_shif++, 0.299212598425197f);
	   }
	   WZP(filt2_1, filt_fed1);
	   RAP(filt2_2, filt_fed2);
	   WAPC(filt2_1,0.0f);
	   chor(chor_m1 + chor_shift);
	   WCP(temp_rev, -rev_diff);
	   WZP(chor_m1, rev_diff);
	   RAP(temp_rev, 1.0f);
//-----------------------------------------------------
	   WZP(dela1,0.0f);
	   RAP(dela1_1, 1.102362204724410f);
	   RAP(dela2_1, -rev_diff);
//-----------------------------------------------------------
	   WZP(dela2,rev_diff);
	   RAP(dela2_1, 1.0f);
	   WZP(dela3, 0.0f);
	   RAP(dela3_1, 0.944881889763780f);
	   RAP(dela4_1, -rev_diff);
//-------------------------------------------------------------
	   WZP(dela4,rev_diff);
	   RAP(dela4_1, 1.0f);
	   WZP(dela5, 0.0f);
	   if(rev_typ == 6)
	   {
		   RZP(dela11 + *mem_d11_shif++, 0.094488188976378f);
		   RAP(dela11 + *mem_d11_shif++, 0.196850393700787f);
		   RAP(dela11 + *mem_d11_shif++, 0.346456692913386f);
		   RAP(dela11 + *mem_d11_shif++, 0.503937007874016f);
	   }
	   else {
		   RZP(dela11 + *mem_d11_shif++, 0.503937007874016f);
		   RAP(dela11 + *mem_d11_shif++, 0.299212598425197f);
		   RAP(dela11 + *mem_d11_shif++, 0.196850393700787f);
		   RAP(dela11 + *mem_d11_shif++, 0.299212598425197f);
	   }
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
	   if(rev_typ == 6)RAP(dela6_1, 1.504f);
	   else RAP(dela6_1, 0.952755905511811f);
	   RAP(dela7_1, -rev_diff);
	   WZP(dela7, rev_diff);
	   RAP(dela7_1, 1.0f);
	   WZP(dela8, 0.0f);
	   RAP(dela8_1, 0.850393700787402f);
	   if(rev_typ == 6)RAP(dela8_1, 0.653543307086614f);
	   else RAP(dela8_1, 0.346456692913386f);
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
