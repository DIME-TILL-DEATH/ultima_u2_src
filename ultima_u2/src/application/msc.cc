#include "msc.h"

#include "usbd_storage_if.h"
#include "controls.h"
#include "fs_browser.h"
#include "gui.h"

#include "tasks/display_task.h"

msc_task_t *msc_task;

void msc_task_t::code()
{
	start();

	while(1)
	{
		pcd_handler(&pcd);
		state_handler();
	}
}

void msc_task_t::start()
{
	usbd_init(&pcd, &usbd, &usbd_descriptors, full_speed);
	usbd_register_class(&usbd, &msc_usbd_class);
	usbd_msc_register_storage(&usbd, &usbd_msc_io);
	usbd_start(&usbd);

	resume();

	controls.usb_vbus_irq_disable();
}
void msc_task_t::stop()
{
	usbd_stop(&usbd);
	usbd_deinit(&usbd);

	fs_browser_task->start();
	controls.usb_vbus_irq_enable();
	gui_task->preset_check();
	gui_task->prog_ch();

	suspend();

}

void msc_task_t::state_handler()
{
	device_state_t curr_device_state = device_state();
	if((curr_device_state == configured) && (prev_device_state != configured))
	{
		gui_task->suspend();
		display_task->clear();
		display_task->line_12x13(5, 0, "PC is connected", 0);
	}
	if((curr_device_state != configured) && (prev_device_state == configured))
	{
		stop();
	}
	prev_device_state = curr_device_state;
}

