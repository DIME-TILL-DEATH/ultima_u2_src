#include "allFonts.h"
#include "display_task.h"
#include "SN1106.h"

display_task_t *display_task;

void display_task_t::code()
{
	sh1106_clear();
	t12x13_line(14, 0, (uint8_t*) "AMT PANGAEA", 0);
	t12x13_line(28, 3, (uint8_t*) "ULTIMA U2", 0);
	t12x13_line(20, 6, (uint8_t*) "UNIVERSAL", 0);
	delay(1500);
	sh1106_clear();

	char strBuf[16];
	memset(strBuf, 0, 16);
	memcpy(&strBuf[0], "Ver.", 4);
	memcpy(&strBuf[4], FIRMWARE_VER, 7);
	t12x13_line(21, 3, (uint8_t*) strBuf, 0);
	delay(500);

	while(1)
	{

		if(!message_buffer->receive_from_task(message, max_messagge_size, portMAX_DELAY))
			std::__throw_logic_error("display_task_t::code(): message received fail");

		while(!dma_complete_fl)
			;

		switch(*((request_t*) message))
		{
		case rqst_clear:
		{
			sh1106_clear();
			break;
		}
		case rqst_vol_ind:
		{
			vol_indic();
			break;
		}
		case rqst_sym_5x7:
		{
			const rqst_sym_5x7_t *obj = (rqst_sym_5x7_t*) message;
			Arsys_sym(obj->col, obj->pag, obj->sym, obj->curs);
			break;
		}
		case rqst_num_5x7:
		{
			const rqst_num_5x7_t *obj = (rqst_num_5x7_t*) message;
			Arsys_num(obj->col, obj->pag, obj->val, obj->curs);
			break;
		}
		case rqst_line_5x7:
		{
			const rqst_line_5x7_t *obj = (rqst_line_5x7_t*) message;
			Arsys_line(obj->col, obj->pag, obj->str, obj->curs);
			break;
		}
		case rqst_line_5x7_clean:
		{
			const rqst_line_5x7_clean_t *obj = (rqst_line_5x7_clean_t*) message;
			Arsys_clean(obj->col, obj->pag, obj->str);
			break;
		}
		case rqst_line_12x13:
		{
			const rqst_line_12x13_t *obj = (rqst_line_12x13_t*) message;
			t12x13_line(obj->col, obj->pag, obj->str, obj->curs);
			break;
		}
		case rqst_line_12x13_clean:
		{
			const rqst_line_12x13_clean_t *obj = (rqst_line_12x13_clean_t*) message;
			t12x13_clear(obj->col, obj->pag, obj->size);
			break;
		}
		case rqst_par_indic:
		{
			const rqst_par_indic_t *obj = (rqst_par_indic_t*) message;
			par_ind(obj->col, obj->pag, obj->val);
			break;
		}
		case rqst_pan_indic:
		{
			const rqst_pan_indic_t *obj = (rqst_pan_indic_t*) message;
			par_ind_pan(obj->col, obj->pag, obj->val);
			break;
		}
		case rqst_mix_indic:
		{
			const rqst_mix_indic_t *obj = (rqst_mix_indic_t*) message;
			par_ind_mix(obj->col, obj->pag, obj->val, obj->type);
			break;
		}
		case rqst_ic_print:
		{
			const rqst_ic_print_t *obj = (rqst_ic_print_t*) message;
			icon_print(obj->num, obj->strel);
			break;
		}
		case rqst_prog_indic:
		{
			const rqst_prog_indic_t *obj = (rqst_prog_indic_t*) message;
			prog_ind(obj->val, obj->clean, obj->type);
			break;
		}
		case rqst_del_time:
		{
			const rqst_del_time_t *obj = (rqst_del_time_t*) message;
			del_sec_ind(obj->col, obj->pag, obj->d, obj->font);
			break;
		}
		case rqst_quad_print:
		{
			const rqst_quad_print_t *obj = (rqst_quad_print_t*) message;
			quad_print(obj->col, obj->pag, obj->val);
			break;
		}
		case rqst_strel_print:
		{
			const rqst_strel_print_t *obj = (rqst_strel_print_t*) message;
			strel_print(obj->col, obj->pag, obj->dir);
			break;
		}
		case rqst_eq_init:
		{
			eq_init();
			break;
		}
		case rqst_eq_ind:
		{
			const rqst_eq_ind_t *obj = (rqst_eq_ind_t*) message;
			eq_ind(obj->col, obj->pag, obj->val, obj->curs);
			break;
		}
		case rqst_icon_eff:
		{
			const rqst_icon_eff_t *obj = (rqst_icon_eff_t*) message;
			eff_ic_init(obj->adr);
			break;
		}
		case rqst_icon_eff_id:
		{
			const rqst_icon_eff_id_t *obj = (rqst_icon_eff_id_t*) message;
			eff_ic_id(obj->num);
			break;
		}
		case rqst_TunIni:
		{
			tun_ini();
			break;
		}
		case rqst_Tun:
		{
			tun_ind();
			break;
		}
		default:
		{
			std::__throw_logic_error("display_task_t::code(): invalid message received");
		}
		}
	}
}

