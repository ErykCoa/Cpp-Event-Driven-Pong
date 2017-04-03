#ifndef IMENUSCREEN
#define IMENUSCREEN

class IMenuScreen
{
public:
	virtual void DrawOverlay(int DrawingCursor, int IncrementBy) = 0;
	virtual int MaxCursorPos() = 0;
	virtual void MoveCursor(int By) = 0;
	virtual void AcceptSelectedOption() = 0;
};

#endif