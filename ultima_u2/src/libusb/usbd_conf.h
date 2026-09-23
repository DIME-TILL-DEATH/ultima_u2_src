#ifndef __USBD_CONF__H__
#define __USBD_CONF__H__

#ifdef __cplusplus
 extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stm32f7xx.h"

#include "stm32f7xx_hal_pcd.h"



/*---------- -----------*/
#define USBD_MAX_NUM_INTERFACES     1
/*---------- -----------*/
#define USBD_MAX_NUM_CONFIGURATION  1
/*---------- -----------*/
#define USBD_MAX_STR_DESC_SIZ     512
/*---------- -----------*/
#define USBD_SUPPORT_USER_STRING    1
/*---------- -----------*/
#define USBD_DEBUG_LEVEL     0
/*---------- -----------*/
#define USBD_LPM_ENABLED     1
/*---------- -----------*/
#define USBD_SELF_POWERED    1
/*---------- -----------*/
#define MSC_MEDIA_PACKET     4096


enum { full_speed=0, high_speed } ;


#define USBD_malloc               malloc
#define USBD_free                 free
#define USBD_memset               memset
#define USBD_memcpy               memcpy



#ifdef __cplusplus
}
#endif

#endif /*__USBD_CONF__H__*/


