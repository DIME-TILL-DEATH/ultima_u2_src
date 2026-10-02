#include "presetnamemenu.h"

#include "tasks/display_task.h"

//extern const uint8_t ascii_low1[];
//extern const uint8_t ascii_low2[];
//extern const uint8_t ascii_hig1[];
//extern const uint8_t ascii_hig2[];

const uint8_t ascii_low1[] = " abcdefghijklmnopqrst";
const uint8_t ascii_low2[] = "uvwxyz0123456789!@#$%";
const uint8_t ascii_hig1[] = "ABCDEFGHIJKLMNOPQRSTU";
const uint8_t ascii_hig2[] = "VWXYZ{}()-+_=<>?*.,/&";

PresetNameMenu::PresetNameMenu(AbstractMenu* parent, uint8_t* presetName, uint8_t* presetNameAlt)
{
	topLevelMenu = parent;
	m_menuType = MENU_PRESET_NAME;
	m_name = presetName;
	m_altName = presetNameAlt;
	m_cursor = 0;
	m_symbolIndex = 0;
	m_editMode = false;
	m_shift = false;
	m_tempChar = 0;
}

void PresetNameMenu::show(TShowMode showMode)
{
	currentMenu = this;
	blinkFlag = 1;
	display_task->clear();
	redrawName();
	drawKeyboard();
}

void PresetNameMenu::task()
{
	const uint8_t nameCursor = presetNameCursorType(m_editMode);
	if(m_cursor < 14)
	{
		display_task->sym_5x7(m_cursor * 6 + 2, 0, m_name[m_cursor], nameCursor);
	}
	else
	{
		display_task->sym_5x7((m_cursor - 14) * 6 + 2, 1, m_altName[m_cursor - 14], nameCursor);
	}

	if(m_editMode)
	{
		if(m_symbolIndex < 21)
		{
			if(!m_shift)
				display_task->sym_5x7(m_symbolIndex * 6, 2, ascii_low1[m_symbolIndex], keyCursorType());
			else
				display_task->sym_5x7(m_symbolIndex * 6, 2, ascii_hig1[m_symbolIndex], keyCursorType());
		}
		else
		{
			if(!m_shift)
				display_task->sym_5x7((m_symbolIndex - 21) * 6, 3, ascii_low2[m_symbolIndex - 21], keyCursorType());
			else
				display_task->sym_5x7((m_symbolIndex - 21) * 6, 3, ascii_hig2[m_symbolIndex - 21], keyCursorType());
		}
	}
}

void PresetNameMenu::encoderPressed()
{
	if(!m_editMode)
	{
		m_editMode = true;
		if(m_cursor < 14)
			display_task->sym_5x7(m_cursor * 6 + 2, 0, m_name[m_cursor], 1);
		else
			display_task->sym_5x7((m_cursor - 14) * 6 + 2, 1, m_altName[m_cursor - 14], 1);
	}
	else
	{
		commitCurrentSymbol();
	}
	
	restartBlinking(0);
}

void PresetNameMenu::keyEditEsc()
{
	if(m_editMode)
	{
		m_shift = !m_shift;
		display_task->line_5x7(0, 2, (char*)(m_shift ? ascii_hig1 : ascii_low1), 0);
		display_task->line_5x7(0, 3, (char*)(m_shift ? ascii_hig2 : ascii_low2), 0);
		m_tempChar = m_shift ? ((m_symbolIndex < 21) ? ascii_hig1[m_symbolIndex] : ascii_hig2[m_symbolIndex - 21])
						  : ((m_symbolIndex < 21) ? ascii_low1[m_symbolIndex] : ascii_low2[m_symbolIndex - 21]);
	}
	else
	{
		returnToParent();
	}
}

