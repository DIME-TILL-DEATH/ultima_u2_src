#ifndef __MSC_H__
#define __MSC_H__

#include "appdefs.h"
#include "stm32f7xx_hal_pcd.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_msc.h"

class msc_task_t : public task_t
{
  public:

     inline msc_task_t (const char* name , const int stack_size , const int priority) : task_t(name , stack_size , priority , false)
     {
       pcd.handler_mode = pool ;
     }

     virtual ~msc_task_t() {} ;

  protected:

     void state_handler();


  private:
     void code() ;

     pcd_t pcd;
     usbd_t usbd;
};

extern msc_task_t* msc_task ;

#endif /*__MSC_H__*/


