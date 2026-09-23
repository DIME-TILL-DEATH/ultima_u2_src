#include "pll.h"
#include "lpc21xx.h"

void get_pll( unsigned int* M,
              unsigned int* P,
              unsigned int* Enable,
              unsigned int* Connect,
              unsigned int* Lock)
{
   *M       = PLLSTAT & PLLSTAT_MSEL_MASK ;                           
   *P       = ((PLLSTAT & PLLSTAT_PSEL_MASK)>>PLLSTAT_PSEL_BIT) ;  
   *Enable  = ((PLLSTAT & PLLSTAT_PLLE_MASK)>>PLLSTAT_PLLE_BIT) ;        
   *Connect = ((PLLSTAT & PLLSTAT_PLLC_MASK)>>PLLSTAT_PLLC_BIT) ;        
   *Lock    = ((PLLSTAT & PLLSTAT_PLOCK_MASK)>>PLLSTAT_PLOCK_BIT);
} 

//-----------------------------------------
void disconnect_pll()
{
  PLLCON  = 0x00 ;
  PLLFEED = 0xAA ;
  PLLFEED = 0x55 ;
}
void connect_pll()
{
  PLLCON  = 0x03 ;
  PLLFEED = 0xAA ;
  PLLFEED = 0x55 ;
}


void set_pll (unsigned int MSel , enum TPSELVals PSel , enum TConnectNeeded connect_needed)
{
  // M = 1....32  P = 1 , 2 , 4 , 8
  unsigned char MSEL = MSel - 1 ;   
  // ���������� � ������� ����
  disconnect_pll()  ;              

  // ������ ������
  PLLCFG  = (MSEL-1) + (PSel<<5) ;         
  // ������ ����
  PLLCON  = 0x1  ;                
  PLLFEED = 0xAA ;
  PLLFEED = 0x55 ;           
  // �������� ������� ����� ����
  while ( !((PLLSTAT) & 0x400) ) ;
  // ����������� ��������� ������� ���� � ����� ������������� 
  if ( connect_needed )
     connect_pll()  ;                 
}
//-----------------------------------------
void set_vpb_div ( enum TVPBDivs vpbDiv)
{
  // ��������� ������� PCLK ������������ ���� VPB
  VPBDIV &= ~0x3  ;  // ����� ������ ���� ����� 
  VPBDIV = vpbDiv ;  // ���������
}
//-----------------------------------------
unsigned int get_cclk()
{
  return F_OCS * ( (PLLSTAT & 0x1f)+1 ) ;
}
//-----------------------------------------
unsigned int get_pcclk()
{
  unsigned char VPB_Div[3] = {2,0,1}; 
  return get_cclk() >> VPB_Div[ VPBDIV & 0x3 ] ;
} 
//----------------------------------------
unsigned int get_fcco()
{
  unsigned long PSels[] = { 1 , 2 , 4 , 8 } ;
  return PSels[  (PLLCFG>>5) & 0x3  ] * get_cclk() ;
}
