#include "baseparam.h"

#include "gui/paramlistmenu.h"

#include "tasks/display_task.h"
//#include "io_task.h"
//#include "sharc_task.h"


BaseParam::BaseParam(gui_param_type paramType, TParamDescriptor* paramDescriptor)
{
	m_type = paramType;
	m_descriptor = paramDescriptor;
}

void BaseParam::setDisplayPosition(uint8_t xCoord)
{
	m_xDisplayPosition = xCoord;
}

void BaseParam::setScaling(uint8_t stepSize, int32_t offset)
{
	m_stepSize = stepSize;
	m_offset = offset;
}

void BaseParam::setBounds(int32_t minBound, int32_t maxBound)
{
	m_minValue = minBound;
	m_maxValue = maxBound;
}

void BaseParam::select(bool& selected)
{
	if(!selected)
	{
		selected = true;
	}
	else
	{
		selected = false;
	}
}

const char* BaseParam::name()
{
	if(!m_descriptor) return "";

	if(m_disabled) return " -- ";
	else
	{
		if(!m_descriptor) return "";
		else return m_descriptor->name;
	}
}

void BaseParam::setByteSize(uint8_t size)
{
	m_byteSize = size;
}

void BaseParam::setIndicatorType(TIndicatorType indicatorType)
{
	m_indicatorType = indicatorType;
}

uint32_t BaseParam::value() const
{
	if(!m_descriptor) return 0;
	else
	{
//		uint32_t fullValue = 0;
//		memcpy(&fullValue, m_descriptor->ptr, m_byteSize);
		return m_descriptor->value + m_offset;
	}
}

void BaseParam::setInverse(bool isInverse)
{
	m_inverse = isInverse;
}


bool BaseParam::updatedByClick()
{
	if(m_isUpdatingByClick)
	{
		m_descriptor->value += m_stepSize;
		if(m_descriptor->value > m_maxValue)
			m_descriptor->value = m_minValue;

		return true;
	}
	else
	{
		return false;
	}
}

void BaseParam::increaseParam()
{
	if(!m_descriptor) return;

//	int32_t data = 0;
//	if(m_byteSize>1) memcpy(&data, m_descriptor->ptr, m_byteSize); // only for positive values
//	else data = (int8_t)(*(uint8_t*)(m_descriptor->ptr));

	if(m_descriptor->value < m_maxValue)
	{
		if(m_type != GUI_PARAMETER_NUM)
			encoderSpeedIncrease();
		else
			m_descriptor->value += m_stepSize;
	}
}

void BaseParam::decreaseParam()
{
	if(!m_descriptor) return;

//	int32_t data = 0;
//	if(m_byteSize>1) memcpy(&data, m_descriptor->ptr, m_byteSize); // only for positive values
//	else data = (int8_t)(*(uint8_t*)(m_descriptor->ptr));

	if(m_descriptor->value > m_minValue)
	{
		if(m_type != GUI_PARAMETER_NUM)
			encoderSpeedDecrease();
		else
			m_descriptor->value -= m_stepSize;
	}
}

void BaseParam::setData()
{
	if(!m_descriptor) return;

//	if(m_descriptor->setterHandler)
//	{
//		int32_t data = 0;
//		memcpy(&data, m_descriptor->ptr, m_byteSize);
//		m_descriptor->setterHandler(data);
//		return;
//	}
}

void BaseParam::printParam(uint8_t yDisplayPosition)
{
	if(m_disabled)
	{
		display_task->line_5x7_clean(m_xDisplayPosition, yDisplayPosition, "     ");
		return;
	}

	// переделать на IndicatorType
	switch(m_type)
	{
		case BaseParam::GUI_PARAMETER_LEVEL:
//			DisplayTask->ParamInd(m_xDisplayPosition, yDisplayPosition, *(uint8_t*)(m_descriptor->ptr) + m_offset);
			display_task->par_indic(m_xDisplayPosition, yDisplayPosition, m_descriptor->value + m_offset);
			break;
		case BaseParam::GUI_PARAMETER_MIX:
//			DisplayTask->ParamIndMix(m_xDisplayPosition, yDisplayPosition, *(uint8_t*)(m_descriptor->ptr) + m_offset);
			break;
		case BaseParam::GUI_PARAMETER_PAN:
//			if(m_inverse) DisplayTask->ParamIndPan(m_xDisplayPosition, yDisplayPosition, m_maxValue - *(uint8_t*)(m_descriptor->ptr) + m_offset);
//			else DisplayTask->ParamIndPan(m_xDisplayPosition, yDisplayPosition, *(uint8_t*)(m_descriptor->ptr) + m_offset);
			break;
		case BaseParam::GUI_PARAMETER_VOLUME:
//			DisplayTask->ParamIndNum(m_xDisplayPosition, yDisplayPosition, *(uint8_t*)(m_descriptor->ptr) + m_offset);
			break;
		case BaseParam::GUI_PARAMETER_NUM:
//			DisplayTask->ParamIndNum(m_xDisplayPosition, yDisplayPosition, *(uint8_t*)(m_descriptor->ptr) + m_offset);
			break;
		default: break;
	}
}

