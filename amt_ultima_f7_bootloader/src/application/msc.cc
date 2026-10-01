#include "msc.h"

#include "usbd_storage_if.h"
#include "display.h"


usb_task_t* usb_task ;


void usb_task_t::code()
{
  usbd_init(&pcd, &usbd, &usbd_descriptors, full_speed);
  usbd_register_class(&usbd, &msc_usbd_class);
  usbd_msc_register_storage(&usbd, &usbd_msc_io);
  usbd_start(&usbd);

  while (1)
  {
    pcd_handler(&pcd);
  }
}


