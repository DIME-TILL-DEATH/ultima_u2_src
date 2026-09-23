
#ifndef __ITM_TRACE_H__
#define __ITM_TRACE_H__

#include <stdint.h>

#ifdef __cplusplus
	extern "C" {
#endif

	  void itm_trace_init(uint32_t boud);
	  void itm_trace_putc(int c);

#ifdef __cplusplus
	}
#endif

#endif /*__ITM_TRACE_H__*/
