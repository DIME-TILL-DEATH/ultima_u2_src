#include "gui.h"
//#include "display/sh1106.h"
#include "msc.h"
#include "controls.h"
#include "fs_browser.h"
#include "spectrum.h"

#include "tasks/display_task.h"
#include "tasks/cc_task.h"
#include "tasks/dsp_task.h"

#include "preset.h"

void init(void);
//----------------------------------------------------------------------------
int main(void)
{
	init();

	memset(&currentPreset, 0, sizeof(currentPreset));

	display_task = new display_task_t("DIS", 5 * configMINIMAL_STACK_SIZE, 0);

	bool usb_suspend = !controls.usb_vbus();

	if(usb_suspend)
		controls.usb_vbus_irq_enable();

	msc_task = new msc_task_t("MSC", 5 * configMINIMAL_STACK_SIZE, 0, usb_suspend);
	fs_browser_task = new fs_browser_task_t("FSB", 10 * configMINIMAL_STACK_SIZE, 0, !usb_suspend);
	gui_task = new gui_task_t("GUI", 30 * configMINIMAL_STACK_SIZE, 0, 16);
	cc_task = new cc_task_t("CC", 5 * configMINIMAL_STACK_SIZE, 0);
	dsp_task = new dsp_task_t("DSP", 10 * configMINIMAL_STACK_SIZE, 0);
	spectrum_task = new spectrum_task_t("ST", 5 * configMINIMAL_STACK_SIZE, 0);

	scheduler_t::start();

	return 0;
}
