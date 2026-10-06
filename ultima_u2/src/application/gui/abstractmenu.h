#ifndef _ABSTRACTMENU_H_
#define _ABSTRACTMENU_H_

#include "appdefs.h"


enum gui_menu_type
{
	MENU_MAIN_SCREEN,

	MENU_GATE,
	MENU_COMPRESSOR,
	MENU_PRESET_NAME,
	MENU_METRONOME,
	MENU_ABSTRACT = 255
};

class AbstractMenu
{
public:
	enum TShowMode
	{
		FirstShow,
		ReturnShow
	};

	enum TReturnMode
	{
		KeepChild,
		DeleteChild,
		ReturnToRoot
	};

	AbstractMenu() {};
	virtual ~AbstractMenu() {};

	virtual void show(TShowMode swhoMode = FirstShow) {};
	virtual void refresh() {};
	virtual void returnFromChildMenu(TReturnMode returnMode = DeleteChild);
	virtual void returnToParent();
	virtual void task() {};

	virtual void encoderPressed() {};
	virtual void encoderDblPressed() {};
	virtual void encoderLongPressed() {};
	virtual void encoderClockwise() {};
	virtual void encoderCounterClockwise() {};

	virtual void keyEditEsc();

	gui_menu_type menuType();

	void setTopLevelMenu(AbstractMenu* parent);
	void showChild(AbstractMenu* child);

	static void blinkRoutine() { blinkFlag = !blinkFlag; };

	void restartBlinking(uint8_t val);

protected:
	AbstractMenu* topLevelMenu = nullptr;
	AbstractMenu* shownChildMenu = nullptr;

	gui_menu_type m_menuType{MENU_ABSTRACT};

	static uint8_t subMenusToRoot;
	static bool blinkFlag;
};

extern AbstractMenu* currentMenu;


#endif /* _ABSTRACTMENU_H_ */
