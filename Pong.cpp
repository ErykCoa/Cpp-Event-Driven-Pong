#include "Pong.h"
#include "window_management.h"



Pong::Pong()
{
	mutx = new mutex();

	Game = new window_management(mutx, 1, 1);

	//GameHandle = (HANDLE)_beginthreadex(0, 0, &GameThread, (void*) Game, 0, 0);

	GameHandle = new thread(GameThread, (void*)Game);

	//InputHandle = (HANDLE) _beginthreadex(0, 0, &InputThread,(void*) Game, 0, 0);

	InputHandle = new thread(InputThread, (void*)Game);

	GameHandle->join();
	InputHandle->join();
}

unsigned int Pong::GameThread(void * pData)
{
	IGame* LocalGame = (IGame*)pData;

	LocalGame->GameLoop();

	delete LocalGame;

	return 0;
}

unsigned int Pong::InputThread(void * pData)
{
	IGame* LocalGame = (IGame*) pData;

//	Nothing = NULL, Exit = 'A', Accept, ChangeBallSize, PaddleLeftMoveUp, PaddleLeftMoveDown, PaddleRightMoveUp, PaddleRightMoveDown

	while (1)
	{
		for (int Index = Nothing; Index < CommandTypeEnding; Index++)
			if (GetAsyncKeyState(VkKeyScan(LocalGame->GetControlAssignment((CommandType)Index)))) LocalGame->SendUserInput((CommandType)Index); 
		Sleep(LocalGame->UserInputDelay);
	}

	return 0;
}


Pong::~Pong()
{
	CloseHandle(InputHandle);
	CloseHandle(GameHandle);
}
