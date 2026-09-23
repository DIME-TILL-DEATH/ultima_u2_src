#ifndef __TASK_H__
#define __TASK_H__

#include "FreeRTOS_headers.h"

#include "supc++.h" // operator new implimentation

namespace freertos

{

class scheduler_t
  {
    public:
    // --- Kernel Control API

    static inline void yeld()
          {
            taskYIELD() ;
          }
    static inline void yeld_from_isr (BaseType_t HigherPriorityTaskWoken)
          {
            portYIELD_FROM_ISR( HigherPriorityTaskWoken );
          }
    static inline void enter_critical()
          {
            taskENTER_CRITICAL() ;
          }
    static inline void exit_critical()
          {
           taskEXIT_CRITICAL() ;
          }
    static inline void disable_interrupt()
          {
           taskDISABLE_INTERRUPTS();
          }
    static inline void enable_interrupt()
          {
           taskENABLE_INTERRUPTS() ;
          }

    static inline void start()
              {
                 vTaskStartScheduler() ;
              }
    static inline void stop()
              {
                 vTaskEndScheduler() ;
              }
    static inline void suspend_all()
              {
                 vTaskSuspendAll() ;
              };
    static inline portBASE_TYPE resume_all()
              {
                 return xTaskResumeAll() ;
              }

    static inline void task_step_tick( TickType_t xTicksToJump )
    	      {
    	 	 vTaskStepTick( xTicksToJump );
    	      }
  };

class task_utilities_t
  {
    public:

      enum scheduler_state_t { not_started = 0, running, suspend }  ;
#if ( configUSE_TRACE_FACILITY == 1 )
      static inline unsigned portBASE_TYPE system_state( TaskStatus_t *pxTaskStatusArray, UBaseType_t uxArraySize, unsigned long *pulTotalRunTime)
          {
             return uxTaskGetSystemState( pxTaskStatusArray, uxArraySize, pulTotalRunTime );
          }
#endif
      static inline void task_info( TaskHandle_t xTask,TaskStatus_t *pxTaskStatus,BaseType_t xGetFreeStackSpace,eTaskState eState )
          {
	     vTaskGetInfo( xTask, pxTaskStatus, xGetFreeStackSpace, eState );
          }
      static inline TaskHandle_t current_task_handle()
          {
            return xTaskGetCurrentTaskHandle();
          }
      static inline TaskHandle_t idle_task_handle()
          {
            return xTaskGetIdleTaskHandle();
          }
      static inline unsigned portBASE_TYPE stack_high_water_mark( TaskHandle_t xTask = NULL )
          {
            return uxTaskGetStackHighWaterMark(xTask);
          }
      static inline eTaskState task_state( TaskHandle_t xTask = NULL )
          {
            return eTaskGetState(xTask);
          }
      static inline char* task_name( TaskHandle_t xTask = NULL )
          {
            return (char*)pcTaskGetTaskName(xTask);
          }
      static inline TaskHandle_t  handle( const char* Name)
          {
            return xTaskGetHandle(Name);
          }
      static inline TickType_t tick_count()
          {
            return xTaskGetTickCount();
          }
      static inline TickType_t tick_count_from_isr()
          {
            return xTaskGetTickCountFromISR();
          }
      static inline scheduler_state_t scheduler_state()
          {
            return (scheduler_state_t) xTaskGetSchedulerState() ;
          }
      static inline unsigned portBASE_TYPE number_of_tasks()
          {
            return uxTaskGetNumberOfTasks();
          }
      static inline void task_list( char  *pcWriteBuffer )
          {
            vTaskList( pcWriteBuffer );
          }
      static inline void run_time_stats( char  *pcWriteBuffer )
          {
	    vTaskGetRunTimeStats( pcWriteBuffer );
          }
#if configUSE_APPLICATION_TASK_TAG == 1
      static inline void application_task_tag(TaskHandle_t xTask, TaskHookFunction_t pxTagValue )
          {
	    vTaskSetApplicationTaskTag(xTask, pxTagValue);
          }
      static inline TaskHookFunction_t application_task_tag(TaskHandle_t xTask )
          {
	     return xTaskGetApplicationTaskTag(xTask);
          }
#endif
      static inline BaseType_t call_application_task_hook(TaskHandle_t xTask, void *pvParameter )
          {
      	     return xTaskCallApplicationTaskHook(xTask, pvParameter);
          }
#if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 )
      static inline void* thread_local_storage_pointer(TaskHandle_t xTask, BaseType_t xIndex )
          {
      	     return pvTaskGetThreadLocalStoragePointer(xTask, xIndex);
          }
      static inline void  thread_local_storage_pointer(TaskHandle_t xTask, BaseType_t xIndex,  void *pvValue)
          {
	     vTaskSetThreadLocalStoragePointer( xTask,  xIndex,  pvValue);
          }
#endif
      static inline void timeout_state(TimeOut_t * const pxTimeOut)
          {
	     vTaskSetTimeOutState( pxTimeOut );
          }
      static inline BaseType_t check_for_timeout(TimeOut_t * const pxTimeOut, TickType_t * const pxTicksToWait )
          {
             return xTaskCheckForTimeOut(pxTimeOut, pxTicksToWait);
          }
  };

class critical_section_t
	{
		public:
                     critical_section_t() { scheduler_t::enter_critical() ; }
                    ~critical_section_t() { scheduler_t::exit_critical() ; }
	};

class queue_set_t ;
class queue_t
  {
	private:
		QueueHandle_t handle ;
	public:
		friend queue_set_t ;

		enum queue_send_result_t { send_pass = pdTRUE , full = errQUEUE_FULL }  ;
		enum queue_receive_result_t { receive_pass = pdTRUE , empty=errQUEUE_EMPTY }  ;

		inline queue_t ( UBaseType_t uxQueueLength, UBaseType_t uxItemSize )
			{
				handle = xQueueCreate( uxQueueLength , uxItemSize ) ;
			}
		inline ~queue_t ()
			{
				vQueueDelete( handle );
				handle = NULL ;
			}

	        bool inline is_owner(const void* obj) { return handle == obj ; }
	        bool inline is_created() { return (bool)handle ; }

		static inline UBaseType_t  messages_waiting_from_task(const QueueHandle_t xQueue)
			{
				return uxQueueMessagesWaiting (xQueue) ;
			}
		inline UBaseType_t  messages_waiting_from_task()
			{
				return uxQueueMessagesWaiting (handle) ;
			}

		static inline UBaseType_t messages_waiting_from_isr( const QueueHandle_t xQueue )
                        {
		              return uxQueueMessagesWaitingFromISR( xQueue ) ;
                        }

		inline UBaseType_t messages_waiting_from_isr()
		        {
			       return uxQueueMessagesWaitingFromISR( handle ) ;
		        }

		static inline UBaseType_t  messages_waiting(const QueueHandle_t xQueue)
		      {
		         if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
		            {
		              return uxQueueMessagesWaiting (xQueue) ;
		            }
		         else
		            {
		              return uxQueueMessagesWaitingFromISR( xQueue ) ;
		            }
		      }
		inline UBaseType_t  messages_waiting()
		      {
		         if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
		            {
		               return uxQueueMessagesWaiting (handle) ;
		            }
		         else
		            {
		               return uxQueueMessagesWaitingFromISR( handle ) ;
		            }
		      }

		static inline UBaseType_t  reset(const QueueHandle_t xQueue)
		      {
	         	     return xQueueReset(xQueue) ;
		      }
		inline UBaseType_t  reset()
		      {
                             return xQueueReset (handle) ;
		      }

		static inline UBaseType_t spaces_available(QueueHandle_t xQueue)
                       {
		              return uxQueueSpacesAvailable(xQueue );
                       }

		inline UBaseType_t spaces_available()
                       {
                              return uxQueueSpacesAvailable(handle);
                       }


		static inline queue_send_result_t  send_to_back_from_task(QueueHandle_t xQueue , const void * pvItemToQueue , TickType_t xTicksToWait )
			{
				return (queue_send_result_t)xQueueSendToBack( xQueue , pvItemToQueue, xTicksToWait ) ;
			}
		static inline queue_send_result_t  send_to_back_from_isr (QueueHandle_t xQueue, const void *pvItemToQueue, BaseType_t *pxHigherPriorityTaskWoken )
                        {
                                return (queue_send_result_t) xQueueSendToBackFromISR( xQueue , pvItemToQueue, pxHigherPriorityTaskWoken ) ;
                        }

		static inline queue_send_result_t  send_to_back(QueueHandle_t xQueue , const void * pvItemToQueue , TickType_t xTicksToWait )
		        {
		            if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
                              {
                                 return send_to_back_from_task( xQueue , pvItemToQueue, xTicksToWait ) ;
                              }
                            else
                              {
                                 // send command from ISR
                                 BaseType_t HigherPriorityTaskWoken ;
                                 queue_send_result_t result  = send_to_back_from_isr(xQueue , pvItemToQueue, &HigherPriorityTaskWoken);
                                 portYIELD_FROM_ISR( HigherPriorityTaskWoken ) ;
                                 return result ;
                              }
		        }

