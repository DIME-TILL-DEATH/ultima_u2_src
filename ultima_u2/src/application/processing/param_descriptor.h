#ifndef _PROCESSING_PARAM_DESCRIPTOR_H_
#define _PROCESSING_PARAM_DESCRIPTOR_H_

#include "appdefs.h"

typedef void (*setter_handler_t)(uint32_t value);

typedef struct
{
	int16_t value;
	int16_t min;
	int16_t max;
	const char* name;
}TParamDescriptor;


#endif /* _PROCESSING_PARAM_DSCRIPTOR_H_ */
