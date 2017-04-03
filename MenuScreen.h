#ifndef MENUSCREEN
#define MENUSCREEN

#include "IMenuScreen.h"
#include <string>
#include "eCurses.h"
#include "DataBus.h"
#include <vector>

class MenuScreen : public IMenuScreen
{
public:
	MenuScreen(DataBus& Data);

	virtual void DrawOverlay(int DrawingCursor, int IncrementBy) override;
	virtual int MaxCursorPos() override;
	virtual void MoveCursor(int By) override;
	void AcceptSelectedOption() =0;

protected:
	DataBus& Data;

	int CursorPosition;

	std::vector<std::string> Options;

	int MaxOptions;
};

#endif
