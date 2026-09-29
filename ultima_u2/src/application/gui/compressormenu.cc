#include "compressormenu.h"

#include "listmenuparams/baseparam.h"
#include "listmenuparams/stringlistparam.h"

CompressorMenu::CompressorMenu(AbstractMenu* parent, gui_menu_type menuType, TModule* module)
	: ParamListMenu(parent, menuType){	BaseParam* paramList[maxParamCount];	uint8_t paramCount = 0;

	paramList[paramCount++] = new StringListParam(&module->parameter[0], {"Off", "On "}, 4);	for (uint8_t i = 1; i < module->parameterCount; ++i)	{		paramList[paramCount++] = new BaseParam(BaseParam::GUI_PARAMETER_LEVEL, &module->parameter[i]);	}	setParams(paramList, paramCount);}
