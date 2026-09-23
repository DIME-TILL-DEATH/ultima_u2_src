#include "console_handlers.h"
#include "mmgr.h"
#include "rt_counter.h"
#include "portmacro.h"
#include "rand.h"

//------------------------------------------------------------------------------
static void echo_command_handler ( TReadLine* rl , TReadLine::const_symbol_type_ptr_t* args , const size_t count )
{
	rl->Echo( !rl->Echo()) ;
	cmsg (rl, "\tconsole echo mode set:  %s\n" , rl->Echo() ? "enable" : "disable" );
}

//------------------------------------------------------------------------------
static void help_command_handler ( TReadLine* rl , TReadLine::const_symbol_type_ptr_t* args , const size_t count )
{
  TReadLine::command_handler_map_iterator_t cmd ;
  TReadLine::command_handler_map_iterator_t end ;

    // out app only command help
        if ( count  == 1 )
          {
            	rl->GetCommandHandlerMapIterators( cmd, end );
            	while ( cmd!= end)
            		 {
            	           if ( !cmd->second.is_internal )
            	             {
            		       cmsg (rl,"\t%s", cmd->first );
            		       if ( cmd->second.description )
            		          cmsg (rl,"\t\t%s\n", cmd->second.description );
            	             }
            	           cmd++;
            		 }
          }
        if ( count  == 2 )
         {
            if ( !strcmp(args[1],"*") )
              {
        	rl->GetCommandHandlerMapIterators( cmd, end );
        	while ( cmd!= end)
        	  {
        	     if ( cmd->second.is_internal )
        	       {
        	         cmsg (rl,"\t%s", cmd->first );
        	         if ( cmd->second.description )
        	         cmsg (rl,"\t\t%s\n", cmd->second.description );
        	       }
        	   cmd++;
      		 }
        	return ;
              }



            if ( rl->GetCommandHandlerIterator(args[1],cmd))
               cmsg (rl,"\t%s\n", cmd->second.description );
            else
               cmsg (rl,"\tundefined command '%s'\n", args[1] );
         }
}

//------------------------------------------------------------------------------
static void reset_command_handler ( TReadLine* rl , TReadLine::const_symbol_type_ptr_t* args , const size_t count )
{
	scb.system_reset();
}
//------------------------------------------------------------------------------
void __attribute__ ((weak)) user_components_version_command_handler(TReadLine* rl)
{
  // weak func for user defined application component version
}

static void version_command_handler ( TReadLine* rl , TReadLine::const_symbol_type_ptr_t* args , const size_t count )
{
	cmsg(rl,"\ttarget board: "  DEV_DESCRIPTION "\n") ;
	cmsg(rl,"\tfirmware:     "  PROJECT_DESCRIPTION "\n") ;
	cmsg(rl,"\tos: FreeRTOS " tskKERNEL_VERSION_NUMBER "\n");
	cmsg(rl,"\tcompiler: GCC " __VERSION__ "\n");
	cmsg(rl,"\tGLIBCXX: %1\n", __GLIBCXX__ ) ;

	cmsg(rl,"\tnewlib: " _NEWLIB_VERSION "\n"  ) ;

        #if defined USBD_MANUFACTURER_STRING
	   cmsg(rl,"\tmanufacturer: " USBD_MANUFACTURER_STRING "\n"  ) ;
        #endif


	user_components_version_command_handler(rl);

	cmsg(rl, "\tfirmware build date: %1 %1\n", gnu_linker_build_date(),  gnu_linker_build_time()) ;
}
//------------------------------------------------------------------------------
void __attribute__ ((weak)) dev_inf_ex_command_handler()
{
  // weak func for user defined device component version
}

