#include "SinglePlayer.h"


bool SinglePlayerMode::IsCommandLegal(CommandType Command)
{
	if (Command == PaddleRightMoveDown || Command == PaddleRightMoveUp) return false;
	return true;
}

SinglePlayerMode::SinglePlayerMode(DataBus & Data) : game_mode(Data)
{
	Data.UserInputDelay = STANDARD_USER_INPUT_DELAY;
	Data.Events.AddHandler<CE::BallHasMoved>([this](Event arg) {BasicPaddleAI(Right); return HandlerReturnCall::Succeed;  });

	AIDifficulty = 20;
	MaxFPS = 60;

	UpdateBallMovementSpeed();
	UpdateMaxFPS();
}


SinglePlayerMode::~SinglePlayerMode()
{
}



void SinglePlayerMode::UpdateBallMovementSpeed()
{
	Ball.SetBallMovementSpeed(BASE_BALL_MOVEMENT_SPEED + 4 * ((Data.ScoreLeft - Data.ScoreRight > -9) ? Data.ScoreLeft - Data.ScoreRight : -8));
}

void SinglePlayerMode::UpdateAIDifficulty()
{
	AIDifficulty = Data.ScoreLeft - Data.ScoreRight + 20;
}


