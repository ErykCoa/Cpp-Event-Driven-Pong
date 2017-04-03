#include "MenuScreen.h"

MenuScreen::MenuScreen(DataBus& Data) : Data{ Data }
{
}

void MenuScreen::DrawOverlay(int DrawingCursor, int IncrementBy)
{
	for (int index = 0; index < MaxOptions; ++index)
	{
		ecur::DrawLineOfText(Data.Screen, DrawingCursor, 0, Options[index], (index == CursorPosition) ? SelectedText : Text, A_BOLD);
		DrawingCursor += IncrementBy+1;
	}
}

int MenuScreen::MaxCursorPos()
{
	return MaxOptions - 1;
}

void MenuScreen::MoveCursor(int By)
{
	if (0 <= CursorPosition + By && CursorPosition + By < MaxOptions)
		CursorPosition += By;
}

