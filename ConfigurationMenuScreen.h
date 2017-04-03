#ifndef CONFIGURATIONMENUSCREEN
#define CONFIGURATIONMENUSCREEN

#include "enums.h"
#include "MenuScreen.h"
#include "DataBus.h"
#include "eCurses.h"
#include <exception>

class ConfigurationMenuScreen : public MenuScreen
{
public:
	ConfigurationMenuScreen(DataBus& Data);
	virtual void DrawOverlay(int DrawingCursor, int IncrementBy) override;
	
	virtual void AcceptSelectedOption() override;

private:
	bool OptionSelected() { return Data.ChangeAssignedKey != CommandType::Nothing; };
};

#endif

