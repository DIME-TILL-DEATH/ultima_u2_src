#ifndef MODULEMENUFACTORY_H_
#define MODULEMENUFACTORY_H_

#include "modulemenu.h"
#include "processing/audio_process.h"

class ModuleMenuFactory
{
public:
	static AbstractMenu* createModuleMenu(AbstractMenu* parent, TModuleRuntime* module);

private:

	static AbstractMenu* createCompressorMenu(AbstractMenu* parent, TModuleRuntime* module);
	static AbstractMenu* createMetronomeMenu(AbstractMenu* parent, TModuleRuntime* module);
};

#endif /* MODULEMENUFACTORY_H_ */
