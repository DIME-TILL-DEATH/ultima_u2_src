
#ifndef __USBD_CORE_H
#define __USBD_CORE_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "usbd_conf.h"
#include "usbd_def.h"
#include "usbd_ioreq.h"
#include "usbd_ctlreq.h"

#define USBD_SOF          usbd_ll_sof

usbd_status_t usbd_init(pcd_t* pcd, usbd_t *pdev, usbd_descriptors_t *pdesc, uint8_t id);
usbd_status_t usbd_deinit(usbd_t *pdev);
usbd_status_t usbd_start  (usbd_t *pdev);
usbd_status_t usbd_stop   (usbd_t *pdev);
usbd_status_t usbd_register_class(usbd_t *pdev, usbd_class_t *pclass);

usbd_status_t usbd_run_test_mode (usbd_t  *pdev);
usbd_status_t usbd_set_class_config(usbd_t  *pdev, uint8_t cfgidx);
usbd_status_t usbd_clear_class_config(usbd_t  *pdev, uint8_t cfgidx);

usbd_status_t usbd_ll_setup_stage(usbd_t *pdev, uint8_t *psetup);
usbd_status_t usbd_ll_data_out_stage(usbd_t *pdev , uint8_t epnum, uint8_t *pdata);
usbd_status_t usbd_ll_data_in_stage(usbd_t *pdev , uint8_t epnum, uint8_t *pdata);

usbd_status_t usbd_ll_reset(usbd_t  *pdev);
usbd_status_t usbd_ll_set_speed(usbd_t  *pdev, USBD_SpeedTypeDef speed);
usbd_status_t usbd_ll_suspend(usbd_t  *pdev);
usbd_status_t usbd_ll_resume(usbd_t  *pdev);

usbd_status_t usbd_ll_sof(usbd_t  *pdev);
usbd_status_t usbd_ll_iso_in_incomplete(usbd_t  *pdev, uint8_t epnum);
usbd_status_t usbd_ll_iso_out_incomplete(usbd_t  *pdev, uint8_t epnum);

usbd_status_t usbd_ll_dev_connected(usbd_t  *pdev);
usbd_status_t usbd_ll_dev_disconnected(usbd_t  *pdev);

/* USBD Low Level Driver */
usbd_status_t  usbd_ll_init (pcd_t* pcd, usbd_t *pdev);
usbd_status_t  usbd_ll_deinit (usbd_t *pdev);
usbd_status_t  usbd_ll_start(usbd_t *pdev);
usbd_status_t  usbd_ll_stop (usbd_t *pdev);
usbd_status_t  usbd_ll_open_ep  (usbd_t *pdev,
                                      uint8_t  ep_addr,                                      
                                      uint8_t  ep_type,
                                      uint16_t ep_mps);

usbd_status_t  usbd_ll_close_ep (usbd_t *pdev, uint8_t ep_addr);
usbd_status_t  usbd_ll_flush_ep (usbd_t *pdev, uint8_t ep_addr);
usbd_status_t  usbd_ll_stall_ep (usbd_t *pdev, uint8_t ep_addr);
usbd_status_t  usbd_ll_clear_stall_ep (usbd_t *pdev, uint8_t ep_addr);
uint8_t        usbd_ll_is_stall_ep (usbd_t *pdev, uint8_t ep_addr);
usbd_status_t  usbd_ll_set_usb_address (usbd_t *pdev, uint8_t dev_addr);
usbd_status_t  usbd_ll_transmit (usbd_t *pdev,
                                      uint8_t  ep_addr,                                      
                                      uint8_t  *pbuf,
                                      uint16_t  size);

usbd_status_t  usbd_ll_prepare_receive(usbd_t *pdev,
                                           uint8_t  ep_addr,                                      
                                           uint8_t  *pbuf,
                                           uint16_t  size);

uint32_t usbd_ll_get_rx_data_size  (usbd_t *pdev, uint8_t  ep_addr);
void  usbd_ll_delay (uint32_t Delay);


#ifdef __cplusplus
}
#endif

#endif /* __USBD_CORE_H */




