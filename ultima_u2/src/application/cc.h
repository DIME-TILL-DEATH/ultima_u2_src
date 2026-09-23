#ifndef __CC_H__
#define __CC_H__

#include "appdefs.h"

class cc_task_t : public task_t
{
  public:
     cc_task_t (const char* name , const int stack_size , const int priority) ;
     virtual ~cc_task_t() {} ;
  private:
     void code() ;
};



extern cc_task_t* cc_task ;

#endif /*__CC_H__*/
