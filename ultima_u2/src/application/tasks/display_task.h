#ifndef __DISPLAY_TASK_H__
#define __DISPLAY_TASK_H__

#include "appdefs.h"

class display_task_t: public task_t
{
public:

	inline display_task_t(const char *name, const int stack_size, const int priority) :
			task_t(name, stack_size, priority, false)

	{
		message_buffer = new message_buffer_t(messagge_buffer_size);
		if(!((bool) message_buffer & message_buffer->is_created()))
			std::__throw_memmgr_error("display_task_t::display_task_t(...): message_buffer allocation fail");

		message = new char[max_messagge_size];
	}

	void clear();
	void sym_5x7(const uint8_t col, const uint8_t pag, const uint16_t sym, const uint8_t curs);
	void num_5x7(const uint8_t col, const uint8_t pag, const uint16_t val, const uint8_t curs);
	void line_5x7(const uint8_t col, const uint8_t pag, const char *str, const uint8_t curs);
	void line_5x7_clean(const uint8_t col, const uint8_t pag, const char *str);
	void line_12x13(const uint8_t col, const uint8_t pag, const char *str, const uint8_t curs);
	void line_12x13_clean(const uint8_t col, const uint8_t pag, const uint8_t size);
	void par_indic(const uint8_t col, const uint8_t pag, const uint8_t val);
	void pan_indic(const uint8_t col, const uint8_t pag, const uint8_t val);
	void mix_indic(const uint8_t col, const uint8_t pag, const uint8_t val, const uint8_t type);
	void ic_print(const uint8_t num, const uint8_t strel);
	void prog_indic(const uint32_t val, const uint8_t clean, const uint8_t type);
	void del_time_ind(const uint8_t col, const uint8_t pag, const uint32_t d, const uint8_t font);
	void VolInd();
	void QuadPrint(const uint8_t col, const uint8_t pag, const uint8_t val);
	void Strel_print(const uint8_t col, const uint8_t pag, const uint8_t dir);
	void EqInit();
	void EqInd(const uint8_t col, const uint8_t pag, const uint8_t val, const uint8_t curs);
	void icon_eff(const uint8_t adr);
	void icon_eff_num(const uint8_t num);
	void TunInit(void);
	void TunInd(void);

protected:

	template<typename T>
	inline size_t request(T &message)
	{
		return message_buffer->send((void*) &message, sizeof(T), 0);
	}

	//template< typename T >
	// void request(T& message) { message_buffer->send_from_task( (void*)&message, sizeof(T), 0); }

private:
	void code();
	message_buffer_t *message_buffer;
	char *message;

	constexpr static size_t max_string_length = 64;
	enum request_t
	{
		rqst_clear,
		rqst_sym_5x7,
		rqst_num_5x7,
		rqst_line_5x7,
		rqst_line_5x7_clean,
		rqst_line_12x13,
		rqst_line_12x13_clean,
		rqst_par_indic,
		rqst_pan_indic,
		rqst_mix_indic,
		rqst_ic_print,
		rqst_prog_indic,
		rqst_del_time,
		rqst_vol_ind,
		rqst_quad_print,
		rqst_strel_print,
		rqst_eq_init,
		rqst_eq_ind,
		rqst_icon_eff,
		rqst_icon_eff_id,
		rqst_TunIni,
		rqst_Tun,
	};

