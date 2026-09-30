#include "modulemenufactory.h"

AbstractMenu* ModuleMenuFactory::createModuleMenu(AbstractMenu* parent, TModuleDescriptor* module)
{
	switch (module->type)
 	{
 		case CM_MODULE:
 			return createCompressorMenu(parent, module);
 			break;
 		default:
 			return nullptr;
 	}
}

AbstractMenu* ModuleMenuFactory::createCompressorMenu(AbstractMenu* parent, TModuleDescriptor* module)
{
 	ModuleMenu* menu = new ModuleMenu(parent, MENU_COMPRESSOR, module);

 	BaseParam* paramList[ParamListMenu::maxParamCount];
 	uint8_t paramCount = 0;

 	paramList[0] = new StringListParam(&module->parameter[0], {"Off", "On "}, 4);
 	paramList[0]->setUpdatedByClick(true);
 	paramCount++;

 	for (uint8_t i = 1; i < module->parameterCount; ++i)
 	{
 		paramList[paramCount++] = new BaseParam(BaseParam::GUI_PARAMETER_LEVEL, &module->parameter[i]);
 	}

 	menu->setParams(paramList, paramCount);

 	return menu;
}