                inline queue_send_result_t  send_to_back_from_task(const void * pvItemToQueue , TickType_t xTicksToWait )
                        {
                            return (queue_send_result_t)send_to_back_from_task( handle , pvItemToQueue, xTicksToWait ) ;
                        }
                inline queue_send_result_t  send_to_back_from_isr (const void *pvItemToQueue, BaseType_t *pxHigherPriorityTaskWoken )
                        {
                            return (queue_send_result_t) send_to_back_from_isr( handle , pvItemToQueue, pxHigherPriorityTaskWoken ) ;
                        }

                inline queue_send_result_t  send_to_back(const void * pvItemToQueue , TickType_t xTicksToWait )
                        {
                            if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
                               {
                                 return send_to_back_from_task(pvItemToQueue, xTicksToWait ) ;
                               }
                            else
                               {
                                 // send command from ISR
                                 BaseType_t HigherPriorityTaskWoken ;
                                 queue_send_result_t result  = send_to_back_from_isr(pvItemToQueue, &HigherPriorityTaskWoken);
                                 portYIELD_FROM_ISR( HigherPriorityTaskWoken ) ;
                                 return result ;
                               }
                        }

		static inline queue_send_result_t  send_to_front_from_task(QueueHandle_t xQueue, const void * pvItemToQueue , TickType_t xTicksToWait )
			{
		            return (queue_send_result_t) xQueueSendToFront( xQueue , pvItemToQueue, xTicksToWait ) ;
			}
		static inline queue_send_result_t  send_to_front_from_isr (QueueHandle_t xQueue, const void *pvItemToQueue, BaseType_t *pxHigherPriorityTaskWoken )
		        {
		            return (queue_send_result_t) xQueueSendToFrontFromISR( xQueue , pvItemToQueue, pxHigherPriorityTaskWoken ) ;
		        }

		static inline queue_send_result_t  send_to_front(QueueHandle_t xQueue , const void * pvItemToQueue , TickType_t xTicksToWait )
		        {
		            if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
		               {
		                  return (queue_send_result_t)send_to_front_from_task( xQueue , pvItemToQueue, xTicksToWait ) ;
		               }
		            else
		               {
		                  // send command from ISR
		                  BaseType_t HigherPriorityTaskWoken ;
		                  queue_send_result_t result  = send_to_front_from_isr(xQueue , pvItemToQueue, &HigherPriorityTaskWoken);
		                  portYIELD_FROM_ISR( HigherPriorityTaskWoken ) ;
		                  return result ;
		               }
		        }

		inline queue_send_result_t  send_to_front_from_task(const void * pvItemToQueue , TickType_t xTicksToWait )
			{
		            return send_to_front_from_task( handle , pvItemToQueue, xTicksToWait ) ;
			}

		inline queue_send_result_t  send_to_front_from_isr (const void *pvItemToQueue, BaseType_t *pxHigherPriorityTaskWoken )
		        {
		            return send_to_front_from_isr( handle , pvItemToQueue, pxHigherPriorityTaskWoken ) ;
		        }

		inline queue_send_result_t  send_to_front(const void * pvItemToQueue , TickType_t xTicksToWait )
                        {
                            if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
                               {
                                  return send_to_front_from_task(pvItemToQueue, xTicksToWait ) ;
                               }
                            else
                               {
                                  // send command from ISR
                                  BaseType_t HigherPriorityTaskWoken ;
                                  queue_send_result_t result  = send_to_front_from_isr(pvItemToQueue, &HigherPriorityTaskWoken);
                                  portYIELD_FROM_ISR( HigherPriorityTaskWoken ) ;
                                  return result ;
                               }
                         }

		static inline queue_receive_result_t  receive_from_task (QueueHandle_t xQueue, void * pvBuffer , TickType_t xTicksToWait )
			{
				return (queue_receive_result_t) xQueueReceive( xQueue , pvBuffer, xTicksToWait ) ;
			}
                static inline queue_receive_result_t  receive_from_isr (QueueHandle_t xQueue, void *pvBuffer, BaseType_t *pxTaskWoken )
                        {
                                return (queue_receive_result_t) xQueueReceiveFromISR( xQueue , pvBuffer, pxTaskWoken ) ;
                        }

                static inline queue_receive_result_t  receive_from(QueueHandle_t xQueue, void * pvBuffer , TickType_t xTicksToWait)
                        {
                            if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
                               {
                                  return receive_from_task( xQueue , pvBuffer, xTicksToWait ) ;
                               }
                            else
                               {
                                  // receive command from ISR
                                  BaseType_t HigherPriorityTaskWoken ;
                                  queue_receive_result_t result  = receive_from_isr(xQueue , pvBuffer, &HigherPriorityTaskWoken);
                                  portYIELD_FROM_ISR( HigherPriorityTaskWoken ) ;
                                  return result ;
                               }
                         }

		inline queue_receive_result_t  receive_from_task (void * pvBuffer , TickType_t xTicksToWait )
			{
			   return receive_from_task( handle , pvBuffer, xTicksToWait ) ;
			}
                inline queue_receive_result_t  receive_from_isr (void *pvBuffer, BaseType_t *pxTaskWoken )
                        {
                           return receive_from_isr( handle , pvBuffer, pxTaskWoken ) ;
                        }

                inline queue_receive_result_t  receive(void * pvBuffer , TickType_t xTicksToWait )
                        {
                            if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
                               {
                                  return receive_from_task(pvBuffer, xTicksToWait ) ;
                               }
                            else
                               {
                                  // receive command from ISR
                                  BaseType_t HigherPriorityTaskWoken ;
                                  queue_receive_result_t result  = receive_from_isr(pvBuffer, &HigherPriorityTaskWoken);
                                  portYIELD_FROM_ISR( HigherPriorityTaskWoken ) ;
                                  return result ;
                               }
                         }



		static inline  queue_receive_result_t  peak_from_task (QueueHandle_t xQueue, void * pvBuffer , TickType_t xTicksToWait )
			{
				return (queue_receive_result_t) xQueuePeek( xQueue , pvBuffer, xTicksToWait ) ;
			}
		static inline  queue_receive_result_t  peak_from_isr (QueueHandle_t xQueue, void * pvBuffer)
			{
				return (queue_receive_result_t) xQueuePeekFromISR( xQueue , pvBuffer ) ;
			}
		static inline  queue_receive_result_t peak(QueueHandle_t xQueue, void * pvBuffer , TickType_t xTicksToWait )
                        {
                            if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
                               {
                                  return peak_from_task( xQueue , pvBuffer, xTicksToWait );
                               }
                            else
                               {
                                  // receive command from ISR
                                  BaseType_t HigherPriorityTaskWoken ;
                                  queue_receive_result_t result  = peak_from_isr(xQueue, pvBuffer);
                                  portYIELD_FROM_ISR( HigherPriorityTaskWoken ) ;
                                  return result ;
                               }
                         }


		inline  queue_receive_result_t  peak_from_task (void * pvBuffer , TickType_t xTicksToWait )
			{
				return peak_from_task( handle , pvBuffer, xTicksToWait ) ;
			}
		inline  queue_receive_result_t  peak_from_isr (void * pvBuffer )
			{
				return peak_from_isr( handle , pvBuffer ) ;
			}
		inline  queue_receive_result_t peak(void * pvBuffer , TickType_t xTicksToWait )
                        {
                            if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
                               {
                                  return peak_from_task(pvBuffer, xTicksToWait );
                               }
                            else
                               {
                                  // receive command from ISR
                                  return peak_from_isr(pvBuffer);
                               }
                         }




		static inline void  add_to_registry (QueueHandle_t xQueue, const char *pcQueueName)
			{
				 vQueueAddToRegistry( xQueue , pcQueueName ) ;
			}
		inline void  add_to_registry (const char *pcQueueName)
			{
				 vQueueAddToRegistry( handle , pcQueueName ) ;
			}

		static inline void remove_from_registry (QueueHandle_t xQueue )
			{
				vQueueUnregisterQueue( xQueue ) ;
			}
		inline void remove_from_registry ()
			{
				vQueueUnregisterQueue( handle ) ;
			}

  };

class semaphore_counting_t
  {
     private:
     protected:
        QueueHandle_t handle ;
     public:
        inline semaphore_counting_t ( UBaseType_t count, UBaseType_t init) { handle = xSemaphoreCreateCounting( count, init ) ; }
        inline virtual ~semaphore_counting_t () { vSemaphoreDelete(handle); }

        bool inline is_owner(const void* obj) { return handle == obj ; }
        bool inline is_created() { return (bool)handle ; }

        inline UBaseType_t count()
           {
              return uxSemaphoreGetCount(handle);
           }

