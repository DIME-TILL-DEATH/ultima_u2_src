#include "cc.h"

#include "init.h"

#include "tasks/display_task.h"

cc_task_t* cc_task ;
volatile uint8_t ind_flag = 0 ;
volatile uint8_t uart_flag = 0 ;

//------------------------------------------------------------------------------
cc_task_t::cc_task_t (const char* name , const int stack_size , const int priority ) : task_t(name , stack_size , priority , false)
{

}
//------------------------------------------------------------------------------

void cc_task_t::code()
{
  while(1)
     {	  	  if(uart_flag)
	  	  {
	  		  gui_task->preset_set();
	  		  uart_flag = 0;
	  	  }
	  	  if(gpioa.pin3())
	  	  {
	  		  if(ind_flag != gpioa.pin3())
	  		  {
	  			  ind_flag = 1;
	  			  gui_task->ind_exp_on(ind_flag);
		  		  delay(50);
	  		  }
	  	  }
	  	  else {
	  		  if(ind_flag != gpioa.pin3())
	  		  {
	  			  ind_flag = 0;
	  			  gui_task->ind_exp_on(ind_flag);
		  		  delay(50);
	  		  }
	  	  }
     }
}
//------------------------------------------------------------------------------
uint8_t midi_id = 0;
IRQ_HANDLER(uart5)
{
	uart5.tx_data = uart5.rx_data;
	switch(midi_id){
	case 0:if(uart5.rx_data == (system_file.midi_ch | 0xc0))midi_id = 1;
	       break;
	case 1:if(uart5.rx_data < FS_PRESETS_COUNT)
	  	   {
		  	  prog1 = (uart5.rx_data + 1);
		  	  if(prog1 != prog)
		  	  {
		  		  uart_flag = 1;
		  	  }
	  	   }
	       midi_id = 0;
	       break;
	}
	uart5.rx_data_flush_request_enable();
}
