#include "appdefs.h"
#include "eq_bitmap.h"
#include "SN1106.h"
#include "12x13.h"
#include "SystemFont5x7.h"
#include "gui.h"
#include "allFonts.h"
//#include "filt.h"

const uint8_t eq_bit[] = {0x00,0x80,0xff,0x7f,
                          0x00,0x80,0xff,0x3f,
                          0x00,0x80,0xff,0x1f,
                          0x00,0x80,0xff,0x0f,
                          0x00,0x80,0xff,0x07,
                          0x00,0x80,0xff,0x03,
                          0x00,0x80,0xff,0x01,
                          0x00,0x80,0xff,0x00,
                          0x00,0x80,0x7f,0x00,
                          0x00,0x80,0x3f,0x00,
                          0x00,0x80,0x1f,0x00,
                          0x00,0x80,0x0f,0x00,
                          0x00,0x80,0x07,0x00,
                          0x00,0x80,0x03,0x00,
                          0x00,0x80,0x01,0x00,

                          0x00,0x80,0x00,0x00,

                          0x00,0xc0,0x00,0x00,
                          0x00,0xe0,0x00,0x00,
                          0x00,0xf0,0x00,0x00,
                          0x00,0xf8,0x00,0x00,
                          0x00,0xfc,0x00,0x00,
                          0x00,0xfe,0x00,0x00,
                          0x00,0xff,0x00,0x00,
                          0x80,0xff,0x00,0x00,
                          0xc0,0xff,0x00,0x00,
                          0xe0,0xff,0x00,0x00,
                          0xf0,0xff,0x00,0x00,
                          0xf8,0xff,0x00,0x00,
                          0xfc,0xff,0x00,0x00,
                          0xfe,0xff,0x00,0x00,
                          0xff,0xff,0x00,0x00,
                          0,0,0,0
};
const uint8_t _15[]="15";
const uint8_t __15[]="-15";
const uint8_t db[]="db";

uint8_t eq_ind(uint8_t col , uint8_t pag , uint32_t val , uint8_t cur )
{
  uint32_t data;
  for(uint8_t i = 0 ; i < 11 ; i++)
    {
      for(uint8_t j = 0 ; j < 4 ; j++)
        {
          data = eq_bit[val * 4 + j];
          sh1106_gotoXY(col + i,pag + j);
          if(cur == 1){
          if((i != 2) && (i != 5) && (i != 8) && (i != 11))
            {
              if(j < 2)
              {
                  if((j & 1) == 0)data |= 0x21;
                  else data |= 0x4;
              }
              else {
                  if((j & 1) == 0)data |= 0x10;
                  else data |= 0x42;
                }
           }
          }
          sh1106_write_byte(1,data);
        }
    }
  return col + 14;
}
void eq_init(void)
{
    sh1106_clear();
    Arsys_line(6,4,(uint8_t*)_15,0);
    Arsys_line(0,7,(uint8_t*)__15,0);
    Arsys_sym_up(9,5,48,0);
    Arsys_sym_down(9,6,48,0);
    sh1106_gotoXY(20,5);
    for(uint8_t i = 0 ; i < 63 ; i++)font_buf[i] = 0x80;
    spi3_dma_init_transfer(63,(uint32_t*)font_buf);
    for(uint8_t i = 0 ; i < 4 ; i++)
      {
    	sh1106_gotoXY(20,i+4);
        for(uint8_t j = 0 ; j < 4 ; j++)
          {
            sh1106_gotoXY(20 + j,i+4);
            if(i < 2)
              {
                if(j > 1)
                  {
                    if((i & 1) == 0)sh1106_write_byte(1,0x21);
                    else sh1106_write_byte(1,0x84);
                  }
                else {
                    if((i & 1) == 0)sh1106_write_byte(1,0x1);
                    else sh1106_write_byte(1,0x80);
                }
              }
            else {
                if(j > 1)
                  {
                    if((i & 1) == 0)sh1106_write_byte(1,0x10);
                    else sh1106_write_byte(1,0x42);
                  }
                else {
                    if((i & 1) == 0)sh1106_write_byte(1,0x0);
                    else sh1106_write_byte(1,0x40);
                }
            }
            if(j == 3)
              {
                if(i < 3)sh1106_write_byte(1,0xff);
                else sh1106_write_byte(1,0x7f);
              }
          }
      }
   uint8_t curs = 27;
   for(uint8_t i = 0 ; i < 5 ; i++)curs = eq_ind(curs , 4 , prog_data[eq1 + i],0);
   Arsys_sym_up(96,5,100,0);
   Arsys_sym_down(96,6,100,0);
   Arsys_sym_up(102,5,66,0);
   Arsys_sym_down(102,6,66,0);
   Arsys_line(0,0,(uint8_t*)eq_list,0);
   Arsys_line(0,1,(uint8_t*)eq_list + 10,0);
   if(prog_data[eq_on])Arsys_line(72,0,(uint8_t*)"On ",0);
   else Arsys_line(72,0,(uint8_t*)"Off",0);
   if(!prog_data[eq_po])Arsys_line(72,1,(uint8_t*)"Pre ",0);
   else Arsys_line(72,1,(uint8_t*)"Post",0);
}