	inline BaseType_t take_from_task (TickType_t  BlockTime = portMAX_DELAY) { return xSemaphoreTake( handle, BlockTime ) ; }
        inline BaseType_t take_from_isr ( BaseType_t* const HigherPriorityTaskWoken ) { return xSemaphoreTakeFromISR( handle, HigherPriorityTaskWoken ); }
        inline BaseType_t take(TickType_t BlockTime = portMAX_DELAY)
                {
                   if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
                     {
                        return take_from_task(BlockTime) ;
                     }
                   else
                     {
                        // give comand from ISR
                        BaseType_t HigherPriorityTaskWoken ;
                        BaseType_t result  = take_from_isr(&HigherPriorityTaskWoken);
                        portYIELD_FROM_ISR( HigherPriorityTaskWoken ) ;
                        return result ;
                     }
               }

	inline BaseType_t give_from_task () { return xSemaphoreGive( handle ) ; }
        inline BaseType_t give_from_isr ( BaseType_t*  const HigherPriorityTaskWoken ) { return xSemaphoreGiveFromISR( handle, HigherPriorityTaskWoken ); }
        inline BaseType_t give()
                {
                   if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
                     {
                        return give_from_task() ;
                     }
                   else
                     {
                        // give comand from ISR
                        BaseType_t HigherPriorityTaskWoken ;
                        BaseType_t result  = give_from_isr(&HigherPriorityTaskWoken);
                        portYIELD_FROM_ISR( HigherPriorityTaskWoken ) ;
                        return result ;
                     }
               }

	static inline void  add_to_registry (semaphore_counting_t* sem, const char *pcQueueName)
		{
			 vQueueAddToRegistry( sem->handle , pcQueueName ) ;
		}
	inline void  add_to_registry (const char *pcQueueName)
		{
			 vQueueAddToRegistry( handle , pcQueueName ) ;
		}

	static inline void remove_from_registry (semaphore_counting_t* sem )
		{
			vQueueUnregisterQueue( sem->handle ) ;
		}
	inline void remove_from_registry ()
		{
			vQueueUnregisterQueue( handle ) ;
		}
  };

class semaphore_binary_t : public semaphore_counting_t
  {
     private:
     protected:
     public:
        enum state_t { taked=0,gived } ;
        inline semaphore_binary_t (state_t state = gived) : semaphore_counting_t(1,state) {} ;

        friend queue_set_t ;

  };


class mutex_t
  {
     private:
     protected:
        QueueHandle_t handle ;
     public:
        inline mutex_t () { handle = xSemaphoreCreateMutex () ; }
        inline virtual ~mutex_t () { vSemaphoreDelete(handle); }

        bool inline is_owner(const void* obj) { return handle == obj ; }
        bool inline is_created() { return (bool)handle ; }

        inline TaskHandle_t holder() { return xSemaphoreGetMutexHolder( handle ); }
        inline BaseType_t take (TickType_t  BlockTime = portMAX_DELAY) { return xSemaphoreTake( handle, BlockTime ) ; }
        inline BaseType_t give () { return xSemaphoreGive( handle ) ; }

  };

class recursive_mutex_t
  {
     private:
     protected:
        QueueHandle_t handle ;
     public:
        inline recursive_mutex_t () { handle = xSemaphoreCreateRecursiveMutex () ; }
        inline virtual ~recursive_mutex_t () { vSemaphoreDelete(handle); }

        bool inline is_owner(const void* obj) { return handle == obj ; }
        bool inline is_created() { return (bool)handle ; }

        inline TaskHandle_t holder() { return xSemaphoreGetMutexHolder( handle ); }
        inline BaseType_t take_recursive ( TickType_t  BlockTime = portMAX_DELAY) { return xSemaphoreTakeRecursive( handle , BlockTime ) ; }
        inline BaseType_t give_recursive () { return xSemaphoreGiveRecursive( handle ) ; }
  };


#if ( configUSE_QUEUE_SETS != 0 )

class queue_set_t
  {
	private:
		QueueSethandle_t handle ;
	public:
                enum result_t { pass = pdPASS , fail = pdFAIL }  ;

		inline queue_set_t ( const UBaseType_t uxEventQueueLength )
			{
				handle = xQueueCreateSet( uxEventQueueLength) ;
			}
		inline ~queue_set_t ()
			{
				vQueueDelete( handle );
				handle = NULL ;
			}

	        bool inline is_owner(const void* obj) { return handle == obj ; }
	        bool inline is_created() { return (bool)handle ; }


		static inline result_t add ( semaphore_binary_t* SemaphoreBinary,   QueueSethandle_t xQueueSet )
			{
				return (queue_set_tResult) xQueueAddToSet( SemaphoreBinary->handle, xQueueSet) ;
			}

                inline result_t add ( semaphore_binary_t* SemaphoreBinary )
			{
				return (result_t) xQueueAddToSet( SemaphoreBinary->handle, handle) ;
			}

		static inline result_t add ( queue_t* Queue,   QueueSethandle_t xQueueSet )
			{
				return (result_t) xQueueAddToSet( Queue->handle, xQueueSet) ;
			}

                inline result_t add ( queue_t* Queue )
			{
				return (result_t) xQueueAddToSet( Queue->handle, handle) ;
			}



		static inline result_t remove ( semaphore_binary_t* SemaphoreBinary,   QueueSethandle_t xQueueSet )
			{
				return (result_t) xQueueRemoveFromSet( SemaphoreBinary->handle, xQueueSet) ;
			}

                inline result_t remove ( semaphore_binary_t* SemaphoreBinary )
			{
				return (result_t) xQueueRemoveFromSet( SemaphoreBinary->handle, handle) ;
			}

		static inline queue_set_tResult remove ( queue_t* Queue,   QueueSethandle_t xQueueSet )
			{
				return (result_t) xQueueRemoveFromSet( Queue->handle, xQueueSet) ;
			}

                inline queue_set_tResult remove ( queue_t* Queue )
			{
				return (result_t) xQueueRemoveFromSet( Queue->handle, handle) ;
			}




		static inline void* select_from_task ( queue_set_t* QueueSet, const TickType_t xTicksToWait )
			{
				return xQueueSelectFromSet( QueueSet->handle, xTicksToWait) ;
			}

		static inline void* select_from_isr ( queue_set_t* QueueSet )
			{
				return xQueueSelectFromSetFromISR( QueueSet->handle) ;
			}

                static inline void* select (queue_set_t* QueueSet, const TickType_t xTicksToWait = 0)
			{
			    if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
                              {
                                 return xQueueSelectFromSet( QueueSet->handle, xTicksToWait) ;
                              }
                            else
                              {
                                 // select comand from ISR
                                 return xQueueSelectFromSetFromISR( QueueSet->handle) ;
                              }
			}

		inline void* select_from_task ( const TickType_t xTicksToWait )
			{
				return select_from_task( handle, xTicksToWait) ;
			}

		inline void* select_from_isr ()
			{
				return select_from_isr( handle) ;
			}

                inline void* select ( const TickType_t xTicksToWait = 0 )
			{
			    if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
                              {
                                 return select_from_task( handle, xTicksToWait) ;
                              }
                            else
                              {
                                 // select comand from ISR
                                 return select_from_isr( handle) ;
                              }
			}
  };
#endif


class sofware_timer_t
	{
		private:
                        TimerHandle_t handle ;
		public:
                        enum sofware_timer_command_result_t { pass = pdTRUE , fail = pdFAIL }  ;

			inline sofware_timer_t ( const char* const name , const TickType_t TimerPeriod, const UBaseType_t AutoReload, void * const TimerID, TimerCallbackFunction_t CallbackFunction  )
				{
				        handle = xTimerCreate  ( name, TimerPeriod , AutoReload, TimerID , CallbackFunction );
				}
			inline ~sofware_timer_t ()
				{
					xTimerDelete(handle, portMAX_DELAY);
					handle = NULL ;
				}

		        bool inline is_owner(const void* obj) { return handle == obj ; }
		        bool inline is_created() { return (bool)handle ; }

			static TimerHandle_t create(const char* const name , const TickType_t TimerPeriod, const UBaseType_t AutoReload, void * const TimerID, TimerCallbackFunction_t CallbackFunction)
			        {
			               TimerHandle_t handle = xTimerCreate  ( name, TimerPeriod , AutoReload, TimerID , CallbackFunction );
			               start( handle, portMAX_DELAY) ;
			               return handle ;
			        }


			inline TimerHandle_t get_handle() { return handle ; }


			static inline BaseType_t is_active( TimerHandle_t handle)
			        {
			                return xTimerIsTimerActive( handle) ;
			        }
			inline BaseType_t is_active()
				{
					return xTimerIsTimerActive( handle) ;
				}

			static inline TickType_t period( const TimerHandle_t handle)
			        {
			                return xTimerGetPeriod( handle) ;
			        }
			inline TickType_t period()
				{
					return xTimerGetPeriod( handle) ;
				}

