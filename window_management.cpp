#include "window_management.h"


unsigned int window_management::GameThread(window_management* LocalGame)
{
	try {
		while (!LocalGame->Data.GameShouldEndFlag)
		{
			LocalGame->Data.Events.extern_AwaitCurrent();

			LocalGame->ConstructionMutex.lock();
			LocalGame->Data.Events.Fire(CE::GameTick());
			auto Delay = LocalGame->GameMode->GameTickDelay();
			LocalGame->ConstructionMutex.unlock();

			std::this_thread::sleep_for(std::chrono::milliseconds(Delay));
		}

		LocalGame->Data.Events.extern_AwaitAll();
	}
	catch (std::exception E)
	{
		std::cerr << std::string("Unhandled exception has been thrown: ") + E.what();
	}

	return 0;
}

unsigned int window_management::InputThread(window_management* LocalGame)
{
	try {
		std::chrono::milliseconds InputDelay;

		while (true)
		{
			{
				std::lock_guard<std::mutex> _lock(LocalGame->ConstructionMutex);

				if (LocalGame->Data.GameShouldEndFlag) break;

				if (CommandType::PaddleLeftMoveUp <= LocalGame->Data.ChangeAssignedKey && LocalGame->Data.ChangeAssignedKey <= CommandType::PaddleRightMoveDown)
					LocalGame->AssignNewKey();
				else
					LocalGame->ReadUserInput();

				LocalGame->ClearKeyboardEvents();

				InputDelay = LocalGame->Data.UserInputDelay;
			}

			std::this_thread::sleep_for(InputDelay);
		}
	}
	catch (std::exception E)
	{
		std::cerr << std::string("Unhandled exception has been thrown: ") + E.what();
	}

	return 0;
}


void window_management::StartGame()
{
	Logo().DrawLogo();

	GameMode.reset(new MainMenuMode(Data));
	Data.Events.AddHandler<CE::ChangeGameMode>([this](Event & arg) {this->ChangeGameMode(arg); return HandlerReturnCall::StopHandlingEvent; });

	std::future<unsigned> GameRes = std::async(GameThread, this);
	std::future<unsigned> InputRes = std::async(InputThread, this);



	GameRes.get();
	InputRes.get();
}

void window_management::SendUserInput(CommandType Command)
{
	if (GameMode->IsCommandLegal(Command))
	{
		Data.UserCommandsBuffer.push(Command);
		Data.Events.Fire(CE::NewUserCommand());
	}
}

void window_management::ChangeControlAssignment(CommandType Command, char Key)
{
	Data.AssignedControls[Command] = Key;
}

char window_management::GetControlAssignment(CommandType Command)
{
	return Data.AssignedControls[Command];
}

std::chrono::milliseconds window_management::UserInputDelay()
{
	return Data.UserInputDelay;
}

void window_management::ChangeGameMode(Event& Mode)
{
	std::lock_guard<std::mutex> _lock(ConstructionMutex);

	Data.Events.thread_AwaitAll();

	Data.SoftReset();
	
		auto _mode = Unwrap<CE::ChangeGameMode>(Mode);

		switch (static_cast<SelectedGameMode>(_mode.Mode))
		{
		case (SelectedGameMode::SinglePlayer) : GameMode.reset(new SinglePlayerMode(Data)); break;
		case (SelectedGameMode::MultiPlayer) : GameMode.reset(new MultiPlayerMode(Data)); break;
		case (SelectedGameMode::AITest) : GameMode.reset(new AITestMode(Data)); break;
		case (SelectedGameMode::MainMenu) : GameMode.reset(new MainMenuMode(Data)); break;
		default: break;
		}

	Data.Events.AddHandler<CE::ChangeGameMode>([this](Event & arg) {this->ChangeGameMode(arg); return HandlerReturnCall::StopHandlingEvent; });
}


window_management::window_management(int Borders[4]) : Data{ Borders }
{
}

void window_management::ClearKeyboardEvents()
{
	for (int Index = Nothing; Index < CommandTypeEnding; Index++)
		GetAsyncKeyState(VkKeyScan(GetControlAssignment((CommandType)Index)));

	for (int Key = 'a'; Key <= 'z'; Key++)
		GetAsyncKeyState(VkKeyScan(Key));
}

void window_management::AssignNewKey()
{
	for (int Key = 'a'; Key <= 'z'; Key++)
		if (GetAsyncKeyState(VkKeyScan(Key)))
		{
			if (IsKeyAssigned(Key) && Data.AssignedControls[Data.ChangeAssignedKey] != Key)
			{
				Data.Events.Fire(CE::ErrorMessage("Choose other key", std::chrono::milliseconds(1200)));
				return;
			}

			ChangeControlAssignment(Data.ChangeAssignedKey, Key);
			Data.ChangeAssignedKey = CommandType::Nothing;

			Data.UserCommandsBuffer.PopBuffer();

			return;
		}
}

void window_management::ReadUserInput()
{
	for (int Index = Nothing; Index < CommandTypeEnding; Index++)
		if (GetAsyncKeyState(VkKeyScan(GetControlAssignment((CommandType)Index))))
			SendUserInput((CommandType)Index);
}

bool window_management::IsKeyAssigned(char Key)
{
	for (int i = CommandType::Nothing; i < CommandType::CommandTypeEnding; ++i)
		if (Data.AssignedControls[i] == Key) return true;

	return false;
}

window_management::~window_management()
{
	endwin();
}