void PresetNameMenu::encoderClockwise()
{
	if(!m_editMode)
	{
		if(m_cursor < 27)
		{
			if(m_cursor > 13)
			{
				display_task->sym_5x7((m_cursor - 14) * 6 + 2, 1, m_altName[(m_cursor++ - 14)], 0);
				display_task->sym_5x7((m_cursor - 14) * 6 + 2, 1, m_altName[(m_cursor - 14)], 2);
			}
			if(m_cursor == 13)
			{
				display_task->sym_5x7(m_cursor * 6 + 2, 0, m_name[m_cursor++], 0);
				display_task->sym_5x7((m_cursor - 14) * 6 + 2, 1, m_altName[(m_cursor - 14)], 2);
			}
			if(m_cursor < 13)
			{
				display_task->sym_5x7(m_cursor * 6 + 2, 0, m_name[m_cursor++], 0);
				display_task->sym_5x7(m_cursor * 6 + 2, 0, m_name[m_cursor], 2);
			}
		}
	}
	else
	{
		if(m_symbolIndex < 20)
		{
			if(!m_shift)
			{
				display_task->sym_5x7(m_symbolIndex * 6, 2, ascii_low1[m_symbolIndex++], 0);
				display_task->sym_5x7(m_symbolIndex * 6, 2, ascii_low1[m_symbolIndex], 0);
				m_tempChar = ascii_low1[m_symbolIndex];
			}
			else
			{
				display_task->sym_5x7(m_symbolIndex * 6, 2, ascii_hig1[m_symbolIndex++], 0);
				display_task->sym_5x7(m_symbolIndex * 6, 2, ascii_hig1[m_symbolIndex], 0);
				m_tempChar = ascii_hig1[m_symbolIndex];
			}
		}
		else
		{
			if(!m_shift)
			{
				if(m_symbolIndex == 41)
				{
					display_task->sym_5x7((m_symbolIndex - 21) * 6, 3, ascii_low2[m_symbolIndex - 21], 0);
					m_symbolIndex = 0;
					display_task->sym_5x7(m_symbolIndex * 6, 2, ascii_low1[m_symbolIndex], 0);
					m_tempChar = ascii_low1[m_symbolIndex];
				}
				else
				{
					if(m_symbolIndex == 20)
						display_task->sym_5x7(m_symbolIndex * 6, 2, ascii_low1[m_symbolIndex++], 0);
					else
						display_task->sym_5x7((m_symbolIndex - 21) * 6, 3, ascii_low2[m_symbolIndex++ - 21], 0);
					display_task->sym_5x7((m_symbolIndex - 21) * 6, 3, ascii_low2[m_symbolIndex - 21], 0);
					m_tempChar = ascii_low2[m_symbolIndex - 21];
				}
			}
			else
			{
				if(m_symbolIndex == 41)
				{
					display_task->sym_5x7((m_symbolIndex - 21) * 6, 3, ascii_hig2[m_symbolIndex - 21], 0);
					m_symbolIndex = 0;
					display_task->sym_5x7(m_symbolIndex * 6, 2, ascii_hig1[m_symbolIndex], 0);
					m_tempChar = ascii_hig1[m_symbolIndex];
				}
				else
				{
					if(m_symbolIndex == 20)
						display_task->sym_5x7(m_symbolIndex * 6, 2, ascii_hig1[m_symbolIndex++], 0);
					else
						display_task->sym_5x7((m_symbolIndex - 21) * 6, 3, ascii_hig2[m_symbolIndex++ - 21], 0);
					display_task->sym_5x7((m_symbolIndex - 21) * 6, 3, ascii_hig2[m_symbolIndex - 21], 0);
					m_tempChar = ascii_hig2[m_symbolIndex - 21];
				}
			}
		}
	}

	restartBlinking(0);
}

void PresetNameMenu::encoderCounterClockwise()
{
	if(!m_editMode)
	{
		if(m_cursor > 0)
		{
			if(m_cursor < 14)
			{
				display_task->sym_5x7(m_cursor * 6 + 2, 0, m_name[m_cursor--], 0);
				display_task->sym_5x7(m_cursor * 6 + 2, 0, m_name[m_cursor], 2);
			}
			if(m_cursor == 14)
			{
				display_task->sym_5x7((m_cursor - 14) * 6 + 2, 1, m_altName[(m_cursor-- - 14)], 0);
				display_task->sym_5x7(m_cursor * 6 + 2, 0, m_name[m_cursor], 2);
			}
			if(m_cursor > 14)
			{
				display_task->sym_5x7((m_cursor - 14) * 6 + 2, 1, m_altName[(m_cursor-- - 14)], 0);
				display_task->sym_5x7((m_cursor - 14) * 6 + 2, 1, m_altName[(m_cursor - 14)], 2);
			}
		}
	}
	else
	{
		if(m_symbolIndex < 21)
		{
			if(!m_shift)
			{
				if(m_symbolIndex == 0)
				{
					display_task->sym_5x7((m_symbolIndex) * 6, 2, ascii_low1[m_symbolIndex], 0);
					m_symbolIndex = 41;
					display_task->sym_5x7((m_symbolIndex - 21) * 6, 3, ascii_low2[m_symbolIndex - 21], 0);
					m_tempChar = ascii_low2[m_symbolIndex - 21];
				}
				else
				{
					display_task->sym_5x7(m_symbolIndex * 6, 2, ascii_low1[m_symbolIndex--], 0);
					display_task->sym_5x7(m_symbolIndex * 6, 2, ascii_low1[m_symbolIndex], 0);
					m_tempChar = ascii_low1[m_symbolIndex];
				}
			}
			else
			{
				if(m_symbolIndex == 0)
				{
					display_task->sym_5x7((m_symbolIndex) * 6, 2, ascii_hig1[m_symbolIndex], 0);
					m_symbolIndex = 41;
					display_task->sym_5x7((m_symbolIndex - 21) * 6, 3, ascii_hig2[m_symbolIndex - 21], 0);
					m_tempChar = ascii_hig2[m_symbolIndex - 21];
				}
				else
				{
					display_task->sym_5x7(m_symbolIndex * 6, 2, ascii_hig1[m_symbolIndex--], 0);
					display_task->sym_5x7(m_symbolIndex * 6, 2, ascii_hig1[m_symbolIndex], 0);
					m_tempChar = ascii_hig1[m_symbolIndex];
				}
			}
		}
		else
		{
			if(m_symbolIndex > 20)
			{
				if(!m_shift)
				{
					if(m_symbolIndex == 21)
					{
						display_task->sym_5x7((m_symbolIndex - 21) * 6, 3, ascii_low2[m_symbolIndex-- - 21], 0);
						display_task->sym_5x7(m_symbolIndex * 6, 2, ascii_low1[m_symbolIndex], 1);
						m_tempChar = ascii_low1[m_symbolIndex];
					}
					else
					{
						display_task->sym_5x7((m_symbolIndex - 21) * 6, 3, ascii_low2[m_symbolIndex-- - 21], 0);
						display_task->sym_5x7((m_symbolIndex - 21) * 6, 3, ascii_low2[m_symbolIndex - 21], 1);
						m_tempChar = ascii_low2[m_symbolIndex - 21];
					}
				}
				else
				{
					if(m_symbolIndex == 21)
					{
						display_task->sym_5x7((m_symbolIndex - 21) * 6, 3, ascii_hig2[m_symbolIndex-- - 21], 0);
						display_task->sym_5x7(m_symbolIndex * 6, 2, ascii_hig1[m_symbolIndex], 1);
						m_tempChar = ascii_hig1[m_symbolIndex];
					}
					else
					{
						display_task->sym_5x7((m_symbolIndex - 21) * 6, 3, ascii_hig2[m_symbolIndex-- - 21], 0);
						display_task->sym_5x7((m_symbolIndex - 21) * 6, 3, ascii_hig2[m_symbolIndex - 21], 0);
						m_tempChar = ascii_hig2[m_symbolIndex - 21];
					}
				}
			}
		}
	}

	restartBlinking(0);
}

