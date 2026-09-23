#ifndef __USB_H__
#define __USB_H__

#include "appdefs.h"

#include "console.h"

#include "libopencm3/usb/usbd.h"
#include "libopencm3/usb/cdc.h"
#include "libopencm3/stm32/otg_fs.h"

extern const console_task_t::readline_io_t  cdc_readline_io ;

class usb_cdc_ocm3_task_t : public task_t
{
  public:
     enum vbus_sense_t { vs_nosense=0, vs_sense } ;

     usb_cdc_ocm3_task_t (const char* name , const int stack_size , const int priority, size_t rx_queue_size, vbus_sense_t vbus_sence = vs_nosense )
     : task_t(name , stack_size , priority , false)
     {
        rx_queue = new queue_t ( rx_queue_size , 1 ) ;
        sem = new semaphore_binary_t();
        this-> vbus_sense = vbus_sense ;
     }

     //-- debug freertos
     inline void queue_add_to_geristry()
        {
    	    rx_queue->add_to_registry("usb_cdc_ocm3_task_rx");
    	    sem->add_to_registry("usb_cdc_ocm3_task_sem");
        }

     virtual ~usb_cdc_ocm3_task_t() {} ;
     inline size_t rx_queue_waiting () { return rx_queue->messages_waiting_from_task(); }
     inline char queue_read() { char c ; rx_queue->receive_from_task( &c , portMAX_DELAY ); return c;  }
     inline queue_t::queue_send_result_t queue_write(void* buf, uint32_t len )
     {
        for (uint32_t i = 0 ; i<len ; i++)
           {
              if ( rx_queue->send_to_back_from_task( ((uint8_t*)buf)+i , 0 ) == queue_t::full)
                 return queue_t::full ;
           }
        return queue_t::send_pass ;
     };
     inline usbd_device* device() {return usbd_dev;}

     inline void send( const char* buf , size_t len )
       {
         take();
         while (usbd_ep_write_packet(usbd_dev, 0x82, buf, len)==0 );
         give();
       }

     inline void take() {  sem->take_from_task(); }
     inline void give() {  sem->give_from_task(); }

     inline void uid2ascii(char* val) const // генерация серийного номера
       {
         const uint16_t* uid = (const uint16_t*)devsign.unuque_id() ;
         const char hex[] = { '0' , '1' , '2', '3', '4' , '5' , '6', '7',
                              '8' , '9' , 'A', 'B', 'C' , 'D' , 'E', 'F'} ;
         uint16_t tmp ;

         tmp = uid[0] + uid[5] ;
         val[0] = hex[ (tmp >> 12) & 0xf ] ;
         val[1] = hex[ (tmp >> 8) & 0xf ] ;
         val[2] = hex[ (tmp >> 4) & 0xf ] ;
         val[3] = hex[ tmp & 0xf ] ;

         tmp = uid[1] + uid[4] ;
         val[4] = hex[ (tmp >> 12) & 0xf ] ;
         val[5] = hex[ (tmp >> 8) & 0xf ] ;
         val[6] = hex[ (tmp >> 4) & 0xf ] ;
         val[7] = hex[ tmp & 0xf ] ;

         tmp = uid[2] + uid[3] ;
         val[8] = hex[ (tmp >> 12) & 0xf ] ;
         val[9] = hex[ (tmp >> 8) & 0xf ] ;
         val[10] = hex[ (tmp >> 4) & 0xf ] ;
         val[11] = hex[ tmp & 0xf ] ;

         val[12] = 0 ;
       }

     static constexpr usb_cdc_line_coding line_coding = {
     	.dwDTERate = 115200,
     	.bCharFormat = USB_CDC_1_STOP_BITS,
     	.bParityType = USB_CDC_NO_PARITY,
     	.bDataBits = 0x08
     };