static void dev_inf_command_handler ( TReadLine* rl , TReadLine::const_symbol_type_ptr_t* args , const size_t count )
{
          cmsg(rl,"\theap mngr: 0x%1x\tsize: %1d\n" , heap_ptr(), heap_size()) ;
          void** pools ;
          size_t poll_count = heap_get_pools(&pools) ;
          for (size_t m = 0 ; m < poll_count ; m++)
             {
                cmsg(rl,"\t\tpool[%1d] area addr : 0x%8X\n" , m , pools[m] ) ;
             }

	  cmsg(rl,"\theap control struct size ... %1d bytes\n" , heap_control_stuct_size()) ;
	  cmsg(rl,"\theap align size ...          %1d bytes\n" , heap_align_size()) ;
	  cmsg(rl,"\theap block size_min ...      %1d bytes\n" , heap_block_size_min()) ;
	  cmsg(rl,"\theap block size_max ...      %1d bytes\n" , heap_block_size_max()) ;
	  cmsg(rl,"\theap pool overhead  ...      %1d bytes\n" , heap_pool_overhead()) ;

	  cmsg(rl,"\n\tF_OSC   freq   ... %3.6 MHz\n" , 1.0f*F_OSC  / 1.0e6f ) ;
	  // TODO реимплементировать
	  cmsg(rl,"\tSYSCLK  clock  ... %3.6 MHz\n" , 1.0f*rcc.sys_clock_freq()  / 1.0e6f ) ;
	  cmsg(rl,"\tHCLK    clock  ... %3.6 MHz\n" , 1.0f*rcc.ahb_clock_freq()  / 1.0e6f ) ;
	  cmsg(rl,"\tPCLK1   clock  ... %3.6 MHz\n" , 1.0f*rcc.apb1_clock_freq() / 1.0e6f ) ;
	  cmsg(rl,"\tPCLK2   clock  ... %3.6 MHz\n" , 1.0f*rcc.apb2_clock_freq() / 1.0e6f ) ;
	  //cmsg("\tADCCLK2 clock  ... %6f MHz\n" , 1.0f*rrc.ADCCLK_Frequency / 1.0e6 ) ;


	  cmsg(rl,"\n\tMain stack end addr: 0x%8X\n" , gnu_linker_stack_end()) ;
	  cmsg(rl,"\tMemory layout:\n\t\tInternal flash addr: 0x%8X size: %1\n" , gnu_linker_flash_start(), gnu_linker_flash_size() ) ;
	  cmsg(rl,"\t\tflash section layout:\n");
	  cmsg(rl,"%sflash_vec_table\taddr: 0x%8X size: %1\n" , "\t\t\t." , gnu_linker_vec_start() ,  gnu_linker_vec_size() ) ;
	  #ifdef __EEPROM_FLASH_SECTOR_A__
	     cmsg(rl,"%seeprom_sector_a\taddr: 0x%8X size: %1\n" , "\t\t\t." , gnu_linker_eeprom_sector_a_start() ,  gnu_linker_eeprom_sector_a_size() ) ;
	  #endif
          #ifdef __EEPROM_FLASH_SECTOR_B__
	     cmsg(rl,"%seeprom_sector_b\taddr: 0x%8X size: %1\n" , "\t\t\t." , gnu_linker_eeprom_sector_b_start() ,  gnu_linker_eeprom_sector_b_size() ) ;
	  #endif
	  cmsg(rl,"%scode\t\t\taddr: 0x%8X size: %1\n" , "\t\t\t." , gnu_linker_code_start(), gnu_linker_code_size() ) ;
          cmsg(rl,"%spreinit_array\t\taddr: 0x%8X size: %1\n" , "\t\t\t\t." , gnu_linker_preinit_array_start() ,  gnu_linker_preinit_array_size() ) ;
          cmsg(rl,"%sinit_array\t\taddr: 0x%8X size: %1\n" , "\t\t\t\t." , gnu_linker_init_array_start() ,  gnu_linker_init_array_size() ) ;
          cmsg(rl,"%sfini_array\t\taddr: 0x%8X size: %1\n" , "\t\t\t\t." , gnu_linker_fini_array_start() ,  gnu_linker_fini_array_size() ) ;
          cmsg(rl,"%sprivileged_functions\taddr: 0x%8X size: %1\n" , "\t\t\t\t." , gnu_linker_privileged_functions_start() , gnu_linker_privileged_functions_size() ) ;
          cmsg(rl,"%stext\t\t\taddr: 0x%8X size: %1\n" , "\t\t\t\t." , gnu_linker_text_start() , gnu_linker_text_size() ) ;
          cmsg(rl,"%srodata\t\t\taddr: 0x%8X size: %1\n" , "\t\t\t\t." , gnu_linker_rodata_start() ,  gnu_linker_rodata_size() ) ;
          cmsg(rl,"\%sconst_data\t\taddr: 0x%8X size: %1\n" , "\t\t\t\t." , gnu_linker_const_data_start() ,  gnu_linker_const_data_size() ) ;
          cmsg(rl,"%sdata LMA\t\taddr: 0x%8X size: %1\n" , "\t\t\t." , gnu_linker_data_load_start() ,  gnu_linker_data_load_size() ) ;

          #if defined (__STM32F4XX__)
             cmsg(rl,"%sccm_data LMA\t\taddr: 0x%8X size: %1\n" , "\t\t\t." , gnu_linker_ccm_data_load_start() ,  gnu_linker_ccm_data_load_size() ) ;
             cmsg(rl,"\t\tInternal CCM addr: 0x%8X size: %1\n" , gnu_linker_ccm_start(),  gnu_linker_ccm_size() ) ;
          #elif defined(__STM32F7XX__)
             cmsg(rl,"%sdtcm_data LMA\t\taddr: 0x%8X size: %1\n" , "\t\t\t." , gnu_linker_dtcm_data_load_start() ,  gnu_linker_dtcm_data_load_size() ) ;
             cmsg(rl,"\t\tInternal DTCM addr: 0x%8X size: %1\n" , gnu_linker_dtcm_start(),  gnu_linker_dtcm_size() ) ;
             cmsg(rl,"\t\tInternal ITCM addr: 0x%8X size: %1\n" , gnu_linker_itcm_start(),  gnu_linker_itcm_size() ) ;
          #endif

          cmsg(rl,"\t\tInternal ram addr: 0x%8X size: %1\n" , gnu_linker_sram_start(),  gnu_linker_sram_size() ) ;
          cmsg(rl,"\t\tram section layout:\n");

          #if defined (__STM32F4XX__)
            cmsg(rl,"%sCCM RAM .data\t\taddr: 0x%8X size: %1\n" , "\t\t\t." ,  gnu_linker_ccm_data_start() , gnu_linker_ccm_data_size() ) ;
            cmsg(rl,"%sCCM RAM .bss\t\taddr: 0x%8X size: %1\n" , "\t\t\t." ,gnu_linker_ccm_bss_start() , gnu_linker_ccm_bss_size()) ;
          #elif defined(__STM32F7XX__)
            cmsg(rl,"%sDTCM RAM .data\t\taddr: 0x%8X size: %1\n" , "\t\t\t." ,  gnu_linker_dtcm_data_start() , gnu_linker_dtcm_data_size() ) ;
            cmsg(rl,"%sDTCM RAM .bss\t\taddr: 0x%8X size: %1\n" , "\t\t\t." ,gnu_linker_dtcm_bss_start() , gnu_linker_dtcm_bss_size()) ;
          #endif

          cmsg(rl,"%sRAM .data\t\taddr: 0x%8X size: %1\n" , "\t\t\t." ,gnu_linker_data_start(), gnu_linker_data_size()) ;
          cmsg(rl,"%sRAM .bss\t\taddr: 0x%8X size: %1\n" , "\t\t\t." ,gnu_linker_bss_start() , gnu_linker_bss_size()) ;

          cmsg(rl,"\n\tFirmware image addr: 0x%8X size: %1\n" , gnu_linker_image_start() ,  gnu_linker_image_size() ) ;

          #if defined USBD_VID
	      cmsg(rl,"\n\tusb device:\n\t\tid : %4X:%4X\n", (void*)USBD_VID, (void*)USBD_PID  ) ;
          #endif

	  dev_inf_ex_command_handler();
}

