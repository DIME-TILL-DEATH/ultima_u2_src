#include "console.h"
#include "int2str.h"

static void undefind_command_handler( TReadLine* rl , TReadLine::const_symbol_type_ptr_t* args , const size_t count )
{
  cmsg (rl,"undefind command %s\n" , args[0]) ;
}

// функции враперы синхронизации для readline
extern "C" void console_take( console_task_t* owner )
{
  owner->take() ;
}

extern "C" void console_give(console_task_t*  owner )
{
  owner->give() ;
}

void console_task_t::code()
{
   while(1)
      {
         rl->Process() ;
      }
}

//-----------------------------------------------------------------------
void console_task_t::set_sync_mode()
{
   rl->SetGiveSem( (TReadLine::sem_fnc)console_give );
   rl->SetTakeSem( (TReadLine::sem_fnc)console_take );
}
//-----------------------------------------------------------------------
void console_task_t::set_no_sync_mode()
 {
   rl->SetGiveSem( no_sync );
   rl->SetTakeSem( no_sync );
 }
//-----------------------------------------------------------------------

console_task_t::console_task_t(const char* name , const int stack_size , const int priority , const readline_io_t& io, const size_t rx_queue_size) : task_t(name , stack_size , priority , false)
{
      rl = new TReadLine( this );
	  rl -> Init(8 , 128 );

	  set_sync_mode();

	  rl->SetCommandNotFound(undefind_command_handler) ;

	  // call user defined handler setter
	  console_set_cmd_handlers(rl);

	  rl->SetPromt("") ;

	  rx_sem = new semaphore_binary_t () ;
	  tx_sem = new semaphore_binary_t () ;

	  rx_queue = new queue_t(rx_queue_size , sizeof(char)) ;

	  // call extern user define api for init HW support of IO interface if defined
	  if (io.console_task_hw_init)
	      io.console_task_hw_init();

	  // set stream IO interfase
	  rl->SendChar(io.send_char) ;
	  rl->RecvChar(io.recv_char) ;
	  rl->SendString(io.send_string);
	  rl->RecvString(io.recv_string) ;
	  rl->RecvLine(io.recv_line);
	  rl->SendBuf(io.send_buf);
	  rl->RecvBuf(io.recv_buf) ;

}