			static inline sofware_timer_command_result_t period_from_task( TimerHandle_t handle, TickType_t NewPeriod, TickType_t BlockTime)
			        {
			                return (sofware_timer_command_result_t) xTimerChangePeriod( handle, NewPeriod, BlockTime) ;
			        }
			inline sofware_timer_command_result_t period_from_task(TickType_t NewPeriod, TickType_t BlockTime)
				{
					return (sofware_timer_command_result_t) xTimerChangePeriod( handle, NewPeriod, BlockTime) ;
				}

			static inline sofware_timer_command_result_t period_from_isr( TimerHandle_t handle, TickType_t NewPeriod, BaseType_t *HigherPriorityTaskWoken)
			        {
			                return (sofware_timer_command_result_t) xTimerChangePeriodFromISR( handle, NewPeriod, HigherPriorityTaskWoken) ;
			        }
			inline sofware_timer_command_result_t period_from_isr(TickType_t NewPeriod, BaseType_t *HigherPriorityTaskWoken)
				{
					return (sofware_timer_command_result_t) xTimerChangePeriodFromISR( handle, NewPeriod, HigherPriorityTaskWoken) ;
				}

		        static inline sofware_timer_command_result_t period( TimerHandle_t handle, TickType_t NewPeriod, TickType_t BlockTime )
		                {
		                   if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
		                     {
		                        return period_from_task(handle, NewPeriod, BlockTime) ;
		                     }
		                   else
		                     {
		                        // give comand from ISR
		                        BaseType_t HigherPriorityTaskWoken ;
		                        sofware_timer_command_result_t result  = period_from_isr(handle, NewPeriod, &HigherPriorityTaskWoken);
		                        portYIELD_FROM_ISR( HigherPriorityTaskWoken ) ;
		                        return result ;
		                     }
		               }

		        inline sofware_timer_command_result_t period(TickType_t NewPeriod, TickType_t BlockTime)
		                {
		                   if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
		                     {
		                        return period_from_task(NewPeriod, BlockTime) ;
		                     }
		                   else
		                     {
		                        // give comand from ISR
		                        BaseType_t HigherPriorityTaskWoken ;
		                        sofware_timer_command_result_t result  = period_from_isr(NewPeriod, &HigherPriorityTaskWoken);
		                        portYIELD_FROM_ISR( HigherPriorityTaskWoken ) ;
		                        return result ;
		                     }
		               }


			static inline sofware_timer_command_result_t start_from_task( TimerHandle_t handle, TickType_t BlockTime)
			        {
			                return (sofware_timer_command_result_t) xTimerStart( handle, BlockTime) ;
			        }
			inline sofware_timer_command_result_t start_from_task(TickType_t BlockTime)
				{
					return (sofware_timer_command_result_t) xTimerStart( handle, BlockTime) ;
				}

			static inline sofware_timer_command_result_t start_from_isr( TimerHandle_t handle, BaseType_t *HigherPriorityTaskWoken)
			        {
			                return (sofware_timer_command_result_t) xTimerStartFromISR( handle, HigherPriorityTaskWoken) ;
			        }
			inline sofware_timer_command_result_t start_from_isr(BaseType_t *HigherPriorityTaskWoken)
				{
					return (sofware_timer_command_result_t) xTimerStartFromISR( handle, HigherPriorityTaskWoken) ;
				}


		        static inline sofware_timer_command_result_t start( TimerHandle_t handle, TickType_t BlockTime )
		                {
		                   if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
		                     {
		                        return start_from_task(handle, BlockTime) ;
		                     }
		                   else
		                     {
		                        // give comand from ISR
		                        BaseType_t HigherPriorityTaskWoken ;
		                        sofware_timer_command_result_t result  = start_from_isr(handle, &HigherPriorityTaskWoken);
		                        portYIELD_FROM_ISR( HigherPriorityTaskWoken ) ;
		                        return result ;
		                     }
		               }

		        inline sofware_timer_command_result_t start(TickType_t BlockTime )
		                {
		                   if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
		                     {
		                        return start_from_task(BlockTime) ;
		                     }
		                   else
		                     {
		                        // give comand from ISR
		                        BaseType_t HigherPriorityTaskWoken ;
		                        sofware_timer_command_result_t result  = start_from_isr(&HigherPriorityTaskWoken);
		                        portYIELD_FROM_ISR( HigherPriorityTaskWoken ) ;
		                        return result ;
		                     }
		               }

			static inline sofware_timer_command_result_t stop_from_task( TimerHandle_t handle, TickType_t BlockTime)
			        {
			                return (sofware_timer_command_result_t) xTimerStop( handle, BlockTime) ;
			        }
			inline sofware_timer_command_result_t stop_from_task(TickType_t BlockTime)
				{
					return (sofware_timer_command_result_t) xTimerStop( handle, BlockTime) ;
				}

			static inline sofware_timer_command_result_t stop_from_isr( TimerHandle_t handle, BaseType_t *HigherPriorityTaskWoken)
			        {
			                return (sofware_timer_command_result_t) xTimerStopFromISR( handle, HigherPriorityTaskWoken) ;
			        }
			inline sofware_timer_command_result_t stop_from_isr(BaseType_t *HigherPriorityTaskWoken)
				{
					return (sofware_timer_command_result_t) xTimerStopFromISR( handle, HigherPriorityTaskWoken) ;
				}

		        static inline sofware_timer_command_result_t stop( TimerHandle_t handle, TickType_t BlockTime )
			                {
			                   if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
			                     {
			                        return stop_from_task(handle, BlockTime) ;
			                     }
			                   else
			                     {
			                        // give comand from ISR
			                        BaseType_t HigherPriorityTaskWoken ;
			                        sofware_timer_command_result_t result  = stop_from_isr(handle, &HigherPriorityTaskWoken);
			                        portYIELD_FROM_ISR( HigherPriorityTaskWoken ) ;
			                        return result ;
			                     }
			               }

			        inline sofware_timer_command_result_t stop(TickType_t BlockTime )
			                {
			                   if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
			                     {
			                        return stop_from_task(BlockTime) ;
			                     }
			                   else
			                     {
			                        // give comand from ISR
			                        BaseType_t HigherPriorityTaskWoken ;
			                        sofware_timer_command_result_t result  = stop_from_isr(&HigherPriorityTaskWoken);
			                        portYIELD_FROM_ISR( HigherPriorityTaskWoken ) ;
			                        return result ;
			                     }
			               }




			static inline sofware_timer_command_result_t reset_from_task( TimerHandle_t handle, TickType_t BlockTime)
			        {
			                return (sofware_timer_command_result_t) xTimerReset( handle, BlockTime) ;
			        }
			inline sofware_timer_command_result_t reset_from_task( TickType_t BlockTime )
				{
					return (sofware_timer_command_result_t) xTimerReset( handle, BlockTime) ;
				}

			static inline sofware_timer_command_result_t reset_from_isr( TimerHandle_t handle, BaseType_t *HigherPriorityTaskWoken)
			        {
			                return (sofware_timer_command_result_t) xTimerResetFromISR( handle, HigherPriorityTaskWoken) ;
			        }
			inline sofware_timer_command_result_t reset_from_isr(BaseType_t *HigherPriorityTaskWoken)
				{
					return (sofware_timer_command_result_t) xTimerResetFromISR( handle, HigherPriorityTaskWoken) ;
				}

		        static inline sofware_timer_command_result_t reset( TimerHandle_t handle, TickType_t BlockTime )
			                {
			                   if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
			                     {
			                        return reset_from_task(handle, BlockTime) ;
			                     }
			                   else
			                     {
			                        // give comand from ISR
			                        BaseType_t HigherPriorityTaskWoken ;
			                        sofware_timer_command_result_t result  = reset_from_isr(handle, &HigherPriorityTaskWoken);
			                        portYIELD_FROM_ISR( HigherPriorityTaskWoken ) ;
			                        return result ;
			                     }
			               }

			        inline sofware_timer_command_result_t reset(TickType_t BlockTime )
			                {
			                   if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
			                     {
			                        return reset_from_task(BlockTime) ;
			                     }
			                   else
			                     {
			                        // give comand from ISR
			                        BaseType_t HigherPriorityTaskWoken ;
			                        sofware_timer_command_result_t result  = reset_from_isr(&HigherPriorityTaskWoken);
			                        portYIELD_FROM_ISR( HigherPriorityTaskWoken ) ;
			                        return result ;
			                     }
			               }



			static inline uint32_t id( TimerHandle_t handle)
			        {
			                return (uint32_t)pvTimerGetTimerID( handle) ;
			        }
			inline uint32_t id()
				{
					return (uint32_t)pvTimerGetTimerID( handle) ;
				}

			static inline void id( TimerHandle_t handle, const uint32_t id)
			        {
			                vTimerSetTimerID( handle, (void*)id) ;
			        }
			inline void id(const uint32_t id)
				{
			                vTimerSetTimerID( handle, (void*)id) ;
				}

			static inline TaskHandle_t daemon()
				{
			                return xTimerGetTimerDaemonTaskHandle() ;
				}