#if ( configGENERATE_RUN_TIME_STATS == 1 )
//------------------------------------------------------------------------------
static void time_command_handler ( TReadLine* rl , TReadLine::const_symbol_type_ptr_t* args , const size_t count )
{
        cmsg(rl,"sec %9.6f\n" , (float) 1.0f * portGET_RUN_TIME_COUNTER_VALUE() / RUN_TIME_STATS_INTERRUPT_FREQUENCY ) ;
}
#endif



//------------------------------------------------------------------------------
static void tlsf_pool_walker(const void* ptr, const size_t size, const int used, const void* user)
{
  (void)user ;
  const char *used_str = used ? "used" : "free" ;
  cmsg ( ((TReadLine*)user) ,"\t\t0x%8X %1 %s \n", ptr , size, used_str);
}

static void heap_walk_command_handler ( TReadLine* rl , TReadLine::const_symbol_type_ptr_t* args , const size_t count )
{
  void** pools ;
  size_t poll_count = heap_get_pools(&pools) ;
  cmsg (rl, "\t\tblock addr   parent  state  size \n");
  for (size_t m = 0 ; m < poll_count ; m++)
    {
       cmsg(rl,"\t--- pool[%1] area addr : 0x%8X --- \n" , m , pools[m] ) ;
       heap_walk_pool ( pools[m] , tlsf_pool_walker, rl ) ;
    }
}

