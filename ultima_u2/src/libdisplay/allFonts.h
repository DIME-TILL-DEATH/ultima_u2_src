#include "appdefs.h"
#include "SystemFont5x7.h"
#include "par_bitmap.h"




//extern const uint8_t sys[];
//extern const uint8_t cc_of[];
//extern const uint8_t expr_type [][12];
//extern const uint8_t expr_menu [][10];
//extern const uint8_t expr_on_off [][5];
//extern const uint8_t foot_sw_type[][12];
//extern const uint8_t footsw_menu[][12];
//extern const uint8_t ext_switch  [][12];
//extern const uint8_t mode_list   [][12];
//extern const uint8_t int_sw_list [][12];
//extern const uint8_t contr_ext_l [][12];
//extern const uint8_t fsw_t[][12];
//extern const uint8_t spdif_type [][12];
//extern const uint8_t tempo_type [][10];
//extern const uint8_t time_type [][4];

//extern uint8_t vol_fl;
//extern uint8_t vol_vol;
//extern uint8_t inp_ind_fl;
//extern uint8_t out_ind_fl;
//extern uint8_t imya_temp;
//extern uint8_t prog_cur;

//extern uint8_t t_po;
//extern volatile uint8_t t_no;

extern uint8_t edit_fl;
extern uint8_t prog_cur;
extern uint8_t zero_buf[];
extern uint8_t font_buf[];
extern volatile uint8_t dma_complete_fl;

void vol_indic();
void menu_init(void);
void main_screen(uint8_t type);
void clear_str(uint8_t col , uint8_t pag , uint8_t font , uint8_t count);
void Arsys_ef(uint8_t col , uint8_t pag , uint8_t* adr ,uint8_t curs);
void disp_contr(uint8_t val);
void mode_ind(uint8_t val);
void tap_ind (uint8_t cur);
void sys_menu_init(void);
void del_sec_ind(uint8_t col , uint8_t pag , uint32_t d , uint8_t font);
void del_sec_ind1(uint8_t col , uint8_t pag , uint32_t d);
uint32_t t12x13_sym(uint8_t col , uint8_t pag , uint16_t sym , uint8_t curs);
void t12x13_line_name(uint32_t col , uint8_t pag , uint8_t* adr );
void t12x13_line(const uint8_t col , const  uint8_t pag , const  uint8_t* adr , const uint8_t curs);
void t12x13_clear(const uint8_t col , const uint8_t pag , const uint8_t size);
uint32_t t33x30_sym(uint8_t col , uint8_t pag , uint16_t sym);
void t33x30_clear(uint8_t col , uint8_t pag , uint8_t size);
void prog_ind(const uint32_t val,const uint8_t clean,const uint8_t type);
void sh1106_clear();
void strel_print(uint8_t col , uint8_t pag , uint8_t dir);
void icon_print(const uint8_t num ,const uint8_t strel);
void quad_print(uint8_t col , uint8_t pag , uint8_t val);
//void spi3_dma_init_transfer(uint8_t length , uint32_t* adr);
void eq_init(void);
uint8_t eq_ind(uint8_t col , uint8_t pag , uint32_t val , uint8_t cur );
void eff_ic_init(const uint8_t adr);
void eff_ic_id(uint8_t num);
void tun_ini(void);
void tun_ind(void);