void BaseParam::encoderSpeedIncrease()
{
	tim6.disable();

	int16_t data = m_descriptor->value;
//	if(m_byteSize > 1) memcpy(&data, m_descriptor->ptr, m_byteSize); // only for positive values
//	else data = (int8_t)(*(uint8_t*)(m_descriptor->ptr));


	if(tim6.update_interrupt_flag())
	{
		data += 1;
	}
	else
	{
		if(tim6.counter > 0x3fff)
		{
			data += 1;
		}
		else
		{
			uint8_t curStep;

			if(tim6.counter > 0x1fff) curStep = 2 * m_stepSize;
			else
			{
				if(tim6.counter > 0xfff) curStep = 4 * m_stepSize;
				else
				{
					if(tim6.counter > 0x7ff) curStep = 8 * m_stepSize;
					else curStep = 16 * m_stepSize;
				}
			}

			if(data < (m_maxValue - curStep - 1)) data += curStep;
			else data += 1;
		}
	}

//	memcpy(m_descriptor->ptr, &data, m_byteSize);
	m_descriptor->value = data;

	tim6.counter = 0;
    tim6.update_interrupt_flag_clear();
    tim6.enable();
}

void BaseParam::encoderSpeedDecrease()
{
	if(!m_descriptor) return;

	tim6.disable();

	int32_t data = m_descriptor->value;
//	if(m_byteSize>1) memcpy(&data, m_descriptor->ptr, m_byteSize); // only for positive values
//	else data = (int8_t)(*(uint8_t*)(m_descriptor->ptr));


	if(tim6.update_interrupt_flag())
	{
		data -= 1;
	}
	else
	{
		if(tim6.counter > 0x3fff)
		{
			data -= 1;
		}
		else
		{
			uint8_t curStep;

			if(tim6.counter > 0x1fff) curStep = 2 * m_stepSize;
			else
			{
				if(tim6.counter > 0xfff) curStep = 4 * m_stepSize;
				else
				{
					if(tim6.counter > 0x7ff) curStep = 8 * m_stepSize;
					else curStep = 16 * m_stepSize;
				}
			}

			if(data > (m_minValue + curStep - 1)) data -= curStep;
			else data -= 1;
		}
	}

//	memcpy(m_descriptor->ptr, &data, m_byteSize);

	m_descriptor->value = data;

	tim6.counter = 0;
	tim6.update_interrupt_flag_clear();
	tim6.enable();
}

int16_t BaseParam::encSpeedInc(int16_t data, int16_t max, uint8_t stepSize)
{
	tim6.disable();

	if(tim6.update_interrupt_flag())
	{
		data += stepSize;
	}
	else
	{
		if(tim6.counter > 0x3fff)
			data += stepSize;
		else
		{
			if(tim6.counter > 0x1fff)
			{
				if(data < (max - 1)) data += 2 * stepSize;
				else data += stepSize;
			}
			else
			{
				if(tim6.counter > 0xfff)
				{
					if(data < (max - 3)) data += 4 * stepSize;
					else data += 1 * stepSize;
				}
				else
				{
					if(tim6.counter > 0x7ff)
					{
						if(data < (max - 7)) data += 8 * stepSize;
						else data += 1 * stepSize;
					}
					else
					{
						if(data < (max - 49)) data += 50 * stepSize;
						else data += 1 * stepSize;
					}
				}
			}
		}
	}

	tim6.counter = 0;
	tim6.update_interrupt_flag_clear();
	tim6.enable();
	return data;
}

int16_t BaseParam::encSpeedDec(int16_t data, int16_t min, uint8_t stepSize)
{
	tim6.disable();

	if(tim6.update_interrupt_flag())
	{
		data -= stepSize;
	}
	else
	{
		if(tim6.counter > 0x3fff)
			data -= stepSize;
		else
		{
			if(tim6.counter > 0x1fff)
			{
				if(data > (min + 1)) data -= 2 * stepSize;
				else data -= stepSize;
			}
			else
			{
				if(tim6.counter > 0xfff)
				{
					if(data > (min + 3)) data -= 4 * stepSize;
					else data -= stepSize;
				}
				else
				{
					if(tim6.counter > 0x7ff)
					{
						if(data > (min + 7)) data -= 8 * stepSize;
						else data -= stepSize;
					}
					else
					{
						if(data > (min + 49)) data -= 50 * stepSize;
						else data -= stepSize;
					}
				}
			}
		}
	}

	tim6.counter = 0;
	tim6.update_interrupt_flag_clear();
	tim6.enable();
	return data;
}
