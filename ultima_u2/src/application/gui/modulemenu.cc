#include "modulemenu.h"

#include "listmenuparams/baseparam.h"
#include "listmenuparams/stringlistparam.h"

ModuleMenu::ModuleMenu(AbstractMenu* parent, gui_menu_type menuType, TModuleDescriptor* module)
	: ParamListMenu(parent, menuType){
	m_module = module;}

void ModuleMenu::encoderPressed()
{
	ParamListMenu::encoderPressed();
	m_module->needUpdateParameters = true;

	// TODO consoleEvent for expression, fsw and gui: console_task_>write("event fxset m%d p%d v%d", m_module->moduleId,
	//m_currentParamNum, m_module->parameter[m_currentParamNum].value);
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
