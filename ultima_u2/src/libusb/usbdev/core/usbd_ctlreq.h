#ifndef __USB_REQUEST_H
#define __USB_REQUEST_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include  "usbd_def.h"



usbd_status_t  usbd_std_dev_req (usbd_t  *pdev, USBD_SetupReqTypedef  *req);
usbd_status_t  usbd_std_itf_req (usbd_t  *pdev, USBD_SetupReqTypedef  *req);
usbd_status_t  usbd_std_ep_req  (usbd_t  *pdev, USBD_SetupReqTypedef  *req);


void usbd_ctl_error  (usbd_t  *pdev, USBD_SetupReqTypedef *req);
void usbd_parse_setup_request (USBD_SetupReqTypedef *req, uint8_t *pdata);
void usbd_get_string         (uint8_t *desc, uint8_t *unicode, uint16_t *len);


#ifdef __cplusplus
}
#endif

#endif /* __USB_REQUEST_H */