//------------------------------------------------------------------------------
#if (configGENERATE_RUN_TIME_STATS == 1)
static void sys_command_handler ( TReadLine* rl , TReadLine::const_symbol_type_ptr_t* args , const size_t count )
{
TaskStatus_t *pxTaskStatusArray;
volatile UBaseType_t uxArraySize = 0 ;
volatile UBaseType_t  x = 0 ;
unsigned long ulTotalRunTime, ulTotalRunTimeExeptIrq,  ulStatsAsPercentage;

/*
         uint32_t tmp , days , hours, minutes, secs ;

         TickType_t rt_tic_counter = portGET_RUN_TIME_COUNTER_VALUE() ;

         TickType_t uSecs = rt_counter_us(rt_tic_counter);
         tmp = uSecs/1000000 ;

         secs = tmp % 60 ;
         minutes  = tmp / 60 ;

         tmp = minutes ;

         hours = tmp % 24 ;
         days = tmp / 24 ;
         cmsg (rl,"\trt tics\t: %U ( %u day %u hour %u min %u sec   )\n" , uSecs , days, hours,minutes,secs );
*/


const static char* task_state_str[] = { "RUN" , "RDY" , "BLK", "SPD", "DEL" } ;

    /* Take a snapshot of the number of tasks in case it changes while this
    function is executing. */
    uxArraySize = uxTaskGetNumberOfTasks();


    /* Allocate a TaskStatus_t structure for each task.  An array could be
    allocated statically at compile time. */
    pxTaskStatusArray = (TaskStatus_t*)malloc( uxArraySize * sizeof( TaskStatus_t ) );

    if( pxTaskStatusArray != NULL )
    {
        /* Generate raw status information about each task. */
        uxArraySize = uxTaskGetSystemState( pxTaskStatusArray, uxArraySize, &ulTotalRunTime );
        ulTotalRunTimeExeptIrq = ulTotalRunTime ;

        /* For percentage calculations. */
        ulTotalRunTime /= 100UL;

        /* Avoid divide by zero errors. */
        if( ulTotalRunTime > 0 )
        {

           #ifdef __USE_REENTRANT__
            {
            cmsg( rl," %s\t%s\t\t%s      %s\t%s\t\t%s\t%s\t%s\t\%s\t%%\n",
                                    "#",
                                    "Name",
                                    "Handle",
				    "Reent",
                                    "State",
                                    "BPrio",
                                    "CPrio",
                                    "Stack",
                                    "Run time"
                                     );
            }
           #else
            {
            cmsg( rl,"%s\t%s\t\t%s\t\t%s\t\t%s\t%s\t%s\t\%s\t%%\n",
                                    "#",
                                    "Name",
                                    "Handle",
                                    "State",
                                    "BPrio",
                                    "CPrio",
                                    "Stack",
                                    "Run time"
                                     );
            }
           #endif



            cmsg(rl,"----------------------------------------------------------------------------------------------------\n");

            /* For each populated position in the pxTaskStatusArray array,
            format the raw data as human readable ASCII data. */
            for( x = 0; x < uxArraySize; x++ )
            {
                /* What percentage of the total run time has the task used?
                This will always be rounded down to the nearest integer.
                ulTotalRunTimeDiv100 has already been divided by 100. */
                ulStatsAsPercentage = pxTaskStatusArray[ x ].ulRunTimeCounter / ulTotalRunTime;

                // TODO сделать правильый расчет
                // eval a exepteion % irq time
                ulTotalRunTimeExeptIrq -= pxTaskStatusArray[ x ].ulRunTimeCounter ;

                if( ulStatsAsPercentage > 0UL )
                {
                    #ifdef __USE_REENTRANT__
                          {
                            cmsg( rl,"%*2\t%s\t\t0x%8X  0x%8X\t%s\t\t%1\t%1\t%1\t\%1.2\t\t%1%%\r\n",
                                                                  (uint32_t)pxTaskStatusArray[ x ].xTaskNumber,
                                                                  pxTaskStatusArray[ x ].pcTaskName,
                                                                  (void*)pxTaskStatusArray[ x ].xHandle,
								  pxTaskStatusArray[ x ].reentrant,
                                                                  task_state_str[pxTaskStatusArray[ x ].eCurrentState],
                                                                  pxTaskStatusArray[ x ].uxBasePriority,
                                                                  pxTaskStatusArray[ x ].uxCurrentPriority,
                                                                  pxTaskStatusArray[ x ].usStackHighWaterMark,
								  run_time_S(pxTaskStatusArray[ x ].ulRunTimeCounter),
                                                                  ulStatsAsPercentage );
                          }
                    #else
                          {
                            cmsg( rl,"%*2\t%s\t\t0x%8X\t%s\t\t%1\t%1\t%1\t\%1.2\t\t%1%%\r\n",
                                                                        (uint32_t)pxTaskStatusArray[ x ].xTaskNumber,
                                                                        pxTaskStatusArray[ x ].pcTaskName,
                                                                        (void*)pxTaskStatusArray[ x ].xHandle,
                                                                        task_state_str[pxTaskStatusArray[ x ].eCurrentState],
                                                                        pxTaskStatusArray[ x ].uxBasePriority,
                                                                        pxTaskStatusArray[ x ].uxCurrentPriority,
                                                                        pxTaskStatusArray[ x ].usStackHighWaterMark,
									run_time_S(pxTaskStatusArray[ x ].ulRunTimeCounter),
                                                                        ulStatsAsPercentage );
                          }
                    #endif
                }
                else
                {
                    /* If the percentage is zero here then the task has
                    consumed less than 1% of the total run time. */

                       #ifdef __USE_REENTRANT__
                         {
                            cmsg( rl,"%*2\t%s\t\t0x%8X  0x%8X\t%s\t\t%1\t%1\t%1\t\%1.2\t\t<1%%\r\n",
                                              (uint32_t)pxTaskStatusArray[ x ].xTaskNumber,
                                              pxTaskStatusArray[ x ].pcTaskName,
                                              (void*)pxTaskStatusArray[ x ].xHandle,
					      pxTaskStatusArray[ x ].reentrant,
                                              task_state_str[pxTaskStatusArray[ x ].eCurrentState],
                                              pxTaskStatusArray[ x ].uxBasePriority,
                                              pxTaskStatusArray[ x ].uxCurrentPriority,
                                              pxTaskStatusArray[ x ].usStackHighWaterMark,
					      run_time_S(pxTaskStatusArray[ x ].ulRunTimeCounter));
                         }
                     #else
                         {
                            cmsg( rl,"%*2\t%s\t\t0x%8X\t%s\t\t%1\t%1\t%1\t\%1.2\t\t<1%%\r\n",
                                                    (uint32_t)pxTaskStatusArray[ x ].xTaskNumber,
                                                    pxTaskStatusArray[ x ].pcTaskName,
                                                    (void*)pxTaskStatusArray[ x ].xHandle,
                                                    task_state_str[pxTaskStatusArray[ x ].eCurrentState],
                                                    pxTaskStatusArray[ x ].uxBasePriority,
                                                    pxTaskStatusArray[ x ].uxCurrentPriority,
                                                    pxTaskStatusArray[ x ].usStackHighWaterMark,
						    run_time_S(pxTaskStatusArray[ x ].ulRunTimeCounter));
                          }
                     #endif
                }
            }

            ulStatsAsPercentage = ulTotalRunTimeExeptIrq / ulTotalRunTime;
            if ( ulStatsAsPercentage > 1UL )
#ifdef __USE_REENTRANT__
              {

              cmsg( rl," *\tExept/IRQ\t*           *           *\t\t*\t*\t*\t%1.2\t\t%1%%\n",
		                                run_time_S(ulTotalRunTimeExeptIrq),
                                                ulStatsAsPercentage
                                              );
              }
            else
              {
              cmsg( rl," *\tExept/IRQ\t*           *           *\t\t*\t*\t*\t%1.2\t\t<1%%\n",
		                                 run_time_S(ulTotalRunTimeExeptIrq)
                                              );
              }
#else
            {
               cmsg( rl," *\tExept/IRQ\t*               *\t\t*\t*\t*\t%1.2\t\t%1%%\n",
		                                run_time_S(ulTotalRunTimeExeptIrq),
                                                ulStatsAsPercentage
                                               );
            }
          else
            {
               cmsg( rl," *\tExept/IRQ\t*               *\t\t*\t*\t*\t%1.2\t\t<1%%\n",
		                                run_time_S(ulTotalRunTimeExeptIrq)
                                               );
            }
#endif
        }

        /* The array is no longer needed, free the memory it consumes. */
        free( pxTaskStatusArray );
    }
    else
    {
	cmsg( rl,"\tnot another memory for this command\n" ) ;
    }
}
#endif
//------------------------------------------------------------------------------

