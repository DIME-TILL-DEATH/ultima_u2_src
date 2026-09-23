/*
 * display.cc
 *
 *  Created on: Nov 12, 2018
 *      Author: klen
 */


#ifndef  __DISPLAY_H__
#define  __DISPLAY_H__

#include "sdk.h"

class dispaly_task_t : task_t
{
   public:

      struct io_t
         {
            void (*write)();
            void (*read)();
            void (*instruction_register_select)();
            void (*data_register_select)();
            void (*read_mode)();
            void (*write_mode)();
            void (*start_high)();
            void (*start_low)();
            void (*delay_ms)();
         };


      inline dispaly_task_t (const char* name , const int stack_size , const int priority, const io_t& io  ) : task_t(name , stack_size , priority , false), io(io)
        {
         // init
        }
      inline ~dispaly_task_t() {} ;


      inline void clear() {} ;
      inline void clear ( const size_t row, const size_t col, const size_t len ) {} ;
      inline void string( const size_t row, const size_t col, const emb_string& src ) {} ;
      inline void string( const size_t row, const size_t col, const char* src ) {} ;
      inline void symbol( const size_t row, const size_t col, const char  src ) {} ;
      inline void progress( const size_t val ) {} ;

   protected:
   private:
      void code();
      const io_t& io ;

} ;

extern const dispaly_task_t::io_t display_task_io ;
extern dispaly_task_t* display_task ;

#endif  /*__DISPLAY_H__*/
