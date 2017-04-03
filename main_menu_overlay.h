#ifndef MAIN_MENU_OVERLAY
#define MAIN_MENU_OVERLAY

#include "enums.h"
#include <string>
#include "DataBus.h"
#include "eCurses.h"

#include "IMenuScreen.h"
#include "MainMenuScreen.h"
#include "ConfigurationMenuScreen.h"

class main_menu_overlay
{
public:
	void AddToDrawingQueue();
	void SendUserCommand(CommandType Command);
	main_menu_overlay(DataBus& Data);

private:
	DataBus& Data;
	std::unique_ptr<IMenuScreen> MenuScreen;
	std::string GameName;
	std::string Credits;

	void DrawMainMenu();
	void UpdateMenuScreen();
};

#endif