			static inline BaseType_t pend_function_call_from_task( PendedFunction_t FunctionToPend, void *param1, uint32_t param2, TickType_t TicksToWait)
				{
			                return xTimerPendFunctionCall(FunctionToPend, param1, param2, TicksToWait) ;
				}

			static inline BaseType_t pend_function_call_from_isr( PendedFunction_t FunctionToPend, void *param1, uint32_t param2, BaseType_t *HigherPriorityTaskWoken)
				{
			                return xTimerPendFunctionCallFromISR(FunctionToPend, param1, param2, HigherPriorityTaskWoken) ;
				}

		        static inline BaseType_t pend_function_call( PendedFunction_t FunctionToPend, void *param1, uint32_t param2, TickType_t TicksToWait )
			                {
			                   if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
			                     {
			                        return pend_function_call_from_task(FunctionToPend, param1, param2, TicksToWait) ;
			                     }
			                   else
			                     {
			                        // give comand from ISR
			                        BaseType_t HigherPriorityTaskWoken ;
			                        BaseType_t result  = pend_function_call_from_isr(FunctionToPend, param1, param2, &HigherPriorityTaskWoken);
			                        portYIELD_FROM_ISR( HigherPriorityTaskWoken ) ;
			                        return result ;
			                     }
			               }


			static inline const char* name( TimerHandle_t handle)
			        {
			                return pcTimerGetName( handle) ;
			        }
			inline const char* name()
				{
					return pcTimerGetName( handle) ;
				}

			static inline TickType_t expiry_time( const TimerHandle_t handle)
			        {
			                return xTimerGetExpiryTime( handle) ;
			        }
			inline TickType_t expiry_time()
				{
					return xTimerGetExpiryTime( handle) ;
				}

  };


class stream_buffer_t
{
   private:
        StreamBufferHandle_t handle ;
   public:
        enum result_t { pass = pdTRUE , fail = pdFAIL }  ;

	inline stream_buffer_t (const size_t size , const size_t trigger_level = 0 )
		{
		        handle = xStreamBufferCreate(size, trigger_level) ;
		}
	inline ~stream_buffer_t ()
		{
	                vStreamBufferDelete(handle);
			handle = NULL ;
		}

        bool inline is_owner(const void* obj) { return handle == obj ; }
        bool inline is_created() { return (bool)handle ; }

	static inline size_t send_from_task ( StreamBufferHandle_t xStreamBuffer, const void *pvTxData, size_t xDataLengthBytes, TickType_t xTicksToWait )
		{
	            return xStreamBufferSend (xStreamBuffer, pvTxData, xDataLengthBytes, xTicksToWait) ;
		}
	static inline size_t send_from_isr ( StreamBufferHandle_t xStreamBuffer, const void *pvTxData, size_t xDataLengthBytes, BaseType_t *pxHigherPriorityTaskWoken )
		{
	            return xStreamBufferSendFromISR ( xStreamBuffer, pvTxData, xDataLengthBytes, pxHigherPriorityTaskWoken) ;
		}
	static inline size_t send ( StreamBufferHandle_t xStreamBuffer, const void *pvTxData, size_t xDataLengthBytes, TickType_t xTicksToWait )
		{
                    if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
                       {
                	   return xStreamBufferSend (xStreamBuffer, pvTxData, xDataLengthBytes, xTicksToWait) ;
                       }
                    else
                       {
                           // give comand from ISR
                           BaseType_t HigherPriorityTaskWoken ;
                           size_t result  = xStreamBufferSendFromISR ( xStreamBuffer, pvTxData, xDataLengthBytes, &HigherPriorityTaskWoken) ;
                           portYIELD_FROM_ISR( HigherPriorityTaskWoken ) ;
                           return result ;
                       }
		}

	inline size_t send_from_task ( const void *pvTxData, size_t xDataLengthBytes, TickType_t xTicksToWait )
		{
	            return xStreamBufferSend (handle, pvTxData, xDataLengthBytes, xTicksToWait) ;
		}
	inline size_t send_from_isr ( const void *pvTxData, size_t xDataLengthBytes, BaseType_t *pxHigherPriorityTaskWoken )
		{
	            return xStreamBufferSendFromISR ( handle, pvTxData, xDataLengthBytes, pxHigherPriorityTaskWoken) ;
		}
	inline size_t send ( const void *pvTxData, size_t xDataLengthBytes, TickType_t xTicksToWait )
		{
                    if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
                       {
                	   return send_from_task (handle, pvTxData, xDataLengthBytes, xTicksToWait) ;
                       }
                    else
                       {
                           // give comand from ISR
                           BaseType_t HigherPriorityTaskWoken ;
                           size_t result  = send_from_isr ( handle, pvTxData, xDataLengthBytes, &HigherPriorityTaskWoken) ;
                           portYIELD_FROM_ISR( HigherPriorityTaskWoken ) ;
                           return result ;
                       }
		}


	static inline size_t receive_from_task ( StreamBufferHandle_t xStreamBuffer, void *pvRxData, size_t xBufferLengthBytes, TickType_t xTicksToWait )
		{
	            return xStreamBufferReceive (xStreamBuffer, pvRxData, xBufferLengthBytes, xTicksToWait) ;
		}
	static inline size_t receive_from_isr ( StreamBufferHandle_t xStreamBuffer, void *pvRxData, size_t xBufferLengthBytes, BaseType_t *pxHigherPriorityTaskWoken )
		{
	            return xStreamBufferReceiveFromISR ( xStreamBuffer, pvRxData, xBufferLengthBytes, pxHigherPriorityTaskWoken) ;
		}
	static inline size_t receive ( StreamBufferHandle_t xStreamBuffer, void *pvRxData, size_t xBufferLengthBytes, TickType_t xTicksToWait )
		{
                    if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
                       {
                	   return receive_from_task (xStreamBuffer, pvRxData, xBufferLengthBytes, xTicksToWait) ;
                       }
                    else
                       {
                           // give comand from ISR
                           BaseType_t HigherPriorityTaskWoken ;
                           size_t result  = receive_from_isr ( xStreamBuffer, pvRxData, xBufferLengthBytes, &HigherPriorityTaskWoken) ;
                           portYIELD_FROM_ISR( HigherPriorityTaskWoken ) ;
                           return result ;
                       }
		}

	inline size_t receive_from_task (void *pvRxData, size_t xBufferLengthBytes, TickType_t xTicksToWait )
		{
	            return receive_from_task (handle, pvRxData, xBufferLengthBytes, xTicksToWait) ;
		}
	inline size_t receive_from_isr (void *pvRxData, size_t xBufferLengthBytes, BaseType_t *pxHigherPriorityTaskWoken )
		{
	            return receive_from_isr ( handle, pvRxData, xBufferLengthBytes, pxHigherPriorityTaskWoken) ;
		}
	inline size_t receive (void *pvRxData, size_t xBufferLengthBytes, TickType_t xTicksToWait )
		{
                    if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
                       {
                	   return receive_from_task (handle, pvRxData, xBufferLengthBytes, xTicksToWait) ;
                       }
                    else
                       {
                           // give comand from ISR
                           BaseType_t HigherPriorityTaskWoken ;
                           size_t result  = receive_from_isr ( handle, pvRxData, xBufferLengthBytes, &HigherPriorityTaskWoken) ;
                           portYIELD_FROM_ISR( HigherPriorityTaskWoken ) ;
                           return result ;
                       }
		}

	static inline size_t bytes_available ( StreamBufferHandle_t xStreamBuffer )
		{
	            return xStreamBufferBytesAvailable (xStreamBuffer) ;
		}
	inline size_t bytes_available ()
		{
	            return xStreamBufferBytesAvailable (handle) ;
		}

	static inline size_t space_available ( StreamBufferHandle_t xStreamBuffer )
		{
	            return xStreamBufferSpacesAvailable (xStreamBuffer) ;
		}
	inline size_t space_available ()
		{
	            return xStreamBufferSpacesAvailable (handle) ;
		}

	static inline result_t trigger_level ( StreamBufferHandle_t xStreamBuffer, size_t xTriggerLevel )
		{
	            return (result_t) xStreamBufferSetTriggerLevel (xStreamBuffer, xTriggerLevel) ;
		}
	inline result_t trigger_level (size_t xTriggerLevel)
		{
	            return (result_t) xStreamBufferSetTriggerLevel (handle, xTriggerLevel) ;
		}

	static inline result_t reset ( StreamBufferHandle_t xStreamBuffer)
		{
	            return (result_t) xStreamBufferReset (xStreamBuffer) ;
		}
	inline result_t rReset ()
		{
	            return (result_t) xStreamBufferReset (handle) ;
		}

	static inline result_t is_empty ( StreamBufferHandle_t xStreamBuffer)
		{
	            return (result_t) xStreamBufferIsEmpty (xStreamBuffer) ;
		}
	inline result_t is_empty ()
		{
	            return (result_t) xStreamBufferIsEmpty (handle) ;
		}