#ifdef __USE_REENTRANT__
#if ( configUSE_TRACE_FACILITY == 1 )

#include "reentrant.h"

static void task_reent_command_handler ( TReadLine* rl , TReadLine::const_symbol_type_ptr_t* args , const size_t count )
{
TaskStatus_t *pxTaskStatusArray;
volatile UBaseType_t uxArraySize = 0 ;
volatile UBaseType_t  x = 0 ;
unsigned long ulTotalRunTime ;

    /* Take a snapshot of the number of tasks in case it changes while this
    function is executing. */
    uxArraySize = task_utilities_t::number_of_tasks();


    /* Allocate a TaskStatus_t structure for each task.  An array could be
    allocated statically at compile time. */
    pxTaskStatusArray = (TaskStatus_t*)malloc( uxArraySize * sizeof( TaskStatus_t ));

    if( pxTaskStatusArray != NULL )
    {
        /* Generate raw status information about each task. */
        uxArraySize = task_utilities_t::system_state( pxTaskStatusArray, uxArraySize, &ulTotalRunTime );

            /* For each populated position in the pxTaskStatusArray array,
            format the raw data as human readable ASCII data. */
            for( x = 0; x < uxArraySize; x++ )
            {
                cmsg( rl,"\t%s\t0x%8x\n",  pxTaskStatusArray[ x ].pcTaskName, pxTaskStatusArray[ x ].reentrant) ;
                cmsg( rl,"\t\terrno_val   %1\n"
                         "\t\trand_state  %1\n"
			 "\t\tstrtok_pos  0x%8X\n",
			     ((reentrant_t*)pxTaskStatusArray[ x ].reentrant)->errno_val ,
			     ((reentrant_t*)pxTaskStatusArray[ x ].reentrant)->rand_state,
			     (uint32_t)((reentrant_t*)pxTaskStatusArray[ x ].reentrant)->strtok_pos ) ;

            }

        /* The array is no longer needed, free the memory it consumes. */
        free( pxTaskStatusArray );
    }
    else
    {
	cmsg( rl,"\tnot another memory for this command\n" ) ;
    }
}
#endif // __USE_REENTRANT__
#endif // configUSE_TRACE_FACILITY == 1
//------------------------------------------------------------------------------
static void unique_id_command_handler ( TReadLine* rl , TReadLine::const_symbol_type_ptr_t* args , const size_t count )
{
  // TODO реимплементировать
  char id_dfu[16] ;
  devsign.unuque_id_dfu(id_dfu);
  cmsg(rl,"\tdev_id 0x%3X, rev_id 0x%4X, flash size %1 kB\n\tunique_id: %s\n", dbgmcu.dev() , dbgmcu.rev(), devsign.flash_size, id_dfu) ;
}

