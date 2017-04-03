#ifndef WINDOW_MANAGEMENT
#define WINDOW_MANAGEMENT

#include "IGame.h"
#include "IUserInput.h"

#include <Windows.h>
#include <future>
#include <memory>
#include <iostream>
#include <mutex>

#include "MainMenu.h"
#include "SinglePlayer.h"
#include "MultiPlayer.h"
#include "AITest.h"
#include "CommonEvents.h"
#include "game_mode.h"
#include "DataBus.h"
#include "enums.h"
#include "Logo.h"


class window_management: public IGame, public IUserInput
{
public:

	void StartGame() override;

	void SendUserInput(CommandType Command) override;
	void ChangeControlAssignment(CommandType Command, char Key) override;
	char GetControlAssignment(CommandType Command) override;	
	std::chrono::milliseconds UserInputDelay() override;

	window_management(int Borders[4]);
	~window_management() override;


private:
	DataBus Data;

	void ChangeGameMode(Event& Mode);

	std::mutex ConstructionMutex;
	std::unique_ptr<game_mode> GameMode;

	static unsigned int __stdcall GameThread(window_management* pData);
	static unsigned int __stdcall InputThread(window_management* pData);

	void ClearKeyboardEvents();
	void AssignNewKey();
	void ReadUserInput();
	bool IsKeyAssigned(char Key);
};

#endif