	struct rqst_clear_t
	{
		const request_t request = rqst_clear;
	};
	struct rqst_vol_ind_t
	{
		const request_t request = rqst_vol_ind;
	};
	struct rqst_eq_init_t
	{
		const request_t request = rqst_eq_init;
	};
	struct rqst_TunIni_t
	{
		const request_t request = rqst_TunIni;
	};
	struct rqst_Tun_t
	{
		const request_t request = rqst_Tun;
	};
	struct rqst_icon_eff_t
	{
		const request_t request = rqst_icon_eff;
		uint8_t adr;
	};
	struct rqst_icon_eff_id_t
	{
		const request_t request = rqst_icon_eff_id;
		uint8_t num;
	};
	struct rqst_sym_5x7_t
	{
		const request_t request = rqst_sym_5x7;
		uint8_t col;
		uint8_t pag;
		uint8_t sym;
		uint8_t curs;
	};
	struct rqst_num_5x7_t
	{
		const request_t request = rqst_num_5x7;
		uint8_t col;
		uint8_t pag;
		uint8_t val;
		uint8_t curs;
	};
	struct rqst_line_5x7_t
	{
		const request_t request = rqst_line_5x7;
		uint8_t col;
		uint8_t pag;
		uint8_t str[max_string_length];
		uint8_t curs;
	};
	struct rqst_line_5x7_clean_t
	{
		const request_t request = rqst_line_5x7_clean;
		uint8_t col;
		uint8_t pag;
		uint8_t str[max_string_length];
	};
	struct rqst_line_12x13_t
	{
		const request_t request = rqst_line_12x13;
		uint8_t col;
		uint8_t pag;
		uint8_t str[max_string_length];
		uint8_t curs;
	};
	struct rqst_line_12x13_clean_t
	{
		const request_t request = rqst_line_12x13_clean;
		uint8_t col;
		uint8_t pag;
		uint8_t size;
	};
	struct rqst_par_indic_t
	{
		const request_t request = rqst_par_indic;
		uint8_t col;
		uint8_t pag;
		uint8_t val;
	};
	struct rqst_pan_indic_t
	{
		const request_t request = rqst_pan_indic;
		uint8_t col;
		uint8_t pag;
		uint8_t val;
	};
	struct rqst_mix_indic_t
	{
		const request_t request = rqst_mix_indic;
		uint8_t col;
		uint8_t pag;
		uint8_t val;
		uint8_t type;
	};
	struct rqst_ic_print_t
	{
		const request_t request = rqst_ic_print;
		uint8_t num;
		uint8_t strel;
	};
	struct rqst_prog_indic_t
	{
		const request_t request = rqst_prog_indic;
		uint32_t val;
		uint8_t clean;
		uint8_t type;
	};
	struct rqst_del_time_t
	{
		const request_t request = rqst_del_time;
		uint8_t col;
		uint8_t pag;
		uint32_t d;
		uint8_t font;
	};
	struct rqst_quad_print_t
	{
		const request_t request = rqst_quad_print;
		uint8_t col;
		uint8_t pag;
		uint8_t val;
	};
	struct rqst_strel_print_t
	{
		const request_t request = rqst_strel_print;
		uint8_t col;
		uint8_t pag;
		uint8_t dir;
	};
	struct rqst_eq_ind_t
	{
		const request_t request = rqst_eq_ind;
		uint8_t col;
		uint8_t pag;
		uint8_t val;
		uint8_t curs;
	};

	union rqst_t
	{
		rqst_clear_t rqst_clear;
		rqst_vol_ind_t rqst_vol_ind;
		rqst_eq_init_t rqst_eq_init;
		rqst_sym_5x7_t rqst_sym_5x7;
		rqst_num_5x7_t rqst_num_5x7;
		rqst_line_5x7_t rqst_line_5x7;
		rqst_line_5x7_clean_t rqst_line_5x7_clean;
		rqst_line_12x13_t rqst_line_12x13;
		rqst_line_12x13_clean_t rqst_line_12x13_clean;
		rqst_par_indic_t rqst_par_indic;
		rqst_pan_indic_t rqst_pan_indic;
		rqst_mix_indic_t rqst_mix_indic;
		rqst_ic_print_t rqst_ic_print;
		rqst_prog_indic_t rqst_prog_indic;
		rqst_del_time_t rqst_del_time;
		rqst_quad_print_t rqst_quad_print;
		rqst_strel_print_t rqst_strel_print;
		rqst_eq_ind_t rqst_eq_ind;
		rqst_icon_eff_t rqst_icon_eff;
		rqst_icon_eff_id_t rqst_icon_eff_id;
	};

	constexpr static size_t max_messagge_size = sizeof(rqst_t);
	constexpr static size_t max_messagge_buffer_depth = 64;
	constexpr static size_t messagge_buffer_size = max_messagge_buffer_depth * max_messagge_size;

};

extern display_task_t *display_task;
extern volatile uint8_t dma_complete_fl;

#endif /* __DISPLAY_TASK_H__ */
