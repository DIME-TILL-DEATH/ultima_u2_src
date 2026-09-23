#ifndef __SDK_H__
#define __SDK_H__

#include "supc++.h"
#include "supstl.h"
#include "emb_string.h" //support printf-style template for emb_string/ebd_printf"

#include "arch.h"

#if defined __USE_FREERTOS__
  #ifdef __cplusplus
    #include "FreeRTOS++.h"
  #else
    #include "FreeRTOS_headers.h"
  #endif
#endif

#include "gnu_linker.h"
#include "platform_config.h"
#include "__aeabi_impl.h"
#include "__cxa_impl.h"

#endif /*__SDK_H__*/
