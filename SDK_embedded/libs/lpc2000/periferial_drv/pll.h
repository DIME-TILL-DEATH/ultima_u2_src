#ifndef __PLL_H__
#define __PLL_H__

void disconnect_pll();
void connect_pll();
void get_pll( unsigned int* M,
              unsigned int* P,
              unsigned int* Enable,
              unsigned int* Connect,
              unsigned int* Lock) ;

enum TConnectNeeded {cnNoConnect=0 , cnConnectImmediately }  ;
enum TPSELVals { psel_1=0 , psel_2=1, psel_4=2, psel_8=3  }  ;
void set_pll (unsigned int MSel , enum TPSELVals PSel , enum TConnectNeeded connect_needed );

// установка делителя переферийной шины
enum TVPBDivs { vpdbiv_4 , vpbdiv_1, vpdiv_2, vpbdivReserve } ;
void set_vpb_div ( enum TVPBDivs vpbdiv);
// чтение частоты локальной шины(процессора)
unsigned int get_cclk();
// чтение частоты переферийной шины
unsigned int get_pcclk();
// чтение частоты ГУТ(CCO)
unsigned int get_fcco();

#endif /*__PLL_H__*/