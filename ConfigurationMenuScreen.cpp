#include "ConfigurationMenuScreen.h"

ConfigurationMenuScreen::ConfigurationMenuScreen(DataBus& Data) : MenuScreen{Data}
{
	Options.push_back("Left paddle up");
	Options.push_back("Left paddle down");
	Options.push_back("Right paddle up");
	Options.push_back("Right paddle down");
	Options.push_back("Back");

	MaxOptions = Options.size();
}

void ConfigurationMenuScreen::DrawOverlay(int DrawingCursor, int IncrementBy)
{
	if (Data.ScreenX < 30) throw std::runtime_error("Console is too small (x < 30)!");

	const int Align = (Data.ScreenX - 30) / 2;
	Environment Color{};
	for (int index = 0; index < MaxOptions - 1; ++index)
	{
		Color = (index == CursorPosition ) ? (OptionSelected()) ? Environment::SelectedField : SelectedText : Text;

		ecur::DrawChar<AlignType::Right>(Data.Screen, DrawingCursor, Align, Data.AssignedControls[index + CommandType::PaddleLeftMoveUp], Color, A_BOLD);
		ecur::DrawLineOfText<AlignType::Left>(Data.Screen, DrawingCursor, Align, Options[index], (index == CursorPosition) ? SelectedText : Text, A_BOLD);

		DrawingCursor += IncrementBy + 1;
	}

	ecur::DrawLineOfText(Data.Screen, DrawingCursor, Align, Options[MaxOptions - 1], (MaxOptions - 1 == CursorPosition) ? SelectedText : Text, A_BOLD);
}

void ConfigurationMenuScreen::AcceptSelectedOption()
{
	switch (CursorPosition)
	{
	case (0) : Data.ChangeAssignedKey = CommandType::PaddleLeftMoveUp; break;
	case (1) : Data.ChangeAssignedKey = CommandType::PaddleLeftMoveDown; break;
	case (2) : Data.ChangeAssignedKey = CommandType::PaddleRightMoveUp; break;
	case (3) : Data.ChangeAssignedKey = CommandType::PaddleRightMoveDown; break;
	case (4) : Data.ChangeMenuScreenTo = SelectedMenuScreen::MainMenu;  break;
	default: break;
	}
}

