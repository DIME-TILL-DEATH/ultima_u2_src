#ifndef __USB_CONSOLE_H__
#define __USB_CONSOLE_H__

#include "sdk.h"
#include "readline.h"

#include "emb_string.h"

class console_task_t : public  task_t , public emb_printf
{
  public:
      typedef void (*console_task_hw_init_t)() ;
      struct readline_io_t
       {
         const console_task_hw_init_t     console_task_hw_init ;

         const TReadLine::send_char_fnc   send_char ;
         const TReadLine::recv_char_fnc   recv_char ;

         const TReadLine::send_string_fnc send_string ;
         const TReadLine::recv_string_fnc recv_string ;
         const TReadLine::recv_string_fnc recv_line   ;

         const TReadLine::send_buf_fnc    send_buf ;
         const TReadLine::recv_buf_fnc    recv_buf ;
       }  ;


     console_task_t (const char* name , const int stack_size , const int priority ,  const readline_io_t&  io, const size_t rx_queue_size);
     virtual ~console_task_t() {} ;

     //-- debug freertos
     inline void queue_add_to_geristry()
        {
    	    rx_queue->add_to_registry("console_task_rx");
    	    rx_sem->add_to_registry("console_task_rx_sem");
    	    tx_sem->add_to_registry("console_task_tx_sen");
        }


        // ----------  readline IO stream interface ------------------

        // Note! befor use TConsoleTask

        // 'char' function
	inline int send_char(const int c) { return rl->SendChar(c); }
	inline TReadLine::symbol_type_ptr_t send_string( TReadLine::const_symbol_type_ptr_t dest ) { return rl->SendString(dest); } ;
	inline TReadLine::symbol_type_ptr_t send_string( emb_string& dest ) { return rl->SendString(dest.c_str()); } ;
	inline int send_buf( TReadLine::const_symbol_type_ptr_t buf , size_t size ) { return rl->SendBuf(buf , size); }

	inline int recv_char(int& c)
	  {
	    suspend();
	    rl->RecvChar(c);
	    resume_from_task();
	    return c ;
	  }

	inline size_t recv_string( emb_string& dest )
	  {
	    size_t size ;
	    suspend();
	    size = rl->RecvString(dest);
	    resume_from_task();
	    return size ;
	  } ;

	// 'line' function
	inline size_t recv_line( emb_string& dest )
	  {
	    size_t size ;
	    suspend();
	    size = rl->RecvLine(dest);
	    resume_from_task();
	    return size ;
	  } ;

	inline size_t recv_buf( TReadLine::symbol_type_ptr_t buf , size_t size )
	  {
            size_t readed_size ;
            suspend();
            readed_size = rl->RecvBuf(buf,size) ;
            resume_from_task();
	    return readed_size ;
	  }




	//------------------------------------------------------------------------------------

     inline void clear(){ rl->Clear() ; }
     inline void take() { tx_sem->take(portMAX_DELAY) ; }
     inline void give() { tx_sem->give_from_task() ; } ;
     static inline void no_sync(const void*) { asm volatile ("nop"); } ;

     void set_sync_mode();
     void set_no_sync_mode();

     inline void echo(bool state) { rl->Echo(state); }
     inline bool echo() { return rl->Echo(); }

     inline void send_buf(void* src, size_t len) { rl->SendBuf((const char*)src, len); }

     inline queue_t::queue_send_result_t write_to_input_buff_from_isr( const char* symbol,  BaseType_t*  HigherPriorityTaskWoken ) {  return rx_queue->send_to_back_from_isr( symbol , HigherPriorityTaskWoken) ; }
     inline queue_t::queue_send_result_t write_to_input_buff( const char symbol) {  return rx_queue->send_to_back_from_task( &symbol , 0) ; }
     inline queue_t::queue_receive_result_t read_from_input_buff( char* symbol ) {  return rx_queue->receive_from_task( symbol , portMAX_DELAY) ; }

     // variadic args format PrintF/UnsafePrintF version
     void unsafe_printf(const char *str)       { rl->UnsafePrint(str); }
     void unsafe_printf(const emb_string& str) { rl->UnsafePrint(str); }
     template<typename T, typename... Args>
     void unsafe_printf(const char *frmt, T value, Args... args)
             {
                dest.clear();
                format(dest, frmt,value,args...);
                rl->UnsafePrint(-1,dest);
             }



     void unsafe_printfn(const size_t len, const char *str)       { rl->UnsafePrint(len,str); }
     void unsafe_printfn(const size_t len, const emb_string& str) { rl->UnsafePrint(len,str); }
     template<typename T, typename... Args>
     void unsafe_printfn(const size_t len, const char *frmt, T value, Args... args)
             {
                dest.clear();
                format(dest, frmt,value,args...);
                rl->UnsafePrint(len,dest);
             }


     void printf(const char *str)             { rl->Print(str);}
     void printf(const emb_string& str)       { rl->Print(str);}
     template<typename T, typename... Args>
     void printf(const char *frmt, T value, Args... args)
             {
                dest.clear();
                format(dest , frmt, value, args...);
                rl->Print(-1,dest);
             }


     void printfn(const size_t len, const char *str)             { rl->Print(len,str);}
     void printfn(const size_t len, const emb_string& str)       { rl->Print(len,str);}
     template<typename T, typename... Args>
     void printfn(const size_t len, const char *frmt, T value, Args... args)
             {
                dest.clear();
                format(dest , frmt, value, args...);
                rl->Print(len,dest);
             }

      inline TReadLine* read_line() {return rl ;}
  private:
     void code() ;
     semaphore_binary_t* rx_sem ;
     semaphore_binary_t* tx_sem ;
     TReadLine*  rl ;
     emb_string  dest ;

     queue_t* rx_queue ;
};

void console_set_cmd_handlers(TReadLine* rl) ;

// команда TReadLine (выполняется в контексте TConsoleTask ) !!!!!!!!!!!!!!!!



// direct specific context macros
#define cmsg(rl,...)  (((console_task_t*)(rl->Owner()))->unsafe_printf(__VA_ARGS__))
#define msg(rl,...)   (((console_task_t*)(rl->Owner()))->printf(__VA_ARGS__))

#define cmsgn(rl,n, ...)  (((console_task_t*)(rl->Owner()))->unsafe_printfn(n, __VA_ARGS__))
#define msgn(rl, n, ...)   (((console_task_t*)(rl->Owner()))->printfn(n, __VA_ARGS__))

// relative context macros
#define rmsg(rl,...) \
               {     \
		if (task_utilities_t::current_task_handle()!=((console_task_t*)(rl->Owner()))->get_handle()) { ((console_task_t*)(rl->Owner()))->printf( __VA_ARGS__ ); } \
		else  { ((console_task_t*)(rl->Owner()))->unsafe_printf( __VA_ARGS__ ); } \
	       }

#define rmsg_buf(rl,msg,size) (((console_task_t*)(rl->Owner()))->send_buf(msg,size))


#endif /*__USB_CONSOLE_H__*/
