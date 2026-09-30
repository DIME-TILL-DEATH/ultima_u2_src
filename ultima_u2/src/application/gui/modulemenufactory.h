#ifndef MODULEMENUFACTORY_H_
#define MODULEMENUFACTORY_H_

#include "modulemenu.h"
#include "module.h"

class ModuleMenuFactory
{
public:
	static AbstractMenu* createModuleMenu(AbstractMenu* parent, TModuleDescriptor* module);

private:

	static AbstractMenu* createCompressorMenu(AbstractMenu* parent, TModuleDescriptor* module);
};

#endif /* MODULEMENUFACTORY_H_ */
