#include "appdefs.h"
#include "allFonts.h"
#include "init.h"
#include "gui.h"
#include "SystemFont5x7.h"
#include "SN1106.h"
#include "tun_bit.h"

const uint8_t ng[]="NG";
const uint8_t cm[]="CM";
const uint8_t pr[]="PR";
const uint8_t pa[]="PA";
const uint8_t ir[]="IR";
const uint8_t eq[]="EQ";
const uint8_t ft[]="FT";
const uint8_t dl[]="DL";
const uint8_t rv[]="RV";
const uint8_t ef[]="FX";
const uint8_t fl[]="FL";

const uint8_t gat_sym1[] = {0xF8, 0x3F, 0x08, 0x20, 0xE8, 0x2F, 0x88, 0x20, 0x08, 0x21, 0x08, 0x22, 0xE8, 0x2F, 0x08, 0x20,
		                    0xC8, 0x27, 0x28, 0x28, 0x28, 0x29, 0x28, 0x29, 0x48, 0x26, 0x08, 0x20, 0xF8, 0x3F
};
const uint8_t gat_sym2[] = {0xF8, 0x3F, 0xF8, 0x3F, 0x18, 0x30, 0x78, 0x3F, 0xF8, 0x3E, 0xF8, 0x3D, 0x18, 0x30, 0xF8, 0x3F,
		                    0x38, 0x38, 0xD8, 0x37, 0xD8, 0x36, 0xD8, 0x36, 0xB8, 0x39, 0xF8, 0x3F, 0xF8, 0x3F
};
const uint8_t com_sym1[] = {0xF8, 0x3F, 0x08, 0x20, 0xC8, 0x27, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x48, 0x24, 0x08, 0x20,
		                    0xE8, 0x2F, 0x48, 0x20, 0x88, 0x20, 0x48, 0x20, 0xE8, 0x2F, 0x08, 0x20, 0xF8, 0x3F
};
const uint8_t com_sym2[] = {0xF8, 0x3F, 0xF8, 0x3F, 0x38, 0x38, 0xD8, 0x37, 0xD8, 0x37, 0xD8, 0x37, 0xB8, 0x3B, 0xF8, 0x3F,
		                    0x18, 0x30, 0xB8, 0x3F, 0x78, 0x3F, 0xB8, 0x3F, 0x18, 0x30, 0xF8, 0x3F, 0xF8, 0x3F
};
const uint8_t phs_sym1[] = {0xF8, 0x3F, 0x08, 0x20, 0xE8, 0x2F, 0x28, 0x21, 0x28, 0x21, 0x28, 0x21, 0xC8, 0x20, 0x08, 0x20,
		                    0xE8, 0x2F, 0x08, 0x21, 0x08, 0x21, 0x08, 0x21, 0xE8, 0x2F, 0x08, 0x20, 0xF8, 0x3F
};
const uint8_t phs_sym2[] = {0xF8, 0x3F, 0xF8, 0x3F, 0x18, 0x30, 0xD8, 0x3E, 0xD8, 0x3E, 0xD8, 0x3E, 0x38, 0x3F, 0xF8, 0x3F,
		                    0x18, 0x30, 0xF8, 0x3E, 0xF8, 0x3E, 0xF8, 0x3E, 0x18, 0x30, 0xF8, 0x3F, 0xF8, 0x3F
};

uint32_t ind_in_p[2];
uint32_t ind_out_l[2];
uint32_t ind_out_r[2];
uint16_t ind_poin;
uint8_t vol_fl;
uint8_t vol_vol;
uint8_t inp_ind_fl = 0;
uint8_t out_ind_fl = 0;

uint8_t t_po;
uint8_t t_po1;
volatile uint8_t t_no;
//volatile uint32_t p_no1 = 0x1ffff;