	static inline result_t is_full ( StreamBufferHandle_t xStreamBuffer)
		{
	            return (result_t)   xStreamBufferIsFull (xStreamBuffer) ;
		}
	inline result_t is_full ()
		{
	            return (result_t)   xStreamBufferIsFull (handle) ;
		}



} ;


class message_buffer_t
{
   private:
        MessageBufferHandle_t handle ;
   public:
        enum result_t { pass = pdTRUE , fail = pdFAIL }  ;

	inline message_buffer_t (const size_t size  )
		{
		        handle = xMessageBufferCreate(size) ;
		}
	inline ~message_buffer_t ()
		{
	                vMessageBufferDelete(handle);
			handle = NULL ;
		}

        bool inline is_owner(const void* obj) { return handle == obj ; }
        bool inline is_created() { return (bool)handle ; }

	static inline size_t send_from_task ( MessageBufferHandle_t xMessageBuffer, const void *pvTxData, size_t xDataLengthBytes, TickType_t xTicksToWait )
		{
	            return xMessageBufferSend (xMessageBuffer, pvTxData, xDataLengthBytes, xTicksToWait) ;
		}
	static inline size_t send_from_isr ( MessageBufferHandle_t xMessageBuffer, const void *pvTxData, size_t xDataLengthBytes, BaseType_t *pxHigherPriorityTaskWoken )
		{
	            return xMessageBufferSendFromISR ( xMessageBuffer, pvTxData, xDataLengthBytes, pxHigherPriorityTaskWoken) ;
		}
	static inline size_t send ( MessageBufferHandle_t xMessageBuffer, const void *pvTxData, size_t xDataLengthBytes, TickType_t xTicksToWait )
		{
                    if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
                       {
                	   return send_from_task (xMessageBuffer, pvTxData, xDataLengthBytes, xTicksToWait) ;
                       }
                    else
                       {
                           // give comand from ISR
                           BaseType_t HigherPriorityTaskWoken ;
                           size_t result  = send_from_isr ( xMessageBuffer, pvTxData, xDataLengthBytes, &HigherPriorityTaskWoken) ;
                           portYIELD_FROM_ISR( HigherPriorityTaskWoken ) ;
                           return result ;
                       }
		}

	inline size_t send_from_task ( const void *pvTxData, size_t xDataLengthBytes, TickType_t xTicksToWait )
		{
	            return send_from_task (handle, pvTxData, xDataLengthBytes, xTicksToWait) ;
		}
	inline size_t send_from_isr ( const void *pvTxData, size_t xDataLengthBytes, BaseType_t *pxHigherPriorityTaskWoken )
		{
	            return send_from_isr ( handle, pvTxData, xDataLengthBytes, pxHigherPriorityTaskWoken) ;
		}
	inline size_t send ( const void *pvTxData, size_t xDataLengthBytes, TickType_t xTicksToWait )
		{
                    if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
                       {
                	   return send_from_task (handle, pvTxData, xDataLengthBytes, xTicksToWait) ;
                       }
                    else
                       {
                           // give comand from ISR
                           BaseType_t HigherPriorityTaskWoken ;
                           size_t result  = send_from_isr ( handle, pvTxData, xDataLengthBytes, &HigherPriorityTaskWoken) ;
                           portYIELD_FROM_ISR( HigherPriorityTaskWoken ) ;
                           return result ;
                       }
		}


	static inline size_t receive_from_task ( MessageBufferHandle_t xMessageBuffer, void *pvRxData, size_t xBufferLengthBytes, TickType_t xTicksToWait )
		{
	            return xMessageBufferReceive (xMessageBuffer, pvRxData, xBufferLengthBytes, xTicksToWait) ;
		}
	static inline size_t receive_from_isr ( MessageBufferHandle_t xMessageBuffer, void *pvRxData, size_t xBufferLengthBytes, BaseType_t *pxHigherPriorityTaskWoken )
		{
	            return xMessageBufferReceiveFromISR ( xMessageBuffer, pvRxData, xBufferLengthBytes, pxHigherPriorityTaskWoken) ;
		}
	static inline size_t receive ( MessageBufferHandle_t xMessageBuffer, void *pvRxData, size_t xBufferLengthBytes, TickType_t xTicksToWait )
		{
                    if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
                       {
                	   return receive_from_task (xMessageBuffer, pvRxData, xBufferLengthBytes, xTicksToWait) ;
                       }
                    else
                       {
                           // give comand from ISR
                           BaseType_t HigherPriorityTaskWoken ;
                           size_t result  = receive_from_isr ( xMessageBuffer, pvRxData, xBufferLengthBytes, &HigherPriorityTaskWoken) ;
                           portYIELD_FROM_ISR( HigherPriorityTaskWoken ) ;
                           return result ;
                       }
		}

	inline size_t receive_from_task (void *pvRxData, size_t xBufferLengthBytes, TickType_t xTicksToWait )
		{
	            return receive_from_task (handle, pvRxData, xBufferLengthBytes, xTicksToWait) ;
		}
	inline size_t receive_from_isr (void *pvRxData, size_t xBufferLengthBytes, BaseType_t *pxHigherPriorityTaskWoken )
		{
	            return receive_from_isr ( handle, pvRxData, xBufferLengthBytes, pxHigherPriorityTaskWoken) ;
		}
	inline size_t receive (void *pvRxData, size_t xBufferLengthBytes, TickType_t xTicksToWait )
		{
                    if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
                       {
                	   return receive_from_task (handle, pvRxData, xBufferLengthBytes, xTicksToWait) ;
                       }
                    else
                       {
                           // give comand from ISR
                           BaseType_t HigherPriorityTaskWoken ;
                           size_t result  = receive_from_isr ( handle, pvRxData, xBufferLengthBytes, &HigherPriorityTaskWoken) ;
                           portYIELD_FROM_ISR( HigherPriorityTaskWoken ) ;
                           return result ;
                       }
		}

	static inline size_t space_available ( MessageBufferHandle_t xMessageBuffer )
		{
	            return xMessageBufferSpaceAvailable (xMessageBuffer) ;
		}
	inline size_t space_available ()
		{
	            return space_available (handle) ;
		}

	static inline result_t reset ( MessageBufferHandle_t xMessageBuffer)
		{
	            return (result_t) xMessageBufferReset (xMessageBuffer) ;
		}
	inline result_t reset ()
		{
	            return reset (handle) ;
		}

	static inline result_t is_empty ( MessageBufferHandle_t xMessageBuffer)
		{
	            return (result_t) xMessageBufferIsEmpty (xMessageBuffer) ;
		}
	inline result_t is_empty ()
		{
	            return (result_t) is_empty (handle) ;
		}

	static inline result_t is_full ( MessageBufferHandle_t xMessageBuffer)
		{
	            return (result_t)   xMessageBufferIsFull (xMessageBuffer) ;
		}
	inline result_t is_full ()
		{
	            return (result_t)   is_full (handle) ;
		}



} ;

class task_t
  {
     private:
       static inline void vm_table_code( task_t* ptr ) { ptr->code() ; }
     protected:
       TaskHandle_t handle ;

       static inline uint32_t notify_take( BaseType_t xClearCountOnExit, TickType_t xTicksToWait)
                  {
                           return ulTaskNotifyTake( xClearCountOnExit, xTicksToWait );
                  }

       static inline BaseType_t notify_wait( uint32_t ulBitsToClearOnEntry, uint32_t ulBitsToClearOnExit, uint32_t *pulNotificationValue, TickType_t xTicksToWait )
                  {
                           return xTaskNotifyWait( ulBitsToClearOnEntry, ulBitsToClearOnExit, pulNotificationValue, xTicksToWait );
                  }

     public:

       enum notify_result_t { pass = pdPASS , fall=pdFAIL }  ;

       inline task_t( const char* name , const int stack_size , const int priority , bool suspended ) : handle(NULL)
                {
	             create( name , stack_size , priority ) ;
	             if ( handle && suspended )
	               suspend() ;
                };

       inline virtual ~task_t()
                {
                     if (handle)
                       remove();
                };

       inline TaskHandle_t get_handle() { return handle ; }
       bool inline is_owner(const void* obj) { return handle == obj ; }
       bool inline is_created() { return (bool)handle ; }

       virtual void code(void) = 0  ;
       inline void create( const char* name , int stack_size , int priority )
               {
    	         xTaskCreate( (TaskFunction_t)vm_table_code ,
    	                      ( const char * ) name ,
    	                      (short unsigned int)stack_size ,
    	                      (void *)this ,
    	                      (long unsigned int)priority ,
    	                      (TaskHandle_t *)&handle ) ;
               }
       inline void remove()
               {
                 vTaskDelete( handle );
               }
       static inline void remove( TaskHandle_t pxTask )
               {
                 vTaskDelete( pxTask );
               }

       static inline void delay(TickType_t xTicksToDelay)
               {
                 vTaskDelay( xTicksToDelay );
               }
       static inline void delay_ms(TickType_t xTimeInMs)
               {
	         delay( pdMS_TO_TICKS( xTimeInMs ) );
               }