void display_task_t::clear()
{
	rqst_clear_t rqst_clear;
	request<rqst_clear_t>(rqst_clear);
}
void display_task_t::VolInd()
{
	rqst_vol_ind_t rqst_vol_ind;
	request<rqst_vol_ind_t>(rqst_vol_ind);
}
void display_task_t::EqInit()
{
	rqst_eq_init_t rqst_eq_init;
	request<rqst_eq_init_t>(rqst_eq_init);
}
void display_task_t::TunInit()
{
	rqst_TunIni_t rqst_TunIni;
	request<rqst_TunIni_t>(rqst_TunIni);
}
void display_task_t::TunInd()
{
	rqst_Tun_t rqst_Tun;
	request<rqst_Tun_t>(rqst_Tun);
}
void display_task_t::sym_5x7(const uint8_t col, const uint8_t pag, const uint16_t sym, const uint8_t curs)
{
	rqst_sym_5x7_t rqst_sym_5x7;
	rqst_sym_5x7.col = col;
	rqst_sym_5x7.pag = pag;
	rqst_sym_5x7.sym = sym;
	rqst_sym_5x7.curs = curs;
	request<rqst_sym_5x7_t>(rqst_sym_5x7);
}
void display_task_t::num_5x7(const uint8_t col, const uint8_t pag, const uint16_t val, const uint8_t curs)
{
	rqst_num_5x7_t rqst_num_5x7;
	rqst_num_5x7.col = col;
	rqst_num_5x7.pag = pag;
	rqst_num_5x7.val = val;
	rqst_num_5x7.curs = curs;
	request<rqst_num_5x7_t>(rqst_num_5x7);
}
void display_task_t::line_5x7(const uint8_t col, const uint8_t pag, const char *str, const uint8_t curs)
{
	rqst_line_5x7_t rqst_line_5x7;
	rqst_line_5x7.col = col;
	rqst_line_5x7.pag = pag;
	strlcpy((char*) rqst_line_5x7.str, str, max_string_length);
	rqst_line_5x7.curs = curs;
	request<rqst_line_5x7_t>(rqst_line_5x7);
}
void display_task_t::line_5x7_clean(const uint8_t col, const uint8_t pag, const char *str)
{
	rqst_line_5x7_clean_t rqst_line_5x7_clean;
	rqst_line_5x7_clean.col = col;
	rqst_line_5x7_clean.pag = pag;
	strlcpy((char*) rqst_line_5x7_clean.str, str, max_string_length);
	request<rqst_line_5x7_clean_t>(rqst_line_5x7_clean);
}
void display_task_t::line_12x13(const uint8_t col, const uint8_t pag, const char *str, const uint8_t curs)
{
	rqst_line_12x13_t rqst_line_12x13;
	rqst_line_12x13.col = col;
	rqst_line_12x13.pag = pag;
	strlcpy((char*) rqst_line_12x13.str, str, max_string_length);
	rqst_line_12x13.curs = curs;
	request<rqst_line_12x13_t>(rqst_line_12x13);
}
void display_task_t::line_12x13_clean(const uint8_t col, const uint8_t pag, const uint8_t size)
{
	rqst_line_12x13_clean_t rqst_line_12x13_clean;
	rqst_line_12x13_clean.col = col;
	rqst_line_12x13_clean.pag = pag;
	rqst_line_12x13_clean.size = size;
	request<rqst_line_12x13_clean_t>(rqst_line_12x13_clean);
}
void display_task_t::par_indic(const uint8_t col, const uint8_t pag, const uint8_t val)
{
	rqst_par_indic_t rqst_par_indic;
	rqst_par_indic.col = col;
	rqst_par_indic.pag = pag;
	rqst_par_indic.val = val;
	request<rqst_par_indic_t>(rqst_par_indic);
}
void display_task_t::pan_indic(const uint8_t col, const uint8_t pag, const uint8_t val)
{
	rqst_pan_indic_t rqst_pan_indic;
	rqst_pan_indic.col = col;
	rqst_pan_indic.pag = pag;
	rqst_pan_indic.val = val;
	request<rqst_pan_indic_t>(rqst_pan_indic);
}
void display_task_t::mix_indic(const uint8_t col, const uint8_t pag, const uint8_t val, const uint8_t type)
{
	rqst_mix_indic_t rqst_mix_indic;
	rqst_mix_indic.col = col;
	rqst_mix_indic.pag = pag;
	rqst_mix_indic.val = val;
	rqst_mix_indic.type = type;
	request<rqst_mix_indic_t>(rqst_mix_indic);
}
void display_task_t::ic_print(const uint8_t num, const uint8_t strel)
{
	rqst_ic_print_t rqst_ic_print;
	rqst_ic_print.num = num;
	rqst_ic_print.strel = strel;
	request<rqst_ic_print_t>(rqst_ic_print);
}
void display_task_t::prog_indic(const uint32_t val, const uint8_t clean, const uint8_t type)
{
	rqst_prog_indic_t rqst_prog_indic;
	rqst_prog_indic.val = val;
	rqst_prog_indic.clean = clean;
	rqst_prog_indic.type = type;
	request<rqst_prog_indic_t>(rqst_prog_indic);
}
void display_task_t::del_time_ind(const uint8_t col, const uint8_t pag, const uint32_t d, const uint8_t font)
{
	rqst_del_time_t rqst_del_time;
	rqst_del_time.col = col;
	rqst_del_time.pag = pag;
	rqst_del_time.d = d;
	rqst_del_time.font = font;
	request<rqst_del_time_t>(rqst_del_time);
}
void display_task_t::QuadPrint(const uint8_t col, const uint8_t pag, const uint8_t val)
{
	rqst_quad_print_t rqst_quad_print;
	rqst_quad_print.col = col;
	rqst_quad_print.pag = pag;
	rqst_quad_print.val = val;
	request<rqst_quad_print_t>(rqst_quad_print);
}
void display_task_t::Strel_print(const uint8_t col, const uint8_t pag, const uint8_t dir)
{
	rqst_strel_print_t rqst_strel_print;
	rqst_strel_print.col = col;
	rqst_strel_print.pag = pag;
	rqst_strel_print.dir = dir;
	request<rqst_strel_print_t>(rqst_strel_print);
}
void display_task_t::EqInd(const uint8_t col, const uint8_t pag, const uint8_t val, const uint8_t curs)
{
	rqst_eq_ind_t rqst_eq_ind;
	rqst_eq_ind.col = col;
	rqst_eq_ind.pag = pag;
	rqst_eq_ind.val = val;
	rqst_eq_ind.curs = curs;
	request<rqst_eq_ind_t>(rqst_eq_ind);
}
void display_task_t::icon_eff(const uint8_t adr)
{
	rqst_icon_eff_t rqst_icon_eff;
	rqst_icon_eff.adr = adr;
	request<rqst_icon_eff_t>(rqst_icon_eff);
}
void display_task_t::icon_eff_num(const uint8_t num)
{
	rqst_icon_eff_id_t rqst_icon_eff_id;
	rqst_icon_eff_id.num = num;
	request<rqst_icon_eff_id_t>(rqst_icon_eff_id);
}
