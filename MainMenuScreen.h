#ifndef MAINMENUSCREEN
#define MAINMENUSCREEN

#include "MenuScreen.h"
#include "DataBus.h"
#include "CommonEvents.h"

class MainMenuScreen : public MenuScreen
{
public:
	MainMenuScreen(DataBus& Data);
	virtual void AcceptSelectedOption() override;
};

#endif