//------------------------------------------------------------------------------
static void standby_console_command_handler ( TReadLine* rl , TReadLine::const_symbol_type_ptr_t* args , const size_t count )
{
    scheduler_t::stop();
    // TODO реимплементировать
    //HAL_PWR_EnterSTANDBYMode();
}
//------------------------------------------------------------------------------

#if defined __STM32F4XX__
static void protect_console_command_handler ( TReadLine* rl , TReadLine::const_symbol_type_ptr_t* args , const size_t count )
{
  // TODO реимплементировать

    #if 0
    FLASH_OBProgramInitTypeDef Optbyte;
    //TScheduler::EnterCritical();
    HAL_FLASHEx_OBGetConfig(&Optbyte);   // read out RDPLvL

    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);

    switch (Optbyte.RDPLevel)
      {
	 case OB_RDP_LEVEL_0:
	     cmsg(rl,"\tdevice perform RDP level 1 algorithm...\n") ;
             Optbyte.OptionType=OPTIONBYTE_RDP; // select RDP optionbyte
             Optbyte.RDPLevel=OB_RDP_LEVEL_1;   // select RDP level 1



             HAL_FLASH_Unlock();                // unlock Flash
             HAL_FLASH_OB_Lock();
             if ( HAL_FLASH_OB_Unlock() != HAL_OK)             // unlock Optionbytes
               {
        	 cmsg(rl,"\tflash ob unlock error\n") ;
               }
             if ( HAL_FLASHEx_OBProgram(&Optbyte)!= HAL_OK)    // set RDP=1
               {
         	 cmsg(rl,"\tflash ob programm error\n") ;
               }
             if ( HAL_FLASH_OB_Launch()!= HAL_OK)    // write OB to Flash and reset
               {
        	 cmsg(rl,"\tflash ob launch error\n") ;
               }
             HAL_FLASH_OB_Lock();               // Lock Optionbytes
             HAL_FLASH_Lock();                  // lock Flash
             asm volatile
	       (
                 "dsb\n"
                 "isb\n"
               );
             cmsg(rl,"\tdevice is reseting...\n") ;
             TTask::Delay(100);
             scb.application_interrupt_and_reset_control.system_reset();
             break ;
	  case OB_RDP_LEVEL_1:
	     if ( strcmp(args[1],"unlock") )
	        cmsg(rl,"\tprotect state is OB_RDP_LEVEL_1\n") ;
	     else
	       {
	     cmsg(rl,"\tdevice perform RDP level 0 & erase algorithm...\n") ;
	     Optbyte.OptionType=OPTIONBYTE_RDP; // select RDP optionbyte
	     Optbyte.RDPLevel=OB_RDP_LEVEL_0;   // select RDP level 0
	     HAL_FLASH_Unlock();                // unlock Flash
	     HAL_FLASH_OB_Lock();
	                  if ( HAL_FLASH_OB_Unlock() != HAL_OK)             // unlock Optionbytes
	                    {
	             	       cmsg(rl,"\tflash ob unlock error\n") ;
	                    }
	                  if ( HAL_FLASHEx_OBProgram(&Optbyte)!= HAL_OK)    // set RDP=1
	                    {
	             	       cmsg(rl,"\tflash ob programm error\n") ;
	                    }
	                  if ( HAL_FLASH_OB_Launch()!= HAL_OK)    // write OB to Flash and reset
	                    {
	             	 cmsg(rl,"\tflash ob launch error\n") ;
	                    }
	                  HAL_FLASH_OB_Lock();               // Lock Optionbytes
	                  HAL_FLASH_Lock();                  // lock Flash


	/*
	                  //
	                  //set RDP level 2                   WRP for sectors 0 and 1
	if ((((*OPTION_BYTES_1) & 0xFFFF) == 0xCCFF) && (((*OPTION_BYTES_2) & 0xFFFF) == 0xFFFC)) {
		return; // already set up correctly - bail out
	}*
	flash_unlock_option_bytes();
	//                                 WRP +    RDP
	flash_program_option_bytes( 0xFFFC0000 + 0xCCFF);
	flash_lock_option_bytes();
	                  */
	                  asm volatile
	     	       (
	                      "dsb\n"
	                      "isb\n"
	                    );
	                  cmsg(rl,"\tdevice is reseting...\n") ;
	                  TTask::Delay(100);
	                  scb.application_interrupt_and_reset_control.system_reset();
	       }
	                  break ;

	  case OB_RDP_LEVEL_2:
	    cmsg(rl,"\tprotect state is OB_RDP_LEVEL_2\n") ;
	    break ;
	  default:
	    cmsg(rl,"\tprotect state unknown, val is 0x%8X \n") ;
      }
    //TScheduler::ExitCritical();
    #endif
}
#endif
//------------------------------------------------------------------------------
static void __RAMFUNC__ erase_console_command_handler ( TReadLine* rl , TReadLine::const_symbol_type_ptr_t* args , const size_t count )
{
  cmsg(rl,"FLASH will be erased and all non volatile programm and data losted, device will be damaged! continue[N/y]?\n");
  int c ;
  rl->RecvChar(c);
  if  (c != 'y')
    return ;

  cmsg(rl,"\tmass erase performed...\n") ;

  flash.mass_erase();

  scb.system_reset();
  isb();
  dsb();
  dmb();
}

