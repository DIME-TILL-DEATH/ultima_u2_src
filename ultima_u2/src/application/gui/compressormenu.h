#ifndef COMPRESSORMENU_H_
#define COMPRESSORMENU_H_

#include "paramlistmenu.h"

#include "module.h"

class CompressorMenu : public ParamListMenu
{
public:
	CompressorMenu(AbstractMenu* parent, gui_menu_type menuType, TModule* module);
private:
};

#endif /* COMPRESSORMENU_H_ */
