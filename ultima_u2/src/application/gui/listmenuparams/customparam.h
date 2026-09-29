#ifndef CUSTOMPARAM_H_
#define CUSTOMPARAM_H_

#include "baseparam.h"

class CustomParam: public BaseParam
{
public:

	enum TDisplayType
	{
		Default,
		Number,
		Level,
		Mix,
		Pan,
		String,
		Custom
	};

	CustomParam(TDisplayType displayType, TParamDescriptor* paramDesc);
	~CustomParam();

	const char* name() override;
	uint32_t value() const override;
	void increaseParam() override;
	void decreaseParam() override;
	void printParam(uint8_t yDisplayPosition) override;
//	void setData() override;

	void setStrings(std::initializer_list<const char*> stringList, uint8_t maxStringLength);

	void (*increaseCallback)(int16_t *valuePtr){nullptr};
	void (*decreaseCallback)(int16_t *valuePtr){nullptr};
	uint32_t (*valueCallback)(int16_t *valuePtr){nullptr};

	void (*encoderPressCallback)(int16_t* parameter){nullptr};
	void (*keyDownCallback)(int16_t* parameter){nullptr};
	const char* (*nameCallback)(int16_t* parameter){nullptr};
	void (*printCallback)(int16_t* parameter){nullptr};
//	void (*setToDspCallback)(int16_t* parameter){nullptr};

private:
	TDisplayType m_displayType;

	char** m_strings{nullptr};
	uint8_t valuesTable;
	uint8_t m_stringCount;
	uint8_t m_maxStringLength;
};

#endif /* CUSTOMPARAM_H_ */
