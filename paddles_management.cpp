#include "paddles_management.h"


void paddles_management::MovePaddle(CommandType Command)
{
	if (!IsCommandCorrect(Command)) mvprintw(Data.ScreenX / 2 - 12, Data.ScreenY / 2, "Incorrect Command Type!");
	else
		switch (Command)
		{
		case (PaddleLeftMoveUp) : if (PaddleLeft.PosY -PaddleLeft.Lenght / 2 > Data.BorderUp.Padding + 1) PaddleLeft.PosY--; break;
		case (PaddleLeftMoveDown) : if (PaddleLeft.PosY + PaddleLeft.Lenght / 2 < Data.ScreenY - Data.BorderDown.Padding - 2) PaddleLeft.PosY++; break;
		case (PaddleRightMoveUp) : if (PaddleRight.PosY - PaddleRight.Lenght / 2 > Data.BorderUp.Padding + 1) PaddleRight.PosY--; break;
		case (PaddleRightMoveDown) : if (PaddleRight.PosY + PaddleRight.Lenght / 2 < Data.ScreenY - Data.BorderDown.Padding - 2) PaddleRight.PosY++; break;
		default: break;
		}
	UpdatePaddlesInfo();
}

paddles_management::paddles_management(DataBus& Data) : Data{ Data }
{
	UpdatePaddlesSize();

	PaddleLeft.PosY = Data.ScreenY / 2;
	PaddleRight.PosY = Data.ScreenY / 2;

	PaddleLeft.PosX = (Data.BorderLeft.Padding > 0) ? Data.BorderLeft.Padding + 1 : 1;
	PaddleRight.PosX = (Data.BorderRight.Padding > 0) ? Data.ScreenX - Data.BorderRight.Padding - 1 : Data.ScreenX - 2;

	UpdatePaddlesInfo();
}


paddles_management::~paddles_management()
{
}

void  paddles_management::UpdatePaddlesSize()
{
	PaddleLeft.Lenght = (Data.ScreenY / 8) + (Data.ScreenY / 8) % 2 + 3;
	PaddleRight.Lenght = (Data.ScreenY / 8) + (Data.ScreenY / 8) % 2 + 3;
}

void paddles_management::UpdatePaddlesInfo()
{
	Data.PaddleLeftInfo.Lenght = PaddleLeft.Lenght;
	Data.PaddleRightInfo.Lenght = PaddleRight.Lenght;

	Data.PaddleLeftInfo.PosX = PaddleLeft.PosX;
	Data.PaddleRightInfo.PosX = PaddleRight.PosX;

	Data.PaddleLeftInfo.PosY = PaddleLeft.PosY;
	Data.PaddleRightInfo.PosY = PaddleRight.PosY;
}

bool paddles_management::IsCommandCorrect(CommandType Command)
{
	switch (Command)
	{
	case (PaddleLeftMoveUp) :
	case (PaddleLeftMoveDown) :
	case (PaddleRightMoveUp) :
	case (PaddleRightMoveDown) : return true;
	default: return false;
	}
}