void PresetNameMenu::redrawName()
{
	for(uint8_t i = 0; i < 14; ++i)
		display_task->sym_5x7(i * 6 + 2, 0, m_name[i], 0);

	for(uint8_t i = 0; i < 14; ++i)
		display_task->sym_5x7(i * 6 + 2, 1, m_altName[i], 0);
}

void PresetNameMenu::redrawSelector()
{
	if(m_editMode)
	{
		if(m_symbolIndex < 21)
		{
			if(!m_shift)
				display_task->sym_5x7(m_symbolIndex * 6, 2, ascii_low1[m_symbolIndex], keyCursorType());
			else
				display_task->sym_5x7(m_symbolIndex * 6, 2, ascii_hig1[m_symbolIndex], keyCursorType());
		}
		else
		{
			if(!m_shift)
				display_task->sym_5x7((m_symbolIndex - 21) * 6, 3, ascii_low2[m_symbolIndex - 21], keyCursorType());
			else
				display_task->sym_5x7((m_symbolIndex - 21) * 6, 3, ascii_hig2[m_symbolIndex - 21], keyCursorType());
		}
	}
}

void PresetNameMenu::drawKeyboard()
{
	display_task->line_5x7(0, 2, (char*)ascii_low1, 0);
	display_task->line_5x7(0, 3, (char*)ascii_low2, 0);

	if(m_shift)
	{
		display_task->line_5x7(0, 2, (char*)ascii_hig1, 0);
		display_task->line_5x7(0, 3, (char*)ascii_hig2, 0);
	}

	redrawSelector();
}

void PresetNameMenu::commitCurrentSymbol()
{
	m_editMode = false;

	if(m_cursor < 14)
	{
		m_name[m_cursor] = m_tempChar;
		display_task->sym_5x7(m_cursor * 6 + 2, 0, m_name[m_cursor], 0);
	}
	else
	{
		m_altName[m_cursor - 14] = m_tempChar;
		display_task->sym_5x7((m_cursor - 14) * 6 + 2, 1, m_altName[m_cursor - 14], 0);
	}

	if(!m_shift)
	{
		if(m_symbolIndex < 21)
			display_task->sym_5x7(m_symbolIndex * 6, 2, ascii_low1[m_symbolIndex], 0);
		else
			display_task->sym_5x7((m_symbolIndex - 21) * 6, 3, ascii_low2[m_symbolIndex - 21], 0);
	}
	else
	{
		if(m_symbolIndex < 21)
			display_task->sym_5x7(m_symbolIndex * 6, 2, ascii_hig1[m_symbolIndex], 0);
		else
			display_task->sym_5x7((m_symbolIndex - 21) * 6, 3, ascii_hig2[m_symbolIndex - 21], 0);
	}
}

Font::TFontState PresetNameMenu::presetNameCursorType(bool editing)
{
	return editing ? Font::TFontState::fnsUnderscore :
			(AbstractMenu::blinkFlag ? Font::TFontState::fnsHighlight : Font::TFontState::fnsNormal);
}

Font::TFontState PresetNameMenu::keyCursorType()
{
	return AbstractMenu::blinkFlag ? Font::TFontState::fnsUnderscore : Font::TFontState::fnsNormal;
}