void vol_indic(void)
{
  uint8_t in = sqrt_f32_main(ind_in_p[1])*(63.0f/sqrt_f32_main(8388607.0f));
  uint8_t outl = sqrt_f32_main(ind_out_l[1])*(63.0f/sqrt_f32_main(8388607.0f));
  uint8_t outr = sqrt_f32_main(ind_out_r[1])*(63.0f/sqrt_f32_main(8388607.0f));
  ind_in_p[1] = ind_out_r[1] = ind_out_l[1] = 0;
  sh1106_gotoXY(31,3);
  for(uint8_t i = 0 ; i < 64 ; i++)
    {
      if(in > i)font_buf[i] = 0xf;
      else
        {
          if((i == 63) || (i == 0))font_buf[i] = 0xf;
          else font_buf[i] = 0;
        }
    }
  spi3_dma_init_transfer(64,(uint32_t*)font_buf);
//------------------------------------------------------------------
  sh1106_gotoXY(31,4);
  for(uint8_t i = 0 ; i < 64 ; i++)
    {
      if((vol_fl == 1) && (i >= vol_vol - 2) && (i <= vol_vol))
        {
          if(i == vol_vol - 1)font_buf[i] = 0x41;
          else  font_buf[i] = 0x3e;
        }
      else {
      if(outl > i)
        {
          if(outr > i)font_buf[i] = 0x77;
          else font_buf[i] = 0x7;
        }
      else
        {
          if((i == 63) || (i == 0))font_buf[i] = 0x77;
          else {
              if(outr > i)font_buf[i] = 0x70;
              else font_buf[i] = 0x0;
          }
        }
     }
   }
  spi3_dma_init_transfer(64,(uint32_t*)font_buf);
}
void del_sec_ind(uint8_t col , uint8_t pag , uint32_t d , uint8_t font)
{
	uint16_t t3[4];
	t3[0] = d / 1000;
	t3[2] = d % 1000;
	t3[1] = t3[2] / 100 ;
	t3[3] = t3[2] % 100;
	t3[2] = t3[3] / 10;
	t3[3] = t3[3] % 10;
	if(!font)
	{
		col += t12x13_sym(col,pag,t3[0]+48,0);
		col += t12x13_sym(col,pag,44,0);
		for(uint8_t i = 1 ; i < 4 ; i++)col += t12x13_sym(col,pag,t3[i]+48,0);
		col = t12x13_sym(col,pag,115,0);
	}
	else {
		col = Arsys_sym(col,pag,t3[0]+48,0);
		col = Arsys_sym(col,pag,44,0);
		for(uint8_t i = 1 ; i < 4 ; i++)col = Arsys_sym(col,pag,t3[i]+48,0);
		col = Arsys_sym(col,pag,115,0);
	}
}
void del_sec_ind1(uint8_t col , uint8_t pag , uint32_t d)
{
	uint16_t t3[4];
	t3[0] = d / 1000;
	t3[2] = d % 1000;
	t3[1] = t3[2] / 100 ;
	t3[3] = t3[2] % 100;
	t3[2] = t3[3] / 10;
	t3[3] = t3[3] % 10;
	col = Arsys_sym(col,pag,t3[0]+48,0);
	col = Arsys_sym(col,pag,44,0);
	for(uint8_t i = 1 ; i < 4 ; i++)col = Arsys_sym(col,pag,t3[i]+48,0);
	col = Arsys_sym(col,pag,115,0);
}

