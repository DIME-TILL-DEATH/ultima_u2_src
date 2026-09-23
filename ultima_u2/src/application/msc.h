#ifndef __MSC_H__
#define __MSC_H__

#include "appdefs.h"
#include "stm32f7xx_hal_pcd.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_msc.h"
#include "ff.h"

class msc_task_t : public task_t
{
  public:

     enum device_state_t { undefined, defaults, addressed, configured, suspended } ;

     inline msc_task_t (const char* name , const int stack_size , const int priority, bool suspend) : task_t(name , stack_size , priority , suspend)
     {
       pcd.handler_mode = pool ;
     }

     virtual ~msc_task_t() {} ;

     inline device_state_t device_state() {return  (device_state_t)usbd.dev_state ; }

     void start();
     void stop();

  protected:

     void state_handler();


  private:
     void code() ;

     pcd_t pcd;
     usbd_t usbd;

     device_state_t prev_device_state ;
};

extern msc_task_t* msc_task ;

#endif /*__MSC_H__*/


