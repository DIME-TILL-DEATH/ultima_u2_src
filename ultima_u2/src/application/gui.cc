//gui_task->update();  приведет к обновлению в gui_task_t::code()
#include "preset.h"

//---------------
#include "processing/configs/cabsim_config.h"
//----------------
#include "gui/compressormenu.h"
//------------------

#include "format.h"

#include "init.h"
#include "string.h"
#include "gui.h"
#include "math.h"

#include "amp_imp.h"
#include "filt.h"
#include "FirststFilt.h"
#include "Gate.h"
#include "compressor.h"
#include "distor.h"
#include "phaser.h"
#include "flanger.h"
#include "fs_browser.h"

#include "tasks/display_task.h"

AbstractMenu* mainMenu = nullptr;

extern Gate gate_pres;
extern Gate gate_glob;
extern Compressor compr;
extern Distor dist;
extern PassFilt hpFilt;
extern PassFilt lpFilt;
extern Phaser phaser;
extern Flanger flanger;

gui_task_t *gui_task;

__attribute__((section(".dtcm_data"))) uint8_t impulse_buf[4096];
__attribute__((section(".itcm_data"))) uint8_t prog_data[256];
__attribute__((section(".itcm_data"))) uint8_t prog_data_t[256];
__attribute__((section(".itcm_data"))) uint8_t sw_temp[SWtempCount];

uint8_t sys_data[64];

int8_t preset_com[7] =
{ -40, 8, 0, 0, 0, 0, 0 };

system_file_t system_file;

uint8_t right_ind_fl;
uint8_t left_ind_fl;
uint8_t prog;
uint8_t prog1;
uint8_t prog_old = 1;
uint8_t prog_flag = 1;
uint8_t condish = 0;
uint8_t tim4_fl = 0;
uint8_t encoder_fl = 0;
uint8_t encoder_fl1 = 0;
uint8_t encoder_but = 0;
uint8_t encoder_but_dub_short = 0;
uint8_t encoder_but_dub_long = 0;
uint8_t edit_but = 0;
uint8_t edit_fl = 0;
uint8_t encoder_but_dub_short_fl = 0;
uint8_t encoder_but_dub_long_fl = 0;
uint8_t foot_sw_dub_short = 0;
uint8_t foot_sw_dub_long = 0;
uint8_t ext_but_long_fl = 0;
uint8_t fs_but;
uint8_t cut = 0;
float lopas;
float hipas;
float ear_vol = 1.0f;
uint8_t par_num = 0;
uint8_t eq_num;
uint8_t key_shift = 0;
volatile uint8_t nam_sym_temp;
uint8_t num_men_temp;
int8_t filt_temp = 0;
int8_t filt_temp_q = 0;
emb_string str_temp;
emb_string preset_str;
uint8_t imya[15];
uint8_t imya1[15];
uint8_t imya_t[15];
uint8_t imya1_t[15];
uint8_t imya_temp;
volatile uint8_t impulse_flag = 0;
imp_data_t impulse_data;
uint8_t adcinv_fl = 0;
volatile uint8_t ind_clean = 0;
volatile uint8_t ind_clean1 = 0;
uint8_t del_men_fl = 0;
uint16_t delay_time;
uint8_t master_volume = 127;
char wave0[128];
char wave1[128];
uint8_t load_i = 0;
uint8_t indic_impul = 0;
uint32_t tap_global;
float del_in_contr = 1.0f;
volatile uint8_t brow_point;
uint8_t tempo = 120;
uint8_t f_sw_sel = 7;
uint8_t f_sw_set = 0;
uint8_t ext_fs_sel = 1;

void del_param(uint32_t val);

const uint8_t imya_init[16]
{ "Preset        " };
const uint8_t imya_init1[16]
{ "Name          " };
const uint8_t eq_list[][10] =
{ "Equalizer", "Position" };
const uint8_t eq_band_list[][13] =
{ "Frequency", "Bandwidth(Q)" };
const uint8_t eq_pos_list[][5] =
{ "Pre ", "Post" };

const uint8_t save_list[][4] =
{ "YES", " NO", "RTN", "CL" };
const uint8_t preamp_list[][7] =
{ "Preamp", "Model", "Gain", "Volume", "Low", "Mid", "High" };
const uint8_t preamp_typ_list[][11] =
{ "Off       ", "Clean     ", "Crunch    ", "Lead      " };

const uint8_t amp_list[][7] =
{ "PwAmp", "Volume", "Presnc", "Slave", "Type" };

const uint8_t fs_list[][12] =
{ "NG", "NG THR", "CM", "PH", "FL", "PR Type", "PR Model", "PR CL Gain", "PR CL Volum", "PR CL Low", "PR CL Mid ", "PR CL High ", "PR CR Gain", "PR CR Volum",
		"PR CR Low", "PR CR Mid ", "PR CR High ", "PR LD Gain", "PR LD Volum", "PR LD Low", "PR LD Mid ", "PR LD High ", "PA", "PA Volume", "PA Slave",
		"PA Presnc ", "IR CabSim", "EQ", "LPF", "HPF", "Presence", "DL/RV", "DL/RV Type", "DL Volume", "ER Volume", "RV Volume", "Tuner" };

const uint8_t fs_list_index[] =
{ 0, 1, 3, 122, 123, 4, 132, 149, 15, 19, 21, 23, 151, 17, 25, 27, 29, 134, 136, 138, 140, 142, 6, 31, 33, 35, 7, 8, 9, 10, 11, 12, 13, 37, 39, 41, 14 };
const uint8_t sel_list_index[] =
{ 0, 1, 2, 81, 82, 3, 122, 110, 4, 6, 7, 8, 111, 5, 9, 10, 11, 101, 102, 103, 104, 105, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 25, 26, 27 };
const uint8_t model_preamp_list[][8]
{ "Off Off", " 1   2 ", " 1   3 ", " 2   1 ", " 3   1 ", " 2   3 ", " 3   2 " };

const uint8_t fs_t_list[][8] =
{ "Off Off", "Off On ", "On  Off" };
const uint8_t fs_ef_list[][8] =
{ "Off Off", "Off On ", "On  Off" };

const uint8_t pr_type_fs[][8] =
{ "Off Off", "Off CL ", "CL  Off", "Off CR ", "CR  Off", "Off LD ", "LD  Off", "CL  CR ", "CR  CL ", "CL  LD ", "LD  CL ", "CR  LD ", "LD  CR" };
const uint8_t eff_type_fs[][8] =
{ "Off Off", "DL  RV ", "RV  DL " };

const uint8_t on_off[][4] =
{ "Off", "On " };
const uint8_t off_on[][4] =
{ "On ", "Off" };
const uint8_t off_on_list[][5] =
{ "Off ", "Pre ", "Post" };
const uint8_t pr_po[][8] =
{ "Off Off", "Off Pre", "Pre Off", "Off Pst", "Pst Off" };
const uint8_t filt_list[][10] =
{ "LPF", "Frequency", "HPF", "Frequency", "Presence", "Level" };
const uint8_t save_[] = "Save?";
const uint8_t usb_t[][12] =
{ "Serial Port", " USB Drive " };
const uint8_t usb_m[] = "USB Usage";
const uint8_t ascii_low1[] = " abcdefghijklmnopqrst";
const uint8_t ascii_low2[] = "uvwxyz0123456789!@#$%";
const uint8_t ascii_hig1[] = "ABCDEFGHIJKLMNOPQRSTU";
const uint8_t ascii_hig2[] = "VWXYZ{}()-+_=<>?*.,/&";
const uint8_t menu_list[][16] =
{ "[NG] Noise Gate", "[CM] Compressor", "[PH] Phaser", "[FL] Flanger", "[PR] Preamp", "[PA] PowerAmp", "[IR] CabSim", "[EQ] Equalizer" };
const uint8_t menu_list1[][14] =
{ "[FT] Filters", "[FX] DL/RV", "Preset Level", "Int F.SW", "Int F.SW list", "Ext F.SW list", "EXP. list", "Rename" };
const uint8_t ext_fsw_l[][3] =
{ "A1", "A2", "B1", "B2" };
const uint8_t fsw_ind[][21] =
{ " Ext F.SW A1  Off On", " Ext F.SW A2  Off On", " Ext F.SW B1  Off On", " Ext F.SW B2  Off On" };
const uint8_t fsw_ind1[][21] =
{ " Int F.Switch Off On", " Ext F.SW A1  Off On", " Ext F.SW A2  Off On", " Ext F.SW B1  Off On", " Ext F.SW B2  Off On" };
const uint8_t menu_list2[][15] =
{ "Ext F.SW A", "Ext F.SW B/Exp", "  ", "MIDI Channel", "Global N.Gate", "Global IR", "Metronome" };
const uint8_t menu_list3[][10] =
{ "Metronome", "Tempo", "Volume" };
const uint8_t ifs_list[][11] =
{ "CTRL/PRST", "CTRL/TAP " };
const uint8_t menu_list11[][12] =
{ "Peamp vol", "Amp vol", "Amp Slave", "Reverb vol", "Reverb time" };
const uint8_t amp_t_list[][11] =
{ "Default   ", "PP 6L6    ", "PP EL34   ", "SE 6L6    ", "SE EL34   ", "AMT TC-3  ", "California", "British M ", "British L ", "Calif Mod ", "Calif Vint",
		"PVH PR0RS0", "PVH PR5RS5", "PVH PR8RS7", "PVH PR9RS8" };
const uint8_t cab_list[][13] =
{ "IR", "Vol/Mix", "WAV Browser" };
const uint8_t fs_type[][10] =
{ "Instantly", "OnRelease", "OnHold   " };
const uint8_t exp_list[][11] =
{ "Preset Vol", "PR CL Vol", "PR DR Vol", "PA Volume", "PA Slave", "PA Presnc" };
const uint8_t od_list[][7] =
{ "OD", "Type", "Volume", "Low", "Mid", "High" };
const uint8_t od_type_list[][5] =
{ "Low ", "High" };
const uint8_t eff_list[][8] =
{ "FX Type", "Edit" };
const uint8_t eff_type[][7] =
{ "Delay ", "Reverb" };
const uint8_t del_list[][9] =
{ "Volume", "Time", "FDBK", "LPF", "HPF", "DL Pan", "DL2 Vol", "DL2 Pan", "DL>>DL2", "DL Mdl", "M Rate", "Direct", "Tail", "ER Vol.", "ER Size" };
const uint8_t del_dir[][8] =
{ "Forward", "Reverse" };
const uint8_t del_tim_l[][13] =
{ "Time", "TAP", "Ext.F.SW TAP" };
const uint8_t tap_tim[][6] =
{ "1/1  ", "1/1.5", "1/2  ", "1/3  ", "1/4  ", "2/1  " };
const float tap_tim_v[6] =
{ 1.0f, 0.6666f, 0.5f, 0.3333f, 0.25f, 2.0f };
const uint8_t del_ex_t[][4] =
{ "Off", "A1 ", "A2 ", "B1 ", "B2 " };
const uint8_t fs_inv[][10] =
{ "Direct   ", "Inverse  ", "MIDI     ", "2-Preamps", "CTR. A   " };
const uint8_t rev_list[][7] =
{ "Volume", "Type", "Time", "Size", "Damp", "LPF", "HPF", "Detune", "Diffus", "PreDL", "PreFDB", "NoPrDL", "Tail" };
const uint8_t rev_type_list[][10] =
{ "Early ref", "Hall     ", "Room     ", "Plate    ", "Spring   ", "Gate     ", "Reverse  " };
const uint8_t ear_list[][10] =
{ "Early ref", "Volume", "Size" };
const uint8_t gate_list[][10] =
{ "N.Gate", "Threshold", "Attack", "Decay" };

const uint8_t compressor_list[][10] =
{ "Compress.", "Threshold", "Ratio", "Volume", "Attack", "Decay" };

const uint8_t filt_typ[][6] =
{ "Off  ", "-6dB", "-12dB", "-18dB" };

const uint8_t pr_filt_menu[][10] =
{ "LPF1_frec", "LPF1_fac ", "HPF1_frec", "HPF1_fac ", "LPF2_frec", "LPF2_fac ", "HPF2_frec", "HPF2_fac " };

const uint8_t phas_list[][7] =
{ "Phaser", "Mix", "Rate", "Center", "Width", "FDBK", "Stage", "HPF" };
const uint8_t phas_stag_list[][3] =
{ "4 ", "6 ", "8" };
const uint8_t phas_stag_type[4] =
{ 3, 5, 7 };

const uint8_t fl_list[][8] =
{ "Flanger", "Mix", "LFO", "Rate", "Width", "Delay", "FDBK", "HPF", "Poz" };
const uint8_t fl_t[][9] =
{ "Triangle", "Sinus   ", "Sinus X3" };
const uint8_t fl_list_t[][4] =
{ "Off", "x1 ", "x3 " };

const uint8_t fl_in[4] =
{ 63, 0, 31, 50 };
const uint8_t ph_in[4] =
{ 127, 49, 0, 55 };

volatile uint8_t asdf = 47;
volatile uint8_t asdf1 = 47;
volatile uint8_t asdf2 = 47;
volatile uint8_t asdf3 = 47;
volatile uint8_t asdf4 = 47;

void tim4_start(uint8_t val)
{
	tim4.update_interrupt_flag_clear();
	tim4.counter = 0xffff;
	tim4_fl = val;
}

void drive_init(void)
{
	float temp;
	display_task->clear();
	for(uint8_t i = 0;i < 8;i++)
	{
		display_task->line_5x7(0, i, (char*) pr_filt_menu + i * 10, 0);
		switch(i)
		{
		case 0:
			temp = powf(195 - prog_data[prf_LP1], 2.0) * (19000.0 / powf(195.0, 2.0)) + 1000.0;
			display_task->line_5x7_clean(80, i, "     ");
			emb_printf::sprintf(str_temp, "%1", (uint16_t) temp);
			display_task->line_5x7(80, i, (char*) str_temp.c_str(), 0);
			break;
		case 1:
			display_task->line_5x7(80, i, (char*) filt_typ + prog_data[prf_LP1_st] * 6, 0);
			break;
		case 2:
			temp = prog_data[prf_HP1] * (980.0f / 255.0f) + 20.0f;
			display_task->line_5x7_clean(80, i, "     ");
			emb_printf::sprintf(str_temp, "%1", (uint16_t) temp);
			display_task->line_5x7(80, i, (char*) str_temp.c_str(), 0);
			break;
		case 3:
			display_task->line_5x7(80, i, (char*) filt_typ + prog_data[prf_HP1_st] * 6, 0);
			break;
		case 4:
			temp = powf(195 - prog_data[prf_LP2], 2.0) * (19000.0 / powf(195.0, 2.0)) + 1000.0;
			display_task->line_5x7_clean(80, i, "     ");
			emb_printf::sprintf(str_temp, "%1", (uint16_t) temp);
			display_task->line_5x7(80, i, (char*) str_temp.c_str(), 0);
			break;
		case 5:
			display_task->line_5x7(80, i, (char*) filt_typ + prog_data[prf_LP2_st] * 6, 0);
			break;
		case 6:
			temp = prog_data[prf_HP2] * (980.0f / 255.0f) + 20.0f;
			display_task->line_5x7_clean(80, i, "     ");
			emb_printf::sprintf(str_temp, "%1", (uint16_t) temp);
			display_task->line_5x7(80, i, (char*) str_temp.c_str(), 0);
			break;
		case 7:
			display_task->line_5x7(80, i, (char*) filt_typ + prog_data[prf_HP2_st] * 6, 0);
			break;
		}
	}
	condish = over_menu;
	par_num = 0;
	edit_fl = 0;
	tim4_start(1);
}