//------------------------------------------------------------------------------
static void IwdtResetTimerCallback( TimerHandle_t pxTimer )
{
   idwg.reset();
}
//------------------------------------------------------------------------------
static void iwdg_console_command_handler ( TReadLine* rl , TReadLine::const_symbol_type_ptr_t* args , const size_t count )
{
    static TimerHandle_t iwdg_reset_timer = NULL ;

    if ( !iwdg_reset_timer )
      {
	// create iwdt
	iwdg_reset_timer = xTimerCreate  ( "IWDGTimer", configTICK_RATE_HZ , pdTRUE, ( void * ) NULL , IwdtResetTimerCallback );
	xTimerStart( iwdg_reset_timer, 0 ) ;

	idwg.period_ms(configTICK_RATE_HZ*2);
	idwg.start();

	cmsg(rl,"\tiwdg create and started\n") ;

      }
    else
      {
	cmsg(rl,"\tiwdg is started\n") ;
      }
}
//------------------------------------------------------------------------------
#ifdef __EEPROM_16K_FLASH_SECTOR_A__
  #include "apptypes.h" //eeprom utility
  static void eeprom_console_command_handler ( TReadLine* rl , TReadLine::const_symbol_type_ptr_t* args , const size_t count )
     {
        // TODO
        //cmsg(rl,"\tcrc32: 0x%8x 0x%8x\n", application_storage.crc ,application_storage.get_crc()) ;
        //cmsg(rl,"\tvalid: %s\n",    application_storage.check_crc() ? "true" : "false");
     }
#endif

#ifdef __STM32F4XX__

  static void rng_console_command_handler ( TReadLine* rl , TReadLine::const_symbol_type_ptr_t* args , const size_t count )
       {
          cmsg(rl,"\t0x%8x\n",  rng.read() ) ;
       }

  static void rngf_console_command_handler ( TReadLine* rl , TReadLine::const_symbol_type_ptr_t* args , const size_t count )
         {
            cmsg(rl,"\t%1.7\n", rng.readf() ) ;
         }
