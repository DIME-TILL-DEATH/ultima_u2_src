#include "abstractmenu.h"

AbstractMenu* currentMenu = nullptr;
bool AbstractMenu::blinkFlag = false;
uint8_t AbstractMenu::subMenusToRoot = 1;

gui_menu_type AbstractMenu::menuType()
{
	return m_menuType;
}

void AbstractMenu::keyEditEsc()
{
	returnToParent();
}

void AbstractMenu::setTopLevelMenu(AbstractMenu* parent)
{
	topLevelMenu = parent;
}

void AbstractMenu::showChild(AbstractMenu* child)
{
	shownChildMenu = child;
	child->setTopLevelMenu(this);
	currentMenu = this;
	child->show();
}

void AbstractMenu::returnToParent()
{
	if(topLevelMenu)
	{
		currentMenu = topLevelMenu;
		topLevelMenu->returnFromChildMenu();
	}
}

void AbstractMenu::returnFromChildMenu(TReturnMode returnMode)
{
	currentMenu = this;

	switch(returnMode)
	{
		case TReturnMode::DeleteChild:
		{
			if(shownChildMenu)
			{
				delete shownChildMenu;
				shownChildMenu = nullptr;
			}
			show(TShowMode::ReturnShow);
			break;
		}

		case TReturnMode::KeepChild:
		{
			show(TShowMode::ReturnShow);
			break;
		}

		case TReturnMode::ReturnToRoot:
		{
			if(shownChildMenu)
			{
				delete shownChildMenu;
				shownChildMenu = nullptr;
			}

			if(topLevelMenu)
			{
				if(subMenusToRoot == 1) topLevelMenu->returnFromChildMenu();
				else
				{
					subMenusToRoot--;
					topLevelMenu->returnFromChildMenu(TReturnMode::ReturnToRoot);
				}
			}
			else
			{
				subMenusToRoot = 1;
				show(TShowMode::ReturnShow);
			}
			break;
		}
	}
}


//void AbstractMenu::setRunningString(StringOutParam* runningString)
//{
//	m_runningString = runningString;
//}
//
//StringOutParam* AbstractMenu::getRunningString()
//{
//	return m_runningString;
//}

void AbstractMenu::restartBlinking(uint8_t val)
{
	tim4.update_interrupt_flag_clear();
	tim4.counter = 0xffff;
//	tim4_fl = val;
	blinkFlag = val;
}
