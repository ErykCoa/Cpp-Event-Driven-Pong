#include "BackgroundDrawing.h"

BackgroundDrawing::BackgroundDrawing(DataBus& Data, int MaxElementsCount) : Data { Data }
{
	Data.Events.AddHandler<CE::PrepareFrame>(
		[this](Event arg) {this->Data.DrawingQueue.push({ [this] {this->UpdateBackground(); }, DrawingPriority::Background }); return HandlerReturnCall::Succeed; }
	);

	MaxNumberOfElements = MaxElementsCount;

	BackgroundBuffer = "";

	ClearBuffer();

	auto CurrentTime = std::chrono::system_clock::now();

	while (MaxElementsCount--)
	{
		AddNewBackgroundElement(rand() % (Data.ScreenX - 1 - (Data.BorderLeft.Padding >= 0 ? Data.BorderLeft.Padding : -1) - (Data.BorderRight.Padding >= 0 ? Data.BorderRight.Padding : -1)), CurrentTime);
	}	
}


void BackgroundDrawing::UpdateBackground()
{
	auto CurrentTime = std::chrono::system_clock::now();

	short ForegroundColor;
	pair_content(Data.LastPlayer, &ForegroundColor, 0);

	init_pair(ColorVar, ForegroundColor, COLOR_BLACK);


	CS::BackgroundElementInfo Element;
	for (unsigned index = 0; index < BackgroundElements.size(); ++index)
	{
		Element = BackgroundElements[index];

		if (CurrentTime - Element.LastMoveTime >= std::chrono::milliseconds(1000 / Element.MovementSpeed) )
		{
			auto LocalTimeCopy = CurrentTime - Element.LastMoveTime;

			while (LocalTimeCopy >= std::chrono::milliseconds(1000 / Element.MovementSpeed))
			{
				Element.PosX++;
				LocalTimeCopy -= std::chrono::milliseconds(1000 / Element.MovementSpeed);
			}

			Element.LastMoveTime = CurrentTime;
		}

		if (Element.PosX >= Data.ScreenX - (Data.BorderRight.Padding >= 0 ? Data.BorderRight.Padding : -1) - 1)
		{
			BackgroundElements.erase(BackgroundElements.begin() + index);
			AddNewBackgroundElement(0, CurrentTime);
		}

		if (Data.BallType == Large && ElementIsNearBall(Element))
		{
		attron(COLOR_PAIR(ColorVar) | A_BOLD);

		mvaddch(Element.PosY, Element.PosX, '=');

		attroff(COLOR_PAIR(ColorVar) | A_BOLD);
		}
		else
		{
			attron(COLOR_PAIR(Background)); 

			mvaddch(Element.PosY, Element.PosX, '-');

			attroff(COLOR_PAIR(Background));
		}
	}

}

void BackgroundDrawing::AddNewBackgroundElement(int PosX, std::chrono::system_clock::time_point Time)
{
	CS::BackgroundElementInfo Element{};

	Element.PosX = (Data.BorderLeft.Padding >= 0 ? Data.BorderLeft.Padding : -1) + 1 + PosX;
	Element.PosY = rand() % (Data.ScreenY - (Data.BorderDown.Padding >= 0 ? Data.BorderDown.Padding : -1) - 1) + (Data.BorderUp.Padding >= 0 ? Data.BorderUp.Padding : -1) + 1;
	Element.MovementSpeed = (rand() % 2) ? FOREGROUND_ELEMENT_MOVEMENTSPEED : BACKGROUND_ELEMENT_MOVEMENTSPEED;
	Element.LastMoveTime = Time;

	BackgroundElements.push_back(Element);
}

void BackgroundDrawing::ClearBuffer()
{
	BackgroundBuffer.erase();
	for (int YCopy = Data.ScreenY; YCopy--;)
	 BackgroundBuffer.append(Data.ScreenX, ' ');
}

void BackgroundDrawing::AddToBuffer(int PosY, int PosX, char Char)
{
	BackgroundBuffer[PosX + Data.ScreenX * PosY] = Char;
}

bool BackgroundDrawing::ElementIsNearBall(CS::BackgroundElementInfo Element)
{
	if (abs(Element.PosX - Data.BallInfo.PosX) + abs(Element.PosY - Data.BallInfo.PosY) < 4) return true;
	return false;
}

