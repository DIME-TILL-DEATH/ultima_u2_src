#ifndef _PROCESSING_CONFIGS_CABSIM_CONFIG_H_
#define _PROCESSING_CONFIGS_CABSIM_CONFIG_H_

#include "appdefs.h"
#include "preset.h"

struct TCabsimFile;
typedef struct TCabsimFile TCabsimFile;
typedef TCabsimFile TCabsimConfig;

TPreset makePresetFromCabsimConfig(const TCabsimConfig& config);

typedef struct TCabsimFile
{
	uint8_t od_on;		// 0
	uint8_t preamp_on;
	uint8_t amp_on;
	uint8_t cab_on;
	uint8_t eq_on;
	uint8_t eq_position;
	uint8_t er_on;

	/* eq */
	uint8_t eq1;				// 7
	uint8_t eq2;
	uint8_t eq3;
	uint8_t eq4;
	uint8_t eq5;

	/* preamp */
	uint8_t preamp_vol;
	uint8_t preamp_lo;
	uint8_t preamp_mi;
	uint8_t preamp_hi;			// 15
	uint8_t preamp_pos;

	/* amplifier */
	uint8_t a_vol;
	uint8_t presen_vol;
	uint8_t amp_slave;
	uint8_t a_t;

	/* reverb */
	uint8_t r_vol;
	uint8_t r_typ;
	uint8_t r_time;		// 23
	uint8_t r_size;
	uint8_t r_dump;
	uint8_t r_lp;
	uint8_t r_hp;
	uint8_t r_det;
	uint8_t r_diff;
	uint8_t r_pre;
	uint8_t rev_tail;		// 31

	/* delay */
	uint8_t d_vol;
	uint8_t reserved1;
	uint8_t d_fed;
	uint8_t d_lp;
	uint8_t d_hp;
	uint8_t d_pan;
	uint8_t dp_vol;
	uint8_t dp_pan;		// 39
	uint8_t dp_d;
	uint8_t d_mod;
	uint8_t d_ra;
	uint8_t d_dir;
	uint8_t d_tim_hi;
	uint8_t d_tim_lo;
	uint8_t d_tap_t;
	uint8_t d_tail;		// 47

	/* early reflections */
	uint8_t ear_del_vol;
	uint8_t ear_del_size;
	uint8_t pres_lev;
	uint8_t cab_vol;

	/* overdrive */
	uint8_t od_typ;
	uint8_t od_vol;

	/* compressor */
	uint8_t compr_on;
	uint8_t c_thr;			// 55
	uint8_t c_rat;
	uint8_t c_vol;
	uint8_t c_at;
	uint8_t c_rel;
	uint8_t od_low;
	uint8_t od_mid;
	uint8_t od_high;

	/* eq band freq */
	uint8_t fr1;				// 63
	uint8_t fr2;
	uint8_t fr3;
	uint8_t fr4;
	uint8_t fr5;

	/* eq band q */
	uint8_t q1;
	uint8_t q2;
	uint8_t q3;
	uint8_t q4;				// 71
	uint8_t q5;

	/* presence */
	uint8_t pr_on;

	/* lohi */
	uint8_t lop;
	uint8_t hip;
	uint8_t hip_on;
	uint8_t lop_on;

	uint8_t fx_type;

	/* fx switch */
	uint8_t Ng;				// 79
	uint8_t Ng_th;
	uint8_t Ng_th_;
	uint8_t Compres;
	uint8_t Pr;
	uint8_t Pr_;
	uint8_t Amp;
	uint8_t Cab;
	uint8_t Equa;				// 87
	uint8_t LPF;
	uint8_t HPF;
	uint8_t Presenc;
	uint8_t FX;
	uint8_t FX_typ;
	uint8_t Tun_on;
	uint8_t Cl_volum;
	uint8_t Cl_volum_;			// 95
	uint8_t Od_vol;
	uint8_t Od_vol_;
	uint8_t Pr_low;
	uint8_t Pr_low_;
	uint8_t Pr_mid;
	uint8_t Pr_mid_;
	uint8_t Pr_hi;
	uint8_t Pr_hi_;			// 103
	uint8_t Od_low;
	uint8_t Od_low_;
	uint8_t Od_mid;
	uint8_t Od_mid_;
	uint8_t Od_hi;
	uint8_t Od_hi_;
	uint8_t Amp_volum;
	uint8_t Amp_volum_;			// 111
	uint8_t Amp_slave;
	uint8_t Amp_slave_;
	uint8_t Amp_presence;
	uint8_t Amp_presence_;
	uint8_t Del_volume;
	uint8_t Del_volume_;
	uint8_t Ear_volume;
	uint8_t Ear_volume_;			// 119
	uint8_t Rev_volume;
	uint8_t Rev_volume_;

	/* selector */
	uint8_t sel_ng;
	uint8_t sel_ng_th;
	uint8_t sel_compr;
	uint8_t sel_pr;
	uint8_t sel_cl_vol;
	uint8_t sel_dr_vol;			// 127
	uint8_t sel_cl_low;
	uint8_t sel_cl_mid;
	uint8_t sel_cl_hi;
	uint8_t sel_dr_low;
	uint8_t sel_dr_mid;
	uint8_t sel_dr_hi;
	uint8_t sel_amp;
	uint8_t sel_amp_vol;			// 135
	uint8_t sel_amp_sl;
	uint8_t sel_amp_pres;
	uint8_t sel_cabsim;
	uint8_t sel_eq;
	uint8_t sel_lopass;
	uint8_t sel_hipass;
	uint8_t sel_pres;
	uint8_t sel_eff;			// 143
	uint8_t sel_eff_t;
	uint8_t sel_del_v;
	uint8_t set_ear_v;
	uint8_t sel_rev_v;
	uint8_t sel_tun_on;

	/* expr preset */
	uint8_t ex_pr_lo;
	uint8_t ex_pr_hi;
	uint8_t ex_cln_lo;			// 151
	uint8_t ex_cln_hi;
	uint8_t ex_drv_lo;
	uint8_t ex_drv_hi;
	uint8_t ex_am_vo_lo;
	uint8_t ex_am_vo_hi;
	uint8_t ex_am_sl_lo;
	uint8_t ex_am_sl_hi;
	uint8_t ex_presen_lo;			// 159
	uint8_t ex_presen_hi;

	/* internal fsw */
	uint8_t ifs_type;
	uint8_t rev_fed;
	uint8_t rev_nofed;
	uint8_t del_ex_tap;
	uint8_t ir_mix;
	uint8_t ga_on;
	uint8_t ga_th;				// 167
	uint8_t ga_at;
	uint8_t ga_de;

	/* preamp gain */
	uint8_t prc_gain;
	uint8_t prl_gain;
	uint8_t prh_gain;
	uint8_t prf_LP1;
	uint8_t prf_LP1_st;
	uint8_t prf_HP1;				// 175
	uint8_t prf_HP1_st;
	uint8_t prf_LP2;
	uint8_t prf_LP2_st;
	uint8_t prf_HP2;
	uint8_t prf_HP2_st;
	uint8_t pr_gain1;
	uint8_t pr_over;

	/* phaser */
	uint8_t phaz_on;			// 183
	uint8_t ph_mix;
	uint8_t ph_rate;
	uint8_t ph_cent;
	uint8_t ph_width;
	uint8_t ph_fb;
	uint8_t ph_stag;
	uint8_t ph_hpf;
	uint8_t ph_poz;			// 191

	/* flanger */
	uint8_t flan_on;
	uint8_t fl_mix;
	uint8_t fl_lfo;
	uint8_t fl_rat;
	uint8_t fl_widt;
	uint8_t fl_del;
	uint8_t fl_fb;
	uint8_t fl_hpf;			// 199
	uint8_t fl_poz;

	/* fs modulation */
	uint8_t Phaz;
	uint8_t Flang;
	uint8_t sel_ph;
	uint8_t sel_fl;
	uint8_t ld_low;
	uint8_t ld_mid;
	uint8_t ld_high;			// 207
	uint8_t pr_over_cl;
	uint8_t pr_over_cr;
	uint8_t pr_over_ld;
	uint8_t reamp_mod_;
	uint8_t sel_preamp_mod_;
	uint8_t Lid_gain;
	uint8_t Lid_gain_;
	uint8_t Lid_vol;			// 215
	uint8_t Lid_vol_;
	uint8_t Lid_low;
	uint8_t Lid_low_;
	uint8_t Lid_mid;
	uint8_t Lid_mid_;
	uint8_t Lid_hig;
	uint8_t Lid_hig_;
	uint8_t sel_lid_gain;			// 223
	uint8_t sel_lid_vol;
	uint8_t sel_lid_low;
	uint8_t sel_lid_mid;
	uint8_t sel_lid_hig;

	/* preamp gain fs */
	uint8_t Preampgain;
	uint8_t Preampgain_;
	uint8_t Cranch_gain;
	uint8_t Cranch_gain_;			// 231
	uint8_t sel_cl_gain;
	uint8_t sel_cr_gain;

	/* tuner */
	uint8_t Tu;
	uint8_t sel_tu;
}TCabsimFile;

#endif /* _PROCESSING_CONFIGS_CABSIM_CONFIG_H_ */
