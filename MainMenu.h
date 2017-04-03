#ifndef MAIN_MENU
#define MAIN_MENU

#include "game_mode.h"
#include "DataBus.h"
#include "main_menu_overlay.h"

#include "enums.h"

class MainMenuMode : public game_mode
{
public:
	MainMenuMode(DataBus& Data);

protected:
	
	main_menu_overlay Overlay;
	void ProcessUserCommands();
	virtual void UpdateAIDifficulty() override;
};

#endif