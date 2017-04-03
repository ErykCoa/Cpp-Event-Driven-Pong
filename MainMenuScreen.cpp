#include "MainMenuScreen.h"

MainMenuScreen::MainMenuScreen(DataBus& Data) : MenuScreen{ Data }
{
	Options.push_back("Single Player");
	Options.push_back("Multiplayer");
	Options.push_back("AI Demonstration");
	Options.push_back("Configuration");
	Options.push_back("Quit");

	MaxOptions = Options.size();
}

void MainMenuScreen::AcceptSelectedOption()
{
	switch (CursorPosition)
	{
	case (0) : Data.Events.Fire(CE::ChangeGameMode(SelectedGameMode::SinglePlayer)); break;
	case (1) : Data.Events.Fire(CE::ChangeGameMode(SelectedGameMode::MultiPlayer)); break;
	case (2) : Data.Events.Fire(CE::ChangeGameMode(SelectedGameMode::AITest)); break;
	case (3) : Data.ChangeMenuScreenTo = SelectedMenuScreen::ConfiguratonMenu; break;
	case (4) : Data.GameShouldEndFlag = true;  break;
	default: break;
	}
}
