#ifndef _PROCESSING_PARAM_DSCRIPTOR_H_
#define _PROCESSING_PARAM_DSCRIPTOR_H_

#include "appdefs.h"

typedef void (*setter_handler_t)(uint32_t value);

typedef struct
{
	void* ptr;
	const char* handlerStr;
	const char* name;
	setter_handler_t setterHandler;
}TParamDescriptor;


#endif /* _PROCESSING_PARAM_DSCRIPTOR_H_ */