       static inline void delay_until( TickType_t *pxPreviousWakeTime, TickType_t xTimeIncrement )
               {
                 vTaskDelayUntil( pxPreviousWakeTime, xTimeIncrement );
               }

       static inline void delay_until_ms( TickType_t *pxPreviousWakeTime, TickType_t xTimeInMs )
               {
	         delay_until( pxPreviousWakeTime,  pdMS_TO_TICKS( xTimeInMs ) );
               }

       inline unsigned portBASE_TYPE priority()
               {
                 return uxTaskPriorityGet( handle );
               }
       static inline unsigned portBASE_TYPE priority( TaskHandle_t pxTask )
               {
                 return uxTaskPriorityGet( pxTask );
               }
       inline void priority( unsigned portBASE_TYPE uxNewPriority )
               {
                 vTaskPrioritySet( handle , uxNewPriority ) ;
               }
       static inline void priority( TaskHandle_t pxTask, unsigned portBASE_TYPE uxNewPriority )
               {
                 vTaskPrioritySet( pxTask, uxNewPriority ) ;
               }
       inline void suspend()
               {
                 vTaskSuspend( handle );
               }
       static inline void suspend( TaskHandle_t pxTaskToSuspend )
               {
                 vTaskSuspend( pxTaskToSuspend );
               }

       static inline void resume_from_task( TaskHandle_t pxTaskToResume )
               {
                 vTaskResume( pxTaskToResume );
               }
       static inline portBASE_TYPE resume_from_isr( TaskHandle_t pxTaskToResume )
               {
                 return xTaskResumeFromISR( pxTaskToResume );
               }
       static inline void resume_from_isr_with_yeld( TaskHandle_t pxTaskToResume )
               {
	         portYIELD_FROM_ISR(resume_from_isr(pxTaskToResume));
               }

      static inline portBASE_TYPE resume( TaskHandle_t pxTask, bool yield_if_required = true )
               {
	         if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
	            {
	               resume_from_task( pxTask );
	               return pdFALSE ;
	            }
	         else
	            {
	              portBASE_TYPE  yield_required = resume_from_isr( pxTask );
	              if ( yield_if_required )
	        	  portYIELD_FROM_ISR( yield_required ) ;
	              return yield_required ;
	            }
               }

       inline void resume_from_task()
               {
	         resume_from_task( handle ) ;
               }
       inline portBASE_TYPE resume_from_isr()
               {
                 return resume_from_isr( handle );
               }
       inline portBASE_TYPE resume()
               {
	         return resume( handle );
               }

       inline unsigned portBASE_TYPE  stack_high_water_mark( TaskHandle_t xTask  )
               {
                 return task_utilities_t::stack_high_water_mark(xTask) ;
               }
       inline portBASE_TYPE stack_high_water_mark()
               {
                 return task_utilities_t::stack_high_water_mark( handle ) ;
               }

       static inline BaseType_t abort_delay( TaskHandle_t pxTask )
               {
                 return xTaskAbortDelay( pxTask );
               }
       inline BaseType_t abort_delay()
               {
                 return xTaskAbortDelay( handle );
               }








       static inline void notify_give_from_task( TaskHandle_t pxTask )
               {
                  xTaskNotifyGive( pxTask );
               }
       static inline void notify_give_from_isr( TaskHandle_t pxTask, BaseType_t *pxHigherPriorityTaskWoken )
               {
                  vTaskNotifyGiveFromISR( pxTask, pxHigherPriorityTaskWoken );
               }
       static inline void notify_give( TaskHandle_t pxTask )
               {
	         if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
	            {
	               notify_give_from_task( pxTask );
	            }
	         else
	            {
	               BaseType_t HigherPriorityTaskWoken ;
	               notify_give_from_isr( pxTask, &HigherPriorityTaskWoken );
	               portYIELD_FROM_ISR( HigherPriorityTaskWoken ) ;
	            }
               }


       inline void notify_give_from_task()
               {
	              notify_give_from_task( handle );
               }
       inline void notify_give_from_isr(BaseType_t *pxHigherPriorityTaskWoken )
               {
	              notify_give_from_isr(handle, pxHigherPriorityTaskWoken );
               }
       inline void notify_give()
               {
	         if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
	            {
	               notify_give_from_task( handle );
	            }
	         else
	            {
	               BaseType_t HigherPriorityTaskWoken ;
	               notify_give_from_isr( handle, &HigherPriorityTaskWoken );
	               portYIELD_FROM_ISR( HigherPriorityTaskWoken ) ;
	            }
               }




       static inline BaseType_t notify_from_task( TaskHandle_t xTaskToNotify, uint32_t ulValue, eNotifyAction eAction )
               {
                  return xTaskNotify( xTaskToNotify, ulValue, eAction );
               }
       static inline BaseType_t notify_from_isr( TaskHandle_t xTaskToNotify, uint32_t ulValue, eNotifyAction eAction, BaseType_t *pxHigherPriorityTaskWoken )
               {
	          return xTaskNotifyFromISR( xTaskToNotify, ulValue, eAction, pxHigherPriorityTaskWoken );
               }
       static inline BaseType_t notify( TaskHandle_t xTaskToNotify, uint32_t ulValue, eNotifyAction eAction )
               {
	         if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
	            {
	               return xTaskNotify( xTaskToNotify, ulValue, eAction );
	            }
	         else
	            {
	               BaseType_t HigherPriorityTaskWoken ;
	               BaseType_t result = xTaskNotifyFromISR( xTaskToNotify, ulValue, eAction, &HigherPriorityTaskWoken );
	               portYIELD_FROM_ISR( HigherPriorityTaskWoken ) ;
	               return result ;
	            }
               }

       inline BaseType_t notify_from_task( uint32_t ulValue, eNotifyAction eAction )
               {
                  return notify_from_task( handle, ulValue, eAction );
               }
       inline BaseType_t notify_from_isr(  uint32_t ulValue, eNotifyAction eAction, BaseType_t *pxHigherPriorityTaskWoken )
               {
	          return notify_from_isr( handle, ulValue, eAction, pxHigherPriorityTaskWoken );
               }
       inline BaseType_t notify( uint32_t ulValue, eNotifyAction eAction )
               {
	         if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
	            {
	               return notify_from_task( handle, ulValue, eAction );
	            }
	         else
	            {
	               BaseType_t HigherPriorityTaskWoken ;
	               BaseType_t result = notify_from_isr( handle, ulValue, eAction, &HigherPriorityTaskWoken );
	               portYIELD_FROM_ISR( HigherPriorityTaskWoken ) ;
	               return result ;
	            }
               }


       static inline BaseType_t notify_and_query_from_task( TaskHandle_t xTaskToNotify, uint32_t ulValue, eNotifyAction eAction, uint32_t *pulPreviousNotifyValue )
               {
                  return xTaskNotifyAndQuery( xTaskToNotify, ulValue, eAction, pulPreviousNotifyValue );
               }
       static inline BaseType_t notify_and_query_from_isr( TaskHandle_t xTaskToNotify, uint32_t ulValue, eNotifyAction eAction, uint32_t *pulPreviousNotifyValue, BaseType_t *pxHigherPriorityTaskWoken )
               {
	          return xTaskNotifyAndQueryFromISR( xTaskToNotify, ulValue, eAction, pulPreviousNotifyValue, pxHigherPriorityTaskWoken );
               }
       static inline BaseType_t notify_and_query( TaskHandle_t xTaskToNotify, uint32_t ulValue, eNotifyAction eAction, uint32_t *pulPreviousNotifyValue )
               {
	         if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
	            {
	               return notify_and_query_from_task( xTaskToNotify, ulValue, eAction, pulPreviousNotifyValue );
	            }
	         else
	            {
	               BaseType_t HigherPriorityTaskWoken ;
	               BaseType_t result = notify_and_query_from_isr( xTaskToNotify, ulValue, eAction, pulPreviousNotifyValue, &HigherPriorityTaskWoken );
	               portYIELD_FROM_ISR( HigherPriorityTaskWoken ) ;
	               return result ;
	            }
               }


       inline BaseType_t notify_and_query_from_task( uint32_t ulValue, eNotifyAction eAction, uint32_t *pulPreviousNotifyValue )
               {
                  return notify_and_query_from_task( handle, ulValue, eAction, pulPreviousNotifyValue );
               }
       inline BaseType_t notify_and_query_from_isr( uint32_t ulValue, eNotifyAction eAction, uint32_t *pulPreviousNotifyValue, BaseType_t *pxHigherPriorityTaskWoken )
               {
	          return notify_and_query_from_isr( handle, ulValue, eAction, pulPreviousNotifyValue, pxHigherPriorityTaskWoken );
               }
       inline BaseType_t notify_and_query( uint32_t ulValue, eNotifyAction eAction, uint32_t *pulPreviousNotifyValue )
               {
	         if ( cpu_exception_num() == ipsr_t::exception_num_t::thread )
	            {
	               return notify_and_query_from_task( handle, ulValue, eAction, pulPreviousNotifyValue );
	            }
	         else
	            {
	               BaseType_t HigherPriorityTaskWoken ;
	               BaseType_t result = notify_and_query_from_isr( handle, ulValue, eAction, pulPreviousNotifyValue, &HigherPriorityTaskWoken );
	               portYIELD_FROM_ISR( HigherPriorityTaskWoken ) ;
	               return result ;
	            }
               }