     static enum usbd_request_return_codes cdcacm_control_request(usbd_device *usbd_dev,
     	struct usb_setup_data *req, uint8_t **buf, uint16_t *len,
     	void (**complete)(usbd_device *usbd_dev, struct usb_setup_data *req))
     {
     	(void)complete;
     	(void)buf;
     	(void)usbd_dev;

     	switch (req->bRequest)
     	{
     	  case USB_CDC_REQ_SET_CONTROL_LINE_STATE:
     	    {
     		char tmp[10];
     		struct usb_cdc_notification *notif = (usb_cdc_notification *)tmp;
     	        // We echo signals back to host as notification.
     		notif->bmRequestType = 0xA1;
     		notif->bNotification = USB_CDC_NOTIFY_SERIAL_STATE;
     		notif->wValue = 0;
     		notif->wIndex = 0;
     		notif->wLength = 2;
     		tmp[8] = req->wValue & 3;
     		tmp[9] = 0;
     		usbd_ep_write_packet(usbd_dev, 0x83, tmp, 10);
     		return USBD_REQ_HANDLED;
     	    }
     	  case USB_CDC_REQ_SET_LINE_CODING:
     	        if (*len < sizeof(struct usb_cdc_line_coding))
     		  {
     		    return USBD_REQ_NOTSUPP;
     		  }

     	        // (usb_cdc_line_coding*)(*buf)->dwDTERate
     	        // (usb_cdc_line_coding*)(*buf)->bCharFormat
     	        // (usb_cdc_line_coding*)(*buf)->bParityType
     	        // (usb_cdc_line_coding*)(*buf)->bDataBits

     	        return USBD_REQ_HANDLED;

     	  case USB_CDC_REQ_GET_LINE_CODING:
     		*buf = (uint8_t *)&line_coding;
                     return USBD_REQ_HANDLED;

     	}
     	return USBD_REQ_NOTSUPP;
     }

     static void cdcacm_data_tx_cb(usbd_device *usbd_dev, uint8_t ep)
     {
     	(void)ep;
     }

  private:
     void code() ;
     queue_t* rx_queue ;
     usbd_device *usbd_dev;
     semaphore_binary_t* sem ;

     vbus_sense_t vbus_sense ;


     static constexpr struct usb_device_descriptor device_descriptor = {
     	.bLength = USB_DT_DEVICE_SIZE,
     	.bDescriptorType = USB_DT_DEVICE,
     	.bcdUSB = 0x0200,
     	.bDeviceClass = USB_CLASS_CDC,
     	.bDeviceSubClass = USB_CDC_SUBCLASS_ACM,
     	.bDeviceProtocol = 0,
     	.bMaxPacketSize0 = 64,
     	.idVendor = USBD_VID,
     	.idProduct = USBD_PID,
     	.bcdDevice = 0x0200,
     	.iManufacturer = 1,
     	.iProduct = 2,
     	.iSerialNumber = 3,
     	.bNumConfigurations = 1,
     };


     /*
      * This notification endpoint isn't implemented. According to CDC spec it's
      * optional, but its absence causes a NULL pointer dereference in the
      * Linux cdc_acm driver.
      */
     static constexpr struct usb_endpoint_descriptor comm_endp[] = {{
     	.bLength = USB_DT_ENDPOINT_SIZE,
     	.bDescriptorType = USB_DT_ENDPOINT,
     	.bEndpointAddress = 0x83,
     	.bmAttributes = USB_ENDPOINT_ATTR_INTERRUPT,
     	.wMaxPacketSize = 16,
     	.bInterval = 255,
     	.extra = NULL,
             .extralen = 0
     } };

     static constexpr struct usb_endpoint_descriptor data_endp[] = {{
     	.bLength = USB_DT_ENDPOINT_SIZE,
     	.bDescriptorType = USB_DT_ENDPOINT,
     	.bEndpointAddress = 0x01,
     	.bmAttributes = USB_ENDPOINT_ATTR_BULK,
     	.wMaxPacketSize = 64,
     	.bInterval = 1,
     	.extra = NULL,
             .extralen = 0
     }, {
     	.bLength = USB_DT_ENDPOINT_SIZE,
     	.bDescriptorType = USB_DT_ENDPOINT,
     	.bEndpointAddress = 0x82,
     	.bmAttributes = USB_ENDPOINT_ATTR_BULK,
     	.wMaxPacketSize = 64,
     	.bInterval = 1,
     	.extra = NULL,
             .extralen = 0
     } };