void compress_init(void)
{
//	display_task->clear();
//	for(uint8_t i = 0;i < 6;i++)
//	{
//		display_task->line_5x7(0, i, (char*) compressor_list + i * 10, 0);
//		if(i)
//			display_task->par_indic(65, i, prog_data[compr_on + i]);
//		else
//			display_task->line_5x7(65, i, (char*) on_off + prog_data[compr_on] * 4, 0);
//	}
	condish = compresss_men;

	currentMenu = new CompressorMenu(mainMenu, gui_menu_type::MENU_COMPRESSOR, &currentPreset.module[1]);
	currentMenu->show();

	par_num = 0;
	edit_fl = 0;
	tim4_start(1);
}
void eq_band_print(uint8_t flag)
{
	if(!flag)
	{
		display_task->line_5x7_clean(74, 0, "     ");
		emb_printf::sprintf(str_temp, "%1", (uint16_t) freq1[par_num - 2]);
		display_task->line_5x7(74, 0, (char*) str_temp.c_str(), 0);
	}
	else
	{
		display_task->line_5x7_clean(80, 1, "    ");
		emb_printf::sprintf(str_temp, "%1.1", (filt_temp_q + 100.0f) * 0.1f + 0.11f);
		display_task->line_5x7(80, 1, (char*) str_temp.c_str(), 0);
	}
}
void start_eq_band_edit(void)
{
	filt_temp = (int8_t) prog_data[fr1 + par_num - 2];
	filt_temp_q = (int8_t) prog_data[q1 + par_num - 2];
	display_task->clear();
	display_task->line_5x7(0, 0, (char*) eq_band_list, 0);
	eq_band_print(0);
	display_task->line_5x7(115, 0, (char*) "Hz", 0);
	display_task->line_5x7(0, 1, (char*) eq_band_list + 13, 0);
	eq_band_print(1);
	condish = eq_para;
	eq_num = 0;
	tim4_start(1);
}
void set_fir_amp(uint8_t num)
{
	int a = num_tab_amp - 1;
	switch(num)
	{
	case 0:
		coef_amp[a--] = 1.0f;
		for(int i = 0;i < (num_tab_amp - 1);i++)
			coef_amp[a--] = 0.0f;
		break;
	case 1:
		for(int i = 0;i < num_tab_amp;i++)
			coef_amp[a--] = PP_6L6[i];
		break;
	case 2:
		for(int i = 0;i < num_tab_amp;i++)
			coef_amp[a--] = PP_EL34[i];
		break;
	case 3:
		for(int i = 0;i < num_tab_amp;i++)
			coef_amp[a--] = SE_6L6[i];
		break;
	case 4:
		for(int i = 0;i < num_tab_amp;i++)
			coef_amp[a--] = SE_EL34[i];
		break;
	case 5:
		for(int i = 0;i < num_tab_amp;i++)
			coef_amp[a--] = tc_1[i];
		break;
	case 6:
		for(int i = 0;i < num_tab_amp;i++)
			coef_amp[a--] = fender[i];
		break;
	case 7:
		for(int i = 0;i < num_tab_amp;i++)
			coef_amp[a--] = jcm800[i];
		break;
	case 8:
		for(int i = 0;i < num_tab_amp;i++)
			coef_amp[a--] = lc50[i];
		break;
	case 9:
		for(int i = 0;i < num_tab_amp;i++)
			coef_amp[a--] = mes_vint[i];
		break;
	case 10:
		for(int i = 0;i < num_tab_amp;i++)
			coef_amp[a--] = mes_mod[i];
		break;
	case 11:
		for(int i = 0;i < num_tab_amp;i++)
			coef_amp[a--] = Pr0_Re0_5150[i];
		break;
	case 12:
		for(int i = 0;i < num_tab_amp;i++)
			coef_amp[a--] = Pr5_Re5_5150[i];
		break;
	case 13:
		for(int i = 0;i < num_tab_amp;i++)
			coef_amp[a--] = Pr8_Re7_5150[i];
		break;
	case 14:
		for(int i = 0;i < num_tab_amp;i++)
			coef_amp[a--] = Pr9_Re8_5150[i];
		break;
	}
}
void param_set(void)
{
	switch(prog_data[preamp_on])
	{
	case 0:
	case 1:
		prog_data[od_on] = 0;
		gpioc.pin2_set();
		break;
	case 2:
		prog_data[od_on] = 1;
		gpioc.pin2_reset();
		gpioc.pin3_reset();
		break;
	case 3:
		m_vol_fl = 1;
		prog_data[od_on] = 1;
		gpioc.pin2_reset();
		gpioc.pin3_set();
		break;
	}
	pream_vol = powf(prog_data[preamp_vol], 2.0f) * (1.0f / powf(127.0f, 2.0f));
	for(uint8_t i = 0;i < 3;i++)
		pre_param(i, coeff_preamp, (int8_t) prog_data[preamp_lo + i]);
	od_volume = powf(prog_data[od_vol], 2.0f) * (1.0f / powf(127.0f, 2.0f));
	if(prog_data[preamp_on] == 2)
		for(uint8_t i = 0;i < 3;i++)
			pre_param(i, coeff_preamp, (int8_t) prog_data[od_low + i]);
	else if(prog_data[preamp_on] == 3)
		for(uint8_t i = 0;i < 3;i++)
			pre_param(i, coeff_preamp, (int8_t) prog_data[ld_low + i]);
	pr_ga = prog_data[prc_gain + prog_data[preamp_on] - 1] * prog_data[prc_gain + prog_data[preamp_on] - 1] * 0.001178002f + 1.0f;

	switch(prog_data[pr_over_cl + prog_data[preamp_on] - 1])
	{
	case 0:
		dist.clip_LPF(8000.0f, 0);
		dist.clip_LPF(8000.0f, 1);
		dist.clip_HPF(120.0f, 0);
		dist.clip_HPF(120.0f, 1);
		break;
	case 1:
		dist.clip_LPF(4000.0f, 0);
		dist.clip_LPF(4000.0f, 1);
		dist.clip_HPF(20.0f, 0);
		dist.clip_HPF(20.0f, 1);
		break;
	case 2:
		dist.clip_LPF(3000.0f, 0);
		dist.clip_LPF(3000.0f, 1);
		dist.clip_HPF(20.0f, 0);
		dist.clip_HPF(20.0f, 1);
		break;
	}

	for(uint8_t i = 0;i < 3;i++)
		gate_pres.gate_par(i | (prog_data[i + ga_th] << 8));
	for(uint8_t i = 1;i < 6;i++)
		compr.comp_par(i | (prog_data[i + compr_on] << 8));
	for(uint8_t i = 0;i < 8;i++)
		phaser.phaser_par(i | (prog_data[i + phaz_on]) << 8);
	for(uint8_t i = 0;i < 8;i++)
		flanger.fl_param(i | (prog_data[i + flan_on]) << 8);

	amp_vol = powf(prog_data[a_vol], 2.0f) * (20.0f / powf(127.0f, 2.0f)) + 1.0f;
	amp_sla = powf(prog_data[amp_slave], 4.0f) * (0.99f / powf(127.0f, 4.0f)) + 0.01f;
	set_fir_amp(prog_data[a_t]);
	p_vol = powf(prog_data[pres_lev], 2.0f) * (1.0f / powf(127.0f, 2.0f));
	for(uint8_t i = 0;i < 5;i++)
		filt_ini(i, prog_data + fr1, prog_data + q1);
	for(uint8_t i = 0;i < 5;i++)
		set_filt(i, prog_data[eq1 + i]);
	lopas = powf(195 - prog_data[lop], 2.0f) * (19000.0f / powf(195.0f, 2.0f)) + 1000.0f;
	lpFilt.SetLPF(lopas);
	hipas = prog_data[hip] * (980.0f / 255.0f) + 20.0f;
	hpFilt.SetHPF(hipas);
	set_shelf(prog_data[presen_vol] * (31.0f / 127.0f));
	cab_volume = powf(prog_data[cab_vol], 2.0f) * (1.0f / powf(127.0f, 2.0f));
	for(uint8_t i = 0;i < 10;i++)
		rever_par(i | (prog_data[i + r_vol] << 8));
	rev_fb_val = prog_data[rev_fed] * (0.9f / 127.0f);
	rev_nopr = prog_data[rev_nofed] * (1.0f / 127.0f);
	revmem_clean();
	ear_vol = (prog_data[ear_del_vol] * prog_data[ear_del_vol]) * 6.2000124000248e-5;
	rev_n = prog_data[ear_del_size] * (8.3553f / 127.0f) + 0.3f;
	early_par(rev_n);
	for(uint8_t i = 0;i < 14;i++)
		del_param(i | (prog_data[i + d_vol] << 8));
	delay_time = (del_p1 / 48000.0f) * 1000.0f;
	del_in_contr = 1.0f;
	if(prog_data[FX] == 2 || prog_data[FX_typ])
		prog_data[er_on] = 1;
	if(prog_data[del_ex_tap])
		tap_ext_fl = 1;
}
void edit_init(uint8_t par)
{
	display_task->clear();
	for(uint8_t i = 0;i < 8;i++)
	{
		display_task->line_5x7(17, i, (char*) menu_list + i * 16, 0);
		switch(i)
		{
		case 0:
			display_task->QuadPrint(6, i, prog_data[ga_on]);
			break;
		case 1:
			display_task->QuadPrint(6, i, prog_data[compr_on]);
			break;
		case 2:
			display_task->QuadPrint(6, i, prog_data[phaz_on]);
			break;
		case 3:
			display_task->QuadPrint(6, i, prog_data[flan_on]);
			break;
		case 4:
			display_task->QuadPrint(6, i, prog_data[preamp_on]);
			break;
		case 5:
			display_task->QuadPrint(6, i, prog_data[amp_on]);
			break;
		case 6:
			if(impulse_flag && prog_data[cab_on])
				display_task->QuadPrint(6, i, 1);
			else
				display_task->QuadPrint(6, i, 0);
			break;
		case 7:
			display_task->QuadPrint(6, i, prog_data[eq_on]);
			break;
		}
	}
	display_task->Strel_print(117, 7, 0);
	condish = men_edit;
	par_num = par;
	edit_fl = 0;
	tim4_start(1);
}
void edit_init1(uint8_t par)
{
	display_task->clear();
	if(prog_data[hip_on] || prog_data[lop_on] || prog_data[pr_on])
		display_task->QuadPrint(6, 0, 1);
	else
		display_task->QuadPrint(6, 0, 0);
	display_task->line_5x7(17, 0, (char*) menu_list1, 0);
	display_task->QuadPrint(6, 1, prog_data[er_on]);
	display_task->line_5x7(17, 1, (char*) menu_list1 + 14, 0);
	for(uint8_t i = 2;i < 8;i++)
		display_task->line_5x7(6, i, (char*) menu_list1 + i * 14, 0);
	display_task->line_5x7(59, 3, (char*) ifs_list + prog_data[ifs_type] * 11, 0);
	display_task->line_5x7(91, 5, (char*) ext_fsw_l, 0);
	display_task->Strel_print(117, 0, 1);
	condish = men_edit1;
	par_num = par;
	edit_fl = f_sw_set = 0;
	ext_fs_sel = 1;
	tim4_start(1);
}
void sys_init(uint8_t num)
{
	display_task->clear();
	display_task->line_5x7(0, 0, (char*) "-------System--------", 0);
	for(uint8_t i = 0;i < 7;i++)
	{
		display_task->line_5x7(0, i + 1, (char*) menu_list2 + i * 15, 0);
		switch(i)
		{
		case 0:
			display_task->line_5x7(68, 1, (char*) fs_inv + system_file.fs_inver * 10, 0);
			break;
		case 1:
			if(system_file.f_sw_exp)
			{
				display_task->line_5x7(90, 2, (char*) "CTR.B", 0);
			}
			else
			{
				display_task->line_5x7(90, 2, (char*) "EXP. ", 0);
			}
			break;
		case 2:
			if(!system_file.exp_On_Off || system_file.f_sw_exp == 1)
				display_task->line_5x7(0, 3, (char*) "Exp. OFF", 0);
			else
				display_task->line_5x7(0, 3, (char*) "Exp.Calibrate", 0);
			break;
		case 3:
			display_task->num_5x7(72, 4, system_file.midi_ch + 1, 0);
			display_task->line_5x7(72, 4, (char*) " ", 0);
			break;
		case 5:
			display_task->line_5x7(68, 6, (char*) off_on + system_file.glob_cab * 4, 0);
			break;
		}
	}
	edit_fl = 0;
	condish = system_menu;
	par_num = num;
	eq_num = 0;
	tim4_start(1);
}
void metronome_init(void)
{
	display_task->clear();
	for(uint8_t i = 0;i < 3;i++)
	{
		display_task->line_5x7(0, i, (char*) menu_list3 + i * 10, 0);
		switch(i)
		{
		case 0:
			display_task->line_5x7(63, i, (char*) on_off + metronom_start * 4, 0);
			break;
		case 1:
			display_task->num_5x7(63, 1, tempo, 0);
			break;
		case 2:
			display_task->par_indic(60, 2, metronom_vol);
			break;
		}
	}
	edit_fl = 0;
	condish = metronome_menu;
	par_num = 0;
	tim4_start(1);
}
void tun_init(void)
{
	m_vol_fl = 1;
	while(m_vol_fl != 2)
		;
	ind_clean = 1;
	while(!ind_clean1)
		;
	tuner_use = 1;
	proc_run = 0;
	ind_clean = 1;
	display_task->TunInit();
	prog_data_t[1] = prog_data[compr_on];
	prog_data[compr_on] = 1;
	compr.comp_par(1 | 50 << 8);
	compr.comp_par(2 | 30 << 8);
	p_vol = 0.0f;
	m_vol_fl = 0;
	condish = tuner;
}
void gate_init(uint8_t num)
{
	display_task->clear();
	for(uint8_t i = 0;i < 4;i++)
	{
		display_task->line_5x7(0, i, (char*) gate_list + i * 10, 0);
		if(!num)
		{
			switch(i)
			{
			case 0:
				display_task->line_5x7(62, i, (char*) on_off + prog_data[ga_on] * 4, 0);
				break;
			case 1:
				display_task->par_indic(62, i, prog_data[ga_th]);
				break;
			case 2:
				display_task->par_indic(62, i, prog_data[ga_at]);
				break;
			case 3:
				display_task->par_indic(62, i, prog_data[ga_de]);
				break;
			}
		}
		else
		{
			switch(i)
			{
			case 0:
				display_task->line_5x7(62, i, (char*) on_off + system_file.gat_on * 4, 0);
				break;
			case 1:
				display_task->par_indic(62, i, system_file.gat_thresh);
				break;
			case 2:
				display_task->par_indic(62, i, system_file.gat_att);
				break;
			case 3:
				display_task->par_indic(62, i, system_file.gat_dec);
				break;
			}
		}
	}
	eq_num = num;
	condish = gate_menu;
	edit_fl = 0;
	par_num = 0;
	tim4_start(0);
}
void phaz_init(void)
{
	display_task->clear();
	for(uint8_t i = 0;i < 8;i++)
	{
		display_task->line_5x7(0, i, (char*) phas_list + i * 7, 0);
		switch(i)
		{
		case 0:
			display_task->line_5x7(62, i, (char*) off_on_list + prog_data[phaz_on] * 5, 0);
			break;
		case 6:
			display_task->line_5x7(74, i, (char*) phas_stag_list + prog_data[ph_stag] * 3, 0);
			break;
		default:
			display_task->par_indic(62, i, prog_data[phaz_on + i]);
			break;
		}
	}
	condish = phaz_edit;
	edit_fl = 0;
	par_num = 0;
	tim4_start(1);
}
void flan_init(void)
{
	display_task->clear();
	for(uint8_t i = 0;i < 8;i++)
	{
		display_task->line_5x7(0, i, (char*) fl_list + i * 8, 0);
		switch(i)
		{
		case 0:
			display_task->line_5x7(62, i, (char*) off_on_list + prog_data[flan_on] * 5, 0);
			break;
		case 1:
			display_task->mix_indic(62, i, prog_data[fl_mix], 0);
			break;
		case 2:
			display_task->line_5x7(62, i, (char*) fl_t + prog_data[fl_lfo] * 9, 0);
			break;
		default:
			display_task->par_indic(62, i, prog_data[flan_on + i]);
			break;
		}
	}
	condish = flan_edit;
	edit_fl = 0;
	par_num = 0;
	tim4_start(1);
}
void cab_init(uint8_t val)
{
	display_task->clear();
	for(uint8_t i = 0;i < 3;i++)
		display_task->line_5x7(3, i, (char*) cab_list + i * 13, 0);
	if(prog_data[cab_on])
		display_task->line_5x7(75, 0, (char*) "On ", 0);
	else
		display_task->line_5x7(75, 0, (char*) "Off", 0);
	if(!load_i && !impulse_flag)
		display_task->line_5x7(30, 3, (char*) "No impulse", 0);
	else
	{
		if(!load_i)
			display_task->line_5x7(1, 3, (char*) &wave0[3], 0);
		else
		{
			fs_browser_task->browser_name(str_temp);
			display_task->line_5x7(1, 3, str_temp.c_str(), 0);
		}
	}
	condish = cab_onoff;
	edit_fl = 0;
	par_num = val;
	tim4_start(0);
}
void preamp_init_disp(void)
{
	display_task->clear();
	int8_t temp1;
	for(uint8_t i = 0;i < 7;i++)
	{
		display_task->line_5x7(6, i, (char*) preamp_list + i * 7, 0);
		switch(i)
		{
		case 0:
			display_task->line_5x7(60, i, (char*) preamp_typ_list + prog_data[preamp_on] * 11, 0);
			break;
		case 1:
			if(prog_data[preamp_on])
				display_task->num_5x7(48, i, prog_data[pr_over_cl + prog_data[preamp_on] - 1] + 1, 0);
			else
				display_task->num_5x7(48, i, 1, 0);
			display_task->line_5x7(48, i, (char*) "  ", 0);
			break;
		case 2:
			display_task->par_indic(60, i, prog_data[prc_gain + prog_data[preamp_on] - 1]);
			break;
		case 3:
			if(prog_data[preamp_on] < 2)
			{
				display_task->par_indic(60, i, prog_data[preamp_vol]);
			}
			else
			{
				display_task->par_indic(60, i, prog_data[od_vol]);
			}
			break;
		case 4:
		case 5:
		case 6:
			switch(prog_data[preamp_on])
			{
			case 1:
				temp1 = prog_data[preamp_lo + i - 4];
				display_task->par_indic(60, i, temp1 + 64);
				break;
			case 2:
				temp1 = prog_data[od_low + i - 4];
				display_task->par_indic(60, i, temp1 + 64);
				break;
			case 3:
				temp1 = prog_data[ld_low + i - 4];
				display_task->par_indic(60, i, temp1 + 64);
				break;
			}
			break;
		}
	}
}
void preamp_init(void)
{
	preamp_init_disp();
	condish = preamp_menu;
	edit_fl = 0;
	par_num = 0;
	tim4_start(1);
}
void amp_init(void)
{
	display_task->clear();
	uint8_t temp;
	for(uint8_t i = 0;i < 5;i++)
	{
		temp = i - 1;
		display_task->line_5x7(6, i, (char*) amp_list + i * 7, 0);
		switch(i)
		{
		case 0:
			if(!prog_data[amp_on])
				display_task->line_5x7(60, i, (char*) "Off", 0);
			else
				display_task->line_5x7(60, i, (char*) "On ", 0);
			break;
		case 1:
		case 2:
		case 3:
			display_task->par_indic(60, i, prog_data[a_vol + temp]);
			break;
		case 4:
			display_task->line_5x7(60, i, (char*) amp_t_list + prog_data[a_t] * 11, 0);
			break;
		}
	}
	condish = amp_menu;
	edit_fl = 0;
	par_num = 0;
	tim4_start(1);
}
void eq_init_men(uint8_t val)
{
	condish = equalis;
	edit_fl = 0;
	display_task->EqInit();
	if(!val)
		par_num = 0;
	else
		display_task->line_5x7(0, 3, (char*) "Press hold for edit", 2);
	tim4_start(0);
}
void eff_init(uint8_t val)
{
	display_task->clear();
	for(uint8_t i = 0;i < 2;i++)
		display_task->line_5x7(6, i, (char*) eff_list + i * 8, 0);
	if(!prog_data[er_on])
		display_task->line_5x7(60, 0, (char*) "Off    ", 0);
	else
		display_task->line_5x7(60, 0, (char*) eff_type + prog_data[fx_type] * 7, 0);
	condish = eff_menu;
	edit_fl = 0;
	par_num = val;
	tim4_start(1);
}
void init_edit_r(void)
{
	display_task->clear();
	for(uint8_t i = 0;i < 8;i++)
	{
		uint8_t temp = i + r_vol;
		display_task->line_5x7(6, i, (char*) rev_list + i * 7, 0);
		if(i == 1)
			display_task->line_5x7(60, i, (char*) rev_type_list + prog_data[r_typ] * 10, 0);
		else
		{
			display_task->par_indic(60, i, prog_data[temp]);
			switch(prog_data[r_typ])
			{
			case 0:
				display_task->line_5x7(60, 2, (char*) " ---     ", 0);
				display_task->line_5x7(60, 4, (char*) " ---     ", 0);
				display_task->line_5x7(60, 7, (char*) " ---     ", 0);
				break;
			case 4:
				if(i == 3 || i == 4 || i == 7)
					display_task->line_5x7(60, i, (char*) " ---     ", 0);
				else
					display_task->par_indic(60, i, prog_data[temp]);
				break;
			case 5:
			case 6:
				if(i == 2 || i == 7)
					display_task->line_5x7(60, i, (char*) " ---     ", 0);
				else
					display_task->par_indic(60, i, prog_data[temp]);
				break;
			}
		}
	}
	condish = reverb_menu;
	edit_fl = 0;
	display_task->ic_print(0, 2);
	par_num = 0;
	tim4_start(1);
	clean_fl();
}
void delay_init(uint8_t num)
{
	condish = del_menu;
	display_task->clear();
	for(uint8_t i = 0;i < 8;i++)
	{
		display_task->line_5x7(6, i, (char*) del_list + i * 9, 0);
		switch(i)
		{
		case 1:
			display_task->del_time_ind(60, i, del_p1 / 48, 1);
			break;
		case 0:
		case 2:
		case 3:
		case 4:
		case 6:
			display_task->par_indic(60, i, prog_data[d_vol + i]);
			break;
		case 5:
		case 7:
			display_task->pan_indic(60, i, prog_data[d_vol + i]);
			break;
		}
	}
	display_task->ic_print(0, 2);
	edit_fl = del_men_fl = 0;
	par_num = num;
	tim4_start(1);
	clean_fl();
}
inline void ind_fs_sr(void)
{
	switch(prog_data[sel_ng + par_num])
	{
	case 0:
		display_task->line_5x7(0, 0, (char*) fsw_ind1 + (f_sw_set - 1) * 21, 1);
		break;
	case 1:
		display_task->line_5x7(0, 0, (char*) " Int F.Switch Off On", 1);
		break;
	case 2:
		display_task->line_5x7(0, 0, (char*) fsw_ind, 1);
		break;
	case 3:
		display_task->line_5x7(0, 0, (char*) fsw_ind + 21, 1);
		break;
	case 4:
		display_task->line_5x7(0, 0, (char*) fsw_ind + 42, 1);
		break;
	case 5:
		display_task->line_5x7(0, 0, (char*) fsw_ind + 63, 1);
		break;
	}
}
inline void __attribute__ ((always_inline)) foot_switch_init(uint8_t pos)
{
	uint8_t pos_temp;
	ind_fs_sr();
	for(uint8_t i = 0;i < 7;i++)
	{
		pos_temp = i + pos;
		display_task->line_5x7(6, i + 1, (char*) "           ", 0);
		display_task->line_5x7(6, i + 1, (char*) fs_list + pos_temp * 12, 0);
		switch(pos_temp)
		{
		case 0:
		case 2:
		case 22:
		case 26:
		case 27:
		case 28:
		case 29:
			display_task->line_5x7(84, i + 1, (char*) fs_t_list + prog_data[Ng + fs_list_index[pos_temp]] * 8, 0);
			break;
		case 3:
		case 4:
			display_task->line_5x7(84, i + 1, (char*) pr_po + prog_data[Ng + fs_list_index[pos_temp]] * 8, 0);
			break;
		case 5:
			display_task->line_5x7(84, i + 1, (char*) pr_type_fs + prog_data[Ng + fs_list_index[pos_temp]] * 8, 0);
			break;
		case 6:
			display_task->line_5x7(84, i + 1, (char*) model_preamp_list + prog_data[reamp_mod_] * 8, 0);
			break;
		case 31:
			display_task->line_5x7(84, i + 1, (char*) fs_ef_list + prog_data[Ng + fs_list_index[pos_temp]] * 8, 0);
			break;
		case 32:
			if(!prog_data[Ng + fs_list_index[pos_temp - 1]])
				display_task->line_5x7(84, i + 1, (char*) eff_type_fs + prog_data[Ng + fs_list_index[pos_temp]] * 8, 0);
			else
				display_task->line_5x7(84, i + 1, (char*) "--- ---", 0);
			break;
		default:
			if(prog_data[preamp_on])
			{
				if((!prog_data[Ng + fs_list_index[pos_temp]]) && (!prog_data[Ng + fs_list_index[pos_temp] + 1]))
					display_task->line_5x7(84, i + 1, (char*) fs_t_list, 0);
				else
				{
					display_task->num_5x7(84, i + 1, prog_data[Ng + fs_list_index[pos_temp]], 0);
					display_task->num_5x7(108, i + 1, prog_data[Ng + fs_list_index[pos_temp] + 1], 0);
				}
			}
			else
			{
				if((!prog_data[Ng + fs_list_index[pos_temp]]) && (!prog_data[Ng + fs_list_index[pos_temp] + 1]))
					display_task->line_5x7(84, i + 1, (char*) fs_t_list, 0);
				else
				{
					display_task->num_5x7(84, i + 1, prog_data[Ng + fs_list_index[pos_temp]], 0);
					display_task->num_5x7(108, i + 1, prog_data[Ng + fs_list_index[pos_temp] + 1], 0);
				}
			}
		}
	}
}
void express_init(void)
{
	display_task->clear();
	display_task->line_5x7(0, 0, (char*) " Expression  Min  Max", 1);
	for(uint8_t i = 0;i < 6;i++)
	{
		display_task->line_5x7(6, i + 1, (char*) exp_list + i * 11, 0);
		if(!(prog_data[ex_pr_lo + i * 2]) && !(prog_data[ex_pr_hi + i * 2]))
			display_task->line_5x7(78, i + 1, (char*) "Off  Off", 0);
		else
		{
			display_task->num_5x7(78, i + 1, prog_data[ex_pr_lo + i * 2], 0);
			display_task->num_5x7(108, i + 1, prog_data[ex_pr_hi + i * 2], 0);
		}
	}
	edit_fl = 0;
	condish = exspression_list;
	par_num = 0;
	eq_num = 0;
	tim4_start(1);
}
void filt_init(void)
{
	display_task->clear();
	for(uint8_t i = 0;i < 6;i++)
	{
		display_task->line_5x7(6, i, (char*) filt_list + i * 10, 0);
		switch(i)
		{
		case 0:
			display_task->line_5x7(80, 0, (char*) filt_typ + prog_data[lop_on] * 6, 0);
			break;
		case 1:
			emb_printf::sprintf(str_temp, "%1", (uint16_t) lopas);
			display_task->line_5x7(80, 1, (char*) str_temp.c_str(), 0);
			display_task->line_5x7(115, 1, (char*) "Hz", 0);
			break;
		case 2:
			display_task->line_5x7(80, 2, (char*) filt_typ + prog_data[hip_on] * 6, 0);
			break;
		case 3:
			emb_printf::sprintf(str_temp, "%1", (uint16_t) hipas);
			display_task->line_5x7(80, 3, (char*) str_temp.c_str(), 0);
			display_task->line_5x7(115, 3, (char*) "Hz", 0);
			break;
		case 4:
			display_task->line_5x7(80, 4, (char*) on_off + prog_data[pr_on] * 4, 0);
			break;
		case 5:
			emb_printf::sprintf(str_temp, "%1", (uint16_t) prog_data[presen_vol]);
			display_task->line_5x7(80, 5, (char*) str_temp.c_str(), 0);
			break;
		}
	}
	edit_fl = 0;
	condish = filt_para;
	par_num = 0;
	tim4_start(1);
}
bool is_valid_wave(char *path)
{
	uint8_t wav_hider[4];
	fs_browser_task->read(path, 0, 4, (char*) wav_hider);
	// RIFF
	if(!(wav_hider[0] == 'R' && wav_hider[1] == 'I' && wav_hider[2] == 'F' && wav_hider[3] == 'F'))
	{
		return false;
	}
	fs_browser_task->read(path, 8, 4, (char*) wav_hider);
	// WAVE
	if(!(wav_hider[0] == 'W' && wav_hider[1] == 'A' && wav_hider[2] == 'V' && wav_hider[3] == 'E'))
	{
		return false;
	}

	uint32_t find_data = 12;
	while(1)
	{
		fs_browser_task->read(path, find_data++, 4, (char*) wav_hider);
		if((wav_hider[0] == 'f' && wav_hider[1] == 'm' && wav_hider[2] == 't' && wav_hider[3] == ' '))
			break;
	}
	find_data += 3;
	fs_browser_task->read(path, find_data, 4, (char*) wav_hider); //16 PCM
	if(wav_hider[0] != 16 && wav_hider[0] != 18)
		return false;
	find_data += 4;
	fs_browser_task->read(path, find_data, 2, (char*) wav_hider); //1 PCM
	if(wav_hider[0] != 1)
		return false;
	find_data += 2;
	fs_browser_task->read(path, find_data, 2, (char*) wav_hider); //1 mono
	if(wav_hider[0] != 1)
		return false;
	find_data += 2;
	uint32_t samp_rat;
	fs_browser_task->read(path, find_data, 4, (char*) &samp_rat); // 48000
	if(samp_rat != 48000)
		return false;
	find_data += 10;
	fs_browser_task->read(path, find_data, 2, (char*) wav_hider); //24 bit
	if(wav_hider[0] != 24)
		return false;
	find_data += 2;
	while(1)
	{
		fs_browser_task->read(path, find_data++, 4, (char*) wav_hider);
		if((wav_hider[0] == 'd' && wav_hider[1] == 'a' && wav_hider[2] == 't' && wav_hider[3] == 'a'))
			break;
	}
	find_data += 7;
	fs_browser_task->truncate_wave(path, find_data, 3072, (char*) impulse_buf);
	impulse_flag = 1;
	return true;
}
uint8_t wav_read(char *path)
{
	if(is_valid_wave(path) == true)
	{
		uint16_t temp = 1023;
		for(uint16_t i = 0;i < 1024;i++)
		{
			impulse_data.im_1 = impulse_buf[i * 3];
			impulse_data.im_2 = impulse_buf[i * 3 + 1];
			impulse_data.im_3 = impulse_buf[i * 3 + 2];
			impulse_data.im_0 = 0;
			coef_cab[temp--] = (float) (impulse_data.val >> 8) * 0.000000119f;
		}
		return 0;
	}
	else
		return 1;
}
void load_imp(void)
{
	emb_printf::sprintf(preset_str, "/%2", prog);
	strncpy(wave0, preset_str.c_str(), 127);
	size_t wave_count = fs_browser_task->check_wave(wave0);
	if(!wave_count)
	{
		impulse_flag = 0;
		//if(condish == start_screen)display_task->line_5x7(0,4,(char*)"No impulse",0);
		prog_flag = 1;
		for(uint16_t i = 0;i < 1024;i++)
			coef_cab[i] = 0.0f;
		coef_cab[1023] = 1.0f;
	}
	else
	{
		prog_flag = 0;
		if(is_valid_wave(wave0) != true)
		{
			//if(condish == start_screen)display_task->line_5x7(0,4,(char*)"Not correct wav file",0);
			prog_flag = 1;
			impulse_flag = 0;
			for(uint16_t i = 0;i < 1024;i++)
				coef_cab[i] = 0.0f;
			coef_cab[1023] = 1.0f;
		}
		else
		{
			uint16_t temp = 1023;
			impulse_flag = 1;
			for(uint16_t i = 0;i < 1024;i++)
			{
				impulse_data.im_1 = impulse_buf[i * 3];
				impulse_data.im_2 = impulse_buf[i * 3 + 1];
				impulse_data.im_3 = impulse_buf[i * 3 + 2];
				impulse_data.im_0 = 0;
				coef_cab[temp--] = (float) (impulse_data.val >> 8) * 0.000000119f;
			}
		}
	}
}
void browser_init(void)
{
	brow_point = 0;
	fs_browser_task->priority(1);
	fs_browser_task->browser_name(str_temp);
	fs_browser_task->curr_path(preset_str);
	fs_browser_task->priority(1 - 1);
	if(!preset_str.compare("/Impulses") && !str_temp.compare(".."))
	{
		fs_browser_task->priority(1);
		fs_browser_task->next_notify();
		fs_browser_task->priority(1 - 1);
		fs_browser_task->curr_path(preset_str);
		fs_browser_task->browser_name(str_temp);
	}
	preset_str.append("/" + str_temp);
	if(!fs_browser_task->status_path())
		eq_num = wav_read((char*) preset_str.c_str());
	path_fold(preset_str);
	preset_str.erase(0, 2);
	display_task->clear();
	display_task->line_5x7(0, 0, preset_str.c_str(), 0);
	if(!fs_browser_task->status_path())
		if(eq_num)
			display_task->line_5x7(2, 7, "Not correct wav file", 0);
	condish = browser_menu;
	load_i = 0;
}
inline void controll_run(void)
{
	for(uint8_t i = 0;i < 38;i++)
	{
		switch(i)
		{
		case 0:
			if(prog_data[sel_pr] == f_sw_sel)
			{
				m_vol_fl = 1;
				while(m_vol_fl != 2)
					;
				switch(prog_data[Pr])
				{
				case 0:
					break;
				case 1:
					prog_data[preamp_on] = fs_but;
					prog_data[od_on] = 0;
					gpioc.pin2_set();
					break;
				case 2:
					prog_data[preamp_on] = 1 - fs_but;
					prog_data[od_on] = 0;
					gpioc.pin2_set();
					break;
				case 3:
					prog_data[od_on] = fs_but;
					gpioc.pin3_reset();
					if(fs_but)
					{
						gpioc.pin2_reset();
						prog_data[preamp_on] = 2;
					}
					else
					{
						prog_data[preamp_on] = 0;
						gpioc.pin2_set();
					}
					break;
				case 4:
					prog_data[od_on] = 1 - fs_but;
					gpioc.pin3_reset();
					if(fs_but)
					{
						prog_data[preamp_on] = 0;
						gpioc.pin2_set();
					}
					else
					{
						prog_data[preamp_on] = 2;
						gpioc.pin2_reset();
					}
					break;
				case 5:
					prog_data[od_on] = fs_but;
					gpioc.pin3_set();
					if(fs_but)
					{
						gpioc.pin2_reset();
						prog_data[preamp_on] = 3;
					}
					else
					{
						prog_data[preamp_on] = 0;
						gpioc.pin2_set();
					}
					break;
				case 6:
					prog_data[od_on] = 1 - fs_but;
					gpioc.pin3_set();
					if(fs_but)
					{
						prog_data[preamp_on] = 0;
						gpioc.pin2_set();
					}
					else
					{
						prog_data[preamp_on] = 3;
						gpioc.pin2_reset();
					}
					break;
				case 7:
					prog_data[od_on] = fs_but;
					gpioc.pin3_reset();
					if(fs_but)
					{
						gpioc.pin2_reset();
						prog_data[preamp_on] = 2;
					}
					else
					{
						prog_data[preamp_on] = 1;
						gpioc.pin2_set();
					}
					break;
				case 8:
					prog_data[od_on] = 1 - fs_but;
					gpioc.pin3_reset();
					if(fs_but)
					{
						prog_data[preamp_on] = 1;
						gpioc.pin2_set();
					}
					else
					{
						prog_data[preamp_on] = 2;
						gpioc.pin2_reset();
					}
					break;
				case 9:
					prog_data[od_on] = fs_but;
					gpioc.pin3_set();
					if(fs_but)
					{
						gpioc.pin2_reset();
						prog_data[preamp_on] = 3;
					}
					else
					{
						prog_data[preamp_on] = 1;
						gpioc.pin2_set();
					}
					break;
				case 10:
					prog_data[od_on] = 1 - fs_but;
					gpioc.pin3_set();
					if(fs_but)
					{
						prog_data[preamp_on] = 1;
						gpioc.pin2_set();
					}
					else
					{
						prog_data[preamp_on] = 3;
						gpioc.pin2_reset();
					}
					break;
				case 11:
					prog_data[od_on] = 1;
					gpioc.pin2_reset();
					if(fs_but)
					{
						prog_data[preamp_on] = 3;
						gpioc.pin3_set();
					}
					else
					{
						prog_data[preamp_on] = 2;
						gpioc.pin3_reset();
					}
					break;
				case 12:
					prog_data[od_on] = 1;
					gpioc.pin2_reset();
					if(fs_but)
					{
						prog_data[preamp_on] = 2;
						gpioc.pin3_reset();
					}
					else
					{
						prog_data[preamp_on] = 3;
						gpioc.pin3_set();
					}
					break;
				}
				m_vol_fl = 0;
				/*if(prog_data[preamp_on] || prog_data[od_on])
				 {
				 pr_ga = prog_data[prc_gain + prog_data[preamp_on] - 1] * prog_data[prc_gain + prog_data[preamp_on] - 1] * 0.001178002f + 1.0f;
				 switch(prog_data[pr_over_cl + prog_data[preamp_on] - 1]){
				 case 0:dist.clip_LPF(8000.0f,0);dist.clip_LPF(8000.0f,1);dist.clip_HPF(120.0f,0);dist.clip_HPF(120.0f,1);break;
				 case 1:dist.clip_LPF(4000.0f,0);dist.clip_LPF(4000.0f,1);dist.clip_HPF(20.0f,0);dist.clip_HPF(20.0f,1);break;
				 case 2:dist.clip_LPF(3000.0f,0);dist.clip_LPF(3000.0f,1);dist.clip_HPF(20.0f,0);dist.clip_HPF(20.0f,1);break;
				 }
				 }*/
				if(condish == men_edit)
				{
					if(prog_data[preamp_on] || prog_data[od_on])
						display_task->QuadPrint(6, 2, 1);
					else
						display_task->QuadPrint(6, 2, 0);
				}
				if(condish == start_screen)
					display_task->icon_eff(0);
				if(condish == preamp_menu)
					preamp_init_disp();
			}
			break;
		case 1:
			if(prog_data[sel_tun_on] == f_sw_sel)
			{
				if(condish == start_screen)
				{
					if(prog_data[Tun_on] == 1)
					{
						if(fs_but)
							tun_init();
					}
					else
					{
						if(prog_data[Tun_on] == 2)
						{
							if(!fs_but)
								tun_init();
						}
					}
				}
			}
			break;
		case 2:
			if(prog_data[sel_cl_vol] == f_sw_sel)
			{
				if(prog_data[Cl_volum] || prog_data[Cl_volum_])
				{
					if(fs_but)
						pream_vol = (prog_data[Cl_volum_] * prog_data[Cl_volum_]) * 6.2000124000248e-5;
					else
						pream_vol = (prog_data[Cl_volum] * prog_data[Cl_volum]) * 6.2000124000248e-5;
				}
			}
			break;
		case 3:
			if(prog_data[sel_dr_vol] == f_sw_sel)
			{
				if(prog_data[Od_vol] || prog_data[Od_vol_])
				{
					if(fs_but)
						od_volume = (prog_data[Od_vol_] * prog_data[Od_vol_]) * 6.2000124000248e-5;
					else
						od_volume = (prog_data[Od_vol] * prog_data[Od_vol]) * 6.2000124000248e-5;
				}
			}
			break;
		case 4:
			if(prog_data[sel_cl_low] == f_sw_sel)
			{
				if(prog_data[Pr_low] || prog_data[Pr_low_])
				{
					int8_t temp = (int8_t) prog_data[Pr_low_] - 64;
					if(fs_but)
						pre_param(0, coeff_preamp, temp);
					else
					{
						temp = (int8_t) prog_data[Pr_low] - 64;
						pre_param(0, coeff_preamp, temp);
					}
				}
			}
			break;
		case 5:
			if(prog_data[sel_cl_mid] == f_sw_sel)
			{
				if(prog_data[Pr_mid] || prog_data[Pr_mid_])
				{
					int8_t temp = (int8_t) prog_data[Pr_mid_] - 64;
					if(fs_but)
						pre_param(1, coeff_preamp, temp);
					else
					{
						temp = (int8_t) prog_data[Pr_mid] - 64;
						pre_param(1, coeff_preamp, temp);
					}
				}
			}
			break;
		case 6:
			if(prog_data[sel_cl_hi] == f_sw_sel)
			{
				if(prog_data[Pr_hi] || prog_data[Pr_hi_])
				{
					int8_t temp = (int8_t) prog_data[Pr_hi_] - 64;
					if(fs_but)
						pre_param(2, coeff_preamp, temp);
					else
					{
						temp = (int8_t) prog_data[Pr_hi] - 64;
						pre_param(2, coeff_preamp, temp);
					}
				}
			}
			break;
		case 7:
			if(prog_data[sel_dr_low] == f_sw_sel)
			{
				if(prog_data[Od_low] || prog_data[Od_low_])
				{
					int8_t temp = (int8_t) prog_data[Od_low_] - 64;
					if(fs_but)
						pre_param(0, coeff_preamp, temp);
					else
					{
						temp = (int8_t) prog_data[Od_low] - 64;
						pre_param(0, coeff_preamp, temp);
					}
				}
			}
			break;
		case 8:
			if(prog_data[sel_dr_mid] == f_sw_sel)
			{
				if(prog_data[Od_mid] || prog_data[Od_mid_])
				{
					int8_t temp = (int8_t) prog_data[Od_mid_] - 64;
					if(fs_but)
						pre_param(1, coeff_preamp, temp);
					else
					{
						temp = (int8_t) prog_data[Od_mid] - 64;
						pre_param(1, coeff_preamp, temp);
					}
				}
			}
			break;
		case 9:
			if(prog_data[sel_dr_hi] == f_sw_sel)
			{
				if(prog_data[Od_hi] || prog_data[Od_hi_])
				{
					int8_t temp = (int8_t) prog_data[Od_hi_] - 64;
					if(fs_but)
						pre_param(2, coeff_preamp, temp);
					else
					{
						temp = (int8_t) prog_data[Od_hi] - 64;
						pre_param(2, coeff_preamp, temp);
					}
				}
			}
			break;
		case 10:
			if(prog_data[sel_amp] == f_sw_sel)
			{
				m_vol_fl = 1;
				while(m_vol_fl != 2)
					;
				if(prog_data[Amp] == 1)
					prog_data[amp_on] = fs_but;
				else
					prog_data[amp_on] = 1 - fs_but;
				if(condish == men_edit)
					display_task->QuadPrint(6, 3, prog_data[amp_on]);
				else if(condish == start_screen)
					display_task->icon_eff(0);
				m_vol_fl = 0;
			}
			break;
		case 11:
			if(prog_data[sel_amp_vol] == f_sw_sel)
			{
				if(prog_data[Amp_volum] || prog_data[Amp_volum_])
				{
					uint8_t temp = prog_data[Amp_volum] + (prog_data[Amp_volum_] - prog_data[Amp_volum]) * fs_but;
					amp_vol = (temp * temp) * 0.001240002480005f + 1.0f;
				}
			}
			break;
		case 12:
			if(prog_data[sel_amp_sl] == f_sw_sel)
			{
				if(prog_data[Amp_slave] || prog_data[Amp_slave_])
				{
					uint8_t temp = prog_data[Amp_slave] + (prog_data[Amp_slave_] - prog_data[Amp_slave]) * fs_but;
					amp_sla = (temp * temp * temp * temp) * 3.805575222285667e-9 + 0.01f;
				}
			}
			break;
		case 13:
			if(prog_data[sel_amp_pres] == f_sw_sel)
			{
				if(prog_data[Amp_presence] || prog_data[Amp_presence_])
				{
					uint8_t temp = prog_data[Amp_presence] + (prog_data[Amp_presence_] - prog_data[Amp_presence]) * fs_but;
					set_shelf(temp * 0.2440944881889764f);
				}
			}
			break;
		case 14:
			if(prog_data[sel_cabsim] == f_sw_sel)
			{
				m_vol_fl = 1;
				while(m_vol_fl != 2)
					;
				if(prog_data[Cab] == 1)
					prog_data[cab_on] = fs_but;
				else
					prog_data[cab_on] = 1 - fs_but;
				if(condish == men_edit)
					display_task->QuadPrint(6, 4, prog_data[cab_on]);
				else if(condish == start_screen)
					display_task->icon_eff(0);
				m_vol_fl = 0;
			}
			break;
		case 15:
			if(prog_data[sel_eq] == f_sw_sel)
			{
				m_vol_fl = 1;
				while(m_vol_fl != 2)
					;
				if(prog_data[Equa] == 1)
					prog_data[eq_on] = fs_but;
				else
					prog_data[eq_on] = 1 - fs_but;
				m_vol_fl = 0;
				if(condish == start_screen)
					display_task->icon_eff(0);
				else if(condish == men_edit)
					display_task->QuadPrint(6, 5, prog_data[eq_on]);
			}
			break;
		case 16:
			if(prog_data[sel_lopass] == f_sw_sel)
			{
				m_vol_fl = 1;
				while(m_vol_fl != 2)
					;
				if(prog_data[LPF] == 1)
					prog_data[lop_on] = fs_but;
				else
					prog_data[lop_on] = 1 - fs_but;
				m_vol_fl = 0;
				if(condish == men_edit)
					display_task->QuadPrint(6, 6, prog_data[lop_on]);
				else if(condish == start_screen)
					display_task->icon_eff(0);
			}
			break;
		case 17:
			if(prog_data[sel_hipass] == f_sw_sel)
			{
				m_vol_fl = 1;
				while(m_vol_fl != 2)
					;
				if(prog_data[HPF] == 1)
					prog_data[hip_on] = fs_but;
				else
					prog_data[hip_on] = 1 - fs_but;
				m_vol_fl = 0;
				if(condish == men_edit)
					display_task->QuadPrint(6, 6, prog_data[hip_on]);
				else if(condish == start_screen)
					display_task->icon_eff(0);
			}
			break;
		case 18:
			if(prog_data[sel_pres] == f_sw_sel)
			{
				m_vol_fl = 1;
				while(m_vol_fl != 2)
					;
				if(prog_data[Presenc] == 1)
					prog_data[pr_on] = fs_but;
				else
					prog_data[pr_on] = 1 - fs_but;
				m_vol_fl = 0;
				if(condish == men_edit)
					display_task->QuadPrint(6, 6, prog_data[pr_on]);
				else if(condish == start_screen)
					display_task->icon_eff(0);
			}
			break;
		case 19:
			if(prog_data[sel_eff] == f_sw_sel)
			{
				if(prog_data[FX] == 1)
					prog_data[er_on] = fs_but;
				else
					prog_data[er_on] = 1 - fs_but;
				if(condish == men_edit)
					display_task->QuadPrint(6, 7, prog_data[er_on]);
				else if(condish == start_screen)
					display_task->icon_eff(0);
			}
			break;
		case 20:
			if(prog_data[sel_eff_t] == f_sw_sel)
			{
				if(!prog_data[FX] && prog_data[sel_eff_t])
				{
					if(prog_data[FX_typ])
					{
						ind_clean = 1;
						while(!ind_clean)
							;
						if(prog_data[FX_typ] == 1)
							prog_data[fx_type] = fs_but;
						else
							prog_data[fx_type] = 1 - fs_but;
						if(condish == eff_menu)
							eff_init(0);
						if(condish == del_menu)
							init_edit_r();
						else if(condish == reverb_menu)
							delay_init(0);
						if(cut)
							if(condish == start_screen)
								display_task->icon_eff(0);
						revmem_clean();
						ind_clean = 0;
					}
				}
			}
			break;
		case 21:
			if(prog_data[sel_del_v] == f_sw_sel)
			{
				if(prog_data[Del_volume] || prog_data[Del_volume_])
				{
					uint8_t temp = prog_data[Del_volume] + (prog_data[Del_volume_] - prog_data[Del_volume]) * fs_but;
					del_in_contr = temp * 0.007874016f;
				}
			}
			break;
		case 22:
			if(prog_data[set_ear_v] == f_sw_sel)
			{
				if(prog_data[Ear_volume] || prog_data[Ear_volume_])
				{
					uint8_t temp = prog_data[Ear_volume] + (prog_data[Ear_volume_] - prog_data[Ear_volume]) * fs_but;
					ear_vol = (temp * temp) * 6.2000124000248e-5;
				}
			}
			break;
		case 23:
			if(prog_data[sel_rev_v] == f_sw_sel)
			{
				if(prog_data[Rev_volume] || prog_data[Rev_volume_])
				{
					uint8_t temp = prog_data[Rev_volume] + (prog_data[Rev_volume_] - prog_data[Rev_volume]) * fs_but;
					rever_par(0 | (temp << 8));
				}
			}
			break;
		case 24:
			if(prog_data[sel_compr] == f_sw_sel)
			{
				if(prog_data[Compres] == 1)
					prog_data[compr_on] = fs_but;
				else
					prog_data[compr_on] = 1 - fs_but;
				if(condish == men_edit)
					display_task->QuadPrint(6, 1, prog_data[compr_on]);
				else if(condish == start_screen)
					display_task->icon_eff(0);
			}
			break;
		case 25:
			if(prog_data[sel_ng] == f_sw_sel)
			{
				if(prog_data[Ng] == 1)
					prog_data[ga_on] = fs_but;
				else
					prog_data[ga_on] = 1 - fs_but;
				if(condish == men_edit)
					display_task->QuadPrint(6, 0, prog_data[ga_on]);
				else if(condish == start_screen)
					display_task->icon_eff(0);
			}
			break;
		case 26:
			if(prog_data[sel_ng_th] == f_sw_sel)
			{
				if(prog_data[Ng_th] || prog_data[Ng_th_])
				{
					uint8_t temp = prog_data[Ng_th] + (prog_data[Ng_th_] - prog_data[Ng_th]) * fs_but;
					gate_pres.gate_par(0 | (temp << 8));
				}
			}
			break;
		case 27:
			if(prog_data[sel_ph] == f_sw_sel)
			{
				switch(prog_data[Phaz])
				{
				case 1:
					prog_data[phaz_on] = fs_but;
					break;
				case 2:
					prog_data[phaz_on] = 1 - fs_but;
					break;
				case 3:
					if(fs_but)
						prog_data[phaz_on] = 2;
					else
						prog_data[phaz_on] = 0;
					break;
				case 4:
					if(fs_but)
						prog_data[phaz_on] = 0;
					else
						prog_data[phaz_on] = 2;
					break;
				}
				if(condish == men_edit)
					display_task->QuadPrint(6, 2, prog_data[phaz_on]);
				else if(condish == start_screen)
					display_task->icon_eff(0);
			}
			break;
		case 28:
			if(prog_data[sel_fl] == f_sw_sel)
			{
				switch(prog_data[Flang])
				{
				case 1:
					prog_data[flan_on] = fs_but;
					break;
				case 2:
					prog_data[flan_on] = 1 - fs_but;
					break;
				case 3:
					if(fs_but)
						prog_data[flan_on] = 2;
					else
						prog_data[flan_on] = 0;
					break;
				case 4:
					if(fs_but)
						prog_data[flan_on] = 0;
					else
						prog_data[flan_on] = 2;
					break;
				}
				if(condish == men_edit)
					display_task->QuadPrint(6, 3, prog_data[flan_on]);
				else if(condish == start_screen)
					display_task->icon_eff(0);
			}
			break;
		case 29:
			if(prog_data[sel_preamp_mod_] == f_sw_sel)
			{
				switch(prog_data[reamp_mod_])
				{
				case 1:
					if(!fs_but)
					{
						dist.clip_LPF(8000.0f, 0);
						dist.clip_LPF(8000.0f, 1);
						dist.clip_HPF(120.0f, 0);
						dist.clip_HPF(120.0f, 1);
					}
					else
					{
						dist.clip_LPF(4000.0f, 0);
						dist.clip_LPF(4000.0f, 1);
						dist.clip_HPF(20.0f, 0);
						dist.clip_HPF(20.0f, 1);
					}
					break;
				case 2:
					if(!fs_but)
					{
						dist.clip_LPF(8000.0f, 0);
						dist.clip_LPF(8000.0f, 1);
						dist.clip_HPF(120.0f, 0);
						dist.clip_HPF(120.0f, 1);
					}
					else
					{
						dist.clip_LPF(3000.0f, 0);
						dist.clip_LPF(3000.0f, 1);
						dist.clip_HPF(20.0f, 0);
						dist.clip_HPF(20.0f, 1);
					}
					break;
				case 3:
					if(!fs_but)
					{
						dist.clip_LPF(4000.0f, 0);
						dist.clip_LPF(4000.0f, 1);
						dist.clip_HPF(20.0f, 0);
						dist.clip_HPF(20.0f, 1);
					}
					else
					{
						dist.clip_LPF(8000.0f, 0);
						dist.clip_LPF(8000.0f, 1);
						dist.clip_HPF(120.0f, 0);
						dist.clip_HPF(120.0f, 1);
					}
					break;
				case 4:
					if(!fs_but)
					{
						dist.clip_LPF(3000.0f, 0);
						dist.clip_LPF(3000.0f, 1);
						dist.clip_HPF(20.0f, 0);
						dist.clip_HPF(20.0f, 1);
					}
					else
					{
						dist.clip_LPF(8000.0f, 0);
						dist.clip_LPF(8000.0f, 1);
						dist.clip_HPF(120.0f, 0);
						dist.clip_HPF(120.0f, 1);
					}
					break;
				case 5:
					if(!fs_but)
					{
						dist.clip_LPF(4000.0f, 0);
						dist.clip_LPF(4000.0f, 1);
						dist.clip_HPF(20.0f, 0);
						dist.clip_HPF(20.0f, 1);
					}
					else
					{
						dist.clip_LPF(3000.0f, 0);
						dist.clip_LPF(3000.0f, 1);
						dist.clip_HPF(20.0f, 0);
						dist.clip_HPF(20.0f, 1);
					}
					break;
				case 6:
					if(!fs_but)
					{
						dist.clip_LPF(3000.0f, 0);
						dist.clip_LPF(3000.0f, 1);
						dist.clip_HPF(20.0f, 0);
						dist.clip_HPF(20.0f, 1);
					}
					else
					{
						dist.clip_LPF(4000.0f, 0);
						dist.clip_LPF(4000.0f, 1);
						dist.clip_HPF(20.0f, 0);
						dist.clip_HPF(20.0f, 1);
					}
					break;
				}
			}
			break;
		case 30:
			if(prog_data[sel_lid_gain] == f_sw_sel)
			{
				if(prog_data[Lid_gain] || prog_data[Lid_gain_])
				{
					uint8_t temp = prog_data[Lid_gain] + (prog_data[Lid_gain_] - prog_data[Lid_gain]) * fs_but;
					pr_ga = (temp * temp) * 0.001240002480005f + 1.0f;
				}
			}
			break;
		case 31:
			if(prog_data[sel_cr_gain] == f_sw_sel)
			{
				if(prog_data[Cranch_gain] || prog_data[Cranch_gain_])
				{
					uint8_t temp = prog_data[Cranch_gain] + (prog_data[Cranch_gain_] - prog_data[Cranch_gain]) * fs_but;
					pr_ga = (temp * temp) * 0.001240002480005f + 1.0f;
				}
			}
			break;
		case 32:
			if(prog_data[sel_cl_gain] == f_sw_sel)
			{
				if(prog_data[Preampgain] || prog_data[Preampgain_])
				{
					uint8_t temp = prog_data[Preampgain] + (prog_data[Preampgain_] - prog_data[Preampgain]) * fs_but;
					pr_ga = (temp * temp) * 0.001240002480005f + 1.0f;
				}
			}
			break;
		case 33:
			if(prog_data[sel_lid_vol] == f_sw_sel)
			{
				if(prog_data[Lid_vol] || prog_data[Lid_vol_])
				{
					if(fs_but)
						od_volume = (prog_data[Lid_vol_] * prog_data[Lid_vol_]) * 6.2000124000248e-5;
					else
						od_volume = (prog_data[Lid_vol] * prog_data[Lid_vol]) * 6.2000124000248e-5;
				}
			}
			break;
		case 34:
			if(prog_data[sel_lid_low] == f_sw_sel)
			{
				if(prog_data[Lid_low] || prog_data[Lid_low_])
				{
					int8_t temp = (int8_t) prog_data[Lid_low_] - 64;
					if(fs_but)
						pre_param(0, coeff_preamp, temp);
					else
					{
						temp = (int8_t) prog_data[Lid_low] - 64;
						pre_param(0, coeff_preamp, temp);
					}
				}
			}
			break;
		case 35:
			if(prog_data[sel_lid_mid] == f_sw_sel)
			{
				if(prog_data[Lid_mid] || prog_data[Lid_mid_])
				{
					int8_t temp = (int8_t) prog_data[Lid_mid_] - 64;
					if(fs_but)
						pre_param(1, coeff_preamp, temp);
					else
					{
						temp = (int8_t) prog_data[Lid_mid] - 64;
						pre_param(1, coeff_preamp, temp);
					}
				}
			}
			break;
		case 36:
			if(prog_data[sel_lid_hig] == f_sw_sel)
			{
				if(prog_data[Lid_hig] || prog_data[Lid_hig_])
				{
					int8_t temp = (int8_t) prog_data[Lid_hig_] - 64;
					if(fs_but)
						pre_param(2, coeff_preamp, temp);
					else
					{
						temp = (int8_t) prog_data[Lid_hig] - 64;
						pre_param(2, coeff_preamp, temp);
					}
				}
			}
			break;
		case 37:
			if(prog_data[sel_tu] == f_sw_sel)
			{
				m_vol_fl = 1;
				while(m_vol_fl != 2)
					;
				ind_clean = 1;
				while(!ind_clean1)
					;
				tuner_use = 1;
				proc_run = 0;
				ind_clean = 1;
				display_task->TunInit();
				prog_data_t[1] = prog_data[compr_on];
				prog_data[compr_on] = 1;
				compr.comp_par(1 | 50 << 8);
				compr.comp_par(2 | 30 << 8);
				p_vol = 0.0f;
				m_vol_fl = 0;
				condish = tuner;
			}
			break;
		}
	}
	f_sw_sel = 7;
	foot_sw_dub_short = 0;
}
void gui_task_t::prog_ch(void)
{
	display_task->clear();
	m_vol_fl = 1;
	while(m_vol_fl != 2)
		;
	proc_run = 0;
	ind_clean = 1;
	gpiod.pin13_set();
	emb_printf::sprintf(preset_str, "/%2/preset_cab.ult", prog);
	fs_browser_task->read(preset_str.c_str(), 0, 256, (char*) prog_data);
	memcpy(imya, prog_data, 15);
	memcpy(imya1, prog_data + 15, 15);

	TCabsimConfig *cabsimConfig = (TCabsimConfig*) (prog_data + 30);
	currentPreset = makePresetFromCabsimConfig(*cabsimConfig);
	memcpy(currentPreset.name, prog_data, 15);
	memcpy(currentPreset.author, prog_data + 15, 15);

	memcpy(prog_data, prog_data + 30, 256 - 30);

	load_imp();
	imya_temp = 0;
	display_task->line_12x13_clean(35, 2, 47);
	display_task->line_12x13_clean(35, 4, 54);
	tap_fs_fl = 0;
	indic_impul = 0;
	par_num = 0;
	for(uint8_t i = 0;i < 4;i++)
		par_num += prog_data[fl_mix + i];
	if(!par_num)
		for(uint8_t i = 0;i < 4;i++)
			prog_data[fl_mix + i] = fl_in[i];
	par_num = 0;
	for(uint8_t i = 0;i < 4;i++)
		par_num += prog_data[ph_mix + i];
	if(!par_num)
		for(uint8_t i = 0;i < 4;i++)
			prog_data[ph_mix + i] = ph_in[i];
	param_set();
	for(uint8_t i = 0;i < (block_samples * 2);i++)
		adc_data[i].left = adc_data[i].right = dac_data[i].left = dac_data[i].right = 0;
	gpioc.pin13_set();
	gpioa.pin0_set();
	gpioa.pin1_set();
	gpioe.pin0_set();
	gpioe.pin1_set();
	fs_but = ext_fsw_a1 = ext_fsw_a2 = ext_fsw_b1 = ext_fsw_b2 = int_fsw_a1 = 0;
	if(cut)
	{
		gui_task->main_screen(0);
		display_task->line_12x13(16, 6, (char*) "IR CabSim/FX", 0);
		m_vol_fl = 0;
	}
	proc_run = 1;
	ind_clean = 0;
	load_i = 0;
	fs_but = 0;
	for(uint8_t i = 1;i < 6;i++)
	{
		foot_sw_dub_short = 1;
		f_sw_sel = i;
		controll_run();
	}
}
void prog_write(void)
{
	emb_printf::sprintf(str_temp, "/%2", prog1);
	emb_printf::sprintf(preset_str, "/%2/preset_cab.ult", prog1);
	fs_browser_task->write(preset_str.c_str(), 0, 15, (char*) imya);
	fs_browser_task->write(preset_str.c_str(), 15, 15, (char*) imya1);
	fs_browser_task->write(preset_str.c_str(), 30, 256 - 30, (char*) prog_data);
	emb_printf::sprintf(preset_str, "/%2", prog);
	fs_browser_task->write_impulse((char*) preset_str.c_str(), (char*) str_temp.c_str(), impulse_buf, load_i);
}
void prog_read(void)
{
	emb_printf::sprintf(preset_str, "/%2/preset_cab.ult", prog1);
	fs_browser_task->read(preset_str.c_str(), 0, 256, (char*) prog_data_t);
	memcpy(imya_t, prog_data_t, 15);
	memcpy(imya1_t, prog_data_t + 15, 15);
	emb_printf::sprintf(preset_str, "/%2", prog1);
	strncpy(wave0, preset_str.c_str(), 127);
	eq_num = fs_browser_task->check_wave(wave0);
	if(!eq_num)
		prog_flag = 1;
	else
		prog_flag = 0;
	imya_temp = 1;
	gui_task->main_screen(1);
}
void gui_task_t::preset_set(void)
{
	gpioc.pin13_set();
	fs_but = 0;
	prog_old = prog;
	prog = prog1;
	system_file.preset_num = prog;
	system_file.preset_old = prog_old;
	fs_browser_task->write("/system.ult", 0, sizeof(system_file_t), &system_file);
	prog_ch();
}
void gui_task_t::preset_check(void)
{
	fs_browser_task->check_preset( FS_PRESETS_COUNT, (char*) prog_data, (char*) prog_init, (char*) imya_init, (char*) imya_init1);
}
void gui_task_t::code()
{
	gui_task->suspend();
	uint8_t temp = fs_browser_task->read("/system.ult", 0, sizeof(system_file_t), &system_file);
	if(gpioa.pin3())
		system_file.exp_On_Off = 1;
	else
		system_file.exp_On_Off = 0;
	if(!temp || (!system_file.preset_num || system_file.preset_num > FS_PRESETS_COUNT))
	{
		system_file.preset_num = 1;
		fs_browser_task->write("/system.ult", 0, sizeof(system_file_t), &system_file);
	}

	if(!system_file.f_sw_exp)
		adc_init();
	else
		adc_contr_init();
	if(system_file.exp_calib_hi < system_file.exp_calib_lo)
	{
		uint16_t a = system_file.exp_calib_lo;
		system_file.exp_calib_lo = system_file.exp_calib_hi;
		system_file.exp_calib_hi = a;
		adcinv_fl = 1;
	}
	adc_delta = 127.0f / (system_file.exp_calib_hi - system_file.exp_calib_lo);
	prog = prog1 = system_file.preset_num;
	if(!system_file.preset_old)
		prog_old = 1;
	else
		prog_old = system_file.preset_old;
	gate_glob.gate_par(0 | (system_file.gat_thresh << 8));
	gate_glob.gate_par(1 | (system_file.gat_att << 8));
	gate_glob.gate_par(2 | (system_file.gat_dec << 8));
	emb_printf::sprintf(preset_str, "/%2/preset_cab.ult", prog);
	fs_browser_task->read(preset_str.c_str(), 0, 256, (char*) prog_data);
	memcpy(prog_data, prog_data + 30, 255 - 30);
	init_ext_fs();
	preset_check();
	prog_ch();
	eq_num = prog_data[od_on];
	prog_data[od_on] = 1;
	display_task->clear();
	display_task->line_12x13(14, 0, (char*) "AMT PANGAEA", 0);
	display_task->line_12x13(28, 3, (char*) "ULTIMA U2", 0);
	display_task->line_12x13(16, 6, (char*) "IR CabSim/FX", 0);
	delay(1500);
	display_task->clear();

	emb_string fw_version_string;
//	const uint8_t amt_ver[]= FIRMWARE_VER;
//	emb_printf::sprintf(fw_version_string, "Ver.%s", amt_ver);
//	display_task->line_12x13(21, 3, fw_version_string.c_str(), 0);
	delay(500);

	prog_data[od_on] = eq_num;
	display_task->clear();
	start_irq();
	cut = 1;
	gui_task->main_screen(0);
	display_task->line_12x13(16, 6, (char*) "IR CabSim/FX", 0);
	m_vol_fl = 0;
	mas_v = powf(master_volume, 2.0f) * (1.0f / powf(127.0f, 2.0f));


	mainMenu = new AbstractMenu();
	currentMenu = mainMenu;

	while(1)
	{
		update_request->take_from_task();

		//--------------------------------------------------------------foot switch process----------------------------------
		if(foot_sw_dub_short)
		{
			controll_run();
		}

		switch(condish)
		{
		case start_screen:
			if(prog != prog1)
			{
				if(!tim4_fl)
				{
					display_task->prog_indic(prog1, 1, prog_flag);
					if(right_ind_fl)
						gpioa.pin0_reset();
					if(left_ind_fl)
						gpioa.pin1_reset();
				}
				else
				{
					display_task->prog_indic(prog1, 0, prog_flag);
					if(right_ind_fl)
						gpioa.pin0_set();
					if(left_ind_fl)
						gpioa.pin1_set();
				}
			}
			if(encoder_fl1)
			{
				if(encoder_fl == 1)
				{
					if(prog1 == 1)
						prog1 = FS_PRESETS_COUNT;
					else
						prog1--;

					tim4_start(1);
				}
				if(encoder_fl == 2)
				{
					if(prog1 == FS_PRESETS_COUNT)
						prog1 = 1;
					else
						prog1++;

					tim4_start(1);
				}
				prog_read();
				if(prog == prog1)
				{
					//if(tap_fs_fl)
					{
						tap_fs_fl = 0;
						//display_task->line_12x13(0,2,(char*)"           ",0);
						//display_task->line_12x13_clean(0,4,127);
						//display_task->line_12x13(45,2,(char*)"TAP",0);
						//display_task->del_time_ind(35,4,delay_time,0);
					}
					//else {
					//display_task->line_12x13(45,2,(char*)"    ",0);
					//display_task->line_12x13_clean(0,4,127);
					//display_task->line_12x13_clean(0,6,127);
					//display_task->line_12x13(16,6,(char*)"IR CabSim/FX",0);
					//display_task->icon_eff(0);
					//}
					display_task->prog_indic(prog1, 1, prog_flag);
				}
			}
			if(encoder_but || ext_but_long_fl)
			{
				if(prog == prog1)
				{
					tim9.disable();
					if(!tim9.update_interrupt_flag())
					{
						display_task->clear();
						display_task->line_5x7(6, 0, (char*) "Master vol", 0);
						display_task->line_5x7(6, 1, (char*) "Tuner", 0);
						display_task->par_indic(72, 0, master_volume);
						condish = mas_vol;
						par_num = edit_fl = 0;
					}
					else
					{
						if(!indic_impul)
						{
							indic_impul = 1;
							display_task->line_12x13(0, 2, (char*) "               ", 0);
							display_task->line_12x13_clean(0, 4, 127);
							display_task->line_12x13_clean(16, 6, 127 - 16);
							if(impulse_flag)
								display_task->line_5x7(1, 4, (char*) &wave0[4], 0);
							else
								display_task->line_5x7(0, 4, (char*) "No impulse", 0);
						}
						else
						{
							indic_impul = 0;
							if(tap_fs_fl)
							{
								display_task->line_12x13_clean(0, 4, 127);
								display_task->line_12x13_clean(0, 2, 54);
								display_task->line_12x13(45, 2, (char*) "TAP", 0);
								if(!indic_impul)
									display_task->del_time_ind(35, 4, delay_time, 0);
							}
							else
							{
								display_task->line_12x13(45, 2, (char*) "       ", 0);
								display_task->line_12x13_clean(0, 4, 127);
								display_task->line_12x13_clean(0, 6, 127);
								display_task->icon_eff(0);
							}
							display_task->line_12x13(16, 6, (char*) "IR CabSim/FX", 0);
						}
					}
					tim9.counter = 0;
					tim9.update_interrupt_flag_clear();
					tim9.enable();
				}
				else
				{
					preset_set();
				}
			}
			if(foot_sw_dub_long)
			{
				switch(prog_data[ifs_type])
				{
				case 0:
					prog1 = prog_old;
					prog_old = prog;
					prog = prog1;
					prog_ch();
					break;
				case 1:
					if(foot_but_fl)
					{
						indic_impul = 0;
						display_task->line_12x13(16, 6, (char*) "IR CabSim/FX", 0);
						if(tap_fs_fl)
						{
							tap_fs_fl = 0;
							if(condish == start_screen)
							{
								display_task->line_12x13_clean(35, 2, 54);
								display_task->line_12x13_clean(35, 4, 54);
								display_task->icon_eff(0);
							}
						}
						else
						{
							display_task->line_12x13_clean(0, 4, 127);
							if(prog_data[er_on] && !prog_data[fx_type])
							{
								tap_fs_fl = 1;
								if(condish == start_screen)
								{
									display_task->line_12x13_clean(0, 2, 54);
									display_task->line_12x13(45, 2, (char*) "TAP", 0);
									display_task->del_time_ind(35, 4, delay_time, 0);
								}
							}
							else
							{
								display_task->line_12x13_clean(0, 2, 54);
								display_task->line_12x13(11, 4, (char*) "Nothing to Tap", 0);
								delay(1500);
								display_task->line_12x13_clean(11, 4, 116);
								display_task->icon_eff(0);
							}
						}
					}
					break;
				case 2:
				case 3:
					tun_init();
					break;
				}
			}
			if(encoder_but_dub_long)
			{
				if(prog == prog1)
					sys_init(0);
			}
			if(edit_but)
			{
				if(prog != prog1)
				{
					prog1 = prog;
					prog_read();
				}
				else
					edit_init(0);
			}
			clean_fl();
			break;
//------------------------------------------------------System-------------------------------------
		case system_menu:
			if(!edit_fl)
			{
				if(!tim4_fl)
				{
					if(par_num != 2)
						display_task->line_5x7(0, par_num + 1, (char*) menu_list2 + par_num * 15, 2);
					else
					{
						if(system_file.exp_On_Off && !system_file.f_sw_exp)
							display_task->line_5x7(0, 3, (char*) "Exp.Calibrate", 2);
						else
						{
							display_task->line_5x7(0, 3, (char*) "Exp. OFF     ", 2);
						}
					}
				}
				else
				{
					if(par_num != 2)
						display_task->line_5x7(0, par_num + 1, (char*) menu_list2 + par_num * 15, 0);
					else
					{
						if(system_file.exp_On_Off && !system_file.f_sw_exp)
							display_task->line_5x7(0, 3, (char*) "Exp.Calibrate", 0);
						else
						{
							display_task->line_5x7(0, 3, (char*) "Exp. OFF     ", 0);
						}
					}
				}
			}
			if(encoder_fl1 && !eq_num)
			{
				if(encoder_fl == 1)
				{
					if(!edit_fl)
					{
						if(par_num)
						{
							if(par_num != 2)
								display_task->line_5x7(0, par_num + 1, (char*) menu_list2 + par_num * 15, 0);
							else
							{
								if(system_file.exp_On_Off && !system_file.f_sw_exp)
									display_task->line_5x7(0, 3, (char*) "Exp.Calibrate", 0);
								else
								{
									display_task->line_5x7(48, 3, (char*) "     ", 0);
									display_task->line_5x7(0, 3, (char*) "Exp. OFF", 0);
								}
							}
							par_num--;
							tim4_start(1);
						}
					}
					else
					{
						if(par_num == 3)
						{
							if(system_file.midi_ch)
							{
								display_task->num_5x7(72, 4, --system_file.midi_ch + 1, 0);
								display_task->line_5x7(72, 4, (char*) " ", 0);
							}
						}
					}
				}
				if(encoder_fl == 2)
				{
					if(!edit_fl)
					{
						if(par_num < 6)
						{
							if(par_num != 2)
								display_task->line_5x7(0, par_num + 1, (char*) menu_list2 + par_num * 15, 0);
							else
							{
								if(system_file.exp_On_Off && !system_file.f_sw_exp)
									display_task->line_5x7(0, 3, (char*) "Exp.Calibrate", 0);
								else
								{
									display_task->line_5x7(48, 3, (char*) "     ", 0);
									display_task->line_5x7(0, 3, (char*) "Exp. OFF", 0);
								}
							}
							par_num++;
							tim4_start(1);
						}
					}
					else
					{
						if(par_num == 3)
						{
							if(system_file.midi_ch < 15)
							{
								display_task->num_5x7(72, 4, ++system_file.midi_ch + 1, 0);
								display_task->line_5x7(72, 4, (char*) " ", 0);
							}
						}
					}
				}
			}
			if(encoder_but)
			{
				switch(par_num)
				{
				case 0:
					++system_file.fs_inver;
					system_file.fs_inver %= 5;
					display_task->line_5x7(68, par_num + 1, (char*) fs_inv + system_file.fs_inver * 10, 0);
					init_ext_fs();
					break;
				case 1:
					++system_file.f_sw_exp;
					system_file.f_sw_exp &= 1;
					if(system_file.f_sw_exp)
					{
						display_task->line_5x7(90, 2, (char*) "CTR.B", 0);
						adc_contr_init();
						gpioe.pin0_set();
						gpioe.pin1_set();
					}
					else
					{
						display_task->line_5x7(90, 2, (char*) "EXP. ", 0);
						adc_init();
					}
					if(!system_file.exp_On_Off || system_file.f_sw_exp)
						display_task->line_5x7(0, 3, (char*) "Exp. OFF     ", 0);
					else
						display_task->line_5x7(0, 3, (char*) "Exp.Calibrate", 0);
					break;
				case 2:
					if(system_file.exp_On_Off && !system_file.f_sw_exp)
					{
						switch(eq_num)
						{
						case 0:
							eq_num = 1;
							display_task->line_5x7(84, 3, (char*) "Set Min", 0);
							break;
						case 1:
							eq_num = 2;
							display_task->line_5x7(84, 3, (char*) "Set Max", 0);
							system_file.exp_calib_lo = adc.converter_1.regular_data;
							break;
						case 2:
							eq_num = 0;
							display_task->line_5x7(84, 3, (char*) "       ", 0);
							system_file.exp_calib_hi = adc.converter_1.regular_data;
							adcinv_fl = 0;
							if(system_file.exp_calib_hi < system_file.exp_calib_lo)
							{
								uint16_t a = system_file.exp_calib_lo;
								system_file.exp_calib_lo = system_file.exp_calib_hi;
								system_file.exp_calib_hi = a;
								adcinv_fl = 1;
							}
							adc_delta = 127.0f / (system_file.exp_calib_hi - system_file.exp_calib_lo);
							break;
						}
					}
					break;
				case 4:
					gate_init(1);
					break;
				case 5:
					++system_file.glob_cab;
					system_file.glob_cab &= 1;
					display_task->line_5x7(68, 6, (char*) off_on + system_file.glob_cab * 4, 0);
					break;
				case 6:
					metronome_init();
					break;
				default:
					if(edit_fl)
					{
						edit_fl = 0;
						display_task->line_5x7(0, par_num + 1, (char*) menu_list2 + par_num * 15, 0);
					}
					else
					{
						edit_fl = 1;
						display_task->line_5x7(0, par_num + 1, (char*) menu_list2 + par_num * 15, 2);
					}
				}
				tim4_start(0);
			}
			if(edit_but && !eq_num)
			{
				fs_browser_task->priority(1);
				fs_browser_task->write("/system.ult", 0, sizeof(system_file_t), &system_file);
				fs_browser_task->priority(1);
				condish = start_screen;
				prog_ch();
			}
			clean_fl();
			break;
//-------------------------------------------------------Master Volume---------------------------------
		case mas_vol:
			if(!tim4_fl)
			{
				if(!edit_fl)
				{
					if(par_num)
						display_task->line_5x7(6, par_num, (char*) "Tuner", 2);
					else
						display_task->line_5x7(6, par_num, (char*) "Master vol", 2);
				}
			}
			else
			{
				if(!edit_fl)
				{
					if(par_num)
						display_task->line_5x7(6, par_num, (char*) "Tuner", 0);
					else
						display_task->line_5x7(6, par_num, (char*) "Master vol", 0);
				}
			}
			if(encoder_fl1)
			{
				if(encoder_fl == 1)
				{
					if(!edit_fl)
					{
						if(par_num)
							display_task->line_5x7(6, par_num--, (char*) "Tuner", 0);
						tim4_start(1);
					}
					else
					{
						if(master_volume)
						{
							master_volume = enc_speed_dec(master_volume, 0);
							mas_v = powf(master_volume, 2.0f) * (1.0f / powf(127.0f, 2.0f));
							display_task->par_indic(72, 0, master_volume);
						}
					}
				}
				if(encoder_fl == 2)
				{
					if(!edit_fl)
					{
						if(!par_num)
							display_task->line_5x7(6, par_num++, (char*) "Master vol", 0);
						tim4_start(1);
					}
					else
					{
						if(master_volume < 127)
						{
							master_volume = enc_speed_inc(master_volume, 127);
							mas_v = powf(master_volume, 2.0f) * (1.0f / powf(127.0f, 2.0f));
							display_task->par_indic(72, 0, master_volume);
						}
					}
				}
			}
			if(encoder_but)
			{
				if(!par_num)
				{
					if(edit_fl)
						edit_fl = 0;
					else
					{
						edit_fl = 1;
						display_task->line_5x7(6, par_num, (char*) "Master vol", 2);
					}
				}
				else
				{
					m_vol_fl = 1;
					while(m_vol_fl != 2)
						;
					ind_clean = 1;
					while(!ind_clean1)
						;
					tuner_use = 1;
					proc_run = 0;
					ind_clean = 1;
					display_task->TunInit();
					prog_data_t[1] = prog_data[compr_on];
					prog_data[compr_on] = 1;
					compr.comp_par(1 | 50 << 8);
					compr.comp_par(2 | 30 << 8);
					p_vol = 0.0f;
					m_vol_fl = 0;
					condish = tuner;
				}
			}
			if(edit_but)
			{
				imya_temp = 0;
				display_task->clear();
				gui_task->main_screen(0);
				if(indic_impul)
				{
					indic_impul = 0;
					display_task->line_12x13(16, 6, (char*) "IR CabSim/FX", 0);
				}
				else
					indic_impul = 1;
			}
			clean_fl();
			break;
//-------------------------------------------------------edit menu------------------------------------
		case men_edit:
			if(!tim4_fl)
				display_task->line_5x7(17, par_num, (char*) menu_list + par_num * 16, 2);
			else
				display_task->line_5x7(17, par_num, (char*) menu_list + par_num * 16, 0);
			if(encoder_fl1)
			{
				if(encoder_fl == 1)
				{
					if(par_num)
					{
						display_task->line_5x7(17, par_num, (char*) menu_list + par_num-- * 16, 0);
						display_task->line_5x7(17, par_num, (char*) menu_list + par_num * 16, 2);
					}
				}
				if(encoder_fl == 2)
				{
					if(par_num < 7)
					{
						display_task->line_5x7(17, par_num, (char*) menu_list + par_num++ * 16, 0);
						display_task->line_5x7(17, par_num, (char*) menu_list + par_num * 16, 2);
					}
					else
						edit_init1(0);
				}
				tim4_start(1);
			}
			if(encoder_but)
			{
				switch(par_num)
				{
				case 0:
					gate_init(0);
					break;
				case 1:
					compress_init();
					break;
				case 2:
					phaz_init();
					break;
				case 3:
					flan_init();
					break;
				case 4:
					preamp_init();
					break;
				case 5:
					amp_init();
					break;
				case 6:
					cab_init(0);
					break;
				case 7:
					eq_init_men(0);
					break;
				}
			}
			if(edit_but)
			{
				condish = save_men;
				display_task->clear();
				display_task->line_12x13(46, 0, "Save?", 0);
				for(uint8_t i = 0;i < 4;i++)
					display_task->line_12x13(i * 35 + 2, 4, (char*) save_list + i * 4, 0);
				par_num = 0;
				tim4_start(0);
			}
			clean_fl();
			break;
			//-------------------------------------------------------Menu edit 1------------------------------------
		case men_edit1:
			if(!tim4_fl)
			{
				if(!edit_fl)
				{
					if(par_num > 1)
						display_task->line_5x7(6, par_num, (char*) menu_list1 + par_num * 14, 2);
					else
						display_task->line_5x7(17, par_num, (char*) menu_list1 + par_num * 14, 2);
				}
			}
			else
			{
				if(!edit_fl)
				{
					if(par_num > 1)
						display_task->line_5x7(6, par_num, (char*) menu_list1 + par_num * 14, 0);
					else
						display_task->line_5x7(17, par_num, (char*) menu_list1 + par_num * 14, 0);
				}
			}
			if(encoder_fl1)
			{
				if(encoder_fl == 1)
				{
					if(!edit_fl)
					{
						if(par_num)
						{
							if(par_num > 2)
							{
								display_task->line_5x7(6, par_num, (char*) menu_list1 + par_num-- * 14, 0);
								display_task->line_5x7(6, par_num, (char*) menu_list1 + par_num * 14, 2);
							}
							else
							{
								if(par_num > 1)
									display_task->line_5x7(6, par_num, (char*) menu_list1 + par_num-- * 14, 0);
								else
									display_task->line_5x7(17, par_num, (char*) menu_list1 + par_num-- * 14, 0);
								display_task->line_5x7(17, par_num, (char*) menu_list1 + par_num * 14, 2);
							}
						}
						else
							edit_init(7);
					}
				}
				if(encoder_fl == 2)
				{
					if(!edit_fl)
					{
						if(par_num < 7)
						{
							if(par_num > 1)
							{
								display_task->line_5x7(6, par_num, (char*) menu_list1 + par_num++ * 14, 0);
								display_task->line_5x7(6, par_num, (char*) menu_list1 + par_num * 14, 2);
							}
							else
							{
								display_task->line_5x7(17, par_num, (char*) menu_list1 + par_num++ * 14, 0);
								if(par_num > 1)
									display_task->line_5x7(6, par_num, (char*) menu_list1 + par_num * 14, 2);
								else
									display_task->line_5x7(17, par_num, (char*) menu_list1 + par_num * 14, 2);
							}
						}
					}
				}
				tim4_start(1);
			}
			if(encoder_but)
			{
				switch(par_num)
				{
				case 0:
					filt_init();
					break;
				case 1:
					eff_init(0);
					break;
				case 2:
					condish = volum;
					display_task->clear();
					display_task->line_5x7(7, 3, (char*) "In ", 0);
					display_task->line_5x7(7, 4, (char*) "Out", 0);
					display_task->line_5x7(0, 1, (char*) "Preset Level", 0);
					display_task->par_indic(75, 1, prog_data[pres_lev]);
					break;
				case 3:
					++prog_data[ifs_type];
					prog_data[ifs_type] &= 1;
					display_task->line_5x7(59, 3, (char*) ifs_list + prog_data[ifs_type] * 11, 0);
					if(prog_data[ifs_type] != 1)
						tap_fs_fl = 0;
					else
						tap_fs_fl = 1;
					break;
				case 4:
					display_task->clear();
					edit_fl = 0;
					condish = fs_para;
					par_num = eq_num = 0;
					f_sw_set = 1;
					foot_switch_init(0);
					tim4_start(1);
					break;
				case 6:
					express_init();
					break;
				case 7:
					condish = name_edit;
					display_task->clear();
					key_shift = 0;
					eq_num = 0;
					par_num = 0;
					num_men_temp = 0;
					nam_sym_temp = 32;
					display_task->line_5x7(2, 0, (char*) imya, 0);
					display_task->line_5x7(2, 1, (char*) imya1, 0);
					display_task->sym_5x7(86, 0, 46, 0);
					display_task->sym_5x7(86, 1, 46, 0);
					display_task->line_5x7(0, 2, (char*) ascii_low1, 0);
					display_task->line_5x7(0, 3, (char*) ascii_low2, 0);
					tim4_start(0);
					break;
				}
				tim4_start(0);
			}
			if(par_num == 5)
			{
				if(encoder_but_dub_short)
				{
					if(++ext_fs_sel == 5)
						ext_fs_sel = 1;
					display_task->line_5x7(91, 5, (char*) ext_fsw_l + (ext_fs_sel - 1) * 3, 0);
					f_sw_set = ext_fs_sel + 1;
				}
				if(encoder_but_dub_long)
				{
					f_sw_set = ext_fs_sel + 1;
					display_task->clear();
					display_task->line_5x7(0, 0, (char*) fsw_ind + (ext_fs_sel - 1) * 21, 1);
					edit_fl = 0;
					condish = fs_para;
					par_num = eq_num = 0;
					foot_switch_init(0);
					tim4_start(1);
				}
			}
			if(edit_but)
			{
				condish = save_men;
				display_task->clear();
				display_task->line_12x13(46, 0, "Save?", 0);
				for(uint8_t i = 0;i < 4;i++)
					display_task->line_12x13(i * 35 + 2, 4, (char*) save_list + i * 4, 0);
				par_num = 0;
				tim4_start(0);
			}
			clean_fl();
			break;
//-----------------------------------------------------------Tuner-------------------------------------
		case tuner:
			if(edit_but || foot_sw_dub_long || foot_sw_dub_short || encoder_but)
			{
				tuner_use = 0;
				delay(100);
				prog_ch();
			}
			clean_fl();
			break;
//-----------------------------------------------Browser------------------------------------------------
		case browser_menu:
			if(encoder_fl1)
			{
				m_vol_fl = 1;
				while(m_vol_fl != 2)
					;
				proc_run = 0;
				if(encoder_fl == 1)
				{
					fs_browser_task->priority(1);
					fs_browser_task->prev_notify();
					fs_browser_task->priority(1 - 1);
					fs_browser_task->browser_name(str_temp);
					fs_browser_task->curr_path(preset_str);
					if(!preset_str.compare("/Impulses") && !str_temp.compare(".."))
						fs_browser_task->next_notify();
					else
					{
						preset_str.append("/");
						preset_str.append(str_temp.c_str());
						if(!fs_browser_task->status_path())
							eq_num = wav_read((char*) preset_str.c_str());
						display_task->clear();
						path_fold(preset_str);
						preset_str.erase(0, 2);
						display_task->line_5x7(0, 0, preset_str.c_str(), 0);
						if(!fs_browser_task->status_path())
							if(eq_num)
								display_task->line_5x7(2, 7, "Not correct wav file", 0);
					}
				}
				if(encoder_fl == 2)
				{
					fs_browser_task->priority(1);
					fs_browser_task->next_notify();
					fs_browser_task->priority(1 - 1);
					fs_browser_task->browser_name(str_temp);
					fs_browser_task->curr_path(preset_str);
					preset_str.append("/");
					preset_str.append(str_temp.c_str());
					if(!fs_browser_task->status_path())
						eq_num = wav_read((char*) preset_str.c_str());
					path_fold(preset_str);
					display_task->clear();
					preset_str.erase(0, 2);
					display_task->line_5x7(0, 0, preset_str.c_str(), 0);
					if(!fs_browser_task->status_path())
						if(eq_num)
							display_task->line_5x7(2, 7, "Not correct wav file", 0);
				}
				proc_run = 1;
				m_vol_fl = 0;
			}
			if(encoder_but)
			{
				fs_browser_task->browser_name(str_temp);
				fs_browser_task->curr_path(preset_str);
				if(!preset_str.compare("/Impulses") && !str_temp.compare(".."))
					nop();
				else
				{
					if(fs_browser_task->status_path())
					{
						fs_browser_task->priority(1);
						fs_browser_task->action_notify();
						fs_browser_task->priority(1 - 1);
						fs_browser_task->browser_name(str_temp);
						fs_browser_task->curr_path(preset_str);
						preset_str.append("/");
						preset_str.append(str_temp.c_str());
						path_fold(preset_str);
						display_task->clear();
						preset_str.erase(0, 2);
						display_task->line_5x7(0, 0, preset_str.c_str(), 0);
					}
					else
					{
						if(!eq_num)
							load_i = 1;
						else
							load_i = 0;
						cab_init(2);
					}
				}
			}
			if(edit_but)
			{
				load_imp();
				cab_init(2);
			}
			clean_fl();
			break;
			//-----------------
//-----------------------------------------------------------------calibrate-------------------------------------------------------------
		case calibrate:
			if(!tim4_fl)
			{
				if(!eq_num)
					display_task->line_12x13(27, 4, (char*) "Set to min", 2);
				if(eq_num == 1)
					display_task->line_12x13(27, 4, (char*) "Set to max", 2);
			}
			else
			{
				if(!eq_num)
					display_task->line_12x13(27, 4, (char*) "Set to min", 0);
				if(eq_num == 1)
					display_task->line_12x13(27, 4, (char*) "Set to max", 0);
			}
			if(encoder_but)
			{
				if(!eq_num)
				{
					system_file.exp_calib_lo = adc.converter_1.regular_data;
					display_task->line_12x13_clean(27, 4, 100);
					display_task->line_12x13(27, 4, (char*) "    Ok!", 0);
					delay(1000);
					eq_num = 1;
					clean_fl();
					break;
				}
				if(eq_num == 1)
				{
					system_file.exp_calib_hi = adc.converter_1.regular_data;
					eq_num = 2;
					display_task->line_12x13_clean(27, 4, 100);
					display_task->line_12x13(27, 4, (char*) "    Ok!", 0);
					delay(1000);
					fs_browser_task->write("/system.ult", 0, sizeof(system_file_t), &system_file);
					clean_fl();
					adcinv_fl = 0;
					if(system_file.exp_calib_hi < system_file.exp_calib_lo)
					{
						uint16_t a = system_file.exp_calib_lo;
						system_file.exp_calib_lo = system_file.exp_calib_hi;
						system_file.exp_calib_hi = a;
						adcinv_fl = 1;
					}
					adc_delta = 127.0f / (system_file.exp_calib_hi - system_file.exp_calib_lo);
					sys_init(0);
					break;
				}
			}
			break;
//-----------------------------------------------------------------expression list-------------------------------------------------------
		case exspression_list:
			if(!tim4_fl)
			{
				switch(eq_num)
				{
				case 0:
					if(!edit_fl)
						display_task->line_5x7(6, par_num + 1, (char*) exp_list + par_num * 11, 2);
					break;
				case 1:
					display_task->num_5x7(78, par_num + 1, prog_data[ex_pr_lo + par_num * 2], 2);
					break;
				case 2:
					display_task->num_5x7(108, par_num + 1, prog_data[ex_pr_hi + par_num * 2], 2);
					break;
				}
			}
			else
			{
				switch(eq_num)
				{
				case 0:
					if(!edit_fl)
						display_task->line_5x7(6, par_num + 1, (char*) exp_list + par_num * 11, 0);
					break;
				case 1:
					display_task->num_5x7(78, par_num + 1, prog_data[ex_pr_lo + par_num * 2], 0);
					break;
				case 2:
					display_task->num_5x7(108, par_num + 1, prog_data[ex_pr_hi + par_num * 2], 0);
					break;
				}
			}
			if(encoder_fl1)
			{
				if(encoder_fl == 1)
				{
					if(!edit_fl)
					{
						if(par_num)
						{
							display_task->line_5x7(6, par_num + 1, (char*) exp_list + par_num-- * 11, 0);
							display_task->line_5x7(6, par_num + 1, (char*) exp_list + par_num * 11, 2);
						}
						tim4_start(1);
					}
					else
					{
						if(eq_num == 1)
						{
							uint8_t temp = prog_data[ex_pr_lo + par_num * 2];
							if(temp)
								temp = enc_speed_dec(temp, 0);
							display_task->num_5x7(78, par_num + 1, temp, 0);
							prog_data[ex_pr_lo + par_num * 2] = temp;
						}
						else
						{
							uint8_t temp = prog_data[ex_pr_hi + par_num * 2];
							if(temp)
								temp = enc_speed_dec(temp, 0);
							display_task->num_5x7(108, par_num + 1, temp, 0);
							prog_data[ex_pr_hi + par_num * 2] = temp;
						}
						tim4_start(0);
					}
				}
				if(encoder_fl == 2)
				{
					if(!edit_fl)
					{
						if(par_num < 5)
						{
							display_task->line_5x7(6, par_num + 1, (char*) exp_list + par_num++ * 11, 0);
							display_task->line_5x7(6, par_num + 1, (char*) exp_list + par_num * 11, 2);
						}
						tim4_start(1);
					}
					else
					{
						if(eq_num == 1)
						{
							uint8_t temp = prog_data[ex_pr_lo + par_num * 2];
							if(temp < 127)
								temp = enc_speed_inc(temp, 127);
							display_task->num_5x7(78, par_num + 1, temp, 0);
							prog_data[ex_pr_lo + par_num * 2] = temp;
							display_task->num_5x7(108, par_num + 1, prog_data[ex_pr_hi + par_num * 2], 0);
						}
						else
						{
							uint8_t temp = prog_data[ex_pr_hi + par_num * 2];
							if(temp < 127)
								temp = enc_speed_inc(temp, 127);
							display_task->num_5x7(108, par_num + 1, temp, 0);
							prog_data[ex_pr_hi + par_num * 2] = temp;
							display_task->num_5x7(78, par_num + 1, prog_data[ex_pr_lo + par_num * 2], 0);
						}
						tim4_start(0);
					}
				}
			}
			if(encoder_but)
			{
				if(!edit_fl)
				{
					edit_fl = eq_num = 1;
					display_task->line_5x7(6, par_num + 1, (char*) exp_list + par_num * 11, 2);
					display_task->num_5x7(108, par_num + 1, prog_data[ex_pr_hi + par_num * 2], 0);
				}
				else
				{
					if(eq_num == 1)
					{
						display_task->num_5x7(78, par_num + 1, prog_data[ex_pr_lo + par_num * 2], 0);
						eq_num++;
					}
					else
					{
						if(eq_num == 2)
						{
							if(!(prog_data[ex_pr_lo + par_num * 2]) && !(prog_data[ex_pr_hi + par_num * 2]))
							{
								display_task->line_5x7(78, par_num + 1, (char*) "Off  Off", 0);
								switch(par_num)
								{
								case 0:
									p_vol = powf(prog_data[pres_lev], 2.0f) * (1.0f / powf(127.0f, 2.0f));
									break;
								case 1:
									pream_vol = powf(prog_data[preamp_vol], 2.0f) * (1.0f / powf(127.0f, 2.0f));
									break;
								case 2:
									od_volume = powf(prog_data[od_vol], 2.0f) * (1.0f / powf(127.0f, 2.0f));
									break;
								case 3:
									amp_vol = powf(prog_data[a_vol], 2.0f) * (20.0f / powf(127.0f, 2.0f)) + 1.0f;
									break;
								case 4:
									amp_sla = powf(prog_data[amp_slave], 4.0f) * (0.99f / powf(127.0f, 4.0f)) + 0.01f;
									break;
								case 5:
									set_shelf(prog_data[presen_vol] * (31.0f / 127.0f));
									break;
								}
							}
							else
							{
								display_task->num_5x7(78, par_num + 1, prog_data[ex_pr_lo + par_num * 2], 0);
								display_task->num_5x7(108, par_num + 1, prog_data[ex_pr_hi + par_num * 2], 0);
							}
							eq_num = edit_fl = 0;
						}
					}
				}
				tim4_start(1);
			}
			if(edit_but)
				edit_init1(6);
			clean_fl();
			break;
//-----------------------------------------------------------------save menu--------------------------------------------------------------
		case save_men:
			if(!tim4_fl)
				display_task->line_12x13(par_num * 35 + 2, 4, (char*) save_list + par_num * 4, 2);
			else
				display_task->line_12x13(par_num * 35 + 2, 4, (char*) save_list + par_num * 4, 0);
			if(encoder_fl1)
			{
				if(encoder_fl == 1)
				{
					if(par_num)
					{
						display_task->line_12x13(par_num * 35 + 2, 4, (char*) save_list + par_num-- * 4, 0);
						display_task->line_12x13(par_num * 35 + 2, 4, (char*) save_list + par_num * 4, 2);
					}
				}
				if(encoder_fl == 2)
				{
					if(par_num < 3)
					{
						display_task->line_12x13(par_num * 35 + 2, 4, (char*) save_list + par_num++ * 4, 0);
						display_task->line_12x13(par_num * 35 + 2, 4, (char*) save_list + par_num * 4, 2);
					}
				}
			}
			if(encoder_but)
			{
				switch(par_num)
				{
				case 0:
					display_task->clear();
					prog1 = prog;
					prog_read();
					display_task->line_12x13(46, 6, "Save?", 0);
					condish = save_confirm_menu;
					break;
				case 1:
					condish = start_screen;
					prog_ch();
					break;
				case 2:
					edit_init(0);
					break;
				case 3:
					display_task->clear();
					display_task->line_12x13(12, 1, "Sure you want", 0);
					display_task->line_12x13(34, 3, "to clear?", 0);
					display_task->line_12x13(72, 5, "YES", 0);
					condish = clear_menu;
					par_num = 0;
					tim4_start(0);
					break;
				}
			}
			if(edit_but)
			{
				condish = start_screen;
				prog_ch();
			}
			clean_fl();
			break;
//----------------------------------------------Clear confirm----------------------------------------------
		case clear_menu:
			if(!tim4_fl)
			{
				if(par_num)
					display_task->line_12x13(par_num * 35 + 37, 5, (char*) "YES", 2);
				else
					display_task->line_12x13(par_num * 35 + 37, 5, (char*) "NO", 2);
			}
			else
			{
				if(par_num)
					display_task->line_12x13(par_num * 35 + 37, 5, (char*) "YES", 0);
				else
					display_task->line_12x13(par_num * 35 + 37, 5, (char*) "NO", 0);
			}
			if(encoder_fl1)
			{
				if(encoder_fl == 1)
				{
					if(par_num)
					{
						display_task->line_12x13(par_num-- * 35 + 37, 5, (char*) "YES", 0);
						tim4_start(1);
					}
				}
				if(encoder_fl == 2)
				{
					if(!par_num)
					{
						display_task->line_12x13(par_num++ * 35 + 37, 5, (char*) "NO", 0);
						tim4_start(1);
					}
				}
			}
			if(encoder_but)
			{
				if(par_num)
				{
					m_vol_fl = 1;
					while(m_vol_fl != 2)
						;
					proc_run = 0;
					ind_clean = 1;
					emb_printf::sprintf(preset_str, "/%2", prog);
					fs_browser_task->priority(1);
					fs_browser_task->erase_cur_preset((char*) preset_str.c_str(), (char*) prog_data, (char*) prog_init, (char*) imya_init, (char*) imya_init1);
					fs_browser_task->priority(1 - 1);
				}
				condish = start_screen;
				prog_ch();
			}
			if(edit_but)
			{
				condish = start_screen;
				prog_ch();
			}
			clean_fl();
			break;
//----------------------------------------------Save confirm-----------------------------------------------
		case save_confirm_menu:
			if(!tim4_fl)
				display_task->prog_indic(prog1, 1, prog_flag);
			else
				display_task->prog_indic(prog1, 0, prog_flag);
			if(encoder_fl1)
			{
				if(encoder_fl == 1)
				{
					if(prog1 == 1)
						prog1 = FS_PRESETS_COUNT;
					else
						prog1--;
					tim4_start(1);
					prog_read();
				}
				if(encoder_fl == 2)
				{
					if(prog1 == FS_PRESETS_COUNT)
						prog1 = 1;
					else
						prog1++;
					tim4_start(1);
					prog_read();
				}
				display_task->line_12x13(46, 6, "Save?", 0);
			}
			if(encoder_but)
			{
				prog_write();
				prog1 = prog;
				condish = start_screen;
				prog_ch();
			}
			if(edit_but)
			{
				prog1 = prog;
				condish = start_screen;
				prog_ch();
			}
			clean_fl();
			break;
//-----------------------------------------------Gate--------------------------------------------------
		case gate_menu:
			if(!tim4_fl)
			{
				if(!edit_fl)
					display_task->line_5x7(0, par_num, (char*) gate_list + par_num * 10, 2);
			}
			else
			{
				if(!edit_fl)
					display_task->line_5x7(0, par_num, (char*) gate_list + par_num * 10, 0);
			}
			if(encoder_fl1)
			{
				if(encoder_fl == 1)
				{
					if(!edit_fl)
					{
						if(par_num)
						{
							display_task->line_5x7(0, par_num, (char*) gate_list + par_num-- * 10, 0);
							tim4_start(1);
						}
					}
					else
					{
						switch(par_num)
						{
						case 1:
							if(!eq_num)
							{
								if(prog_data[ga_th])
								{
									prog_data[ga_th] = enc_speed_dec(prog_data[ga_th], 0);
									display_task->par_indic(62, par_num, prog_data[ga_th]);
									gate_pres.gate_par(0 | (prog_data[ga_th] << 8));
								}
							}
							else
							{
								if(system_file.gat_thresh)
								{
									system_file.gat_thresh = enc_speed_dec(system_file.gat_thresh, 0);
									display_task->par_indic(62, par_num, system_file.gat_thresh);
									gate_glob.gate_par(0 | (system_file.gat_thresh << 8));
								}
							}
							break;
						case 2:
							if(!eq_num)
							{
								if(prog_data[ga_at])
								{
									prog_data[ga_at] = enc_speed_dec(prog_data[ga_at], 0);
									display_task->par_indic(62, par_num, prog_data[ga_at]);
									gate_pres.gate_par(1 | (prog_data[ga_at] << 8));
								}
							}
							else
							{
								if(system_file.gat_att)
								{
									system_file.gat_att = enc_speed_dec(system_file.gat_att, 0);
									display_task->par_indic(62, par_num, system_file.gat_att);
									gate_glob.gate_par(1 | (system_file.gat_att << 8));
								}
							}
							break;
						case 3:
							if(!eq_num)
							{
								if(prog_data[ga_de])
								{
									prog_data[ga_de] = enc_speed_dec(prog_data[ga_de], 0);
									display_task->par_indic(62, par_num, prog_data[ga_de]);
									gate_pres.gate_par(2 | (prog_data[ga_de] << 8));
								}
							}
							else
							{
								if(system_file.gat_dec)
								{
									system_file.gat_dec = enc_speed_dec(system_file.gat_dec, 0);
									display_task->par_indic(62, par_num, system_file.gat_dec);
									gate_glob.gate_par(2 | (system_file.gat_dec << 8));
								}
							}
							break;
						}
					}
				}
				if(encoder_fl == 2)
				{
					if(!edit_fl)
					{
						if(par_num < 3)
						{
							display_task->line_5x7(0, par_num, (char*) gate_list + par_num++ * 10, 0);
							tim4_start(1);
						}
					}
					else
					{
						switch(par_num)
						{
						case 1:
							if(!eq_num)
							{
								if(prog_data[ga_th] < 127)
								{
									prog_data[ga_th] = enc_speed_inc(prog_data[ga_th], 127);
									display_task->par_indic(62, par_num, prog_data[ga_th]);
									gate_pres.gate_par(0 | (prog_data[ga_th] << 8));
								}
							}
							else
							{
								if(system_file.gat_thresh < 127)
								{
									system_file.gat_thresh = enc_speed_inc(system_file.gat_thresh, 127);
									display_task->par_indic(62, par_num, system_file.gat_thresh);
									gate_glob.gate_par(0 | (system_file.gat_thresh << 8));
								}
							}
							break;
						case 2:
							if(!eq_num)
							{
								if(prog_data[ga_at] < 127)
								{
									prog_data[ga_at] = enc_speed_inc(prog_data[ga_at], 127);
									display_task->par_indic(62, par_num, prog_data[ga_at]);
									gate_pres.gate_par(1 | (prog_data[ga_at] << 8));
								}
							}
							else
							{
								if(system_file.gat_att < 127)
								{
									system_file.gat_att = enc_speed_inc(system_file.gat_att, 127);
									display_task->par_indic(62, par_num, system_file.gat_att);
									gate_glob.gate_par(1 | (system_file.gat_att << 8));
								}
							}
							break;
						case 3:
							if(!eq_num)
							{
								if(prog_data[ga_de] < 127)
								{
									prog_data[ga_de] = enc_speed_inc(prog_data[ga_de], 127);
									display_task->par_indic(62, par_num, prog_data[ga_de]);
									gate_pres.gate_par(2 | (prog_data[ga_de] << 8));
								}
							}
							else
							{
								if(system_file.gat_dec < 127)
								{
									system_file.gat_dec = enc_speed_inc(system_file.gat_dec, 127);
									display_task->par_indic(62, par_num, system_file.gat_dec);
									gate_glob.gate_par(2 | (system_file.gat_dec << 8));
								}
							}
							break;
						}
					}
				}
			}
			if(encoder_but)
			{
				if(!par_num)
				{
					if(!eq_num)
					{
						++prog_data[ga_on];
						prog_data[ga_on] &= 1;
						display_task->line_5x7(62, 0, (char*) on_off + prog_data[ga_on] * 4, 0);
					}
					else
					{
						++system_file.gat_on;
						system_file.gat_on &= 1;
						display_task->line_5x7(62, 0, (char*) on_off + system_file.gat_on * 4, 0);
					}
				}
				else
				{
					if(!edit_fl)
					{
						edit_fl = 1;
						display_task->line_5x7(0, par_num, (char*) gate_list + par_num * 10, 2);
					}
					else
					{
						edit_fl = 0;
						display_task->line_5x7(0, par_num, (char*) gate_list + par_num * 10, 0);
					}
				}
			}
			if(edit_but)
			{
				if(eq_num)
					sys_init(4);
				else
					edit_init(0);
			}
			clean_fl();
			break;
//--------------------------------------------------------Phazer-----------------------------------------------
		case phaz_edit:
			if(!tim4_fl)
			{
				if(!edit_fl)
					display_task->line_5x7(0, par_num, (char*) phas_list + par_num * 7, 2);
			}
			else
			{
				if(!edit_fl)
					display_task->line_5x7(0, par_num, (char*) phas_list + par_num * 7, 0);
			}
			if(encoder_fl1)
			{
				if(encoder_fl == 1)
				{
					if(!edit_fl)
					{
						if(par_num)
						{
							display_task->line_5x7(0, par_num, (char*) phas_list + par_num-- * 7, 0);
						}
					}
					else
					{
						eq_num = prog_data[phaz_on + par_num];
						if(eq_num)
							eq_num = enc_speed_dec(eq_num, 0);
						if(!par_num)
							display_task->mix_indic(62, par_num, eq_num, 0);
						else
							display_task->par_indic(62, par_num, eq_num);
						prog_data[phaz_on + par_num] = eq_num;
						phaser.phaser_par(par_num | eq_num << 8);
					}
				}
				if(encoder_fl == 2)
				{
					if(!edit_fl)
					{
						if(par_num < 7)
						{
							display_task->line_5x7(0, par_num, (char*) phas_list + par_num++ * 7, 0);
						}
					}
					else
					{
						eq_num = prog_data[phaz_on + par_num];
						if(eq_num < 127)
							eq_num = enc_speed_inc(eq_num, 127);
						if(!par_num)
							display_task->mix_indic(62, par_num, eq_num, 0);
						else
							display_task->par_indic(62, par_num, eq_num);
						prog_data[phaz_on + par_num] = eq_num;
						phaser.phaser_par(par_num | eq_num << 8);
					}
				}
				tim4_start(1);
			}
			if(encoder_but)
			{
				switch(par_num)
				{
				case 0:
					prog_data[phaz_on]++;
					prog_data[phaz_on] %= 3;
					display_task->line_5x7(62, par_num, (char*) off_on_list + prog_data[phaz_on] * 5, 0);
					break;
				case 6:
					prog_data[ph_stag]++;
					prog_data[ph_stag] %= 3;
					display_task->line_5x7(74, par_num, (char*) phas_stag_list + prog_data[ph_stag] * 3, 0);
					phaser.phaser_par(par_num | prog_data[ph_stag] << 8);
					break;
				default:
					if(!edit_fl)
					{
						edit_fl = 1;
						display_task->line_5x7(0, par_num, (char*) phas_list + par_num * 7, 2);
					}
					else
						edit_fl = 0;
				}
				tim4_start(0);
			}
			if(edit_but)
				edit_init(2);
			clean_fl();
			break;
//--------------------------------------------------------Flanger-------------------------
		case flan_edit:
			if(!tim4_fl)
			{
				if(!edit_fl)
					display_task->line_5x7(0, par_num, (char*) fl_list + par_num * 8, 2);
			}
			else
			{
				if(!edit_fl)
					display_task->line_5x7(0, par_num, (char*) fl_list + par_num * 8, 0);
			}
			if(encoder_fl1)
			{
				if(encoder_fl == 1)
				{
					if(!edit_fl)
					{
						if(par_num)
						{
							display_task->line_5x7(0, par_num, (char*) fl_list + par_num-- * 8, 0);
						}
					}
					else
					{
						eq_num = prog_data[flan_on + par_num];
						if(eq_num)
							eq_num = enc_speed_dec(eq_num, 0);
						if(par_num == 1)
							display_task->mix_indic(62, par_num, eq_num, 0);
						else
							display_task->par_indic(62, par_num, eq_num);
						prog_data[flan_on + par_num] = eq_num;
						flanger.fl_param(par_num | eq_num << 8);
					}
				}
				if(encoder_fl == 2)
				{
					if(!edit_fl)
					{
						if(par_num < 7)
						{
							display_task->line_5x7(0, par_num, (char*) fl_list + par_num++ * 8, 0);
						}
					}
					else
					{
						eq_num = prog_data[flan_on + par_num];
						if(eq_num < 127)
							eq_num = enc_speed_inc(eq_num, 127);
						if(par_num == 1)
							display_task->mix_indic(62, par_num, eq_num, 0);
						else
							display_task->par_indic(62, par_num, eq_num);
						prog_data[flan_on + par_num] = eq_num;
						flanger.fl_param(par_num | eq_num << 8);
					}
				}
				tim4_start(1);
			}
			if(encoder_but)
			{
				switch(par_num)
				{
				case 0:
					prog_data[flan_on] = ++prog_data[flan_on] % 3;
					display_task->line_5x7(62, par_num, (char*) off_on_list + prog_data[flan_on] * 5, 0);
					flanger.fl_param(par_num | prog_data[flan_on] << 8);
					break;
				case 2:
					prog_data[fl_lfo] = ++prog_data[fl_lfo] % 3;
					display_task->line_5x7(62, par_num, (char*) fl_t + prog_data[fl_lfo] * 9, 0);
					flanger.fl_param(par_num | prog_data[fl_lfo] << 8);
					break;
				default:
					if(!edit_fl)
					{
						edit_fl = 1;
						display_task->line_5x7(0, par_num, (char*) fl_list + par_num * 8, 2);
					}
					else
						edit_fl = 0;
					tim4_start(0);
				}
			}
			if(edit_but)
				edit_init(3);
			clean_fl();
			break;
//-------------------------------------------------------Preamp-----------------------------------------
		case preamp_menu:
			int8_t temp_preamp;
			uint8_t temp;
			if(!tim4_fl)
			{
				if(!edit_fl)
					display_task->line_5x7(6, par_num, (char*) preamp_list + par_num * 7, 2);
			}
			else
			{
				if(!edit_fl)
					display_task->line_5x7(6, par_num, (char*) preamp_list + par_num * 7, 0);
			}
			if(encoder_fl1)
			{
				if(encoder_fl == 1)
				{
					if(!edit_fl)
					{
						if(par_num)
						{
							display_task->line_5x7(6, par_num, (char*) preamp_list + par_num-- * 7, 0);
							display_task->line_5x7(6, par_num, (char*) preamp_list + par_num * 7, 2);
							tim4_start(1);
						}
					}
					else
					{
						switch(par_num)
						{
						case 2:
							if(prog_data[preamp_on])
							{
								temp = prog_data[prc_gain + prog_data[preamp_on] - 1];
								if(temp)
								{
									temp = enc_speed_dec(temp, 0);
									display_task->par_indic(60, par_num, temp);
									prog_data[prc_gain + prog_data[preamp_on] - 1] = temp;
									pr_ga = temp * temp * 0.001178002f + 1.0f;
								}
							}
							break;
						case 3:
							if(prog_data[preamp_on] < 2)
								temp = prog_data[preamp_vol];
							else
								temp = prog_data[od_vol];
							if(temp)
							{
								temp = enc_speed_dec(temp, 0);
								display_task->par_indic(60, par_num, temp);
							}
							if(prog_data[preamp_on] < 2)
							{
								pream_vol = powf(temp, 2.0f) * (1.0f / powf(127.0f, 2.0f));
								prog_data[preamp_vol] = temp;
							}
							else
							{
								od_volume = powf(temp, 2.0f) * (1.0f / powf(127.0f, 2.0f));
								prog_data[od_vol] = temp;
							}
							break;
						case 4:
						case 5:
						case 6:
							switch(prog_data[preamp_on])
							{
							case 1:
								temp_preamp = prog_data[preamp_lo + par_num - 4];
								break;
							case 2:
								temp_preamp = prog_data[od_low + par_num - 4];
								break;
							case 3:
								temp_preamp = prog_data[ld_low + par_num - 4];
								break;
							}
							if(temp_preamp > -64)
							{
								temp_preamp = enc_speed_dec(temp_preamp, -64);
								display_task->par_indic(60, par_num, temp_preamp + 64);
								switch(prog_data[preamp_on])
								{
								case 1:
									prog_data[preamp_lo + par_num - 4] = temp_preamp;
									pre_param(par_num - 4, coeff_preamp, temp_preamp);
									break;
								case 2:
									prog_data[od_low + par_num - 4] = temp_preamp;
									pre_param(par_num - 4, coeff_preamp, temp_preamp);
									break;
								case 3:
									prog_data[ld_low + par_num - 4] = temp_preamp;
									pre_param(par_num - 4, coeff_preamp, temp_preamp);
									break;
								}
							}
							break;
						}
					}
				}
				if(encoder_fl == 2)
				{
					if(!edit_fl)
					{
						if(par_num < 6)
						{
							display_task->line_5x7(6, par_num, (char*) preamp_list + par_num++ * 7, 0);
							display_task->line_5x7(6, par_num, (char*) preamp_list + par_num * 7, 2);
							tim4_start(1);
						}
					}
					else
					{
						switch(par_num)
						{
						case 2:
							if(prog_data[preamp_on])
							{
								temp = prog_data[prc_gain + prog_data[preamp_on] - 1];
								if(temp < 127)
								{
									temp = enc_speed_inc(temp, 127);
									display_task->par_indic(60, par_num, temp);
									prog_data[prc_gain + prog_data[preamp_on] - 1] = temp;
									pr_ga = temp * temp * 0.001178002f + 1.0f;
								}
							}
							break;
						case 3:
							if(prog_data[preamp_on] < 2)
								temp = prog_data[preamp_vol];
							else
								temp = prog_data[od_vol];
							if(temp < 127)
							{
								temp = enc_speed_inc(temp, 127);
								display_task->par_indic(60, par_num, temp);
							}
							if(prog_data[preamp_on] < 2)
							{
								pream_vol = powf(temp, 2.0f) * (1.0f / powf(127.0f, 2.0f));
								prog_data[preamp_vol] = temp;
							}
							else
							{
								od_volume = powf(temp, 2.0f) * (1.0f / powf(127.0f, 2.0f));
								prog_data[od_vol] = temp;
							}
							break;
						case 4:
						case 5:
						case 6:
							switch(prog_data[preamp_on])
							{
							case 1:
								temp_preamp = prog_data[preamp_lo + par_num - 4];
								break;
							case 2:
								temp_preamp = prog_data[od_low + par_num - 4];
								break;
							case 3:
								temp_preamp = prog_data[ld_low + par_num - 4];
								break;
							}
							if(temp_preamp < 63)
							{
								temp_preamp = enc_speed_inc(temp_preamp, 63);
								display_task->par_indic(60, par_num, temp_preamp + 64);
								switch(prog_data[preamp_on])
								{
								case 1:
									prog_data[preamp_lo + par_num - 4] = temp_preamp;
									pre_param(par_num - 4, coeff_preamp, temp_preamp);
									break;
								case 2:
									prog_data[od_low + par_num - 4] = temp_preamp;
									pre_param(par_num - 4, coeff_preamp, temp_preamp);
									break;
								case 3:
									prog_data[ld_low + par_num - 4] = temp_preamp;
									pre_param(par_num - 4, coeff_preamp, temp_preamp);
									break;
								}
							}
							break;
						}
					}
				}
			}
			if(encoder_but)
			{
				switch(par_num)
				{
				case 0:
					prog_data[preamp_on]++;
					prog_data[preamp_on] %= 4;
					display_task->line_5x7(60, 0, (char*) preamp_typ_list + prog_data[preamp_on] * 11, 0);
					switch(prog_data[preamp_on])
					{
					case 0:
						prog_data[preamp_on] = 0;
						prog_data[od_on] = 0;
						gpioc.pin2_set();
						break;
					case 1:
						prog_data[preamp_on] = 1;
						m_vol_fl = 1;
						while(m_vol_fl != 2)
							;
						prog_data[od_on] = 0;
						gpioc.pin2_set();
						m_vol_fl = 0;
						display_task->par_indic(60, 2, prog_data[prc_gain]);
						display_task->par_indic(60, 3, prog_data[preamp_vol]);
						for(uint8_t i = 0;i < 3;i++)
							display_task->par_indic(60, i + 4, prog_data[preamp_lo + i] + 64);
						break;
					case 2:
						m_vol_fl = 1;
						while(m_vol_fl != 2)
							;
						prog_data[od_on] = 1;
						gpioc.pin2_reset();
						gpioc.pin3_reset();
						m_vol_fl = 0;
						display_task->par_indic(60, 2, prog_data[prl_gain]);
						display_task->par_indic(60, 3, prog_data[od_vol]);
						for(uint8_t i = 0;i < 3;i++)
							display_task->par_indic(60, i + 4, prog_data[od_low + i] + 64);
						break;
					case 3:
						m_vol_fl = 1;
						while(m_vol_fl != 2)
							;
						prog_data[od_on] = 1;
						gpioc.pin2_reset();
						gpioc.pin3_set();
						display_task->par_indic(60, 2, prog_data[prh_gain]);
						for(uint8_t i = 0;i < 3;i++)
							display_task->par_indic(60, i + 4, prog_data[ld_low + i] + 64);
						m_vol_fl = 0;
						break;
					}
					if(prog_data[preamp_on])
					{
						pr_ga = prog_data[prc_gain + prog_data[preamp_on] - 1] * prog_data[prc_gain + prog_data[preamp_on] - 1] * 0.000868002f + 1.0f;
						switch(prog_data[pr_over_cl + prog_data[preamp_on] - 1])
						{
						case 0:
							dist.clip_LPF(8000.0f, 0);
							dist.clip_LPF(8000.0f, 1);
							dist.clip_HPF(120.0f, 0);
							dist.clip_HPF(120.0f, 1);
							break;
						case 1:
							dist.clip_LPF(4000.0f, 0);
							dist.clip_LPF(4000.0f, 1);
							dist.clip_HPF(20.0f, 0);
							dist.clip_HPF(20.0f, 1);
							break;
						case 2:
							dist.clip_LPF(3000.0f, 0);
							dist.clip_LPF(3000.0f, 1);
							dist.clip_HPF(20.0f, 0);
							dist.clip_HPF(20.0f, 1);
							break;
						}
						display_task->num_5x7(48, 1, prog_data[pr_over_cl + prog_data[preamp_on] - 1] + 1, 0);
						display_task->line_5x7(48, 1, (char*) "  ", 0);
					}
					break;
				case 1:
					if(prog_data[preamp_on])
					{
						prog_data[pr_over_cl + prog_data[preamp_on] - 1]++;
						prog_data[pr_over_cl + prog_data[preamp_on] - 1] %= 3;
						switch(prog_data[pr_over_cl + prog_data[preamp_on] - 1])
						{
						case 0:
							dist.clip_LPF(8000.0f, 0);
							dist.clip_LPF(8000.0f, 1);
							dist.clip_HPF(120.0f, 0);
							dist.clip_HPF(120.0f, 1);
							break;
						case 1:
							dist.clip_LPF(4000.0f, 0);
							dist.clip_LPF(4000.0f, 1);
							dist.clip_HPF(20.0f, 0);
							dist.clip_HPF(20.0f, 1);
							break;
						case 2:
							dist.clip_LPF(3000.0f, 0);
							dist.clip_LPF(3000.0f, 1);
							dist.clip_HPF(20.0f, 0);
							dist.clip_HPF(20.0f, 1);
							break;
						}
						display_task->num_5x7(48, par_num, prog_data[pr_over_cl + prog_data[preamp_on] - 1] + 1, 0);
						display_task->line_5x7(48, par_num, (char*) "  ", 0);
					}
					break;
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
					if(prog_data[preamp_on])
					{
						if(edit_fl)
						{
							display_task->line_5x7(6, par_num, (char*) preamp_list + par_num * 7, 0);
							edit_fl = 0;
						}
						else
						{
							display_task->line_5x7(6, par_num, (char*) preamp_list + par_num * 7, 2);
							edit_fl = 1;
						}
					}
					break;
					//case 7:drive_init();break;
				}
				tim4_start(0);
			}
			if(edit_but)
				edit_init(4);
			clean_fl();
			break;
//-----------------------------------------Over soft----------------
		case over_menu:
			if(!tim4_fl)
			{
				if(!edit_fl)
					display_task->line_5x7(0, par_num, (char*) pr_filt_menu + par_num * 10, 2);
			}
			else
			{
				if(!edit_fl)
					display_task->line_5x7(0, par_num, (char*) pr_filt_menu + par_num * 10, 0);
			}
			if(encoder_fl1)
			{
				if(encoder_fl == 1)
				{
					if(!edit_fl)
					{
						if(par_num)
						{
							display_task->line_5x7(0, par_num, (char*) pr_filt_menu + par_num-- * 10, 0);
							display_task->line_5x7(0, par_num, (char*) pr_filt_menu + par_num * 10, 2);
							tim4_start(1);
						}
					}
					else
					{
						switch(par_num)
						{
						case 0:
							if(prog_data[prf_LP1] < 195)
							{
								prog_data[prf_LP1] = enc_speed_inc(prog_data[prf_LP1], 195);
								float temp = powf(195 - prog_data[prf_LP1], 2.0) * (19000.0 / powf(195.0, 2.0)) + 1000.0;
								dist.clip_LPF(temp, 0);
								display_task->line_5x7_clean(80, par_num, "     ");
								emb_printf::sprintf(str_temp, "%1", (uint16_t) temp);
								display_task->line_5x7(80, par_num, (char*) str_temp.c_str(), 0);
							}
							break;
						case 2:
							if(prog_data[prf_HP1])
							{
								prog_data[prf_HP1] = enc_speed_dec(prog_data[prf_HP1], 0);
								float temp = prog_data[prf_HP1] * (980.0f / 255.0f) + 20.0f;
								dist.clip_HPF(temp, 0);
								display_task->line_5x7_clean(80, par_num, "     ");
								emb_printf::sprintf(str_temp, "%1", (uint16_t) temp);
								display_task->line_5x7(80, par_num, (char*) str_temp.c_str(), 0);
							}
							break;
						case 4:
							if(prog_data[prf_LP2] < 195)
							{
								prog_data[prf_LP2] = enc_speed_inc(prog_data[prf_LP2], 195);
								float temp = powf(195 - prog_data[prf_LP2], 2.0) * (19000.0 / powf(195.0, 2.0)) + 1000.0;
								dist.clip_LPF(temp, 1);
								display_task->line_5x7_clean(80, par_num, "     ");
								emb_printf::sprintf(str_temp, "%1", (uint16_t) temp);
								display_task->line_5x7(80, par_num, (char*) str_temp.c_str(), 0);
							}
							break;
						case 6:
							if(prog_data[prf_HP2])
							{
								prog_data[prf_HP2] = enc_speed_dec(prog_data[prf_HP2], 0);
								float temp = prog_data[prf_HP2] * (980.0f / 255.0f) + 20.0f;
								dist.clip_HPF(temp, 1);
								display_task->line_5x7_clean(80, par_num, "     ");
								emb_printf::sprintf(str_temp, "%1", (uint16_t) temp);
								display_task->line_5x7(80, par_num, (char*) str_temp.c_str(), 0);
							}
							break;
						}
					}
				}
				if(encoder_fl == 2)
				{
					if(!edit_fl)
					{
						if(par_num < 7)
						{
							display_task->line_5x7(0, par_num, (char*) pr_filt_menu + par_num++ * 10, 0);
							display_task->line_5x7(0, par_num, (char*) pr_filt_menu + par_num * 10, 2);
							tim4_start(1);
						}
					}
					else
					{
						switch(par_num)
						{
						case 0:
							if(prog_data[prf_LP1])
							{
								prog_data[prf_LP1] = enc_speed_dec(prog_data[prf_LP1], 0);
								float temp = powf(195 - prog_data[prf_LP1], 2.0) * (19000.0 / powf(195.0, 2.0)) + 1000.0;
								dist.clip_LPF(temp, 0);
								display_task->line_5x7_clean(80, par_num, "     ");
								emb_printf::sprintf(str_temp, "%1", (uint16_t) temp);
								display_task->line_5x7(80, par_num, (char*) str_temp.c_str(), 0);
							}
							break;
						case 2:
							if(prog_data[prf_HP1] < 255)
							{
								prog_data[prf_HP1] = enc_speed_inc(prog_data[prf_HP1], 255);
								float temp = prog_data[prf_HP1] * (980.0f / 255.0f) + 20.0f;
								dist.clip_HPF(temp, 0);
								display_task->line_5x7_clean(80, par_num, "     ");
								emb_printf::sprintf(str_temp, "%1", (uint16_t) temp);
								display_task->line_5x7(80, par_num, (char*) str_temp.c_str(), 0);
							}
							break;
						case 4:
							if(prog_data[prf_LP2])
							{
								prog_data[prf_LP2] = enc_speed_dec(prog_data[prf_LP2], 0);
								float temp = powf(195 - prog_data[prf_LP2], 2.0) * (19000.0 / powf(195.0, 2.0)) + 1000.0;
								dist.clip_LPF(temp, 1);
								display_task->line_5x7_clean(80, par_num, "     ");
								emb_printf::sprintf(str_temp, "%1", (uint16_t) temp);
								display_task->line_5x7(80, par_num, (char*) str_temp.c_str(), 0);
							}
							break;
						case 6:
							if(prog_data[prf_HP2] < 255)
							{
								prog_data[prf_HP2] = enc_speed_inc(prog_data[prf_HP2], 255);
								float temp = prog_data[prf_HP2] * (980.0f / 255.0f) + 20.0f;
								dist.clip_HPF(temp, 1);
								display_task->line_5x7_clean(80, par_num, "     ");
								emb_printf::sprintf(str_temp, "%1", (uint16_t) temp);
								display_task->line_5x7(80, par_num, (char*) str_temp.c_str(), 0);
							}
							break;
						}
					}
				}
			}
			if(encoder_but)
			{
				switch(par_num)
				{
				case 1:
					prog_data[prf_LP1_st]++;
					prog_data[prf_LP1_st] &= 3;
					display_task->line_5x7(80, par_num, (char*) filt_typ + prog_data[prf_LP1_st] * 6, 0);
				case 3:
					prog_data[prf_HP1_st]++;
					prog_data[prf_HP1_st] &= 3;
					display_task->line_5x7(80, par_num, (char*) filt_typ + prog_data[prf_HP1_st] * 6, 0);
				case 5:
					prog_data[prf_LP2_st]++;
					prog_data[prf_LP2_st] &= 3;
					display_task->line_5x7(80, par_num, (char*) filt_typ + prog_data[prf_LP2_st] * 6, 0);
				case 7:
					prog_data[prf_HP2_st]++;
					prog_data[prf_HP2_st] &= 3;
					display_task->line_5x7(80, par_num, (char*) filt_typ + prog_data[prf_HP2_st] * 6, 0);
				default:
					if(edit_fl)
					{
						display_task->line_5x7(0, par_num, (char*) pr_filt_menu + par_num * 10, 0);
						edit_fl = 0;
					}
					else
					{
						display_task->line_5x7(0, par_num, (char*) pr_filt_menu + par_num * 10, 2);
						edit_fl = 1;
					}
					break;
				}
			}
			if(edit_but)
				preamp_init();
			clean_fl();
			break;
//-------------------------------------------------------Amp-----------------------------------------
		case amp_menu:
			if(!tim4_fl)
			{
				if(!edit_fl)
					display_task->line_5x7(6, par_num, (char*) amp_list + par_num * 7, 2);
			}
			else
			{
				if(!edit_fl)
					display_task->line_5x7(6, par_num, (char*) amp_list + par_num * 7, 0);
			}
			if(encoder_fl1)
			{
				if(encoder_fl == 1)
				{
					if(!edit_fl)
					{
						if(par_num)
						{
							display_task->line_5x7(6, par_num, (char*) amp_list + par_num-- * 7, 0);
							display_task->line_5x7(6, par_num, (char*) amp_list + par_num * 7, 2);
							tim4_start(1);
						}
					}
					else
					{
						switch(par_num)
						{
						case 1:
							if(prog_data[a_vol])
							{
								prog_data[a_vol] = enc_speed_dec(prog_data[a_vol], 0);
								display_task->par_indic(60, par_num, prog_data[a_vol]);
								amp_vol = powf(prog_data[a_vol], 2.0f) * (20.0f / powf(127.0f, 2.0f)) + 1.0f;
							}
							break;
						case 2:
							if(prog_data[presen_vol])
							{
								prog_data[presen_vol] = enc_speed_dec(prog_data[presen_vol], 0);
								display_task->par_indic(60, par_num, prog_data[presen_vol]);
								set_shelf(prog_data[presen_vol] * (31.0f / 127.0f));
							}
							break;
						case 3:
							if(prog_data[amp_slave])
							{
								prog_data[amp_slave] = enc_speed_dec(prog_data[amp_slave], 0);
								display_task->par_indic(60, par_num, prog_data[amp_slave]);
								amp_sla = powf(prog_data[amp_slave], 4.0f) * (0.99f / powf(127.0f, 4.0f)) + 0.01f;
							}
							break;
						case 4:
							if(prog_data[a_t])
							{
								prog_data[a_t]--;
								set_fir_amp(prog_data[a_t]);
								display_task->line_5x7(60, par_num, (char*) amp_t_list + prog_data[a_t] * 11, 0);
							}
							break;
						}
					}
				}
				if(encoder_fl == 2)
				{
					if(!edit_fl)
					{
						if(par_num < 4)
						{
							display_task->line_5x7(6, par_num, (char*) amp_list + par_num++ * 7, 0);
							display_task->line_5x7(6, par_num, (char*) amp_list + par_num * 7, 2);
							tim4_start(1);
						}
					}
					else
					{
						switch(par_num)
						{
						case 1:
							if(prog_data[a_vol] < 127)
							{
								prog_data[a_vol] = enc_speed_inc(prog_data[a_vol], 127);
								display_task->par_indic(60, par_num, prog_data[a_vol]);
								amp_vol = powf(prog_data[a_vol], 2.0f) * (20.0f / powf(127.0f, 2.0f)) + 1.0f;
							}
							break;
						case 2:
							if(prog_data[presen_vol] < 127)
							{
								prog_data[presen_vol] = enc_speed_inc(prog_data[presen_vol], 127);
								display_task->par_indic(60, par_num, prog_data[presen_vol]);
								set_shelf(prog_data[presen_vol] * (31.0f / 127.0f));
							}
							break;
						case 3:
							if(prog_data[amp_slave] < 127)
							{
								prog_data[amp_slave] = enc_speed_inc(prog_data[amp_slave], 127);
								display_task->par_indic(60, par_num, prog_data[amp_slave]);
								amp_sla = powf(prog_data[amp_slave], 4.0f) * (0.99f / powf(127.0f, 4.0f)) + 0.01f;
							}
							break;
						case 4:
							if(prog_data[a_t] < 14)
							{
								prog_data[a_t]++;
								set_fir_amp(prog_data[a_t]);
								display_task->line_5x7(60, par_num, (char*) amp_t_list + prog_data[a_t] * 11, 0);
							}
							break;
						}
					}
				}
			}
			if(encoder_but)
			{
				if(!par_num)
				{
					if(prog_data[amp_on])
					{
						prog_data[amp_on]--;
						display_task->line_5x7(60, par_num, (char*) "Off", 0);
					}
					else
					{
						prog_data[amp_on]++;
						display_task->line_5x7(60, par_num, (char*) "On ", 0);
					}
				}
				else
				{
					if(edit_fl)
					{
						display_task->line_5x7(6, par_num, (char*) amp_list + par_num * 7, 0);
						edit_fl = 0;
					}
					else
					{
						display_task->line_5x7(6, par_num, (char*) amp_list + par_num * 7, 2);
						edit_fl = 1;
					}
				}
				tim4_start(0);
			}
			if(edit_but)
				edit_init(5);
			clean_fl();
			break;
//---------------------------------------------------------Cab On Off---------------------------------
		case cab_onoff:
			if(!edit_fl)
			{
				if(tim4_fl == 1)
					display_task->line_5x7(3, par_num, (char*) cab_list + par_num * 13, 2);
				else
					display_task->line_5x7(3, par_num, (char*) cab_list + par_num * 13, 0);
			}
			if(encoder_fl1)
			{
				if(encoder_fl == 1)
				{
					if(!edit_fl)
					{
						if(par_num)
						{
							display_task->line_5x7(3, par_num, (char*) cab_list + par_num-- * 13, 0);
							display_task->line_5x7(3, par_num, (char*) cab_list + par_num * 13, 2);
							tim4_start(0);
						}
					}
					else
					{
						switch(par_num)
						{
						case 1:
							if(prog_data[cab_vol])
							{
								prog_data[cab_vol] = enc_speed_dec(prog_data[cab_vol], 0);
								display_task->par_indic(75, par_num, prog_data[cab_vol]);
								cab_volume = powf(prog_data[cab_vol], 2.0f) * (0.99f / powf(127.0f, 2.0f)) + 0.01f;
							}
							break;
						}
					}
				}
				if(encoder_fl == 2)
				{
					if(!edit_fl)
					{
						if(par_num < 2)
						{
							display_task->line_5x7(3, par_num, (char*) cab_list + par_num++ * 13, 0);
							display_task->line_5x7(3, par_num, (char*) cab_list + par_num * 13, 2);
							tim4_start(0);
						}
					}
					else
					{
						switch(par_num)
						{
						case 1:
							if(prog_data[cab_vol] < 127)
							{
								prog_data[cab_vol] = enc_speed_inc(prog_data[cab_vol], 127);
								display_task->par_indic(75, par_num, prog_data[cab_vol]);
								cab_volume = powf(prog_data[cab_vol], 2.0f) * (0.99f / powf(127.0f, 2.0f)) + 0.01f;
							}
							break;
						}
					}
				}
			}
			if(encoder_but)
			{
				switch(par_num)
				{
				case 0:
					if(prog_data[cab_on])
					{
						prog_data[cab_on]--;
						display_task->line_5x7(75, par_num, (char*) "Off", 0);
					}
					else
					{
						prog_data[cab_on]++;
						display_task->line_5x7(75, par_num, (char*) "On ", 0);
					}
					break;
				case 1:
					display_task->clear();
					display_task->line_5x7(7, 3, (char*) "In ", 0);
					display_task->line_5x7(7, 4, (char*) "Out", 0);
					display_task->line_5x7(0, 1, (char*) "IR volume", 0);
					display_task->line_5x7(0, 6, (char*) "IR/Dry", 0);
					display_task->par_indic(75, 1, prog_data[cab_vol]);
					display_task->mix_indic(75, 6, prog_data[ir_mix], 1);
					condish = cab_vol_ind;
					edit_fl = par_num = 0;
					break;
				case 2:
					browser_init();
					break;
				}
				tim4_start(0);
			}
			if(edit_but)
				edit_init(6);
			clean_fl();
			break;
//---------------------------------------------Cab Volume-----------------------------------------
		case cab_vol_ind:
			if(!edit_fl)
			{
				if(tim4_fl == 1)
				{
					if(!par_num)
						display_task->line_5x7(0, 1, (char*) "IR volume", 2);
					else
						display_task->line_5x7(0, 6, (char*) "IR/Dry", 2);
				}
				else
				{
					if(!par_num)
						display_task->line_5x7(0, 1, (char*) "IR volume", 0);
					else
						display_task->line_5x7(0, 6, (char*) "IR/Dry", 0);
				}
			}
			if(encoder_fl1)
			{
				if(encoder_fl == 1)
				{
					if(!edit_fl)
					{
						if(par_num)
						{
							display_task->line_5x7(0, 6, (char*) "IR/Dry", 0);
							par_num--;
						}
						tim4_start(0);
					}
					else
					{
						if(!par_num)
						{
							if(prog_data[cab_vol])
							{
								prog_data[cab_vol] = enc_speed_dec(prog_data[cab_vol], 0);
								display_task->par_indic(75, 1, prog_data[cab_vol]);
								cab_volume = powf(prog_data[cab_vol], 2.0f) * (0.99f / powf(127.0f, 2.0f)) + 0.01f;
							}
						}
						else
						{
							if(prog_data[ir_mix])
							{
								prog_data[ir_mix] = enc_speed_dec(prog_data[ir_mix], 0);
								display_task->mix_indic(75, 6, prog_data[ir_mix], 1);

							}
						}
					}
				}
				if(encoder_fl == 2)
				{
					if(!edit_fl)
					{
						if(!par_num)
							display_task->line_5x7(0, ++par_num * 1, (char*) "IR volume", 0);
						tim4_start(0);
					}
					else
					{
						if(!par_num)
						{
							if(prog_data[cab_vol] < 127)
							{
								prog_data[cab_vol] = enc_speed_inc(prog_data[cab_vol], 127);
								display_task->par_indic(75, 1, prog_data[cab_vol]);
								cab_volume = powf(prog_data[cab_vol], 2.0f) * (0.99f / powf(127.0f, 2.0f)) + 0.01f;
							}
						}
						else
						{
							if(prog_data[ir_mix] < 126)
							{
								prog_data[ir_mix] = enc_speed_inc(prog_data[ir_mix], 126);
								display_task->mix_indic(75, 6, prog_data[ir_mix], 1);

							}
						}
					}
				}
			}
			if(encoder_but)
			{
				if(!edit_fl)
				{
					edit_fl = 1;
					if(!par_num)
						display_task->line_5x7(0, 1, (char*) "IR volume", 2);
					else
						display_task->line_5x7(0, 6, (char*) "IR/Dry", 2);
				}
				else
					edit_fl = 0;
			}
			if(edit_but)
				cab_init(1);
			clean_fl();
			break;
//---------------------------------------------Equaliser-------------------------------------------
		case equalis:
			if(!edit_fl)
			{
				if(!tim4_fl)
				{
					if(par_num > 1)
						display_task->EqInd(27 + (par_num - 2) * 14, 4, prog_data[eq1 + (par_num - 2)], 0);
					else
						display_task->line_5x7(0, par_num, (char*) eq_list + par_num * 10, 0);
				}
				else
				{
					if(par_num > 1)
						display_task->EqInd(27 + (par_num - 2) * 14, 4, prog_data[eq1 + (par_num - 2)], 1);
					else
						display_task->line_5x7(0, par_num, (char*) eq_list + par_num * 10, 2);
				}
			}
			if(encoder_fl1)
			{
				if(encoder_fl == 1)
				{
					if(!edit_fl)
					{
						if(par_num)
						{
							if(par_num < 2)
							{
								display_task->line_5x7(0, par_num, (char*) eq_list + par_num-- * 10, 0);
								display_task->line_5x7(0, par_num, (char*) eq_list + par_num * 10, 2);
							}
							else
							{
								display_task->EqInd(27 + (par_num - 2) * 14, 4, prog_data[eq1 + (par_num-- - 2)], 0);
								if(par_num == 1)
								{
									display_task->line_5x7_clean(0, 3, "                   ");
									display_task->line_5x7(0, par_num, (char*) eq_list + par_num * 10, 0);
								}
								else
									display_task->EqInd(27 + (par_num - 2) * 14, 4, prog_data[eq1 + (par_num - 2)], 1);
							}
							tim4_start(0);
						}
					}
					else
					{
						if(par_num > 1)
						{
							if(prog_data[eq1 + par_num - 2])
							{
								prog_data[eq1 + par_num - 2]--;
								display_task->EqInd(27 + (par_num - 2) * 14, 4, prog_data[eq1 + (par_num - 2)], 1);
								filt_ini(par_num - 2, prog_data + fr1, prog_data + q1);
								set_filt(par_num - 2, prog_data[eq1 + par_num - 2]);
							}
						}
					}
				}
				if(encoder_fl == 2)
				{
					if(!edit_fl)
					{
						if(par_num < 6)
						{
							if(!par_num)
							{
								display_task->line_5x7(0, par_num, (char*) eq_list + par_num++ * 10, 0);
								display_task->line_5x7(0, par_num, (char*) eq_list + par_num * 10, 2);
							}
							else
							{
								if(par_num == 1)
								{
									display_task->line_5x7(0, par_num, (char*) eq_list + par_num++ * 10, 0);
									display_task->EqInd(27 + (par_num - 2) * 14, 4, prog_data[eq1 + par_num - 2], 1);
									display_task->line_5x7(0, 3, (char*) "Press hold for edit", 2);
								}
								else
								{
									display_task->EqInd(27 + (par_num - 2) * 14, 4, prog_data[eq1 + par_num++ - 2], 0);
									display_task->EqInd(27 + (par_num - 2) * 14, 4, prog_data[eq1 + (par_num - 2)], 1);
								}
							}
							tim4_start(0);
						}
					}
					else
					{
						if(par_num > 1)
						{
							if(prog_data[eq1 + par_num - 2] < 30)
							{
								prog_data[eq1 + par_num - 2]++;
								display_task->EqInd(27 + (par_num - 2) * 14, 4, prog_data[eq1 + (par_num - 2)], 1);
								filt_ini(par_num - 2, prog_data + fr1, prog_data + q1);
								set_filt(par_num - 2, prog_data[eq1 + par_num - 2]);
							}
						}
					}
				}
			}
			if(encoder_but)
			{
				switch(par_num)
				{
				case 0:
					if(!prog_data[eq_on])
						display_task->line_5x7(72, 0, (char*) on_off + ++prog_data[eq_on] * 4, 0);
					else
						display_task->line_5x7(72, 0, (char*) on_off + --prog_data[eq_on] * 4, 0);
					break;
				case 1:
					if(!prog_data[eq_po])
						display_task->line_5x7(72, 1, (char*) eq_pos_list + ++prog_data[eq_po] * 5, 0);
					else
						display_task->line_5x7(72, 1, (char*) eq_pos_list + --prog_data[eq_po] * 5, 0);
					break;
				}
				tim4_start(0);
			}
			if(encoder_but_dub_short && (par_num > 1))
			{
				if(edit_fl)
				{
					display_task->EqInd(27 + (par_num - 2) * 14, 4, prog_data[eq1 + par_num - 2], 0);
					edit_fl = 0;
				}
				else
				{
					display_task->EqInd(27 + (par_num - 2) * 14, 4, prog_data[eq1 + par_num - 2], 1);
					edit_fl = 1;
				}
				tim4_start(0);
			}
			if(encoder_but_dub_long && (par_num > 1))
			{
				condish = eq_para;
				start_eq_band_edit();
				edit_fl = 0;
			}
			if(edit_but)
			{
				encoder_but_dub_short_fl = 0;
				edit_init(7);
			}
			clean_fl();
			break;
//-------------------------------------------------------Edit band------------------------------------
		case eq_para:
			if(!tim4_fl)
			{
				if(!edit_fl)
					display_task->line_5x7(0, eq_num, (char*) eq_band_list + eq_num * 13, 2);
			}
			else
			{
				if(!edit_fl)
					display_task->line_5x7(0, eq_num, (char*) eq_band_list + eq_num * 13, 0);
			}
			if(encoder_fl1)
			{
				if(encoder_fl == 1)
				{
					if(!edit_fl)
					{
						if(eq_num)
						{
							display_task->line_5x7(0, eq_num, (char*) eq_band_list + eq_num-- * 13, 0);
							display_task->line_5x7(0, eq_num, (char*) eq_band_list + eq_num * 13, 2);
							tim4_start(1);
						}
					}
					else
					{
						if(!eq_num)
						{
							if(filt_temp > -100)
							{
								filt_temp = enc_speed_dec(filt_temp, -100);
								prog_data[fr1 + par_num - 2] = filt_temp;
								filt_ini(par_num - 2, prog_data + fr1, prog_data + q1);
								set_filt(par_num - 2, prog_data[eq1 + par_num - 2]);
								eq_band_print(0);
							}
						}
						else
						{
							if(filt_temp_q > -100)
							{
								filt_temp_q = enc_speed_dec(filt_temp_q, -100);
								prog_data[q1 + par_num - 2] = filt_temp_q;
								filt_ini(par_num - 2, prog_data + fr1, prog_data + q1);
								set_filt(par_num - 2, prog_data[eq1 + par_num - 2]);
								eq_band_print(1);
							}
						}
					}
				}
				if(encoder_fl == 2)
				{
					if(!edit_fl)
					{
						if(!eq_num)
						{
							display_task->line_5x7(0, eq_num, (char*) eq_band_list + eq_num++ * 13, 0);
							display_task->line_5x7(0, eq_num, (char*) eq_band_list + eq_num * 13, 2);
							tim4_start(1);
						}
					}
					else
					{
						if(!eq_num)
						{
							if(filt_temp < 100)
							{
								filt_temp = enc_speed_inc(filt_temp, 100);
								prog_data[fr1 + par_num - 2] = filt_temp;
								filt_ini(par_num - 2, prog_data + fr1, prog_data + q1);
								set_filt(par_num - 2, prog_data[eq1 + par_num - 2]);
								eq_band_print(0);
							}
						}
						else
						{
							if(filt_temp_q < 99)
							{
								filt_temp_q = enc_speed_inc(filt_temp_q, 99);
								prog_data[q1 + par_num - 2] = filt_temp_q;
								filt_ini(par_num - 2, prog_data + fr1, prog_data + q1);
								set_filt(par_num - 2, prog_data[eq1 + par_num - 2]);
								eq_band_print(1);
							}
						}
					}
				}
			}
			if(encoder_but)
			{
				if(edit_fl)
				{
					display_task->line_5x7(0, eq_num, (char*) eq_band_list + eq_num * 13, 0);
					edit_fl = 0;
				}
				else
				{
					display_task->line_5x7(0, eq_num, (char*) eq_band_list + eq_num * 13, 2);
					edit_fl = 1;
				}
				tim4_start(0);
			}
			if(edit_but)
				eq_init_men(1);
			clean_fl();
			break;
			//-------------------------------------------------------Filters--------------------------------------
		case filt_para:
			if(!tim4_fl)
			{
				if(!edit_fl)
					display_task->line_5x7(6, par_num, (char*) filt_list + par_num * 10, 2);
			}
			else
			{
				if(!edit_fl)
					display_task->line_5x7(6, par_num, (char*) filt_list + par_num * 10, 0);
			}
			if(encoder_fl1)
			{
				if(encoder_fl == 1)
				{
					if(!edit_fl)
					{
						if(par_num)
						{
							display_task->line_5x7(6, par_num, (char*) filt_list + par_num-- * 10, 0);
							display_task->line_5x7(6, par_num, (char*) filt_list + par_num * 10, 2);
							tim4_start(1);
						}
					}
					else
					{
						switch(par_num)
						{
						case 1:
							if(prog_data[lop] < 195)
							{
								prog_data[lop] = enc_speed_inc(prog_data[lop], 195);
								lopas = powf(195 - prog_data[lop], 2.0) * (19000.0 / powf(195.0, 2.0)) + 1000.0;
								lpFilt.SetLPF(lopas);
								display_task->line_5x7_clean(80, 1, "     ");
								emb_printf::sprintf(str_temp, "%1", (uint16_t) lopas);
								display_task->line_5x7(80, 1, (char*) str_temp.c_str(), 0);
							}
							break;
						case 3:
							if(prog_data[hip])
							{
								prog_data[hip] = enc_speed_dec(prog_data[hip], 0);
								hipas = prog_data[hip] * (980.0f / 255.0f) + 20.0f;
								hpFilt.SetHPF(hipas);
								display_task->line_5x7_clean(80, 3, "     ");
								emb_printf::sprintf(str_temp, "%1", (uint16_t) hipas);
								display_task->line_5x7(80, 3, (char*) str_temp.c_str(), 0);
							}
							break;
						case 5:
							if(prog_data[presen_vol])
							{
								prog_data[presen_vol] = enc_speed_dec(prog_data[presen_vol], 0);
								emb_printf::sprintf(str_temp, "%1", (uint16_t) prog_data[presen_vol]);
								display_task->line_5x7_clean(80, 5, "   ");
								display_task->line_5x7(80, 5, (char*) str_temp.c_str(), 0);
								set_shelf(prog_data[presen_vol] * (31.0f / 127.0f));
							}
							break;
						}
					}
				}
				if(encoder_fl == 2)
				{
					if(!edit_fl)
					{
						if(par_num < 5)
						{
							display_task->line_5x7(6, par_num, (char*) filt_list + par_num++ * 10, 0);
							display_task->line_5x7(6, par_num, (char*) filt_list + par_num * 10, 2);
							tim4_start(1);
						}
					}
					else
					{
						switch(par_num)
						{
						case 1:
							if(prog_data[lop])
							{
								prog_data[lop] = enc_speed_dec(prog_data[lop], 0);
								lopas = powf(195 - prog_data[lop], 2.0) * (19000.0 / powf(195.0, 2.0)) + 1000.0;
								lpFilt.SetLPF(lopas);
								display_task->line_5x7_clean(80, 1, "     ");
								emb_printf::sprintf(str_temp, "%1", (uint16_t) lopas);
								display_task->line_5x7(80, 1, (char*) str_temp.c_str(), 0);
							}
							break;
						case 3:
							if(prog_data[hip] < 255)
							{
								prog_data[hip] = enc_speed_inc(prog_data[hip], 255);
								hipas = prog_data[hip] * (980.0f / 255.0f) + 20.0f;
								hpFilt.SetHPF(hipas);
								display_task->line_5x7_clean(80, 3, "     ");
								emb_printf::sprintf(str_temp, "%1", (uint16_t) hipas);
								display_task->line_5x7(80, 3, (char*) str_temp.c_str(), 0);
							}
							break;
						case 5:
							if(prog_data[presen_vol] < 127)
							{
								prog_data[presen_vol] = enc_speed_inc(prog_data[presen_vol], 127);
								emb_printf::sprintf(str_temp, "%1", (uint16_t) prog_data[presen_vol]);
								display_task->line_5x7_clean(80, 5, "   ");
								display_task->line_5x7(80, 5, (char*) str_temp.c_str(), 0);
								set_shelf(prog_data[presen_vol] * (31.0f / 127.0f));
							}
							break;
						}
					}
				}
			}
			if(encoder_but)
			{
				switch(par_num)
				{
				case 0:
					prog_data[lop_on]++;
					prog_data[lop_on] &= 3;
					display_task->line_5x7(80, 0, (char*) filt_typ + prog_data[lop_on] * 6, 0);
					break;
				case 2:
					prog_data[hip_on]++;
					prog_data[hip_on] &= 3;
					display_task->line_5x7(80, 2, (char*) filt_typ + prog_data[hip_on] * 6, 0);
					break;
				case 4:
					if(!prog_data[pr_on])
						display_task->line_5x7(80, 4, (char*) on_off + ++prog_data[pr_on] * 4, 0);
					else
						display_task->line_5x7(80, 4, (char*) on_off + --prog_data[pr_on] * 4, 0);
					break;
				case 1:
				case 3:
				case 5:
					if(edit_fl)
					{
						display_task->line_5x7(6, par_num, (char*) filt_list + par_num * 10, 0);
						edit_fl = 0;
					}
					else
					{
						display_task->line_5x7(6, par_num, (char*) filt_list + par_num * 10, 2);
						edit_fl = 1;
					}
					break;
				}
				tim4_start(0);
			}
			if(edit_but)
				edit_init1(0);
			clean_fl();
			break;
//----------------------------------------------------------FX select---------------------------------------
		case eff_menu:
			if(!tim4_fl)
			{
				if(!edit_fl)
					display_task->line_5x7(6, par_num, (char*) eff_list + par_num * 8, 2);
			}
			else
			{
				if(!edit_fl)
					display_task->line_5x7(6, par_num, (char*) eff_list + par_num * 8, 0);
			}
			if(encoder_fl1)
			{
				if(encoder_fl == 1)
				{
					if(par_num)
					{
						display_task->line_5x7(6, par_num, (char*) eff_list + par_num-- * 8, 0);
						display_task->line_5x7(6, par_num, (char*) eff_list + par_num * 8, 2);
						tim4_start(1);
					}
				}
				if(encoder_fl == 2)
				{
					if(!par_num)
					{
						display_task->line_5x7(6, par_num, (char*) eff_list + par_num++ * 8, 0);
						display_task->line_5x7(6, par_num, (char*) eff_list + par_num * 8, 2);
						tim4_start(1);
					}
				}
			}
			if(encoder_but)
			{
				if(!par_num)
				{
					prog_data[er_on]++;
					prog_data[er_on] %= 3;
					ind_clean = 1;
					while(!ind_clean)
						;
					if(prog_data[er_on] == 2)
						prog_data[fx_type] = 1;
					if(prog_data[er_on] == 1)
						prog_data[fx_type] = 0;
					if(!prog_data[er_on])
						display_task->line_5x7(60, 0, (char*) "Off   ", 0);
					else
						display_task->line_5x7(60, 0, (char*) eff_type + prog_data[fx_type] * 7, 0);
					revmem_clean();
					ind_clean = 0;
				}
				else if(prog_data[er_on])
				{
					if(prog_data[fx_type])
						init_edit_r();
					else
						delay_init(0);
				}

			}
			if(edit_but)
				edit_init1(1);
			clean_fl();
			break;
//-------------------------------------------------------reverb-----------------------------------------
		case reverb_menu:
			if(!tim4_fl)
			{
				if(!edit_fl)
					display_task->line_5x7(6, par_num & 7, (char*) rev_list + par_num * 7, 2);
			}
			else
			{
				if(!edit_fl)
					display_task->line_5x7(6, par_num & 7, (char*) rev_list + par_num * 7, 0);
			}
			if(encoder_fl1)
			{
				if(encoder_fl == 1)
				{
					if(!edit_fl)
					{
						if(par_num)
						{
							display_task->line_5x7(6, par_num & 7, (char*) rev_list + par_num-- * 7, 0);
							if(par_num == 7)
							{
								init_edit_r();
								par_num = 7;
							}
							display_task->line_5x7(6, par_num & 7, (char*) rev_list + par_num * 7, 2);
							tim4_start(1);
						}
					}
					else
					{
						switch(par_num)
						{
						case 1:
							if(prog_data[r_typ])
							{
								prog_data[r_typ]--;
								display_task->line_5x7(60, par_num & 7, (char*) rev_type_list + prog_data[r_typ] * 10, 0);
								if(prog_data[r_typ] == 4)
								{
									display_task->par_indic(60, 2, prog_data[r_time]);
									display_task->line_5x7(60, 3, (char*) " ---     ", 0);
									display_task->line_5x7(60, 4, (char*) " ---     ", 0);
									display_task->line_5x7(60, 7, (char*) " ---     ", 0);
								}
								else
								{
									if(prog_data[r_typ] > 4)
									{
										display_task->par_indic(60, 3, prog_data[r_size]);
										display_task->par_indic(60, 4, prog_data[r_dump]);
										display_task->line_5x7(60, 2, (char*) " ---     ", 0);
										display_task->line_5x7(60, 7, (char*) " ---     ", 0);
									}
									else
									{
										if(!prog_data[r_typ])
										{
											display_task->line_5x7(60, 2, (char*) " ---     ", 0);
											display_task->line_5x7(60, 4, (char*) " ---     ", 0);
											display_task->line_5x7(60, 7, (char*) " ---     ", 0);
										}
										else
										{
											display_task->par_indic(60, 2, prog_data[r_time]);
											display_task->par_indic(60, 3, prog_data[r_size]);
											display_task->par_indic(60, 4, prog_data[r_dump]);
											display_task->par_indic(60, 7, prog_data[r_det]);
										}
									}
								}
								rever_par(par_num | (prog_data[par_num + r_vol] << 8));
							}
							break;
						case 9:
							if(prog_data[par_num + r_vol])
							{
								prog_data[par_num + r_vol] = enc_speed_dec(prog_data[par_num + r_vol], 0);
								display_task->par_indic(60, par_num & 7, prog_data[par_num + r_vol]);
								if(prog_data[r_pre] > 20)
								{
									display_task->par_indic(60, 2, prog_data[rev_fed]);
									display_task->par_indic(60, 3, prog_data[rev_nofed]);
								}
								else
								{
									display_task->line_5x7(60, 2, (char*) " ---     ", 0);
									display_task->line_5x7(60, 3, (char*) " ---     ", 0);
								}
								rever_par(par_num | (prog_data[par_num + r_vol] << 8));
							}
							break;
						case 10:
							if(prog_data[r_pre] > 20)
							{
								if(prog_data[rev_fed])
								{
									prog_data[rev_fed] = enc_speed_dec(prog_data[rev_fed], 0);
									display_task->par_indic(60, 2, prog_data[rev_fed]);
								}
								rev_fb_val = prog_data[rev_fed] * (0.9f / 127.0f);
							}
							break;
						case 11:
							if(prog_data[r_pre] > 20)
							{
								if(prog_data[rev_nofed])
								{
									prog_data[rev_nofed] = enc_speed_dec(prog_data[rev_nofed], 0);
									display_task->par_indic(60, 3, prog_data[rev_nofed]);
								}
								rev_nopr = prog_data[rev_nofed] * (0.9f / 127.0f);
							}
							break;
						default:
							if(prog_data[par_num + r_vol])
							{
								prog_data[par_num + r_vol] = enc_speed_dec(prog_data[par_num + r_vol], 0);
								display_task->par_indic(60, par_num & 7, prog_data[par_num + r_vol]);
								rever_par(par_num | (prog_data[par_num + r_vol] << 8));
							}
							break;
						}
					}
				}
				if(encoder_fl == 2)
				{
					if(!edit_fl)
					{
						if(par_num < 12)
						{
							display_task->line_5x7(6, par_num & 7, (char*) rev_list + par_num++ * 7, 0);
							if(par_num == 8)
							{
								display_task->clear();
								display_task->ic_print(0, 1);
								for(uint8_t i = 0;i < 5;i++)
								{
									display_task->line_5x7(6, i, (char*) rev_list + (par_num + i) * 7, 0);
									switch(i)
									{
									case 0:
										if(!prog_data[r_typ] || prog_data[r_typ] == 4)
											display_task->line_5x7(60, 0, (char*) " ---     ", 0);
										else
											display_task->par_indic(60, 0, prog_data[r_diff]);
										break;
									case 1:
										display_task->par_indic(60, 1, prog_data[r_pre]);
										break;
									case 2:
										if(prog_data[r_pre] > 20)
											display_task->par_indic(60, 2, prog_data[rev_fed]);
										else
											display_task->line_5x7(60, 2, (char*) " ---     ", 0);
										break;
									case 3:
										if(prog_data[r_pre] > 20)
											display_task->par_indic(60, 3, prog_data[rev_nofed]);
										else
											display_task->line_5x7(60, 3, (char*) " ---     ", 0);
										break;
									case 4:
										display_task->line_5x7(60, 4, (char*) off_on + prog_data[rev_tail] * 4, 0);
										break;
									}
								}
							}
							display_task->line_5x7(6, par_num & 7, (char*) rev_list + par_num * 7, 2);
							tim4_start(1);
						}
					}
					else
					{
						switch(par_num)
						{
						case 1:
							if(prog_data[r_typ] < 6)
							{
								prog_data[r_typ]++;
								display_task->line_5x7(60, par_num & 7, (char*) rev_type_list + prog_data[r_typ] * 10, 0);
								if(prog_data[r_typ] == 4)
								{
									display_task->par_indic(60, 2, prog_data[r_time]);
									display_task->line_5x7(60, 3, (char*) " ---     ", 0);
									display_task->line_5x7(60, 4, (char*) " ---     ", 0);
									display_task->line_5x7(60, 7, (char*) " ---     ", 0);
								}
								else
								{
									if(prog_data[r_typ] > 4)
									{
										display_task->par_indic(60, 3, prog_data[r_size]);
										display_task->par_indic(60, 4, prog_data[r_dump]);
										display_task->line_5x7(60, 2, (char*) " ---     ", 0);
										display_task->line_5x7(60, 7, (char*) " ---     ", 0);
									}
									else
									{
										if(!prog_data[r_typ])
										{
											display_task->line_5x7(60, 2, (char*) " ---     ", 0);
											display_task->line_5x7(60, 4, (char*) " ---     ", 0);
											display_task->line_5x7(60, 7, (char*) " ---     ", 0);
										}
										else
										{
											display_task->par_indic(60, 2, prog_data[r_time]);
											display_task->par_indic(60, 3, prog_data[r_size]);
											display_task->par_indic(60, 4, prog_data[r_dump]);
											display_task->par_indic(60, 7, prog_data[r_det]);
										}
									}
								}
								rever_par(par_num | (prog_data[par_num + r_vol] << 8));
							}
							break;
						case 9:
							if(prog_data[par_num + r_vol] < 127)
							{
								prog_data[par_num + r_vol] = enc_speed_inc(prog_data[par_num + r_vol], 127);
								display_task->par_indic(60, par_num & 7, prog_data[par_num + r_vol]);
								if(prog_data[r_pre] > 20)
								{
									display_task->par_indic(60, 2, prog_data[rev_fed]);
									display_task->par_indic(60, 3, prog_data[rev_nofed]);
								}
								else
								{
									display_task->line_5x7(60, 2, (char*) " ---     ", 0);
									display_task->line_5x7(60, 3, (char*) " ---     ", 0);
								}
								rever_par(par_num | (prog_data[par_num + r_vol] << 8));
							}
							break;
						case 10:
							if(prog_data[r_pre] > 20)
							{
								if(prog_data[rev_fed] < 127)
								{
									prog_data[rev_fed] = enc_speed_inc(prog_data[rev_fed], 127);
									display_task->par_indic(60, 2, prog_data[rev_fed]);
								}
								rev_fb_val = prog_data[rev_fed] * (0.9f / 127.0f);
							}
							break;
						case 11:
							if(prog_data[r_pre] > 20)
							{
								if(prog_data[rev_nofed] < 127)
								{
									prog_data[rev_nofed] = enc_speed_inc(prog_data[rev_nofed], 127);
									display_task->par_indic(60, 3, prog_data[rev_nofed]);
								}
								rev_nopr = prog_data[rev_nofed] * (0.9f / 127.0f);
							}
							break;
						default:
							if(prog_data[par_num + r_vol] < 127)
							{
								prog_data[par_num + r_vol] = enc_speed_inc(prog_data[par_num + r_vol], 127);
								display_task->par_indic(60, par_num & 7, prog_data[par_num + r_vol]);
								rever_par(par_num | (prog_data[par_num + r_vol] << 8));
							}
							break;
						}
					}
				}
			}
			if(encoder_but)
			{
				if(par_num == 12)
				{
					if(!prog_data[rev_tail])
						display_task->line_5x7(60, 4, (char*) off_on + ++prog_data[rev_tail] * 4, 0);
					else
						display_task->line_5x7(60, 4, (char*) off_on + --prog_data[rev_tail] * 4, 0);
				}
				else
				{
					if(edit_fl)
					{
						display_task->line_5x7(6, par_num & 7, (char*) rev_list + par_num * 7, 0);
						edit_fl = 0;
					}
					else
					{
						if((par_num == 2 || par_num == 7) && prog_data[r_typ] > 4)
							goto ex;
						if((par_num == 3 || par_num == 4 || par_num == 7 || par_num == 8) && prog_data[r_typ] == 4)
							goto ex;
						if((par_num == 2 || par_num == 4 || par_num == 7 || par_num == 8) && !prog_data[r_typ])
							goto ex;
						display_task->line_5x7(6, par_num & 7, (char*) rev_list + par_num * 7, 2);
						edit_fl = 1;
					}
				}
				tim4_start(0);
				ex: ;
			}
			if(edit_but)
				eff_init(1);
			clean_fl();
			break;
//--------------------------------------------------------Delay------------------------------------------------------
		case del_menu:
			if(!tim4_fl)
			{
				if(!edit_fl)
				{
					display_task->line_5x7(6, par_num & 7, (char*) del_list + par_num * 9, 2);
					if(par_num == 15)
						display_task->line_5x7(60, 7, (char*) "Tap", 2);
				}
			}
			else
			{
				if(!edit_fl)
				{
					display_task->line_5x7(6, par_num & 7, (char*) del_list + par_num * 9, 0);
					if(par_num == 15)
						display_task->line_5x7(60, 7, (char*) "Tap", 0);
				}
			}
			if(encoder_fl1)
			{
				if(encoder_fl == 1)
				{
					if(!edit_fl)
					{
						if(par_num)
						{
							display_task->line_5x7(6, par_num & 7, (char*) del_list + par_num-- * 9, 0);
							if(par_num == 7)
							{
								delay_init(7);
								display_task->ic_print(0, 2);
								del_men_fl = 0;
							}
							display_task->line_5x7(6, par_num & 7, (char*) del_list + par_num * 9, 2);
							tim4_start(1);
						}
					}
					else
					{
						switch(par_num)
						{
						case 0:
						case 2:
						case 3:
						case 4:
						case 6:
						case 8:
						case 9:
						case 10:
							if(prog_data[par_num + d_vol])
							{
								prog_data[par_num + d_vol] = enc_speed_dec(prog_data[par_num + d_vol], 0);
								display_task->par_indic(60, par_num & 7, prog_data[par_num + d_vol]);
							}
							break;
						case 5:
						case 7:
							if(prog_data[par_num + d_vol])
							{
								prog_data[par_num + d_vol] = enc_speed_dec(prog_data[par_num + d_vol], 0);
								display_task->pan_indic(60, par_num & 7, prog_data[par_num + d_vol]);
							}
							break;
						case 13:
							if(prog_data[ear_del_vol])
							{
								prog_data[ear_del_vol] = enc_speed_dec(prog_data[ear_del_vol], 0);
								display_task->par_indic(60, par_num & 7, prog_data[ear_del_vol]);
								ear_vol = (prog_data[ear_del_vol] * prog_data[ear_del_vol]) * 6.2000124000248e-5;
							}
							break;
						case 14:
							if(prog_data[ear_del_size])
							{
								prog_data[ear_del_size] = enc_speed_dec(prog_data[ear_del_size], 0);
								display_task->par_indic(60, par_num & 7, prog_data[ear_del_size]);
								rev_n = prog_data[ear_del_size] * (8.3553f / 127.0f) + 0.3f;
								early_par(rev_n);
							}
							break;
						}
						if(par_num < 11)
							del_param(par_num | prog_data[par_num + d_vol] << 8);
					}
				}
				if(encoder_fl == 2)
				{
					if(!edit_fl)
					{
						if(par_num < 14)
						{
							display_task->line_5x7(6, par_num & 7, (char*) del_list + par_num++ * 9, 0);
							if(par_num == 8)
							{
								display_task->clear();
								display_task->ic_print(0, 1);
								for(uint8_t i = 0;i < 8;i++)
									display_task->line_5x7(6, i, (char*) del_list + (i + par_num) * 9, 0);
								for(uint8_t i = 0;i < 3;i++)
									display_task->par_indic(60, i, prog_data[i + par_num + d_vol]);
								display_task->par_indic(60, 5, prog_data[ear_del_vol]);
								display_task->par_indic(60, 6, prog_data[ear_del_size]);
								display_task->line_5x7(60, 4, (char*) on_off + prog_data[d_tail] * 4, 0);
								display_task->line_5x7(60, 3, (char*) del_dir + prog_data[d_dir] * 8, 0);
								del_men_fl = 1;
							}
							display_task->line_5x7(6, par_num & 7, (char*) del_list + par_num * 9, 2);
							tim4_start(1);
						}
					}
					else
					{
						switch(par_num)
						{
						case 0:
						case 2:
						case 3:
						case 4:
						case 6:
						case 8:
						case 9:
						case 10:
							if(prog_data[par_num + d_vol] < 127)
							{
								prog_data[par_num + d_vol] = enc_speed_inc(prog_data[par_num + d_vol], 127);
								display_task->par_indic(60, par_num & 7, prog_data[par_num + d_vol]);
							}
							break;
						case 5:
						case 7:
							if(prog_data[par_num + d_vol] < 126)
							{
								prog_data[par_num + d_vol] = enc_speed_inc(prog_data[par_num + d_vol], 126);
								display_task->pan_indic(60, par_num & 7, prog_data[par_num + d_vol]);
							}
							break;
						case 13:
							if(prog_data[ear_del_vol] < 127)
							{
								prog_data[ear_del_vol] = enc_speed_inc(prog_data[ear_del_vol], 127);
								display_task->par_indic(60, par_num & 7, prog_data[ear_del_vol]);
								ear_vol = (prog_data[ear_del_vol] * prog_data[ear_del_vol]) * 6.2000124000248e-5;
							}
							break;
						case 14:
							if(prog_data[ear_del_size] < 127)
							{
								prog_data[ear_del_size] = enc_speed_inc(prog_data[ear_del_size], 127);
								display_task->par_indic(60, par_num & 7, prog_data[ear_del_size]);
								rev_n = prog_data[ear_del_size] * (8.3553f / 127.0f) + 0.3f;
								early_par(rev_n);
							}
							break;
						}
						if(par_num < 11)
							del_param(par_num | prog_data[par_num + d_vol] << 8);
					}
				}
			}
			if(encoder_but)
			{
				switch(par_num)
				{
				case 1:
					display_task->clear();
					condish = tap_del_menu;
					eq_num = 0;
					for(uint8_t i = 0;i < 3;i++)
						display_task->line_5x7(6, i, (char*) del_tim_l + i * 13, 0);
					delay_time = del_p1 / 48;
					display_task->del_time_ind(60, 0, delay_time, 1);
					display_task->line_5x7(60, 1, (char*) tap_tim + prog_data[d_tap_t] * 6, 0);
					display_task->line_5x7(90, 2, (char*) del_ex_t + prog_data[del_ex_tap] * 4, 0);
					tim4_start(0);
					break;
				case 11:
					if(!prog_data[d_dir])
						display_task->line_5x7(60, 3, (char*) del_dir + ++prog_data[d_dir] * 8, 0);
					else
						display_task->line_5x7(60, 3, (char*) del_dir + --prog_data[d_dir] * 8, 0);
					del_param(par_num | prog_data[d_dir] << 8);
					break;
				case 12:
					if(!prog_data[d_tail])
						display_task->line_5x7(60, 4, (char*) on_off + ++prog_data[d_tail] * 4, 0);
					else
						display_task->line_5x7(60, 4, (char*) on_off + --prog_data[d_tail] * 4, 0);
					break;
				default:
					if(edit_fl)
					{
						display_task->line_5x7(6, par_num & 7, (char*) del_list + par_num * 9, 0);
						edit_fl = 0;
					}
					else
					{
						display_task->line_5x7(6, par_num & 7, (char*) del_list + par_num * 9, 2);
						edit_fl = 1;
					}
				}
				tim4_start(0);
			}
			if(edit_but)
				eff_init(1);
			clean_fl();
			break;
//---------------------------------------------------------TAP Delay type---------------------------
		case tap_del_menu:
			if(edit_fl == 0)
			{
				if(tim4_fl == 1)
					display_task->line_5x7(6, eq_num, (char*) del_tim_l + eq_num * 13, 2);
				else
					display_task->line_5x7(6, eq_num, (char*) del_tim_l + eq_num * 13, 0);
			}
			if(encoder_fl1)
			{
				if(encoder_fl == 1)
				{
					if(!edit_fl)
					{
						if(eq_num)
						{
							display_task->line_5x7(6, eq_num, (char*) del_tim_l + eq_num-- * 13, 0);
							display_task->line_5x7(6, eq_num, (char*) del_tim_l + eq_num * 13, 2);
						}
					}
					else
					{
						if(eq_num)
						{
							if(prog_data[d_tap_t])
								display_task->line_5x7(60, 1, (char*) tap_tim + --prog_data[d_tap_t] * 6, 0);
						}
						else
						{
							if(delay_time > 10)
							{
								if(tim6.update_interrupt_flag())
									delay_time--;
								else
								{
									if(tim6.counter > 0x1fff)
									{
										if(delay_time > 20)
											delay_time -= 10;
										else
											delay_time--;
									}
									else
									{
										if(tim6.counter > 0x1fff > 0xfff)
										{
											if(delay_time > 40)
												delay_time -= 30;
											else
												delay_time--;
										}
										else
										{
											if(tim6.counter > 0x1fff > 0x7ff)
											{
												if(delay_time > 70)
													delay_time -= 60;
												else
													delay_time--;
											}
											else
											{
												if(delay_time > 110)
													delay_time -= 100;
												else
													delay_time--;
											}
										}
									}
								}
								display_task->del_time_ind(60, 0, delay_time, 1);
								tim6.counter = 0;
								tim6.update_interrupt_flag_clear();
								tim6.enable();
								prog_data[d_tim_lo] = delay_time & 0xff;
								prog_data[d_tim_hi] = delay_time >> 8;
								del_param(12 | prog_data[d_tim_hi] << 8);
								del_param(13 | prog_data[d_tim_lo] << 8);
							}
						}
					}
				}
				if(encoder_fl == 2)
				{
					if(!edit_fl)
					{
						if(eq_num < 2)
						{
							display_task->line_5x7(6, eq_num, (char*) del_tim_l + eq_num++ * 13, 0);
							display_task->line_5x7(6, eq_num, (char*) del_tim_l + eq_num * 13, 2);
						}
					}
					else
					{
						if(eq_num)
						{
							if(prog_data[d_tap_t] < 5)
								display_task->line_5x7(60, 1, (char*) tap_tim + ++prog_data[d_tap_t] * 6, 0);
						}
						else
						{
							if(delay_time < 2730)
							{
								if(tim6.update_interrupt_flag())
									delay_time++;
								else
								{
									if(tim6.counter > 0x1fff)
									{
										if(delay_time < 2720)
											delay_time += 10;
										else
											delay_time++;
									}
									else
									{
										if(tim6.counter > 0xfff)
										{
											if(delay_time < 2690)
												delay_time += 30;
											else
												delay_time++;
										}
										else
										{
											if(tim6.counter > 0x7ff)
											{
												if(delay_time < 2630)
													delay_time += 60;
												else
													delay_time++;
											}
											else
											{
												if(delay_time < 2530)
													delay_time += 100;
												else
													delay_time++;
											}
										}
									}
								}
								display_task->del_time_ind(60, 0, delay_time, 1);
								tim6.counter = 0;
								tim6.update_interrupt_flag_clear();
								tim6.enable();
								prog_data[d_tim_lo] = delay_time & 0xff;
								prog_data[d_tim_hi] = delay_time >> 8;
								del_param(12 | prog_data[d_tim_hi] << 8);
								del_param(13 | prog_data[d_tim_lo] << 8);
							}
						}
					}
				}
				tim4_start(0);
			}
			if(encoder_but)
			{
				if(eq_num == 2)
				{
					prog_data[del_ex_tap]++;
					prog_data[del_ex_tap] %= 5;
					display_task->line_5x7(90, 2, (char*) del_ex_t + prog_data[del_ex_tap] * 4, 0);
					if(prog_data[del_ex_tap])
						tap_ext_fl = 1;
					else
						tap_ext_fl = 0;
				}
				else
				{
					if(!edit_fl)
					{
						edit_fl = 1;
						display_task->line_5x7(6, eq_num, (char*) del_tim_l + eq_num * 13, 2);
					}
					else
					{
						edit_fl = 0;
						display_task->line_5x7(6, eq_num, (char*) del_tim_l + eq_num * 13, 0);
					}
				}
				tim4_start(1);
			}
			if(edit_but)
			{
				condish = del_menu;
				delay_init(1);
				tim4_start(1);
			}
			clean_fl();
			break;
//--------------------------------------------------------------FS Select-------------------------------------------
		case fs_para:
			if(!tim4_fl)
			{
				if(!edit_fl)
				{
					if(par_num < 31)
						display_task->line_5x7(6, 1, (char*) fs_list + par_num * 12, 2);
					else
						display_task->line_5x7(6, par_num - 29, (char*) fs_list + par_num * 12, 2);
				}
				else
				{
					switch(par_num)
					{
					case 0:
					case 2:
					case 22:
					case 26:
					case 27:
					case 28:
					case 29:
					case 5:
						display_task->line_5x7(84, 1, (char*) pr_type_fs + prog_data[Pr] * 8, 2);
						break;
					default:
						if(par_num < 29)
						{
							if(eq_num == 1)
								display_task->num_5x7(84, 1, prog_data[Ng + fs_list_index[par_num]], 2);
							if(eq_num == 2)
								display_task->num_5x7(108, 1, prog_data[Ng + fs_list_index[par_num] + 1], 2);
						}
						else
						{
							if(eq_num == 1)
								display_task->num_5x7(84, par_num - 29, prog_data[Ng + fs_list_index[par_num]], 2);
							if(eq_num == 2)
								display_task->num_5x7(108, par_num - 29, prog_data[Ng + fs_list_index[par_num] + 1], 2);
						}
					}
				}
			}
			else
			{
				if(!edit_fl)
				{
					if(par_num < 31)
						display_task->line_5x7(6, 1, (char*) fs_list + par_num * 12, 0);
					else
						display_task->line_5x7(6, par_num - 29, (char*) fs_list + par_num * 12, 0);
				}
				else
				{
					switch(par_num)
					{
					case 0:
					case 2:
					case 22:
					case 26:
					case 27:
					case 28:
					case 29:
					case 5:
						display_task->line_5x7(84, 1, (char*) pr_type_fs + prog_data[Pr] * 8, 0);
						break;
					default:
						if(par_num < 29)
						{
							if(eq_num == 1)
								display_task->num_5x7(84, 1, prog_data[Ng + fs_list_index[par_num]], 0);
							if(eq_num == 2)
								display_task->num_5x7(108, 1, prog_data[Ng + fs_list_index[par_num] + 1], 0);
						}
						else
						{
							if(eq_num == 1)
								display_task->num_5x7(84, par_num - 29, prog_data[Ng + fs_list_index[par_num]], 0);
							if(eq_num == 2)
								display_task->num_5x7(108, par_num - 29, prog_data[Ng + fs_list_index[par_num] + 1], 0);
						}
					}
				}
			}
			if(encoder_fl1)
			{
				if(encoder_fl == 1)
				{
					if(!edit_fl)
					{
						if(par_num)
						{
							if(par_num < 31)
								foot_switch_init(--par_num);
							else
								display_task->line_5x7(6, par_num - 29, (char*) fs_list + par_num-- * 12, 0);
							ind_fs_sr();
							tim4_start(1);
						}
					}
					else
					{
						if(eq_num == 1)
						{
							uint8_t temp = prog_data[Ng + fs_list_index[par_num]];
							if(temp)
								temp = enc_speed_dec(temp, 0);
							prog_data[Ng + fs_list_index[par_num]] = temp;
							tim4_start(1);
						}
						else
						{
							uint8_t temp = prog_data[Ng + fs_list_index[par_num] + 1];
							if(temp)
								temp = enc_speed_dec(temp, 0);
							prog_data[Ng + fs_list_index[par_num] + 1] = temp;
							tim4_start(1);
						}
						if(prog_data[Ng + fs_list_index[par_num]] || prog_data[Ng + fs_list_index[par_num] + 1])
							prog_data[sel_ng + sel_list_index[par_num]] = f_sw_set;
						else
							prog_data[sel_ng + sel_list_index[par_num]] = 0;
						ind_fs_sr();
					}
				}
				if(encoder_fl == 2)
				{
					if(!edit_fl)
					{
						if(par_num < 36)
						{
							if(par_num < 30)
								foot_switch_init(++par_num);
							else
								display_task->line_5x7(6, par_num - 29, (char*) fs_list + par_num++ * 12, 0);
							ind_fs_sr();
							tim4_start(1);
						}
					}
					else
					{
						if(eq_num == 1)
						{
							uint8_t temp = prog_data[Ng + fs_list_index[par_num]];
							if(par_num != 3)
							{
								if(temp < 127)
									temp = enc_speed_inc(temp, 127);
							}
							else
							{
								temp++;
								temp &= 3;
							}
							prog_data[Ng + fs_list_index[par_num]] = temp;
							tim4_start(0);
						}
						else
						{
							uint8_t temp = prog_data[Ng + fs_list_index[par_num] + 1];
							if(par_num != 3)
							{
								if(temp < 127)
									temp = enc_speed_inc(temp, 127);
							}
							else
							{
								temp++;
								temp &= 3;
							}
							prog_data[Ng + fs_list_index[par_num] + 1] = temp;
							tim4_start(1);
						}
						if(prog_data[Ng + fs_list_index[par_num]] || prog_data[Ng + fs_list_index[par_num] + 1])
							prog_data[sel_ng + sel_list_index[par_num]] = f_sw_set;
						else
							prog_data[sel_ng + sel_list_index[par_num]] = 0;
						ind_fs_sr();
					}
				}
			}
			if(encoder_but)
			{
				switch(par_num)
				{
				case 0:
				case 2:
				case 22:
				case 26:
				case 27:
				case 28:
				case 29:
					prog_data[Ng + fs_list_index[par_num]]++;
					prog_data[Ng + fs_list_index[par_num]] %= 3;
					if(par_num < 31)
						display_task->line_5x7(84, 1, (char*) fs_t_list + prog_data[Ng + fs_list_index[par_num]] * 8, 0);
					else
						display_task->line_5x7(84, par_num - 29, (char*) fs_t_list + prog_data[Ng + fs_list_index[par_num]] * 8, 0);
					if(prog_data[Ng + fs_list_index[par_num]])
						prog_data[sel_ng + sel_list_index[par_num]] = f_sw_set;
					else
						prog_data[sel_ng + sel_list_index[par_num]] = 0;
					break;
				case 3:
				case 4:
					prog_data[Ng + fs_list_index[par_num]]++;
					prog_data[Ng + fs_list_index[par_num]] %= 5;
					display_task->line_5x7(84, 1, (char*) pr_po + prog_data[Ng + fs_list_index[par_num]] * 8, 0);
					if(prog_data[Ng + fs_list_index[par_num]])
						prog_data[sel_ph + par_num - 3] = f_sw_set;
					else
						prog_data[sel_ph + par_num - 3] = 0;
					break;
				case 5:
					prog_data[Ng + fs_list_index[par_num]]++;
					prog_data[Ng + fs_list_index[par_num]] %= 13;
					display_task->line_5x7(84, 1, (char*) pr_type_fs + prog_data[Ng + fs_list_index[par_num]] * 8, 0);
					if(prog_data[Ng + fs_list_index[par_num]])
						prog_data[sel_ng + sel_list_index[par_num]] = f_sw_set;
					else
						prog_data[sel_ng + sel_list_index[par_num]] = 0;
					break;
				case 6:
					prog_data[reamp_mod_]++;
					prog_data[reamp_mod_] %= 7;
					display_task->line_5x7(84, 1, (char*) model_preamp_list + prog_data[reamp_mod_] * 8, 0);
					if(prog_data[reamp_mod_])
						prog_data[sel_preamp_mod_] = f_sw_set;
					else
						prog_data[sel_preamp_mod_] = 0;
					break;
				case 32:
					if(!prog_data[FX])
					{
						prog_data[FX_typ]++;
						prog_data[FX_typ] %= 3;
						display_task->line_5x7(84, 3, (char*) eff_type_fs + prog_data[FX_typ] * 8, 0);
					}
					if(!prog_data[FX_typ])
					{
						prog_data[sel_eff_t] = 0;
						prog_data[er_on] = 0;
					}
					else
					{
						prog_data[sel_eff_t] = f_sw_set;
						prog_data[er_on] = 1;
					}
					break;
				case 31:
					prog_data[FX]++;
					prog_data[FX] %= 3;
					display_task->line_5x7(84, par_num - 21, (char*) fs_ef_list + prog_data[FX] * 8, 0);
					if(prog_data[FX])
						prog_data[sel_eff] = f_sw_set;
					if(!prog_data[FX])
					{
						display_task->line_5x7(84, 3, (char*) eff_type_fs, 0);
						prog_data[sel_eff] = 0;
					}
					else
					{
						display_task->line_5x7(84, 3, (char*) "--- ---", 0);
						prog_data[sel_eff] = f_sw_set;
					}
					break;
				case 36:
					prog_data[Tu]++;
					prog_data[Tu] &= 1;
					if(par_num < 31)
						display_task->line_5x7(84, 1, (char*) fs_t_list + prog_data[Tu] * 8, 0);
					else
						display_task->line_5x7(84, par_num - 29, (char*) fs_t_list + prog_data[Tu] * 8, 0);
					if(prog_data[Tu])
						prog_data[sel_tu] = f_sw_set;
					else
						prog_data[sel_tu] = 0;
					break;
				default:
					if(!edit_fl)
					{
						if(par_num < 31)
						{
							display_task->line_5x7(6, 1, (char*) fs_list + par_num * 12, 2);
							if(par_num != 3)
								display_task->num_5x7(108, 1, prog_data[Ng + fs_list_index[par_num] + 1], 0);
							else
								display_task->line_5x7(108, 1, (char*) pr_type_fs + prog_data[Pr_] * 4, 0);
						}
						else
						{
							display_task->line_5x7(6, par_num - 29, (char*) fs_list + par_num * 12, 2);
							display_task->num_5x7(108, par_num - 29, prog_data[Ng + fs_list_index[par_num] + 1], 0);
						}
						edit_fl = eq_num = 1;
						tim4_start(1);
					}
					else
					{
						if(eq_num == 1)
						{
							eq_num = 2;
							if(par_num < 31)
							{
								if(par_num != 3)
									display_task->num_5x7(84, 1, prog_data[Ng + fs_list_index[par_num]], 0);
								else
									display_task->line_5x7(84, 1, (char*) pr_type_fs + prog_data[Pr] * 4, 0);
							}
							else
								display_task->num_5x7(84, par_num - 29, prog_data[Ng + fs_list_index[par_num]], 0);
						}
						else
						{
							if(par_num < 31)
							{
								if((!prog_data[Ng + fs_list_index[par_num]]) && (!prog_data[Ng + fs_list_index[par_num] + 1]))
									display_task->line_5x7(84, 1, (char*) fs_t_list, 0);
								else
								{
									if(par_num != 3)
										display_task->num_5x7(108, 1, prog_data[Ng + fs_list_index[par_num] + 1], 0);
									else
										display_task->line_5x7(108, 1, (char*) pr_type_fs + prog_data[Pr_] * 4, 0);
								}
							}
							else
							{
								if((!prog_data[Ng + fs_list_index[par_num]]) && (!prog_data[Ng + fs_list_index[par_num] + 1]))
									display_task->line_5x7(84, par_num - 29, (char*) fs_t_list, 0);
								else
									display_task->num_5x7(108, par_num - 29, prog_data[Ng + fs_list_index[par_num] + 1], 0);
							}
							edit_fl = eq_num = 0;
						}
					}
				}
				ind_fs_sr();
				tim4_start(1);
			}
			if(edit_but)
			{
				if(f_sw_set == 1)
					edit_init1(4);
				if(f_sw_set > 1)
					edit_init1(5);
			}
			clean_fl();
			break;
//--------------------------------------------------------------Menu Name-------------------------------------------
		case name_edit:
			if(par_num < 14)
				display_task->sym_5x7(par_num * 6 + 2, 0, imya[par_num], tim4_fl * 2 - edit_fl);
			else
				display_task->sym_5x7((par_num - 14) * 6 + 2, 1, imya1[(par_num - 14)], tim4_fl * 2 - edit_fl);
			if(edit_fl)
			{
				if(eq_num < 21)
				{
					if(!key_shift)
						display_task->sym_5x7(eq_num * 6, 2, ascii_low1[eq_num], tim4_fl);
					else
						display_task->sym_5x7(eq_num * 6, 2, ascii_hig1[eq_num], tim4_fl);
				}
				else
				{
					if(!key_shift)
						display_task->sym_5x7((eq_num - 21) * 6, 3, ascii_low2[eq_num - 21], tim4_fl);
					else
						display_task->sym_5x7((eq_num - 21) * 6, 3, ascii_hig2[eq_num - 21], tim4_fl);
				}
			}
			if(encoder_fl1)
			{
				if(encoder_fl == 1)
				{
					if(!edit_fl)
					{
						if(par_num > 0)
						{
							if(par_num < 14)
							{
								display_task->sym_5x7(par_num * 6 + 2, 0, imya[par_num--], 0);
								display_task->sym_5x7(par_num * 6 + 2, 0, imya[par_num], 2);
							}
							if(par_num == 14)
							{
								display_task->sym_5x7((par_num - 14) * 6 + 2, 1, imya1[(par_num-- - 14)], 0);
								display_task->sym_5x7(par_num * 6 + 2, 0, imya[par_num], 2);
							}
							if(par_num > 14)
							{
								display_task->sym_5x7((par_num - 14) * 6 + 2, 1, imya1[(par_num-- - 14)], 0);
								display_task->sym_5x7((par_num - 14) * 6 + 2, 1, imya1[(par_num - 14)], 2);
							}
						}
					}
					else
					{
						if(eq_num < 21)
						{
							if(!key_shift)
							{
								if(eq_num == 0)
								{
									display_task->sym_5x7((eq_num) * 6, 2, ascii_low1[eq_num], 0);
									eq_num = 41;
									display_task->sym_5x7((eq_num - 21) * 6, 3, ascii_low2[eq_num - 21], 0);
									nam_sym_temp = ascii_low2[eq_num - 21];
								}
								else
								{
									display_task->sym_5x7(eq_num * 6, 2, ascii_low1[eq_num--], 0);
									display_task->sym_5x7(eq_num * 6, 2, ascii_low1[eq_num], 0);
									nam_sym_temp = ascii_low1[eq_num];
								}
							}
							else
							{
								if(eq_num == 0)
								{
									display_task->sym_5x7((eq_num) * 6, 2, ascii_hig1[eq_num], 0);
									eq_num = 41;
									display_task->sym_5x7((eq_num - 21) * 6, 3, ascii_hig2[eq_num - 21], 0);
									nam_sym_temp = ascii_hig2[eq_num - 21];
								}
								else
								{
									display_task->sym_5x7(eq_num * 6, 2, ascii_hig1[eq_num--], 0);
									display_task->sym_5x7(eq_num * 6, 2, ascii_hig1[eq_num], 0);
									nam_sym_temp = ascii_hig1[eq_num];
								}
							}
						}
						else
						{
							if(eq_num > 20)
							{
								if(!key_shift)
								{
									if(eq_num == 21)
									{
										display_task->sym_5x7((eq_num - 21) * 6, 3, ascii_low2[eq_num-- - 21], 0);
										display_task->sym_5x7(eq_num * 6, 2, ascii_low1[eq_num], 1);
										nam_sym_temp = ascii_low1[eq_num];
									}
									else
									{
										display_task->sym_5x7((eq_num - 21) * 6, 3, ascii_low2[eq_num-- - 21], 0);
										display_task->sym_5x7((eq_num - 21) * 6, 3, ascii_low2[eq_num - 21], 1);
										nam_sym_temp = ascii_low2[eq_num - 21];
									}
								}
								else
								{
									if(eq_num == 21)
									{
										display_task->sym_5x7((eq_num - 21) * 6, 3, ascii_hig2[eq_num-- - 21], 0);
										display_task->sym_5x7(eq_num * 6, 2, ascii_hig1[eq_num], 1);
										nam_sym_temp = ascii_hig1[eq_num];
									}
									else
									{
										display_task->sym_5x7((eq_num - 21) * 6, 3, ascii_hig2[eq_num-- - 21], 0);
										display_task->sym_5x7((eq_num - 21) * 6, 3, ascii_hig2[eq_num - 21], 0);
										nam_sym_temp = ascii_hig2[eq_num - 21];
									}
								}
							}
						}
					}
				}
				if(encoder_fl == 2)
				{
					if(!edit_fl)
					{
						if(par_num < 27)
						{
							if(par_num > 13)
							{
								display_task->sym_5x7((par_num - 14) * 6 + 2, 1, imya1[(par_num++ - 14)], 0);
								display_task->sym_5x7((par_num - 14) * 6 + 2, 1, imya1[(par_num - 14)], 2);
							}
							if(par_num == 13)
							{
								display_task->sym_5x7(par_num * 6 + 2, 0, imya[par_num++], 0);
								display_task->sym_5x7((par_num - 14) * 6 + 2, 1, imya1[(par_num - 14)], 2);
							}
							if(par_num < 13)
							{
								display_task->sym_5x7(par_num * 6 + 2, 0, imya[par_num++], 0);
								display_task->sym_5x7(par_num * 6 + 2, 0, imya[par_num], 2);
							}
						}
					}
					else
					{
						if(eq_num < 20)
						{
							if(!key_shift)
							{
								display_task->sym_5x7(eq_num * 6, 2, ascii_low1[eq_num++], 0);
								display_task->sym_5x7(eq_num * 6, 2, ascii_low1[eq_num], 0);
								nam_sym_temp = ascii_low1[eq_num];
							}
							else
							{
								display_task->sym_5x7(eq_num * 6, 2, ascii_hig1[eq_num++], 0);
								display_task->sym_5x7(eq_num * 6, 2, ascii_hig1[eq_num], 0);
								nam_sym_temp = ascii_hig1[eq_num];
							}
						}
						else
						{
							if(!key_shift)
							{
								if(eq_num == 41)
								{
									display_task->sym_5x7((eq_num - 21) * 6, 3, ascii_low2[eq_num - 21], 0);
									eq_num = 0;
									display_task->sym_5x7(eq_num * 6, 2, ascii_low1[eq_num], 0);
									nam_sym_temp = ascii_low1[eq_num];
								}
								else
								{
									if(eq_num == 20)
										display_task->sym_5x7(eq_num * 6, 2, ascii_low1[eq_num++], 0);
									else
										display_task->sym_5x7((eq_num - 21) * 6, 3, ascii_low2[eq_num++ - 21], 0);
									display_task->sym_5x7((eq_num - 21) * 6, 3, ascii_low2[eq_num - 21], 0);
									nam_sym_temp = ascii_low2[eq_num - 21];
								}
							}
							else
							{
								if(eq_num == 41)
								{
									display_task->sym_5x7((eq_num - 21) * 6, 3, ascii_hig2[eq_num - 21], 0);
									eq_num = 0;
									display_task->sym_5x7(eq_num * 6, 2, ascii_hig1[eq_num], 0);
									nam_sym_temp = ascii_hig1[eq_num];
								}
								else
								{
									if(eq_num == 20)
										display_task->sym_5x7(eq_num * 6, 2, ascii_hig1[eq_num++], 0);
									else
										display_task->sym_5x7((eq_num - 21) * 6, 3, ascii_hig2[eq_num++ - 21], 0);
									display_task->sym_5x7((eq_num - 21) * 6, 3, ascii_hig2[eq_num - 21], 0);
									nam_sym_temp = ascii_hig2[eq_num - 21];
								}
							}
						}
					}
				}
				tim4_start(0);
				clean_fl();
			}
			if(edit_but)
			{
				if(edit_fl)
				{
					if(key_shift)
					{
						key_shift = 0;
						display_task->line_5x7(0, 2, (char*) ascii_low1, 0);
						display_task->line_5x7(0, 3, (char*) ascii_low2, 0);
						if(eq_num < 21)
							nam_sym_temp = ascii_low1[eq_num];
						else
							nam_sym_temp = ascii_low2[eq_num - 21];
					}
					else
					{
						key_shift = 1;
						display_task->line_5x7(0, 2, (char*) ascii_hig1, 0);
						display_task->line_5x7(0, 3, (char*) ascii_hig2, 0);
						if(eq_num < 21)
							nam_sym_temp = ascii_hig1[eq_num];
						else
							nam_sym_temp = ascii_hig2[eq_num - 21];
					}
				}
				else
					edit_init1(7);
				tim4_start(1);
				clean_fl();
			}
			if(encoder_but)
			{
				if(!edit_fl)
				{
					edit_fl = 1;
					if(par_num < 14)
						display_task->sym_5x7(par_num * 6 + 2, 0, imya[par_num], 1);
					else
						display_task->sym_5x7((par_num - 14) * 6 + 2, 1, imya1[par_num - 14], 1);
				}
				else
				{
					edit_fl = 0;
					if(par_num < 14)
					{
						imya[par_num] = nam_sym_temp;
						display_task->sym_5x7(par_num * 6 + 2, 0, imya[par_num], 0);
					}
					else
					{
						imya1[par_num - 14] = nam_sym_temp;
						display_task->sym_5x7((par_num - 14) * 6 + 2, 1, imya1[par_num - 14], 0);
					}
					if(!key_shift)
					{
						if(eq_num < 21)
							display_task->sym_5x7(eq_num * 6, 2, ascii_low1[eq_num], 0);
						else
							display_task->sym_5x7((eq_num - 21) * 6, 3, ascii_low2[eq_num - 21], 0);
					}
					else
					{
						if(eq_num < 21)
							display_task->sym_5x7(eq_num * 6, 2, ascii_hig1[eq_num], 0);
						else
							display_task->sym_5x7((eq_num - 21) * 6, 3, ascii_hig2[eq_num - 21], 0);
					}
				}
				tim4_start(0);
				clean_fl();
			}
			break;
//--------------------------------------------------------------Volume---------------------------------------------
		case volum:
			if(encoder_fl1)
			{
				if(encoder_fl == 1)
				{
					if(prog_data[pres_lev])
					{
						prog_data[pres_lev] = enc_speed_dec(prog_data[pres_lev], 0);
						p_vol = powf(prog_data[pres_lev], 2.0f) * (1.0f / powf(127.0f, 2.0f));
						display_task->par_indic(75, 1, prog_data[pres_lev]);
					}
				}
				if(encoder_fl == 2)
				{
					if(prog_data[pres_lev] < 127)
					{
						prog_data[pres_lev] = enc_speed_inc(prog_data[pres_lev], 127);
						p_vol = powf(prog_data[pres_lev], 2.0f) * (1.0f / powf(127.0f, 2.0f));
						display_task->par_indic(75, 1, prog_data[pres_lev]);
					}
				}
			}
			if(edit_but)
			{
				condish = men_edit;
				edit_init1(2);
				tim4_start(1);
			}
			clean_fl();
			break;
//------------------------------------------------------Compressor--------------
		case compresss_men:
			if(currentMenu)
			{
				if(currentMenu->menuType() != gui_menu_type::MENU_ABSTRACT)
				{
					currentMenu->task();

					if(encoder_fl1)
					{
						if(encoder_fl == 1)
						{
							currentMenu->encoderCounterClockwise();
						}
						if(encoder_fl == 2)
						{
							currentMenu->encoderClockwise();
						}
					}
					if(encoder_but)
					{
						currentMenu->encoderPressed();
					}
					if(edit_but)
					{
						currentMenu->keyEditEsc();
						edit_init(1);
					}

					clean_fl();
				}
			}
			/*
			if(!tim4_fl)
			{
				if(!edit_fl)
					display_task->line_5x7(0, par_num, (char*) compressor_list + par_num * 10, 2);
			}
			else
			{
				if(!edit_fl)
					display_task->line_5x7(0, par_num, (char*) compressor_list + par_num * 10, 0);
			}
			if(encoder_fl1)
			{
				if(encoder_fl == 1)
				{
					if(!edit_fl)
					{
						if(par_num)
						{
							display_task->line_5x7(0, par_num, (char*) compressor_list + par_num-- * 10, 0);
							tim4_start(1);
						}
					}
					else
					{
						if(prog_data[compr_on + par_num])
						{
							prog_data[compr_on + par_num] = enc_speed_dec(prog_data[compr_on + par_num], 0);
							display_task->par_indic(65, par_num, prog_data[compr_on + par_num]);
							compr.comp_par(par_num | prog_data[par_num + compr_on] << 8);
						}
					}
				}
				if(encoder_fl == 2)
				{
					if(!edit_fl)
					{
						if(par_num < 5)
						{
							display_task->line_5x7(0, par_num, (char*) compressor_list + par_num++ * 10, 0);
							tim4_start(1);
						}
					}
					else
					{
						if(prog_data[compr_on + par_num] < 127)
						{
							prog_data[compr_on + par_num] = enc_speed_inc(prog_data[compr_on + par_num], 127);
							display_task->par_indic(65, par_num, prog_data[compr_on + par_num]);
							compr.comp_par(par_num | prog_data[par_num + compr_on] << 8);
						}
					}
				}
			}
			if(encoder_but)
			{
				if(!par_num)
				{
					prog_data[compr_on] = (prog_data[compr_on] + 1) & 1;
					display_task->line_5x7(65, par_num, (char*) on_off + prog_data[compr_on] * 4, 0);
				}
				else
				{
					if(!edit_fl)
					{
						edit_fl = 1;
						display_task->line_5x7(0, par_num, (char*) compressor_list + par_num * 10, 2);
					}
					else
						edit_fl = 0;
				}
				tim4_start(0);
			}
			if(edit_but)
				edit_init(1);
			clean_fl();
			*/
			break;
//---------------------------------------------------------------Metronome-----------------------
		case metronome_menu:
			if(!tim4_fl)
			{
				if(!edit_fl)
					display_task->line_5x7(0, par_num, (char*) menu_list3 + par_num * 10, 2);
			}
			else
			{
				if(!edit_fl)
					display_task->line_5x7(0, par_num, (char*) menu_list3 + par_num * 10, 0);
			}
			if(encoder_fl1)
			{
				if(encoder_fl == 1)
				{
					if(!edit_fl)
					{
						if(par_num)
							display_task->line_5x7(0, par_num, (char*) menu_list3 + par_num-- * 10, 0);
					}
					else
					{
						if(par_num == 1)
						{
							if(tempo > 20)
							{
								tempo = enc_speed_dec(tempo, 20);
								metronom_int = 48000.0f / (tempo / 60.0f) + 0.5f;
								display_task->num_5x7(64, 1, tempo, 0);
							}
						}
						else
						{
							if(metronom_vol)
							{
								metronom_vol = enc_speed_dec(metronom_vol, 0);
								display_task->par_indic(60, 2, metronom_vol);
							}
						}
					}
				}
				if(encoder_fl == 2)
				{
					if(!edit_fl)
					{
						if(par_num < 2)
							display_task->line_5x7(0, par_num, (char*) menu_list3 + par_num++ * 10, 0);
					}
					else
					{
						if(par_num == 1)
						{
							if(tempo < 240)
							{
								tempo = enc_speed_inc(tempo, 240);
								metronom_int = 48000.0f / (tempo / 60.0f) + 0.5f;
								display_task->num_5x7(64, 1, tempo, 0);
							}
						}
						else
						{
							if(metronom_vol < 127)
							{
								metronom_vol = enc_speed_inc(metronom_vol, 127);
								display_task->par_indic(60, 2, metronom_vol);
							}
						}
					}
				}
				tim4_start(1);
			}
			if(encoder_but)
			{
				if(!par_num)
				{
					if(!metronom_start)
					{
						metronom_int = 48000.0f / (tempo / 60.0f) + 0.5f;
						metronom_counter = temp_counter = 0;
						metronom_start = 1;
						display_task->line_5x7(63, 0, (char*) on_off + metronom_start * 4, 0);
					}
					else
					{
						metronom_start = 0;
						display_task->line_5x7(63, 0, (char*) on_off + metronom_start * 4, 0);
					}
				}
				else
				{
					if(!edit_fl)
					{
						edit_fl = 1;
						display_task->line_5x7(0, par_num, (char*) menu_list3 + par_num * 10, 2);
					}
					else
						edit_fl = 0;
					tim4_start(1);
				}
			}
			if(edit_but)
				sys_init(6);
			clean_fl();
			break;
		}
	}
}
uint8_t tap_temp_global(void)
{
	uint8_t a = 0;
	if(tap_temp < 8191)
	{
		tap_global = tap_temp * 16;
		revmem_clean();
		tap_global *= tap_tim_v[prog_data[d_tap_t]];
		if(tap_global > 131071)
			tap_global = 131071;
		delay_time = tap_global / 48;
		if(condish == start_screen && !indic_impul)
		{
			if(tap_fs_fl)
			{
				display_task->line_12x13_clean(35, 4, 54);
				display_task->del_time_ind(35, 4, delay_time, 0);
			}
		}
		else
		{
			if(condish == del_menu && !del_men_fl)
				display_task->del_time_ind(60, 1, delay_time, 1);
			else if(condish == tap_del_menu)
				display_task->del_time_ind(60, 0, delay_time, 1);
		}
		a = 1;
	}
	tap_temp = 0;
	return a;
}
void path_fold(emb_string &path)
{
	auto it = path.end();
	while(*(--it) != '/' && it != path.begin())
		;
	while(--it != path.begin())
	{
		if(*it != '/')
			path.erase(it);
	}
}

extern volatile uint8_t tim4_upd;
IRQ_HANDLER(tim4)
{
	tim4.update_interrupt_flag_clear();
	if(tim4_fl)
		tim4_fl = 0;
	else
		tim4_fl = 1;

	AbstractMenu::blinkRoutine();

	gui_task->update();
}
