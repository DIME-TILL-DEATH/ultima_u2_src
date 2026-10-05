#ifndef MODULEMENU_H_
#define MODULEMENU_H_

#include "paramlistmenu.h"

#include "processing/audio_process.h"

class ModuleMenu : public ParamListMenu
{
public:
	ModuleMenu(AbstractMenu* parent, gui_menu_type menuType, TModuleRuntime* module);

	void encoderPressed() override;
	void encoderClockwise() override;
	void encoderCounterClockwise() override;
private:

	TModuleRuntime* m_module;
};

#endif /* MODULEMENU_H_ */
