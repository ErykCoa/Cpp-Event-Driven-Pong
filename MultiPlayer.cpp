#include "MultiPlayer.h"

MultiPlayerMode::MultiPlayerMode(DataBus& Data) : game_mode(Data)
{
	Data.UserInputDelay = STANDARD_USER_INPUT_DELAY;

	UpdateBallMovementSpeed();
	UpdateMaxFPS();
}


void MultiPlayerMode::UpdateBallMovementSpeed()
{
	Ball.SetBallMovementSpeed(BASE_BALL_MOVEMENT_SPEED/2 + 8 * (10 - abs(Data.ScoreLeft - Data.ScoreRight) > 0 ? 10 - abs(Data.ScoreLeft - Data.ScoreRight) : 0));	
}

bool MultiPlayerMode::IsCommandLegal(CommandType Command)
{
	return true;
}
