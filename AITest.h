#ifndef AI_TEST
#define AI_TEST

#include "game_mode.h"
#include "DataBus.h"
#include "enums.h"
#include "Defines.h"




class AITestMode : public game_mode
{
public:
	AITestMode(DataBus& Data);
	~AITestMode();
protected:
	bool IsCommandLegal(CommandType Command);
	void UpdateAIDifficulty();
};

#endif