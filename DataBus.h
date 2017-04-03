#ifndef DATA_RAIL
#define DATA_RAIL

#include "enums.h"
#include <queue>
#include <mutex>
#include <atomic>
#include <chrono>

#include "PriorityQueueElement.h"
#include "GuardedBuffer.h"

#include "eCurses.h"
#include <functional>
#include "EventHandler.h"
#include "CommonEvents.h"
#include "Event.h"
#include "CommonStructs.h"

struct DataBus
{
	WINDOW* Screen;
	int ScreenX;
	int ScreenY;

	EventHandler<Event> Events;

	// Current Game State //////////////////////////////////////////////////////////////////////////////////////////////////////

	int ScoreLeft;
	int ScoreRight;

	Player LastPlayer;
	BallType BallType;

	CS::PaddleInfo PaddleLeftInfo, PaddleRightInfo;
	CS::BallInfo BallInfo;
	CS::Border BorderUp, BorderDown, BorderLeft, BorderRight;

	GuardedBuffer<std::priority_queue<QueueElement<std::function<void()>, DrawingPriority>>> DrawingQueue;

	SelectedMenuScreen ChangeMenuScreenTo;

	std::atomic<bool> GameShouldEndFlag;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Controls ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GuardedBuffer<std::queue<CommandType>> UserCommandsBuffer;

	std::atomic<char> AssignedControls[CommandTypeEnding];

	std::atomic<CommandType> ChangeAssignedKey;

	std::chrono::milliseconds UserInputDelay;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	DataBus(int Paddings[4]);

	void SoftReset();

private:
	void PrepareWindow();
};

#endif