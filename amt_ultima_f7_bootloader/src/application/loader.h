
#ifndef __LOADER_H__

#include "appdefs.h"
#include "ff.h"

class loader_task_t : public task_t
{
public:
  inline loader_task_t (const char* name , const int stack_size , const int priority ) : task_t(name , stack_size , priority , false)
     {

     }

  //------------------- APP OFFSET ------------
  const uint32_t header = ((uint32_t)gnu_linker_flash_start() + header_offset) ;
  const uint32_t app    = ((uint32_t)gnu_linker_flash_start() + app_offset) ;

  void check_fs();
  void check_firmware();
  void recovery();
  void check_app();
  void check_read_protect();
  void firmware_update();

  void draw_progres_bar(uint8_t progress);

  private:
     void code() ;

     FRESULT fres ; // результат вызова функций fatsf
     FATFS   fs   ;
     FIL     fw   ; // дескриптор файла прошивки

     const uint8_t ok_msg_pos_row=110 ;
};

extern loader_task_t* loader_task ;

#endif /*__LOADER_H__*/
