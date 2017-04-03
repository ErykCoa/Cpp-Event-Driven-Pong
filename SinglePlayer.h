#ifndef SINGLE_PLAYER
#define SINGLE_PLAYER


#include "game_mode.h"
#include "DataBus.h"

#include "enums.h"



class SinglePlayerMode : public game_mode
{
public:
	SinglePlayerMode(DataBus& Data);
	~SinglePlayerMode();
protected:
	bool IsCommandLegal(CommandType Command);

	void UpdateBallMovementSpeed();
	void UpdateAIDifficulty();
};

#endif