#ifndef GAME_MODE
#define GAME_MODE

#include "enums.h"
#include "windows.h"
#include <time.h>
#include <chrono>

#include "DataBus.h"
#include "ball_management.h"
#include "paddles_management.h"
#include "window_drawing.h"
#include "Defines.h"


class game_mode
{
public:
	virtual void SingleGameTick();
	virtual std::chrono::milliseconds GameTickDelay();
	virtual bool IsCommandLegal(CommandType Command);	
	virtual int GetMaxFPS() { return MaxFPS; }

	~game_mode();
	game_mode(DataBus& Data);

protected:
	std::chrono::system_clock::time_point LastFrameRenedr;
	std::chrono::milliseconds GameTickDuration;

	ball_management Ball;
	paddles_management Paddles;
	window_drawing Render;

	DataBus& Data;

	virtual void UpdateAIDifficulty();
	virtual void UpdateBallMovementSpeed();
	virtual void UpdateMaxFPS();

	virtual void FrameShouldBeRendered();
	void FrameRender();

	virtual void ProcessUserCommands();
	void SendAICommand(CommandType Command);

	int MaxFPS;
	int AIDifficulty;

	void BasicPaddleAI(Player ControledPaddle);
};

#endif