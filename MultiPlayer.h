#ifndef MULTI_PLAYER
#define MULTI_PLAYER

#include "game_mode.h"
#include "DataBus.h"

#include "enums.h"

class MultiPlayerMode : public game_mode
{
public:
	MultiPlayerMode(DataBus& Data);
protected:
	bool IsCommandLegal(CommandType Command);
	void UpdateBallMovementSpeed();
};

#endif