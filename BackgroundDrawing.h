#pragma once

#include "eCurses.h"
#include "enums.h"
#include <vector>
#include <chrono>
#include "DataBus.h"
#include "CommonStructs.h"
#include "Defines.h"


class BackgroundDrawing
{
public:
	BackgroundDrawing( DataBus& Data, int MaxElementsCount = 150 );

private:
	DataBus& Data;

	std::string BackgroundBuffer;

	int MaxNumberOfElements;

	void UpdateBackground();

	void AddNewBackgroundElement(int PosX, std::chrono::system_clock::time_point Time);

	void ClearBuffer();

	void AddToBuffer(int PosY, int PosX, char Char);

	bool ElementIsNearBall(CS::BackgroundElementInfo Element);

	std::vector<CS::BackgroundElementInfo> BackgroundElements;
};

