#ifndef PRESETNAMEMENU_H_
#define PRESETNAMEMENU_H_

#include "abstractmenu.h"
#include "gui/fonts/font.h"

class PresetNameMenu : public AbstractMenu
{
public:
	PresetNameMenu(AbstractMenu* parent, uint8_t* presetName, uint8_t* presetNameAlt);

	void show(TShowMode showMode = FirstShow) override;
	void task() override;

	void encoderPressed() override;
	void encoderClockwise() override;
	void encoderCounterClockwise() override;

	void keyEditEsc() override;

	bool editMode() { return m_editMode; } // temporaly while refactoring

private:
	void redrawName();
	void redrawSelector();
	void drawKeyboard();
	void commitCurrentSymbol();

	// Persistent preset data used outside this menu.
	uint8_t* m_name{nullptr};
	uint8_t* m_altName{nullptr};

	// Local UI state only: selection/index counters, not project-wide parameter data.
	uint8_t m_cursor{0};
	uint8_t m_symbolIndex{0};
	bool m_editMode{false};
	bool m_shift{false};
	uint8_t m_tempChar{0};

	Font::TFontState presetNameCursorType(bool editing);
	Font::TFontState keyCursorType();
};

#endif /* PRESETNAMEMENU_H_ */