#endif


 static void srand_console_command_handler ( TReadLine* rl , TReadLine::const_symbol_type_ptr_t* args , const size_t count )
       {
          if ( count )
            {
     	      long i ;
     	      char* endptr ;
     	      i = strtol(args[1], &endptr,10);
     	      if ( endptr != args[1] )
     		{
     		  srand(i);
     		}
            }
       }

  static void rand_console_command_handler ( TReadLine* rl , TReadLine::const_symbol_type_ptr_t* args , const size_t count )
       {
          cmsg(rl,"\t0x%8x\n", rand() ) ;
       }

  static void randf_console_command_handler ( TReadLine* rl , TReadLine::const_symbol_type_ptr_t* args , const size_t count )
       {
          cmsg(rl,"\t%1.7\n", randf() ) ;
       }


  static void rcc_csr_console_command_handler ( TReadLine* rl , TReadLine::const_symbol_type_ptr_t* args , const size_t count )
       {
          if (rcc.bor_reset()==rcc_t::clock_control_status_t::bor_reset_t::occured) {  cmsg(rl,"\tBOR reset\n"); } ;
          if (rcc.nrst_reset()==rcc_t::clock_control_status_t::nrst_reset_t::occured) {  cmsg(rl,"\tNRST reset\n"); } ;
          if (rcc.por_pdr_reset()==rcc_t::clock_control_status_t::por_pdr_reset_t::occured) {  cmsg(rl,"\tPOR/PDR reset\n"); } ;
          if (rcc.software_reset()==rcc_t::clock_control_status_t::software_reset_t::occured) {  cmsg(rl,"\tSOFTWARE reset\n"); } ;
          if (rcc.iwdg_reset()==rcc_t::clock_control_status_t::iwdg_reset_t::occured) {  cmsg(rl,"\tIWDG reset\n"); } ;
          if (rcc.wwdg_reset()==rcc_t::clock_control_status_t::wwdg_reset_t::occured) {  cmsg(rl,"\tWWDG reset\n"); } ;
          if (rcc.lpmr_reset()==rcc_t::clock_control_status_t::lpmr_reset_t::occured) {  cmsg(rl,"\tLPMR reset\n"); } ;
       }

//------------------------------------------------------------------------------

void SetConsoleCmdDefaultHandlers(TReadLine* rl)
{
    rl->AddCommandHandler("echo", echo_command_handler, true);

    rl->AddCommandHandler("help" , help_command_handler, true);
    rl->AddCommandHandler("reset" , reset_command_handler, true,"reset device");
    rl->AddCommandHandler("ver" , version_command_handler, true);
    rl->AddCommandHandler("dev" , dev_inf_command_handler, true);
    #if ( configGENERATE_RUN_TIME_STATS == 1 )
       rl->AddCommandHandler("time" , time_command_handler, true);
    #endif
    rl->AddCommandHandler("heap",    heap_walk_command_handler,true, "walk heap and get info");
    #if (configGENERATE_RUN_TIME_STATS == 1)
    rl->AddCommandHandler("sys", sys_command_handler, true);
    #endif
    #ifdef __USE_REENTRANT__
       rl->AddCommandHandler("reent", task_reent_command_handler, true);
    #endif
    rl->AddCommandHandler("id", unique_id_command_handler, true);
    rl->AddCommandHandler("standby" , standby_console_command_handler, true);
    #if defined __STM32F4XX__
      rl->AddCommandHandler("protect" , protect_console_command_handler, true);
      rl->AddCommandHandler("erase" , erase_console_command_handler, true);
    #endif
    rl->AddCommandHandler("iwdg" , iwdg_console_command_handler, true, "create and start IWDG 2sec period and reset FreeRTOS 1sec timer if not yet");
    #ifdef __EEPROM_16K_FLASH_SECTOR_A__
       rl->AddCommandHandler("eeprom" , eeprom_console_command_handler, true);
    #endif
    #ifdef __STM32F4XX__
       // need for 'rng' command
       rcc.rng_enable();
       rng.state_enable();

       rl->AddCommandHandler("rng", rng_console_command_handler, true);
       rl->AddCommandHandler("rngf", rngf_console_command_handler, true);
    #endif
       rl->AddCommandHandler("srand", srand_console_command_handler, true, "seed pseudo random generator state");
       rl->AddCommandHandler("rand",  rand_console_command_handler, true, "get pseudo random int value");
       rl->AddCommandHandler("randf", randf_console_command_handler, true, "get pseudo random float value");

       rl->AddCommandHandler("rcc_csr", rcc_csr_console_command_handler, true);


}

//------------------------------------------------------------------------------

