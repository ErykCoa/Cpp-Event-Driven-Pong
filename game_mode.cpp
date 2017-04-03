#include "game_mode.h"


void game_mode::SingleGameTick()
{
	try {
	std::chrono::system_clock::time_point GameTickStart = std::chrono::system_clock::now();

	Ball.BallMovement();

	FrameShouldBeRendered();

	GameTickDuration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - GameTickStart);
	}
	catch (std::exception e)
	{

	}
}

bool game_mode::IsCommandLegal(CommandType Command)
{
	return true;
}

game_mode::game_mode(DataBus& Data) : Data{ Data }, Ball{ Data }, Paddles{ Data }, Render{ Data }
{
	Data.Events.AddHandler<CE::ScoreHasChanged>([this](Event arg) {this->UpdateAIDifficulty(); return HandlerReturnCall::Succeed; });
	Data.Events.AddHandler<CE::ScoreHasChanged>([this](Event arg) {this->UpdateBallMovementSpeed(); return HandlerReturnCall::Succeed; });
	Data.Events.AddHandler<CE::ScoreHasChanged>([this](Event arg) {this->UpdateMaxFPS(); return HandlerReturnCall::Succeed; });
	Data.Events.AddHandler<CE::RenderFrame>([this](Event arg) { this->FrameRender(); return HandlerReturnCall::HandledCompletely;  });
	Data.Events.AddHandler<CE::NewUserCommand>([this](Event arg) { this->ProcessUserCommands(); return HandlerReturnCall::Succeed; });
	Data.Events.AddHandler<CE::GameTick>([this](Event arg) { this->SingleGameTick(); return HandlerReturnCall::Succeed; });
	
	LastFrameRenedr = std::chrono::system_clock::now();
	GameTickDuration = std::chrono::milliseconds(0);

	MaxFPS = 60;
}

game_mode::~game_mode()
{
}

void game_mode::UpdateAIDifficulty()
{
	AIDifficulty = Data.ScoreLeft - Data.ScoreRight;
}

void game_mode::UpdateBallMovementSpeed()
{
	Ball.SetBallMovementSpeed(STANDARD_MAIN_MENU_GAME_TEMPO);
}

void game_mode::UpdateMaxFPS()
{
	MaxFPS = 60; //Ball.GetMovementSpeed();
}

void game_mode::FrameShouldBeRendered()
{
	if (std::chrono::system_clock::now() >= LastFrameRenedr + std::chrono::milliseconds(1000 / MaxFPS))
	{
		LastFrameRenedr = std::chrono::system_clock::now();

		try {
			Data.Events.Fire(CE::PrepareFrame());

			Data.Events.Fire(CE::RenderFrame());
		}
		catch (std::exception e)
		{

		}

	}
}

void game_mode::FrameRender()
{
	Data.Events.thread_AwaitCurrent();

	auto tmp = Data.DrawingQueue.PopBuffer();

	while (!tmp.empty())
	{
		tmp.top()();
		tmp.pop();
	}

	refresh();
	erase();
}

std::chrono::milliseconds game_mode::GameTickDelay()
{	
	return std::chrono::milliseconds(1000 / MaxFPS) - GameTickDuration;
}

void game_mode::ProcessUserCommands()
{
	auto tmp = Data.UserCommandsBuffer.PopBuffer();

	if (!tmp.empty())
		for (auto Command = tmp.front(); !tmp.empty(); tmp.pop())
		{
		Command = tmp.front();

		switch (Command)
		{
		case (PaddleRightMoveDown) :
		case (PaddleRightMoveUp) :
		case (PaddleLeftMoveDown) :
		case (PaddleLeftMoveUp) : Paddles.MovePaddle(Command); break;
		case (ChangeBallSize) : Render.ChangeBallSize(); break;
 		case (Exit) : Data.Events.Fire(CE::ChangeGameMode(SelectedGameMode::MainMenu)); while (GetAsyncKeyState(VkKeyScan(Data.AssignedControls[Exit]))) Sleep(1);  break;
		default: break;
		}
	}
}

void game_mode::SendAICommand(CommandType Command)
{
	switch (Command)
	{
	case (PaddleRightMoveDown) :
	case (PaddleRightMoveUp) :
	case (PaddleLeftMoveDown) :
	case (PaddleLeftMoveUp) : Paddles.MovePaddle(Command); break;
	case (ChangeBallSize) : Render.ChangeBallSize(); break;
	case (Exit) : Data.Events.Fire(CE::ChangeGameMode(SelectedGameMode::MainMenu)); break;
	default: break;
	}
}

void game_mode::BasicPaddleAI(Player ControledPaddle)
{
	if (ControledPaddle == Right) {
		if ((Data.BallInfo.PosX >= Data.PaddleRightInfo.PosX - AIDifficulty - BASE_BASIC_AI_SEARCH_RANGE) && (Data.PaddleRightInfo.PosY != Data.BallInfo.PosY))
		{
			if (Data.PaddleRightInfo.PosY > Data.BallInfo.PosY)
			{
				if (rand() % (11 + AIDifficulty / 5) > 8)
				{
					SendAICommand(PaddleRightMoveUp);
				}
			}
			else if (rand() % (11 + AIDifficulty / 5) > 8)
			{
				SendAICommand(PaddleRightMoveDown);
			}
		}
	}
	if (ControledPaddle == Left) {
		if ((Data.BallInfo.PosX <= Data.PaddleLeftInfo.PosX + AIDifficulty + BASE_BASIC_AI_SEARCH_RANGE) && (Data.PaddleLeftInfo.PosY != Data.BallInfo.PosY))
		{
			if (Data.PaddleLeftInfo.PosY > Data.BallInfo.PosY)
			{
				if (rand() % (11 + AIDifficulty / 5) > 8)
				{
					SendAICommand(PaddleLeftMoveUp);
				}
			}
			else if (rand() % (11 + AIDifficulty / 5) > 8)
			{
				SendAICommand(PaddleLeftMoveDown);
			}
		}
	}
}

