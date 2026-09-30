#include "modulemenu.h"

#include "listmenuparams/baseparam.h"
#include "listmenuparams/stringlistparam.h"

ModuleMenu::ModuleMenu(AbstractMenu* parent, gui_menu_type menuType, TModuleDescriptor* module)
	: ParamListMenu(parent, menuType){
	m_module = module;
}

void ModuleMenu::encoderPressed()
{
	ParamListMenu::encoderPressed();
	m_module->needUpdateParameters = true;
}

void ModuleMenu::encoderClockwise()
{
	ParamListMenu::encoderClockwise();
	m_module->needUpdateParameters = true;
}

void ModuleMenu::encoderCounterClockwise()
{
	ParamListMenu::encoderCounterClockwise();
	m_module->needUpdateParameters = true;
}
