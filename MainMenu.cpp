#include "MainMenu.h"

MainMenuMode::MainMenuMode(DataBus& Data) : game_mode(Data), Overlay{Data}
{
	Data.Events.AddHandler<CE::BallHasMoved>([this](Event arg) {BasicPaddleAI(Right); BasicPaddleAI(Left); return HandlerReturnCall::Succeed;  });

	Data.UserInputDelay = STANDARD_MAIN_MENU_USER_INPUT_DELAY;

	AIDifficulty = 10;
	MaxFPS = 60;

	UpdateBallMovementSpeed();
	UpdateMaxFPS();
}

void MainMenuMode::ProcessUserCommands()
{
	auto tmp = Data.UserCommandsBuffer.PopBuffer();

	for (; !tmp.empty(); tmp.pop())
	{
		Overlay.SendUserCommand(tmp.front());

	}		
}

void MainMenuMode::UpdateAIDifficulty()
{
}
