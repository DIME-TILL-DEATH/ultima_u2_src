#ifndef _PROCESSING_PARAM_DESCRIPTOR_H_
#define _PROCESSING_PARAM_DESCRIPTOR_H_

#include "appdefs.h"

typedef void (*setter_handler_t)(uint32_t value);

typedef struct
{
	uint16_t* ptr;
	uint16_t min;
	uint16_t max;
	const char* handlerStr;
	const char* name;
	setter_handler_t setterHandler;
}TParamDescriptor;


#endif /* _PROCESSING_PARAM_DSCRIPTOR_H_ */
