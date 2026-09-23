#ifndef __IO_PORT_H__
#define __IO_PORT_H__

enum TGPIOMode {iomGeneral=0, iomFast } ;

void  set_gpio0_mode( enum TGPIOMode gpio_mode );
void  set_gpio1_mode( enum TGPIOMode gpio_mode);

enum TGPIOMode  get_gpio0_mode();
enum TGPIOMode  get_gpio1_mode();

#endif /*__IO_PORT_H__*/
