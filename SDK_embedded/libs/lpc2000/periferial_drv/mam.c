#include "mam.h"
#include "lpc21xx.h"

void set_mam( unsigned char mam_mode, unsigned char mam_tim )
{
  // выключение MAM
  MAMCR = 0x00 ; 
  // установка тайминга МАМ
  MAMTIM = mam_tim ;
  // установка режима MAM
  MAMCR = mam_mode ; 
}

void get_mam( unsigned char* mam_mode, unsigned char* mam_tim ) 
{
  // чтение режима MAM
  *mam_mode = MAMCR  ;
  // чтение тайминга МАМ
  *mam_tim   = MAMTIM ;
}