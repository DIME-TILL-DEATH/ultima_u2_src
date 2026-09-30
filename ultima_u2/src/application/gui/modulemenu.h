#ifndef MODULEMENU_H_
#define MODULEMENU_H_

#include "paramlistmenu.h"

#include "module.h"

class ModuleMenu : public ParamListMenu
{
public:
	ModuleMenu(AbstractMenu* parent, gui_menu_type menuType, TModuleDescriptor* module);

	void encoderPressed() override;
	void encoderClockwise() override;
	void encoderCounterClockwise() override;
private:

	TModuleDescriptor* m_module;
};

#endif /* MODULEMENU_H_ */
