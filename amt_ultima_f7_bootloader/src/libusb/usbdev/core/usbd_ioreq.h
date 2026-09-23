#ifndef __USBD_IOREQ_H
#define __USBD_IOREQ_H

#ifdef __cplusplus
 extern "C" {
#endif

#include  "usbd_def.h"
#include  "usbd_core.h"

usbd_status_t  usbd_ctl_send_data (usbd_t  *pdev, uint8_t *buf, uint16_t len);
usbd_status_t  usbd_ctl_continue_send_data (usbd_t  *pdev, uint8_t *pbuf, uint16_t len);
usbd_status_t  usbd_ctl_prepare_rx (usbd_t  *pdev, uint8_t *pbuf,uint16_t len);
usbd_status_t  usbd_ctl_continue_rx (usbd_t  *pdev, uint8_t *pbuf, uint16_t len);
usbd_status_t  usbd_ctl_send_status (usbd_t  *pdev);
usbd_status_t  usbd_ctl_receive_status (usbd_t  *pdev);
uint16_t       usbd_get_rx_count (usbd_t  *pdev, uint8_t epnum);


#ifdef __cplusplus
}
#endif

#endif /* __USBD_IOREQ_H */
