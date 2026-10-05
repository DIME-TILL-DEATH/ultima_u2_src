#include "metronomemenu.h"

#include "gui/fonts/font.h"
#include "gui/listmenuparams/customparam.h"
#include "tasks/display_task.h"

//#include "init.h"

#include "processing/metronome.h"

MetronomeMenu::MetronomeMenu(AbstractMenu* parent)
	: ParamListMenu(parent, MENU_METRONOME)
{
	BaseParam* params[3];

	params[0] = new BaseParam(BaseParam::GUI_PARAMETER_NUM, &metronomeModuleDescriptor.parameter[0]);
	params[0]->setDisplayPosition(63);

	params[1] = new CustomParam(CustomParam::TDisplayType::Number, &metronomeModuleDescriptor.parameter[1]);
	params[1]->setScaling(1, 0);
	params[1]->setDisplayPosition(63);

	params[2] = new BaseParam(BaseParam::GUI_PARAMETER_LEVEL, &metronomeModuleDescriptor.parameter[2]);
	params[2]->setDisplayPosition(60);

	setParams(params, 3);
}

MetronomeMenu::~MetronomeMenu() = default;

//void MetronomeMenu::show(TShowMode showMode)
//{
////	blinkFlag = 1;
//	currentMenu = this;
//	m_currentParamNum = 0;
//	m_encoderKnobSelected = false;
//	m_firstSelectableParam = 0;
//	m_lastSelectableParam = 2;
//	drawValueRow();
//}

//void MetronomeMenu::refresh()
//{
//	drawValueRow();
//}

//void MetronomeMenu::task()
//{
//	if(!m_encoderKnobSelected)
//		display_task->line_5x7(leftPad, m_currentParamNum % paramsOnPage,
//			m_paramsList[m_currentParamNum]->name(),
//			(Font::TFontState)(Font::fnsHighlight * blinkFlag));
//	else
//		display_task->line_5x7(leftPad, m_currentParamNum % paramsOnPage,
//			m_paramsList[m_currentParamNum]->name(),
//			Font::fnsUnderscore);
//}

//void MetronomeMenu::encoderPressed()
//{
//	if(m_currentParamNum == 0)
//	{
//		globalRuntime.onOff.value = globalRuntime.onOff.value ? 0 : 1;
//		metronom_start = globalRuntime.onOff.value;
//		if(metronom_start)
//		{
//			metronom_counter = 0;
//			temp_counter = 0;
//		}
//		global_runtime_mark_dirty();
//		drawValueRow();
//		return;
//	}
//
//	if(m_paramsList[m_currentParamNum]->disabled()) return;
//	m_paramsList[m_currentParamNum]->select(m_encoderKnobSelected);
//	if(m_encoderKnobSelected)
//		display_task->line_5x7(leftPad, m_currentParamNum % paramsOnPage,
//			m_paramsList[m_currentParamNum]->name(),
//			Font::fnsHighlight);
//	restartBlinking(1);
//}
//
//void MetronomeMenu::encoderClockwise()
//{
//	if(!m_encoderKnobSelected)
//	{
//		if(m_currentParamNum < m_lastSelectableParam)
//		{
//			m_currentParamNum++;
//			drawValueRow();
//			restartBlinking(0);
//		}
//		return;
//	}
//
//	if(m_currentParamNum == 1)
//	{
//		if(globalRuntime.tempo.value < tempoMax)
//		{
//			globalRuntime.tempo.value++;
//			updateRuntimeValues();
//			global_runtime_mark_dirty();
//		}
//	}
//	else if(m_currentParamNum == 2)
//	{
//		if(globalRuntime.volume.value < volumeMax)
//		{
//			globalRuntime.volume.value++;
//			updateRuntimeValues();
//			global_runtime_mark_dirty();
//		}
//	}
//
//	drawValueRow();
//}
//
//void MetronomeMenu::encoderCounterClockwise()
//{
//	if(!m_encoderKnobSelected)
//	{
//		if(m_currentParamNum > m_firstSelectableParam)
//		{
//			m_currentParamNum--;
//			drawValueRow();
//			restartBlinking(0);
//		}
//		return;
//	}
//
//	if(m_currentParamNum == 1)
//	{
//		if(globalRuntime.tempo.value > tempoMin)
//		{
//			globalRuntime.tempo.value--;
//			updateRuntimeValues();
//			global_runtime_mark_dirty();
//		}
//	}
//	else if(m_currentParamNum == 2)
//	{
//		if(globalRuntime.volume.value > volumeMin)
//		{
//			globalRuntime.volume.value--;
//			updateRuntimeValues();
//			global_runtime_mark_dirty();
//		}
//	}
//
//	drawValueRow();
//}
//
//void MetronomeMenu::syncGlobalRuntime()
//{
//	globalRuntime.onOff.value = metronom_start ? 1 : 0;
//	globalRuntime.tempo.value = 120;
//	globalRuntime.volume.value = metronom_vol;
//}
//
//void MetronomeMenu::updateRuntimeValues()
//{
//	metronom_start = globalRuntime.onOff.value;
//	metronom_int = 48000.0f / (globalRuntime.tempo.value / 60.0f) + 0.5f;
//	metronom_vol = globalRuntime.volume.value;
//	if(metronom_start)
//	{
//		metronom_counter = 0;
//		temp_counter = 0;
//	}
//}
//
//void MetronomeMenu::drawValueRow()
//{
//	display_task->clear();
//	display_task->line_5x7(0, 0, (char*)"Metronome", 0);
//	display_task->line_5x7(0, 1, (char*)"Tempo", 0);
//	display_task->line_5x7(0, 2, (char*)"Volume", 0);
//
//	display_task->line_5x7(63, 0, (char*)(metronom_start ? "On " : "Off"), 0);
//	display_task->num_5x7(63, 1, globalRuntime.tempo.value, 0);
//	display_task->par_indic(60, 2, globalRuntime.volume.value);
//
//	display_task->line_5x7(leftPad, m_currentParamNum % paramsOnPage,
//		m_paramsList[m_currentParamNum]->name(),
//		(m_encoderKnobSelected ? Font::fnsUnderscore : (Font::TFontState)(Font::fnsHighlight * blinkFlag)));
//}
