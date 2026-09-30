#ifndef COMPRESSORMENU_H_
#define COMPRESSORMENU_H_

#include "paramlistmenu.h"

#include "module.h"

class CompressorMenu : public ParamListMenu
{
public:
	CompressorMenu(AbstractMenu* parent, gui_menu_type menuType, TModuleDescriptor* module);

	void encoderPressed() override;
	void encoderClockwise() override;
	void encoderCounterClockwise() override;
private:

	TModuleDescriptor* m_module;
};

#endif /* COMPRESSORMENU_H_ */
