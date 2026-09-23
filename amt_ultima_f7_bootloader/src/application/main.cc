#include "appdefs.h"
#include "loader.h"
#include "display.h"


int main(void)
{
  display_task  = new display_task_t("DIS", 20*configMINIMAL_STACK_SIZE, 0 , display_io, fonts );
  loader_task   = new loader_task_t("LDR", 20*configMINIMAL_STACK_SIZE, 0 );

  scheduler_t::start();
}