     static constexpr struct {
     	struct usb_cdc_header_descriptor header;
     	struct usb_cdc_call_management_descriptor call_mgmt;
     	struct usb_cdc_acm_descriptor acm;
     	struct usb_cdc_union_descriptor cdc_union;
     } __attribute__((packed)) cdcacm_functional_descriptors = {
     	.header = {
     		.bFunctionLength = sizeof(struct usb_cdc_header_descriptor),
     		.bDescriptorType = CS_INTERFACE,
     		.bDescriptorSubtype = USB_CDC_TYPE_HEADER,
     		.bcdCDC = 0x0110,
     	},
     	.call_mgmt = {
     		.bFunctionLength =
     			sizeof(struct usb_cdc_call_management_descriptor),
     		.bDescriptorType = CS_INTERFACE,
     		.bDescriptorSubtype = USB_CDC_TYPE_CALL_MANAGEMENT,
     		.bmCapabilities = 0,
     		.bDataInterface = 1,
     	},
     	.acm = {
     		.bFunctionLength = sizeof(struct usb_cdc_acm_descriptor),
     		.bDescriptorType = CS_INTERFACE,
     		.bDescriptorSubtype = USB_CDC_TYPE_ACM,
     		.bmCapabilities = 0x2,
     	},
     	.cdc_union = {
     		.bFunctionLength = sizeof(struct usb_cdc_union_descriptor),
     		.bDescriptorType = CS_INTERFACE,
     		.bDescriptorSubtype = USB_CDC_TYPE_UNION,
     		.bControlInterface = 0,
     		.bSubordinateInterface0 = 1,
     	 }
     };

     static constexpr struct usb_interface_descriptor comm_iface[] = {{
     	.bLength = USB_DT_INTERFACE_SIZE,
     	.bDescriptorType = USB_DT_INTERFACE,
     	.bInterfaceNumber = 0,
     	.bAlternateSetting = 0,
     	.bNumEndpoints = 1,
     	.bInterfaceClass = USB_CLASS_CDC,
     	.bInterfaceSubClass = USB_CDC_SUBCLASS_ACM,
     	.bInterfaceProtocol = USB_CDC_PROTOCOL_AT,
     	.iInterface = 0,

     	.endpoint = comm_endp,

     	.extra = &cdcacm_functional_descriptors,
     	.extralen = sizeof(cdcacm_functional_descriptors)
     } };

     static constexpr struct usb_interface_descriptor data_iface[] = {{
     	.bLength = USB_DT_INTERFACE_SIZE,
     	.bDescriptorType = USB_DT_INTERFACE,
     	.bInterfaceNumber = 1,
     	.bAlternateSetting = 0,
     	.bNumEndpoints = 2,
     	.bInterfaceClass = USB_CLASS_DATA,
     	.bInterfaceSubClass = 0,
     	.bInterfaceProtocol = 0,
     	.iInterface = 0,

     	.endpoint = data_endp,
     	.extra = NULL,
             .extralen = 0
     } };

     static constexpr struct usb_interface ifaces[] =
         {
     	{
     	  .cur_altsetting=NULL,
     	  .num_altsetting = 1,
     	  .iface_assoc=NULL,
     	  .altsetting = comm_iface,
             },
             {
       	  .cur_altsetting=NULL,
     	  .num_altsetting = 1,
     	  .iface_assoc=NULL,
     	  .altsetting = data_iface,
             },
         };

     static constexpr struct usb_config_descriptor config = {
     	.bLength = USB_DT_CONFIGURATION_SIZE,
     	.bDescriptorType = USB_DT_CONFIGURATION,
     	.wTotalLength = 0,
     	.bNumInterfaces = 2,
     	.bConfigurationValue = 1,
     	.iConfiguration = 0,
     	.bmAttributes = 0x80,
     	.bMaxPower = 0x32,
     	.interface = ifaces,
     };


     /* Buffer to be used for control requests. */
     uint8_t usbd_control_buffer[128];




};

extern usb_cdc_ocm3_task_t* usb_cdc_ocm3_task ;

#endif /*__USB_H__*/
