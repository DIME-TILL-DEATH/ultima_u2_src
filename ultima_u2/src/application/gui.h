#ifndef __GUI_H__
#define __GUI_H__

#include "appdefs.h"

#include "tasks/display_task.h"

typedef union
{
	int32_t val ;
	struct {
		uint8_t im_0 ;
		uint8_t im_1 ;
		uint8_t im_2 ;
		uint8_t im_3 ;
	};
} imp_data_t ;

enum {start_screen,men_edit,men_edit1,preamp_menu,amp_menu,equalis,reverb_menu,volum,name_edit,cab_onoff,eq_para,fs_para,fs_proc,filt_para,ext_fs1,ext_fs2,save_men,
	  calibrate,exspression_list,od_menu,eff_menu,del_menu,mas_vol,early_menu,od_t_menu,browser_menu,save_confirm_menu,
	  gate_menu,system_menu,compresss_men,cab_vol_ind,tap_del_menu,metronome_menu,tuner,clear_menu,over_menu,phaz_edit,flan_edit};

enum {/*OD on*/od_on,/*preamp_on*/preamp_on,/*amp_on*/amp_on,/*cab_on*/cab_on,/*eq_on*/eq_on,
	  /*eq position*/eq_po,/*er_on*/er_on,/*eq*/eq1,eq2,eq3,eq4,eq5,/*preamp vol*/preamp_vol,preamp_lo,preamp_mi,preamp_hi,preamp_pos,
      /*amplif*/a_vol,/*presence*/presen_vol,/*amplifier slave*/amp_slave,a_t,/*rev_vol*/r_vol,/*rev type*/r_typ,/*rev time*/r_time,
	  /*rev size*/r_size,/*rev dump*/r_dump,/*rev lp*/r_lp,/*rev hp*/r_hp,/*rev det*/r_det,/*rev diff*/r_diff,/*rev pred*/r_pre,
	  /*rev tail*/rev_tail,/*delay vol*/d_vol,/*delay fed*/d_fed = 34,/*delay lp*/d_lp,/*delay hp*/d_hp,/*delay pan*/d_pan,
      /*delay2 vol*/dp_vol,/*delay2 pan*/dp_pan,/*delay2 tim*/dp_d,/*delay mod*/d_mod,/*delay rate*/d_ra,/*delay dir*/d_dir,
	  /*delay tim hi*/d_tim_hi,/*delay tim lo*/d_tim_lo,/*delay tap type*/d_tap_t,/*delay tail*/d_tail,/*ear vol*/ear_del_vol,
	  /*ear size*/ear_del_size,/*pres_vol*/pres_lev,/*cab*/cab_vol,/*od type*/od_typ,/*od volum*/od_vol,
	  /*compr on*/compr_on,/*c thr*/c_thr,/*c rat*/c_rat,/*c vol*/c_vol,/*c a*/c_at,/*c re*/c_rel,/*od low*/od_low,
	  /*od mid*/od_mid,/*od high*/od_high,/*eq band freq*/fr1,fr2,fr3,fr4,fr5,/*eq band q*/q1,q2,q3,q4,q5,/*presence*/pr_on,
	  /*lohi*/lop,hip,hip_on,lop_on,/*fx type*/fx_type,/*FS On*/Ng,Ng_th,Ng_th_,Compres,Pr,Pr_,Amp,Cab,Equa,LPF,HPF,Presenc,
	  FX,FX_typ,Tun_on,Cl_volum,Cl_volum_,Od_vol,Od_vol_,Pr_low,Pr_low_,Pr_mid,Pr_mid_,Pr_hi,Pr_hi_,Od_low, Od_low_,Od_mid,
	  Od_mid_,Od_hi,Od_hi_,Amp_volum,Amp_volum_,Amp_slave,Amp_slave_,Amp_presence,Amp_presence_,Del_volume,Del_volume_,
	  Ear_volume,Ear_volume_,Rev_volume,Rev_volume_,
	  /*FS On1*/sel_ng,sel_ng_th,sel_compr,sel_pr,sel_cl_vol,sel_dr_vol,sel_cl_low,
	  sel_cl_mid,sel_cl_hi,sel_dr_low,sel_dr_mid,sel_dr_hi,sel_amp,sel_amp_vol,sel_amp_sl,sel_amp_pres,sel_cabsim,sel_eq,
	  sel_lopass,sel_hipass,sel_pres,sel_eff,sel_eff_t,sel_del_v,set_ear_v,sel_rev_v,sel_tun_on,
	  /*expr preset*/ex_pr_lo,ex_pr_hi,/*expr prmp*/ex_cln_lo,ex_cln_hi,ex_drv_lo,ex_drv_hi,/*expr amp vol*/ex_am_vo_lo,ex_am_vo_hi,
	  /*expr amp sl*/ex_am_sl_lo,ex_am_sl_hi,/*expr presen*/ex_presen_lo,ex_presen_hi,
	  /*int fsw*/ifs_type,/*rev fed*/rev_fed,
	  /*rev nofed val*/rev_nofed,/*del_ext_tap*/del_ex_tap,/*cab mix*/ir_mix,/*gat preset*/ga_on,ga_th,ga_at,ga_de,
	  /*Preamp Gain*/prc_gain,prl_gain,prh_gain,prf_LP1,prf_LP1_st,prf_HP1,prf_HP1_st,prf_LP2,prf_LP2_st,prf_HP2,prf_HP2_st,
	  pr_gain1,pr_over,
	  /*phaz_on*/phaz_on,/*phaz mix*/ph_mix,/*phaz rat*/ph_rate,/*phaz center*/ph_cent,/*phaz width*/ph_width,/*phaz fb*/ph_fb,
	  /*phaz stage*/ph_stag,/*phaz hpf*/ph_hpf,/*phaz poz*/ph_poz,