void clear_str(uint8_t col , uint8_t pag , uint8_t font , uint8_t count)
{
	switch (font){
	case 0: t12x13_clear(col , pag , count);
		break;
	case 1: t33x30_clear(col , pag , count);
		break;
	case 2: Arsys_clean_(col , pag , count);
		break;
	}
}
void quad_print(uint8_t col , uint8_t pag , uint8_t val)
{
  sh1106_gotoXY(col,pag);
  for( uint8_t i = 0 ; i < 7 ; i++)
    {
      if(val)font_buf[i] = 0x7f;
      else {
    	  if(!i || (i == 6))font_buf[i] = 0x7f;
    	  else font_buf[i] = 0x41;
      }
    }
  spi3_dma_init_transfer(7,(uint32_t*)font_buf);
}
void Arsys_ef(uint8_t col , uint8_t pag , uint8_t* adr ,uint8_t curs)
{
  uint8_t fl = 0;
  uint32_t sym;
  sym = adr[0];
  sym = (sym - 32)*6;
  for(uint8_t i = 0 ; i < 8 ; i++)
    {
      sh1106_gotoXY(col + i,pag);
      if(i > 1)
        {
          if((SystemFont5x7[sym + i - 2] & 0xc0) == 0)fl = 0;
          else fl = 1;
          switch (curs){
          case 0:
        	  sh1106_write_byte(1,(SystemFont5x7[sym + i - 2] << 2) | 1);
            break;
          case 1:
        	  sh1106_write_byte(1,(~(SystemFont5x7[sym + i - 2] << 2)) | 3);
            if(fl == 1)fl = 0;
            else fl = 1;
            break;
          case 2:
        	  sh1106_write_byte(1,1);
            fl = 0;
            break;
          }
        }
      if((i == 1)&&(curs != 1))sh1106_write_byte(1,1);
      else sh1106_write_byte(1,0xff);
      sh1106_gotoXY(col+i,pag+1);
      if(i != 0)
        {
          if(i == 1)
            {
              if(curs != 1)sh1106_write_byte(1,4);
              else sh1106_write_byte(1,7);
            }
          else {
              if(curs != 1)sh1106_write_byte(1,4 + fl);
              else sh1106_write_byte(1,(4 + fl) | 2);
          }
        }
      else sh1106_write_byte(1,7);
    }
  sym = adr[1];
  sym = (sym - 32)*6;
  for(uint8_t i = 0 ; i < 7 ; i++)
    {
      sh1106_gotoXY(col+i+8,pag);
      if(i < 6)
        {
          if((SystemFont5x7[sym + i] & 0xc0) == 0)fl = 0;
          else fl = 1;
          switch (curs){
          case 0:
        	  sh1106_write_byte(1,(SystemFont5x7[sym + i] << 2) | 1);
            break;
          case 1:
        	  sh1106_write_byte(1,(~(SystemFont5x7[sym + i] << 2)) | 3);
            if(fl == 1)fl = 0;
            else fl = 1;
            break;
          case 2:
        	  sh1106_write_byte(1,1);
            fl = 0;
            break;
          }
        }
      if(i == 6)sh1106_write_byte(1,0xff);
      sh1106_gotoXY(col+i+8,pag+1);
      if(i != 6)
        {
          if(curs != 1)sh1106_write_byte(1,4 + fl);
          else sh1106_write_byte(1,(4 + fl) | 2);
        }
      else sh1106_write_byte(1,7);
    }
}
void print_gat(uint8_t val)
{
	sh1106_gotoXY(2,2);
	for(uint8_t i = 0 ; i < 15 ; i++)
	{
		if(!val)font_buf[i] = gat_sym1[i * 2];
		else font_buf[i] = gat_sym2[i * 2];
	}
	spi3_dma_init_transfer(15,(uint32_t*)font_buf);
	sh1106_gotoXY(2,3);
	for(uint8_t i = 0 ; i < 15 ; i++)
	{
		if(!val)font_buf[i] = gat_sym1[i * 2 + 1];
		else font_buf[i] = gat_sym2[i * 2 + 1];
	}
	spi3_dma_init_transfer(15,(uint32_t*)font_buf);
}
void print_comp(uint8_t val)
{
	sh1106_gotoXY(20,2);
	for(uint8_t i = 0 ; i < 15 ; i++)
	{
		if(!val)font_buf[i] = com_sym1[i * 2];
		else font_buf[i] = com_sym2[i * 2];
	}
	spi3_dma_init_transfer(15,(uint32_t*)font_buf);
	sh1106_gotoXY(20,3);
	for(uint8_t i = 0 ; i < 15 ; i++)
	{
		if(!val)font_buf[i] = com_sym1[i * 2 + 1];
		else font_buf[i] = com_sym2[i * 2 + 1];
	}
	spi3_dma_init_transfer(15,(uint32_t*)font_buf);
}
void print_phas(uint8_t val)
{
	sh1106_gotoXY(38,2);
	for(uint8_t i = 0 ; i < 15 ; i++)
	{
		if(!val)font_buf[i] = phs_sym1[i * 2];
		else font_buf[i] = phs_sym2[i * 2];
	}
	spi3_dma_init_transfer(15,(uint32_t*)font_buf);
	sh1106_gotoXY(38,3);
	for(uint8_t i = 0 ; i < 15 ; i++)
	{
		if(!val)font_buf[i] = phs_sym1[i * 2 + 1];
		else font_buf[i] = phs_sym2[i * 2 + 1];
	}
	spi3_dma_init_transfer(15,(uint32_t*)font_buf);
}
void eff_ic_init(uint8_t adr)
{
	if(!adr)
	{
		print_gat(prog_data[ga_on]);
		print_comp(prog_data[compr_on]);
		print_phas(prog_data[phaz_on]);
		if(prog_data[flan_on])Arsys_ef(2,4,(uint8_t*)fl,1);//   2,20,38,56,74,92,110
		else Arsys_ef(2,4,(uint8_t*)fl,0);
		if(prog_data[preamp_on] || prog_data[od_on])Arsys_ef(20,4,(uint8_t*)pr,1);
		else Arsys_ef(20,4,(uint8_t*)pr,0);
		Arsys_ef(38,4,(uint8_t*)pa,prog_data[amp_on]);
		if(impulse_flag && prog_data[cab_on])Arsys_ef(56,4,(uint8_t*)ir,1);
		else Arsys_ef(56,4,(uint8_t*)ir,0);
		Arsys_ef(74,4,(uint8_t*)eq,prog_data[eq_on]);
		if(prog_data[lop_on] || prog_data[hip_on] || prog_data[pr_on])Arsys_ef(92,4,(uint8_t*)ft,1);
		else Arsys_ef(92,4,(uint8_t*)ft,0);
		if((prog_data[er_on] || (prog_data_t[FX] == 2)) && !prog_data[fx_type])Arsys_ef(110,4,(uint8_t*)dl,1);
		else {
			if((prog_data[er_on] || (prog_data_t[FX] == 2)) && prog_data[fx_type])Arsys_ef(110,4,(uint8_t*)rv,1);
			else Arsys_ef(110,4,(uint8_t*)ef,0);
		}
	}
	else {
		if(prog_data_t[ga_on + 30] || prog_data_t[Ng + 30])print_gat(1);
		else print_gat(0);
		if(prog_data_t[compr_on + 30] || prog_data_t[Compres + 30])print_comp(1);
		else print_comp(0);
		if(prog_data_t[phaz_on + 30] || prog_data_t[Phaz + 30])print_phas(1);
		else print_phas(0);
		if(prog_data_t[flan_on + 30] || prog_data_t[Flang + 30])Arsys_ef(2,4,(uint8_t*)fl,1);
		else Arsys_ef(2,4,(uint8_t*)fl,0);                //   2,20,38,56,74,92,110
		if(prog_data_t[preamp_on + 30] || (prog_data_t[Pr + 30] != 1 && prog_data_t[Pr + 30] != 2 && prog_data_t[Pr + 30] != 0))Arsys_ef(20,4,(uint8_t*)pr,1);
		else Arsys_ef(20,4,(uint8_t*)pr,0);
		if(prog_data_t[amp_on + 30] || prog_data_t[Amp + 30])Arsys_ef(38,4,(uint8_t*)pa,1);
		else Arsys_ef(38,4,(uint8_t*)pa,0);
		if(eq_num && (prog_data_t[cab_on + 30] || prog_data_t[Cab + 30] == 2))Arsys_ef(56,4,(uint8_t*)ir,1);
		else Arsys_ef(56,4,(uint8_t*)ir,0);
		Arsys_ef(74,4,(uint8_t*)eq,prog_data_t[eq_on + 30]);
		if(prog_data_t[lop_on + 30] || prog_data_t[hip_on + 30] || prog_data_t[pr_on + 30])Arsys_ef(92,4,(uint8_t*)ft,1);
		else Arsys_ef(92,4,(uint8_t*)ft,0);
		if((prog_data_t[er_on + 30] || (prog_data_t[FX + 30] == 2)) && !prog_data_t[fx_type + 30])Arsys_ef(110,4,(uint8_t*)dl,1);
		else {
			if((prog_data_t[er_on + 30] || (prog_data_t[FX + 30] == 2)) && prog_data_t[fx_type + 30])Arsys_ef(110,4,(uint8_t*)rv,1);
			else Arsys_ef(110,4,(uint8_t*)ef,0);
		}
	}
}
void eff_ic_id(uint8_t num)
{
	switch(num){
	case 0:print_gat(prog_data[ga_on]);break;
	case 1:print_comp(prog_data[compr_on]);break;
	case 2:print_phas(prog_data[phaz_on]);break;
	case 3:if(prog_data[flan_on])Arsys_ef(2,4,(uint8_t*)fl,1);else Arsys_ef(2,4,(uint8_t*)fl,0);break;
	case 4:if(prog_data[preamp_on] || prog_data[od_on])Arsys_ef(20,4,(uint8_t*)pr,1);else Arsys_ef(20,4,(uint8_t*)pr,0);break;
	case 5:Arsys_ef(38,4,(uint8_t*)pa,prog_data[amp_on]);break;
	case 6:if(impulse_flag && prog_data[cab_on] )Arsys_ef(56,4,(uint8_t*)ir,1);
	       else Arsys_ef(56,4,(uint8_t*)ir,0);
	       break;
	case 7:Arsys_ef(38,4,(uint8_t*)pa,prog_data[eq_on]);break;
	case 8:if(prog_data[lop_on] || prog_data[hip_on] || prog_data[pr_on])Arsys_ef(92,4,(uint8_t*)ft,1);
	       else Arsys_ef(92,4,(uint8_t*)ft,0);
	       break;
	case 9:if(prog_data[er_on])
		   {
				if(prog_data[fx_type])Arsys_ef(110,4,(uint8_t*)rv,1);
				else Arsys_ef(110,4,(uint8_t*)dl,1);
		   }
		   else {
				if(prog_data[fx_type])Arsys_ef(110,4,(uint8_t*)rv,0);
				else Arsys_ef(110,4,(uint8_t*)dl,0);
		   }
	       break;
	}
}
void tun_ini(void)
{
	sh1106_clear();
	scal_tun();
}
void tun_ind(void)
{
	strel_tun();
}
