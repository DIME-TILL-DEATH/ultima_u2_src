/*
 * display.cc
 *
 *  Created on: Nov 12, 2018
 *      Author: klen
 */



#include "display.h"

dispaly_task_t* display_task ;

void dispaly_task_t::code()

{
     while(1)
       {
          delay(100);
       }
}



void dispaly_write(){};
void dispaly_read(){};
void dispaly_instruction_register_select(){};
void dispaly_data_register_select(){};
void dispaly_read_mode(){};
void dispaly_write_mode(){};
void dispaly_start_high(){};
void dispaly_start_low(){};
void dispaly_delay_ms(){};

const dispaly_task_t::io_t display_task_io =
    {
	dispaly_write,
	dispaly_read,
	dispaly_instruction_register_select,
	dispaly_data_register_select,
	dispaly_read_mode,
	dispaly_write_mode,
	dispaly_start_high,
	dispaly_start_low,
	dispaly_delay_ms
    };