       static inline BaseType_t notify_state_clear( TaskHandle_t xTask)
               {
                 return xTaskNotifyStateClear( xTask);
               }
       inline BaseType_t notify_state_clear()
               {
                 return xTaskNotifyStateClear( handle);
               }

  } ;

#if 0
template <size_t stack_size>
class TStaticTask
  {
     private:

       StaticTask_t task;
       StackType_t  stack[ stack_size ];

       static inline void VMTable_Code( TTask* ptr ) { ptr->Code() ; }
     protected:
       TaskHandle_t handle ;

       static inline uint32_t NotifyTake( BaseType_t xClearCountOnExit, TickType_t xTicksToWait)
                  {
                           return ulTaskNotifyTake( xClearCountOnExit, xTicksToWait );
                  }

       static inline BaseType_t NotifyWait( uint32_t ulBitsToClearOnEntry, uint32_t ulBitsToClearOnExit, uint32_t *pulNotificationValue, TickType_t xTicksToWait )
                  {
                           return xTaskNotifyWait( ulBitsToClearOnEntry, ulBitsToClearOnExit, pulNotificationValue, xTicksToWait );
                  }

     public:

       enum TNotifyResult { nrPass = pdPASS , nrFall=pdFAIL }  ;

       inline TStaticTask( const char* name , const int priority , bool suspend ) : handle(NULL)
                {
	             Create( name , priority) ;
	             if ( handle && suspend )
	               Suspend() ;
                };

       inline virtual ~TStaticTask()
                {
                     if (handle)
                       Delete();
                };

       inline TaskHandle_t Gethandle() { return handle ; }
       bool inline IsOwner(const void* obj) { return handle == obj ; }
       bool inline IsCreated() { return (bool)handle ; }

       virtual void Code(void) = 0  ;
       inline void Create( const char* name, int priority )
                {
    	             /*handle =*/ xTaskCreateStatic( (TaskFunction_t)VMTable_Code ,
    	                        ( const char * ) name ,
    	                        (short unsigned int)stack_size ,
    	                        (void *)this ,
    	                        (long unsigned int)priority ,
			        stack,
			        &task
			      ) ;
                }
       inline void Delete()
               {
                 vTaskDelete( handle );
               }
       static inline void Delete( TaskHandle_t pxTask )
               {
                 vTaskDelete( pxTask );
               }
       static inline void Delay(TickType_t xTicksToDelay)
               {
                 vTaskDelay( xTicksToDelay );
               }
       static inline void delay_ms(TickType_t xTimeInMs)
               {
	         Delay( pdMS_TO_TICKS( xTimeInMs ) );
               }

       static inline void DelayUntil( TickType_t *pxPreviousWakeTime, TickType_t xTimeIncrement )
               {
                 vTaskDelayUntil( pxPreviousWakeTime, xTimeIncrement );
               }

       static inline void delay_until_ms( TickType_t *pxPreviousWakeTime, TickType_t xTimeInMs )
               {
	         DelayUntil( pxPreviousWakeTime,  pdMS_TO_TICKS( xTimeInMs ) );
               }

       inline unsigned portBASE_TYPE GetPriority()
               {
                 return uxTaskPriorityGet( handle );
               }
       static inline unsigned portBASE_TYPE GetPriority( TaskHandle_t pxTask )
               {
                 return uxTaskPriorityGet( pxTask );
               }
       inline void SetPriority( unsigned portBASE_TYPE uxNewPriority )
               {
                 vTaskPrioritySet( handle , uxNewPriority ) ;
               }
       static inline void SetPriority( TaskHandle_t pxTask, unsigned portBASE_TYPE uxNewPriority )
               {
                 vTaskPrioritySet( pxTask, uxNewPriority ) ;
               }
       inline void Suspend()
               {
                 vTaskSuspend( handle );
               }
       static inline void Suspend( TaskHandle_t pxTaskToSuspend )
               {
                 vTaskSuspend( pxTaskToSuspend );
               }
       inline void Resume()
               {
                 vTaskResume( handle ) ;
               }
       static inline void Resume( TaskHandle_t pxTaskToResume )
               {
                 vTaskResume( pxTaskToResume );
               }
       static inline portBASE_TYPE ResumeFromISR( TaskHandle_t pxTaskToResume )
               {
                 return xTaskResumeFromISR( pxTaskToResume );
               }
       inline portBASE_TYPE ResumeFromISR()
               {
                 return xTaskResumeFromISR( handle );
               }

       inline unsigned portBASE_TYPE  stack_high_water_mark( TaskHandle_t xTask  )
               {
                 return task_utilities_t::stack_high_water_mark(xTask) ;
               }
       inline portBASE_TYPE stack_high_water_mark()
               {
                 return task_utilities_t::stack_high_water_mark( handle ) ;
               }

       static inline BaseType_t AbortDelay( TaskHandle_t pxTask )
               {
                 return xTaskAbortDelay( pxTask );
               }
       inline BaseType_t AbortDelay()
               {
                 return xTaskAbortDelay( handle );
               }

       static inline BaseType_t NotifyGive( TaskHandle_t pxTask )
               {
                 return xTaskNotifyGive( pxTask );
               }
       inline BaseType_t NotifyGive()
               {
                 return xTaskNotifyGive( handle );
               }

       static inline void NotifyGiveFromISR( TaskHandle_t pxTask, BaseType_t *pxHigherPriorityTaskWoken )
               {
                  vTaskNotifyGiveFromISR( pxTask, pxHigherPriorityTaskWoken );
               }
       inline void NotifyGiveFromISR(BaseType_t *pxHigherPriorityTaskWoken)
               {
                  vTaskNotifyGiveFromISR( handle, pxHigherPriorityTaskWoken );
               }

       static inline BaseType_t Notify( TaskHandle_t xTask, uint32_t ulValue, eNotifyAction eAction )
               {
                 return xTaskNotify( xTask, ulValue, eAction );
               }
       inline BaseType_t Notify(uint32_t ulValue, eNotifyAction eAction)
               {
                 return xTaskNotify( handle, ulValue, eAction );
               }

       static inline BaseType_t NotifyAndQuery( TaskHandle_t xTask, uint32_t ulValue, eNotifyAction eAction, uint32_t *pulPreviousNotifyValue )
               {
                 return xTaskNotifyAndQuery( xTask, ulValue, eAction, pulPreviousNotifyValue );
               }
       inline BaseType_t NotifyAndQuery(uint32_t ulValue, eNotifyAction eAction, uint32_t *pulPreviousNotifyValue)
               {
                 return xTaskNotifyAndQuery( handle, ulValue, eAction, pulPreviousNotifyValue );
               }

       static inline BaseType_t NotifyAndQueryFromISR(  TaskHandle_t xTask, uint32_t ulValue, eNotifyAction eAction, uint32_t *pulPreviousNotifyValue, BaseType_t *pxHigherPriorityTaskWoken  )
               {
                 return xTaskNotifyAndQueryFromISR( xTask, ulValue, eAction, pulPreviousNotifyValue, pxHigherPriorityTaskWoken );
               }
       inline BaseType_t NotifyAndQueryFromISR(uint32_t ulValue, eNotifyAction eAction, uint32_t *pulPreviousNotifyValue, BaseType_t *pxHigherPriorityTaskWoken)
               {
                 return xTaskNotifyAndQueryFromISR( handle, ulValue, eAction, pulPreviousNotifyValue, pxHigherPriorityTaskWoken );
               }

       static inline TNotifyResult NotifyFromISR(  TaskHandle_t xTask, uint32_t ulValue, eNotifyAction eAction, BaseType_t *pxHigherPriorityTaskWoken  )
               {
                 return (TNotifyResult)xTaskNotifyFromISR( xTask, ulValue, eAction, pxHigherPriorityTaskWoken );
               }
       inline TNotifyResult NotifyFromISR(uint32_t ulValue, eNotifyAction eAction, BaseType_t *pxHigherPriorityTaskWoken)
               {
                 return (TNotifyResult)xTaskNotifyFromISR( handle, ulValue, eAction, pxHigherPriorityTaskWoken );
               }


       static inline BaseType_t NotifyStateClear( TaskHandle_t xTask)
               {
                 return xTaskNotifyStateClear( xTask);
               }
       inline BaseType_t NotifyStateClear()
               {
                 return xTaskNotifyStateClear( handle);
               }

  } ;
#endif

}

using namespace freertos ;

#endif /*__TASK_H__*/