	  /*flan_on*/flan_on,/*flan mix*/fl_mix,/*flan LFO*/fl_lfo,/*flan rate*/fl_rat,/*flan width*/fl_widt,/*flan delay*/fl_del,
	  /*fl fb*/fl_fb,/*flan HPF*/fl_hpf,/*flan poz*/fl_poz,
	  /*FS Phaser*/Phaz,/*FS Flang*/Flang,/*Sel*/sel_ph,sel_fl,/*ld low*/ld_low,/*ld mid*/ld_mid,/*ld high*/ld_high,
	  /*over type*/pr_over_cl,pr_over_cr,pr_over_ld,/*peamp model*/reamp_mod_,sel_preamp_mod_,Lid_gain,Lid_gain_,Lid_vol,Lid_vol_,Lid_low,Lid_low_,Lid_mid,Lid_mid_,Lid_hig,Lid_hig_,
	  /*sel*/sel_lid_gain,sel_lid_vol,sel_lid_low,sel_lid_mid,sel_lid_hig,
	  /*FS preamp gain*/Preampgain,Preampgain_,Cranch_gain,Cranch_gain_,sel_cl_gain,sel_cr_gain,
	  /*FS Tuner*/Tu,sel_tu,

	  /*end*/pdCount};

enum {Phaz_temp,Flan_temp,SWtempCount};

struct system_file_t
{
  uint8_t preset_num ;
  uint16_t exp_calib_lo ;
  uint16_t exp_calib_hi ;
  uint8_t exp_On_Off;
  uint8_t fs_inver = 4;
  uint8_t fs_singl_duble;
  uint8_t extFS_type;
  uint8_t preset_old;
  uint8_t midi_ch;
  uint8_t gat_on = 0;
  uint8_t gat_thresh = 0;
  uint8_t gat_att = 0;
  uint8_t gat_dec = 10;
  uint8_t glob_cab = 0;
  uint8_t f_sw_exp = 1;
  // сюда дописывать чего угодно и сколько угодно
} ;

extern system_file_t system_file ;

