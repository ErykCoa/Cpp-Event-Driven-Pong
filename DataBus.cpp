#include "DataBus.h"

DataBus::DataBus(int Paddings[4])
{
	PrepareWindow();

	BorderUp.Padding = Paddings[0];
	BorderDown.Padding = Paddings[1];
	BorderLeft.Padding = Paddings[2];
	BorderRight.Padding = Paddings[3];

	AssignedControls[Nothing] = NULL;
	AssignedControls[Exit] = 'q';
	AssignedControls[Accept] = ' ';
	AssignedControls[CommandType::ChangeBallSize] = 'o';
	AssignedControls[PaddleLeftMoveUp] = 'd';
	AssignedControls[PaddleLeftMoveDown] = 'c';
	AssignedControls[PaddleRightMoveUp] = 'k';
	AssignedControls[PaddleRightMoveDown] = 'm';

	LastPlayer = None;
}

void DataBus::SoftReset()
{
	LastPlayer = None;

	BallInfo = { 0,0,0,0,0,0 };

	ScoreLeft = 0;
	ScoreRight = 0;

	Events.RemoveAllHandlers();

	UserCommandsBuffer.PopBuffer();
	DrawingQueue.PopBuffer();
}


void DataBus::PrepareWindow()
{
	Screen = initscr();
	noecho();
	keypad(Screen, true);
	raw();
	curs_set(0);
	start_color();

	resize_term(40, 150);

	getmaxyx(Screen, ScreenY, ScreenX);
}

