#ifndef _PARAMLISTMENU_H_
#define _PARAMLISTMENU_H_

#include "abstractmenu.h"

//#include "sharc.h"
//
//#include "system.h"
//#include "modules.h"
//
//#include "display_task.h"
//
//#include "bitmaps.h"
//#include "icons_bitmap.h"

#include "listmenuparams/baseparam.h"
#include "listmenuparams/stringlistparam.h"
#include "listmenuparams/submenuparam.h"

class ParamListMenu : public AbstractMenu
{
public:
	ParamListMenu(AbstractMenu* parent, gui_menu_type menuType);
	~ParamListMenu() override;

	void setParams(BaseParam** settlingParamList, uint8_t setlingParamCount);

	virtual void show(TShowMode showMode = FirstShow) override;
	virtual void task() override;
	virtual void refresh() override;

	virtual void encoderPressed() override;
	virtual void encoderClockwise() override;
	virtual void encoderCounterClockwise() override;

	static constexpr uint8_t maxParamCount = 16;

//	void setTapDestination(System::TapDestination tapDst) { m_tapDst = tapDst; }

	static constexpr uint8_t paramsOnPage = 8;
	static constexpr uint8_t leftPad = 0;

protected:
	uint8_t m_currentParamNum = 0;

	BaseParam* m_paramsList[maxParamCount];
	uint8_t m_paramsCount{0};

	uint8_t m_firstSelectableParam;
	uint8_t m_lastSelectableParam;

//	System::TapDestination m_tapDst{System::TapDestination::TAP_OFF};
//	bool m_drawIcon{true};

	int8_t m_currentPageNumber{-1};

	uint8_t m_pagesCount;

	bool m_encoderKnobSelected;

	void printPage(bool forceDrawIcon = false);
};


#endif