extern uint8_t encoder_fl1;
extern uint8_t encoder_but;
extern uint8_t edit_but;
extern uint8_t encoder_but_dub_short;
extern uint8_t encoder_but_dub_long;
extern uint8_t foot_sw_dub_short;
extern uint8_t foot_sw_dub_long;
extern uint8_t ext_but_long_fl;
extern uint8_t fs_but;
extern uint8_t edit_fl;
extern uint16_t ind_poin;
extern const uint8_t rev_type_list [][10];
extern const uint8_t menu_list     [][16];
extern const uint8_t eq_list [][10];
extern uint8_t  imya [];
extern uint8_t  imya1[];
extern uint8_t  imya_t [];
extern uint8_t  imya1_t[];
extern uint8_t imya_temp;
extern uint8_t prog;
extern uint8_t prog1;
extern uint8_t condish;
extern uint8_t prog_flag;
extern volatile uint8_t impulse_flag;
extern uint8_t re_par[];
extern const uint8_t eff_type[][7];
extern int32_t del_p1;
extern uint8_t prog_data[];
extern float chor_rate;
extern uint16_t rev_pre;
extern float adc_delta;
extern float pream_vol;
extern float od_volume;
extern volatile uint8_t ind_clean;
extern volatile uint8_t ind_clean1;
extern uint8_t right_ind_fl;
extern uint8_t left_ind_fl;

class gui_task_t : public task_t
{
public:
  inline gui_task_t (const char* name , const int stack_size , const int priority, size_t update_count ) : task_t(name , stack_size , priority , false)
     {
        update_request = new semaphore_counting_t ( update_count , 0 ) ;
     }


  inline void update() { update_request->give(); }

  void prog_ch(void);
  void preset_check(void);
  void preset_set(void);

  inline void right_ind(void){right_ind_fl = 1;}
  inline void left_ind(void){left_ind_fl = 1;}
  inline void right_ind_cl(void){right_ind_fl = 0;gpioa.pin0_set();}
  inline void left_ind_cl(void){left_ind_fl = 0;gpioa.pin1_set();}

  inline void ind_exp_on(uint8_t pos)
  {
	  system_file.exp_On_Off = pos;
	  if(condish == system_menu)
	  {
		  if(system_file.f_sw_exp || !pos)
		  {
			  display_task->line_5x7(0,3,(char*)       "             ",0);
			  display_task->line_5x7(0,3,(char*)       "Exp. OFF     ",0);
		  }
		  else {
			  if(pos)display_task->line_5x7(0,3,(char*)"Exp.Calibrate",0);
		  }
	  }
  }
  inline void gu_del(uint16_t tim){delay(tim);}

  inline void main_screen(uint8_t type)
  {
	  encoder_fl1 = encoder_but = edit_but = edit_fl = 0;
      ind_poin = 0;
      display_task->line_5x7_clean(2,0,(char*)imya);
      display_task->line_5x7_clean(2,1,(char*)imya);
      display_task->line_5x7_clean(0,2,(char*)"             ");
      display_task->line_5x7_clean(0,3,(char*)"             ");
      display_task->line_5x7_clean(0,4,(char*)"                     ");
      display_task->line_5x7_clean(0,5,(char*)"                     ");
      display_task->line_5x7_clean(0,6,(char*)"                     ");
      display_task->line_5x7_clean(0,7,(char*)"                     ");
      if(!imya_temp)
        {
      	display_task->line_5x7(2,0,(char*)imya,0);
      	display_task->line_5x7(2,1,(char*)imya1,0);
        }
      else {
      	display_task->line_5x7(2,0,(char*)imya_t,0);
      	display_task->line_5x7(2,1,(char*)imya1_t,0);
      }
      if(!type)
      {
    	  display_task->prog_indic(prog,1,prog_flag);
    	  condish = start_screen;
    	  display_task->icon_eff(0);
      }
      else {
    	  display_task->prog_indic(prog1,1,prog_flag);
    	  display_task->icon_eff(1);
      }
      display_task->line_12x13(16,6,(char*)"IR CabSim/FX",0);
  }

  private:
     void code() ;

     semaphore_counting_t* update_request ;
};

inline void clean_fl(void){encoder_fl1 = encoder_but = edit_but = encoder_but_dub_short = encoder_but_dub_long = foot_sw_dub_long = ext_but_long_fl = 0;}
extern gui_task_t* gui_task ;

#endif /* __GUI_H__ */
