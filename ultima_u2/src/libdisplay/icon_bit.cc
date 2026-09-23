#include "appdefs.h"
#include "allFonts.h"

#include "SN1106.h"


const uint8_t strelk[]={
	0x60, 0x50, 0x48, 0x44, 0x42,0x41,//UP
	0x42, 0x44, 0x48, 0x50, 0x60,0x00,
	0x06, 0x0a, 0x12, 0x22, 0x42,0x82,//DOWN
	0x42, 0x22, 0x12, 0x0a, 0x06,0x00
};
void icon_print(const uint8_t num ,const uint8_t strel)
{
  uint8_t col1 = 114;
  switch (strel){
    case 0:break;
    case 1:{
      sh1106_gotoXY(col1,0);
      for(uint32_t i = 0 ; i < 12 ; i++)font_buf[i] = strelk[i];
      spi3_dma_init_transfer(12,(uint32_t*)font_buf);
      sh1106_gotoXY(col1,7);
      for(uint32_t i = 12 ; i < 24 ; i++)font_buf[i - 12] = 0;
      spi3_dma_init_transfer(12,(uint32_t*)font_buf);
      break;
	}
    case 2:{
      sh1106_gotoXY(col1,0);
      for(uint32_t i = 0 ; i < 12 ; i++)font_buf[i] = 0;
      spi3_dma_init_transfer(12,(uint32_t*)font_buf);
      sh1106_gotoXY(col1,7);
      for(uint32_t i = 12 ; i < 24 ; i++)font_buf[i - 12] = strelk[i];
      spi3_dma_init_transfer(12,(uint32_t*)font_buf);
      break;
    }
    case 3:{
      sh1106_gotoXY(col1,0);
      for(uint32_t i = 0 ; i < 12 ; i++)font_buf[i] = strelk[i];
      spi3_dma_init_transfer(12,(uint32_t*)font_buf);
      sh1106_gotoXY(col1,7);
      for(uint32_t i = 12 ; i < 24 ; i++)font_buf[i - 12] = strelk[i];
      spi3_dma_init_transfer(12,(uint32_t*)font_buf);
      break;
    }
  }
}
void strel_print(uint8_t col , uint8_t pag , uint8_t dir)
{
   sh1106_gotoXY(col,pag);
   switch(dir){
   case 0:for(uint32_t i = 12 ; i < 24 ; i++)font_buf[i - 12] = strelk[i];break;
   case 1:for(uint32_t i = 0 ; i < 12 ; i++)font_buf[i] = strelk[i];break;
   case 2:for(uint32_t i = 0 ; i < 12 ; i++)font_buf[i] = 0;break;
   }
   spi3_dma_init_transfer(12,(uint32_t*)font_buf);
}

