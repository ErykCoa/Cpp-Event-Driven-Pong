#ifndef WINDOW_DRAWING
#define WINDOW_DRAWING

#include <string>
#include "eCurses.h"
#include "enums.h"
#include "BackgroundDrawing.h"
#include "DataBus.h"
#include "Defines.h"


class window_drawing
{

public:

	void AddToDrawingQueue();
	void UpdateScore();
	void ChangeBallSize();

	BallType GetBallType() { return Data.BallType; };

	window_drawing(DataBus& Data);
	~window_drawing();

private:

	BackgroundDrawing Background;

	DataBus& Data;

	void ColorInitialization();
	void UpdateBordersSize();

	void DrawBorders();
	void DrawPaddle(Player WhichPaddle);
	void DrawBall();	
	void DrawScore();

	void ReciveMessage(Event& Event);
	std::chrono::system_clock::time_point CurrentMessageRecived;
	std::string CurrentMessage;
	std::chrono::milliseconds CurrentMessageDuration;
	std::mutex MessageLock;
	
	void DrawErrorMessage();

	char *BorderLeft;
	char *BorderRight;
	char *BorderTop;
	char *BorderBottom;

	std::string score;
	
	void mvvprintw(int, int, char*);
};

#endif