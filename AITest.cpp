#include "AITest.h"


bool AITestMode::IsCommandLegal(CommandType Command)
{
	if (Command == Exit) return true;
	return false;
}


AITestMode::AITestMode(DataBus& Data) : game_mode(Data)
{
	Data.UserInputDelay = STANDARD_USER_INPUT_DELAY;

	Data.Events.AddHandler<CE::BallHasMoved>([this](Event arg) {BasicPaddleAI(Right); BasicPaddleAI(Left); return HandlerReturnCall::Succeed;  });

	UpdateBallMovementSpeed();
	UpdateAIDifficulty();
	UpdateMaxFPS();
}


AITestMode::~AITestMode()
{
}

void AITestMode::UpdateAIDifficulty()
{
	AIDifficulty = 20;
}
