#include "main_menu_overlay.h"



void main_menu_overlay::AddToDrawingQueue()
{
	Data.DrawingQueue.push({ [this] {this->DrawMainMenu(); }, DrawingPriority::Overlay });
}

void main_menu_overlay::DrawMainMenu()
{
	UpdateMenuScreen();

	int DrawingCursor = Data.BorderUp.Padding + 2;

	DrawingCursor += Data.ScreenY / 10;
	ecur::DrawLineOfText(Data.Screen, DrawingCursor, 0, GameName, Title, A_BOLD);
	DrawingCursor += Data.ScreenY / 10;

	MenuScreen->DrawOverlay(DrawingCursor, Data.ScreenY / 12);

	DrawingCursor = Data.ScreenY - ((Data.BorderDown.Padding > 0) ? Data.BorderDown.Padding : 0) - 2;

	ecur::DrawLineOfText(Data.Screen, DrawingCursor, 0, Credits, Text);
}

void main_menu_overlay::SendUserCommand(CommandType Command)
{
	switch (Command)
	{
	case (PaddleLeftMoveUp) :
	case (PaddleRightMoveUp) : MenuScreen->MoveCursor(-1); break;
	case (PaddleLeftMoveDown) :
	case (PaddleRightMoveDown) : MenuScreen->MoveCursor(1); break;
	case (Accept) : MenuScreen->AcceptSelectedOption(); break;
	case (Exit) : Data.GameShouldEndFlag = true; break;
	default: break;
	}
}

main_menu_overlay::main_menu_overlay(DataBus& Data) : Data{ Data }, MenuScreen{new MainMenuScreen(Data) }
{
	Data.Events.AddHandler<CE::PrepareFrame>([this](Event arg) { this->AddToDrawingQueue(); return HandlerReturnCall::Succeed; });

	GameName = "PONG SIMULATOR 2016";

	Credits = "Game made by ErykCoa, v 1.4";
}

void main_menu_overlay::UpdateMenuScreen()
{
	switch (Data.ChangeMenuScreenTo)
	{
	case (SelectedMenuScreen::MainMenu) : MenuScreen.reset(new MainMenuScreen(Data)); break;
	case (SelectedMenuScreen::ConfiguratonMenu) : MenuScreen.reset(new ConfigurationMenuScreen(Data));  break;
	default: break;
	}
	Data.ChangeMenuScreenTo = SelectedMenuScreen::None;
}
