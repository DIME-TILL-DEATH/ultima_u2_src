
#include "usb_console.h"
#include "console.h"
#include "stm32++.h"



usb_cdc_ocm3_task_t* usb_cdc_ocm3_task ;


static char serial_no[13];

static constexpr char * usb_strings[] = {
        ( char*)USBD_MANUFACTURER_STRING,
	( char*)USBD_PRODUCT_STRING,
	serial_no,
	( char*)"cdc interface"
};

static void cdcacm_data_rx_cb(usbd_device *usbd_dev, uint8_t ep)
{
	(void)ep;

	char buf[64];
	int len = usbd_ep_read_packet(usbd_dev, 0x01, buf, 64);

	usb_cdc_ocm3_task->queue_write( buf , len) ;
}



static void cdcacm_set_config(usbd_device *usbd_dev, uint16_t wValue)
{
	(void)wValue;

	usbd_ep_setup(usbd_dev, 0x01, USB_ENDPOINT_ATTR_BULK, 64, cdcacm_data_rx_cb);
	usbd_ep_setup(usbd_dev, 0x82, USB_ENDPOINT_ATTR_BULK, 64, usb_cdc_ocm3_task_t::cdcacm_data_tx_cb);
	usbd_ep_setup(usbd_dev, 0x83, USB_ENDPOINT_ATTR_INTERRUPT, 16, NULL);

	usbd_register_control_callback(
				usbd_dev,
				USB_REQ_TYPE_CLASS | USB_REQ_TYPE_INTERFACE,
				USB_REQ_TYPE_TYPE | USB_REQ_TYPE_RECIPIENT,
				usb_cdc_ocm3_task_t::cdcacm_control_request);
}

//------------------------------------------------------------------------------
void usb_cdc_ocm3_task_t::code()
{

#if defined (__STM32F4XX__)
         gpioa.clock_enable();
         gpioa.pin(  gpio_t::mode_t::pin11_t::alternate_function,
                     gpio_t::mode_t::pin12_t::alternate_function,
                     gpioa_t::af_t::pin11_t::otgfs_dm,
		     gpioa_t::af_t::pin12_t::otgfs_dp
		   );
#elif defined (__STM32F7XX__)

         rcc.gpioa_enable();
         gpioa.pin(gpio_t::mode_t::pin11_t::alternate_function, gpio_t::mode_t::pin12_t::alternate_function, gpioa_t::af_t::pin11_t::otgfs_dm, gpioa_t::af_t::pin12_t::otgfs_dp);

         //gpioa.pin11_mode_alternate_function();
         //gpioa.pin12_mode_alternate_function();
	 //gpioa.af.modify( gpioa_t::af_t::pin11_t::otgfs_dm , gpioa_t::af_t::pin12_t::otgfs_dp ) ;

#else /*defined __STM32F1XX__*/

   ????? fix 
   #if 0  // если есть подтяжка для управления D+
   rcc.gpioa_enable();
   rcc_periph_clock_enable(RCC_GPIOC);
   /* Setup GPIOC Pin 12 to pull up the D+ high, so autodect works
    * with the bootloader.  The circuit is active low. */
   gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ,GPIO_CNF_OUTPUT_OPENDRAIN, GPIO12);
   gpio_set(GPIOC, GPIO12);
   Delay(250);
   gpio_clear(GPIOC, GPIO12);
   #endif

#endif

   uid2ascii(serial_no) ;

   usbd_dev = usbd_init(
      #ifdef __STM32F4XX__
              &otgfs_usb_driver,
      #elif defined __STM32F1XX__
	      &st_usbfs_v1_usb_driver,
      #elif defined __STM32F7XX__
	      &otghs_usb_driver , //&stm32f7xx_usb_driver,
      #elif
           #error "USB define by chip type"
      #endif
	     &device_descriptor, &config, usb_strings, sizeof(usb_strings)/sizeof(char *), usbd_control_buffer, sizeof(usbd_control_buffer));

#if defined (__STM32F4XX__) || defined (__STM32F7XX__)
   // отключение детектирования VBUS
   if (vbus_sense == vs_nosense )
     OTG_FS_GCCFG |= OTG_GCCFG_NOVBUSSENS;
   else
     OTG_FS_GCCFG &= ~OTG_GCCFG_NOVBUSSENS;
#endif

   usbd_register_set_config_callback(usbd_dev, cdcacm_set_config);

   while(1)
     {
       take() ;

       usbd_poll(usbd_dev);

       give();

       #if defined (__STM32F4XX__) || defined (__STM32F7XX__)
           scheduler_t::yeld();
       #elif defined __STM32F1XX__
	    // ....  почему то Yeld() приводит к неработоспособности
       #elif
          #error "USB define by chip type"
       #endif

     }
}



//---------------------------------------------------------------------------
static int cdc_send_char( const int c )
{
   char tmp = c ;
   usb_cdc_ocm3_task->send( &tmp , 1 );
   return c ;
}
//---------------------------------------------------------------------------
static size_t cdc_send_buf( const char* buf , size_t size )
{
   if (!size) return size ;
   while (size)
       {
         uint16_t l = size < 64 ? size : 64 ;
         usb_cdc_ocm3_task->send( buf , l );
         buf+=l ;
         size-=l ;
       }
   return size ;
}
//---------------------------------------------------------------------------
static char* cdc_send_string( const char* s, const size_t len )
{
   size_t length = (len == (uint32_t)-1  ?  strlen(s) : len) ;

   if (!length)
     return (char*)s ;
   cdc_send_buf( s , length ) ;
   return (char*)s ;
}
//---------------------------------------------------------------------------
static int cdc_recv_char (int& c)
{
  c = usb_cdc_ocm3_task->queue_read() ;
  return c ;
}
//---------------------------------------------------------------------------
static size_t cdc_recv_string (kgp::emb_string& dest)
{
   dest.clear() ;
   int c ;
   do
     {
       c = usb_cdc_ocm3_task->queue_read() ;
       if ( !c ) return dest.length() ;
       else dest.push_back(c);
     }while(1) ;
}
//---------------------------------------------------------------------------
static size_t cdc_recv_line (kgp::emb_string& dest)
{
   dest.clear() ;
   int c ;
   do
     {
       c = usb_cdc_ocm3_task->queue_read() ;
       if (c == '\r') return dest.length() ;
       else dest.push_back(c);
     }while(1) ;
}
//---------------------------------------------------------------------------
static size_t cdc_recv_buf (char* buf , size_t size)
{
   size_t c = 0 ;
   while ( c < size )
     {
       *(buf++) = usb_cdc_ocm3_task->queue_read() ;
       c++ ;
     }
   return c ;
}

//---------------------------------------------------------------------------
const console_task_t::readline_io_t  cdc_readline_io =
         {
               .console_task_hw_init = NULL,

               .send_char = cdc_send_char,
               .recv_char = cdc_recv_char,

               .send_string = cdc_send_string,
               .recv_string = cdc_recv_string,
	       .recv_line   = cdc_recv_line,

               .send_buf = cdc_send_buf,
               .recv_buf = cdc_recv_buf,
         };
