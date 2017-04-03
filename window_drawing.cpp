#include "window_drawing.h"


window_drawing::window_drawing(DataBus& Data) : Data{Data}, Background{Data}
	{
		Data.Events.AddHandler<CE::ScoreHasChanged>([this](Event arg) {UpdateScore(); return HandlerReturnCall::Succeed; });
		Data.Events.AddHandler<CE::PrepareFrame>([this](Event arg) {AddToDrawingQueue(); return HandlerReturnCall::Succeed; });
		Data.Events.AddHandler<CE::PrepareFrame>([this](Event arg) {DrawErrorMessage(); return HandlerReturnCall::Succeed; });
		Data.Events.AddHandler<CE::ErrorMessage>([this](Event& arg) {ReciveMessage(arg); return HandlerReturnCall::Succeed; });

		srand(static_cast<unsigned>(time(NULL)));

		BorderTop = new char[1];
		BorderBottom = new char[1];
		BorderLeft = new char[1];
		BorderRight = new char[1];

		ColorInitialization();
		UpdateBordersSize();

		score.resize(Data.ScreenX, ' ');
		std::string ScoreLeft = "SCORE: " + std::to_string(Data.ScoreLeft);
		std::string ScoreRight = "SCORE: " + std::to_string(Data.ScoreRight);
		score.replace(2, ScoreLeft.size(), ScoreLeft);
		score.replace(Data.ScreenX - ScoreRight.size() - 2, ScoreRight.size(), ScoreRight);

	}


window_drawing::~window_drawing()
	{
		delete[] BorderTop;
		delete[] BorderBottom;
		delete[] BorderLeft;
		delete[] BorderRight;
	}

void window_drawing::ColorInitialization()
{
	init_pair(Left, COLOR_BLUE, COLOR_WHITE);
	init_pair(Right, COLOR_RED, COLOR_WHITE);
	init_pair(None, COLOR_BLACK, COLOR_WHITE);
	init_pair(Border, COLOR_WHITE, COLOR_WHITE);
	init_pair(Score, COLOR_WHITE, COLOR_BLACK);
	init_pair(SelectedText, COLOR_WHITE, COLOR_BLUE);
	init_pair(Text, COLOR_WHITE, COLOR_BLACK);
	init_pair(Title, COLOR_RED, COLOR_WHITE);
	init_pair(SelectedField, COLOR_RED, COLOR_GREEN);

}

void  window_drawing::DrawBorders()
	{
		attron(COLOR_PAIR(Border) | A_INVIS);
		(Data.BorderUp.Padding < 0) ? 1 : mvprintw(Data.BorderUp.Padding, (Data.BorderLeft.Padding < 0) ? 0 : Data.BorderLeft.Padding, BorderTop);
		(Data.BorderDown.Padding < 0) ? 1 : mvprintw(Data.ScreenY - 1 - Data.BorderDown.Padding, (Data.BorderLeft.Padding < 0) ? 0 : Data.BorderLeft.Padding, BorderBottom);
		(Data.BorderLeft.Padding < 0) ? 1 : mvvprintw((Data.BorderUp.Padding < 0) ? 0 : Data.BorderUp.Padding, Data.BorderLeft.Padding, BorderLeft);
		(Data.BorderRight.Padding < 0) ? 1 : mvvprintw((Data.BorderUp.Padding < 0) ? 0 : Data.BorderUp.Padding, Data.ScreenX - 1 - Data.BorderRight.Padding, BorderRight);
		attroff(COLOR_PAIR(Border) | A_INVIS);
	}



	void  window_drawing::DrawScore()
	{
		attron(COLOR_PAIR('S') | A_BOLD);
		mvprintw(Data.ScreenY - Data.BorderDown.Padding, 0, score.c_str());
		attroff(COLOR_PAIR('S') | A_BOLD);
	}

	void window_drawing::ReciveMessage(Event& Event)
	{
		std::lock_guard<std::mutex> _lock(MessageLock);

		CurrentMessageRecived = std::chrono::system_clock::now();

		auto Message = Unwrap<CE::ErrorMessage>(Event);
		CurrentMessage = Message.Message;
		CurrentMessageDuration = Message.Duration;
	}

	void window_drawing::DrawErrorMessage()
	{
		std::lock_guard<std::mutex> _lock(MessageLock);

		if (CurrentMessageRecived + CurrentMessageDuration > std::chrono::system_clock::now())
		{
			
			std::string Filler(MAX_MSG_LENGTH, ' ');		
			int BorderAlign = (Data.ScreenX - MAX_MSG_LENGTH)/2;

			Data.DrawingQueue.push({ [this, Filler, BorderAlign] {

				for (int i = 5; i--;)
				{
					ecur::DrawLineOfText(Data.Screen, Data.ScreenY / 2 - i, 0, Filler, Environment::Text, A_BOLD);
					ecur::DrawChar<AlignType::Left>(Data.Screen, Data.ScreenY / 2 - i, BorderAlign, ' ', Environment::Border, A_BOLD);
					ecur::DrawChar<AlignType::Right>(Data.Screen, Data.ScreenY / 2 - i, BorderAlign, ' ', Environment::Border, A_BOLD);
				}

				ecur::DrawLineOfText(Data.Screen, Data.ScreenY / 2 - 5, 0, Filler, Environment::Border, A_BOLD);
				ecur::DrawLineOfText(Data.Screen, Data.ScreenY / 2 + 1, 0, Filler, Environment::Border, A_BOLD);				
				ecur::DrawLineOfText(Data.Screen, Data.ScreenY/2 - 2, 0, CurrentMessage, Environment::Text, A_BOLD); 
			
			}, DrawingPriority::Message});
		}
	}

	void  window_drawing::mvvprintw(int iy, int ix, char* str)
	{
		for (int index = 0; *(str + index); index++) mvprintw(iy + index, ix, "%c", *(str + index));
	}

	void  window_drawing::UpdateBordersSize()
	{
		delete[] BorderTop;
		delete[] BorderBottom;
		delete[] BorderLeft;
		delete[] BorderRight;

		Data.BorderUp.Lenght = Data.ScreenX - ((Data.BorderLeft.Padding < 0) ? 0 : Data.BorderLeft.Padding) - ((Data.BorderRight.Padding < 0) ? 0 : Data.BorderRight.Padding);
		BorderTop = new char[Data.BorderUp.Lenght + 1];
		memset(BorderTop, '=', sizeof(char)*Data.BorderUp.Lenght);
		BorderTop[Data.BorderUp.Lenght] = NULL;

		Data.BorderDown.Lenght = Data.ScreenX - ((Data.BorderLeft.Padding < 0) ? 0 : Data.BorderLeft.Padding) - ((Data.BorderRight.Padding < 0) ? 0 : Data.BorderRight.Padding);
		BorderBottom = new char[Data.BorderDown.Lenght + 1];
		memset(BorderBottom, '=', sizeof(char)*Data.BorderDown.Lenght);
		BorderBottom[Data.BorderDown.Lenght] = NULL;

		Data.BorderLeft.Lenght = Data.ScreenY - ((Data.BorderUp.Padding < 0) ? 0 : Data.BorderUp.Padding) - ((Data.BorderDown.Padding < 0) ? 0 : Data.BorderDown.Padding);
		BorderLeft = new char[Data.BorderLeft.Lenght + 1];
		memset(BorderLeft, '=', sizeof(char)*Data.BorderLeft.Lenght);
		BorderLeft[Data.BorderLeft.Lenght] = NULL;

		Data.BorderRight.Lenght = Data.ScreenY - ((Data.BorderUp.Padding < 0) ? 0 : Data.BorderUp.Padding) - ((Data.BorderDown.Padding < 0) ? 0 : Data.BorderDown.Padding);
		BorderRight = new char[Data.BorderRight.Lenght + 1];
		memset(BorderRight, '=', sizeof(char)*Data.BorderRight.Lenght);
		BorderLeft[Data.BorderLeft.Lenght] = NULL;
	}

	void  window_drawing::DrawPaddle(Player WhichPaddle) {
		
		attron(COLOR_PAIR(WhichPaddle) | A_BOLD);
		switch (WhichPaddle)
		{
		default: mvvline(Data.PaddleRightInfo.PosY - Data.PaddleRightInfo.Lenght / 2, Data.PaddleRightInfo.PosX, ACS_VLINE, Data.PaddleRightInfo.Lenght);
		case Left: mvvline(Data.PaddleLeftInfo.PosY - Data.PaddleLeftInfo.Lenght / 2, Data.PaddleLeftInfo.PosX, ACS_VLINE, Data.PaddleLeftInfo.Lenght); break;
		case Right: mvvline(Data.PaddleRightInfo.PosY - Data.PaddleRightInfo.Lenght / 2, Data.PaddleRightInfo.PosX, ACS_VLINE, Data.PaddleRightInfo.Lenght); break;
		}
		attroff(COLOR_PAIR(WhichPaddle) | A_BOLD);
	}


	void  window_drawing::DrawBall() {

		if (Data.BallType == Large)
		{
			short ForegroundColor;
			short BackgroundColor;

			pair_content(Data.LastPlayer, &ForegroundColor, &BackgroundColor);

			init_pair(ColorVar, ForegroundColor, COLOR_BLACK);

			attron(COLOR_PAIR(ColorVar) | A_BOLD);

			mvprintw(Data.BallInfo.PosY - 1, Data.BallInfo.PosX, "v");
			mvprintw(Data.BallInfo.PosY + 1, Data.BallInfo.PosX, "^");
			mvprintw(Data.BallInfo.PosY, Data.BallInfo.PosX - 1, ">");
			mvprintw(Data.BallInfo.PosY, Data.BallInfo.PosX + 1, "<");

			attroff(COLOR_PAIR(ColorVar) | A_BOLD);

			if (Data.BallInfo.PrevPosY == Data.ScreenY - Data.BorderDown.Padding - 1)
			{
				attron(COLOR_PAIR(Border));
				mvprintw(Data.BallInfo.PrevPosY + 1, Data.BallInfo.PrevPosX, "=");
				attroff(COLOR_PAIR(Border));
			}

			if (Data.BallInfo.PrevPosY == Data.BorderUp.Padding + 1)
			{
				attron(COLOR_PAIR(Border));
				mvprintw(Data.BallInfo.PrevPosY - 1, Data.BallInfo.PrevPosX, "=");
				attroff(COLOR_PAIR(Border));
			}
		}

		attron(COLOR_PAIR(Data.LastPlayer) | A_BOLD);
		mvprintw(Data.BallInfo.PosY, Data.BallInfo.PosX, "O");
		attroff(COLOR_PAIR(Data.LastPlayer) | A_BOLD);
		
	}

	void  window_drawing::UpdateScore()
	{
		score.resize(Data.ScreenX, ' ');

		std::string ScoreLeft = "SCORE: " + std::to_string(Data.ScoreLeft);
		std::string ScoreRight = "SCORE: " + std::to_string(Data.ScoreRight);

		score.replace(2, ScoreLeft.size(), ScoreLeft);
		score.replace(Data.ScreenX - ScoreRight.size() - 2, ScoreRight.size(), ScoreRight);
	}

	void window_drawing::ChangeBallSize()
	{
		switch (Data.BallType)
		{
		case (Large) : Data.BallType = Normal; break;
		case (Normal) : Data.BallType = Large; break;
		default: break;
		}
	}


	void  window_drawing::AddToDrawingQueue()
	{
		Data.DrawingQueue.push({ [this] {this->DrawBall(); }, DrawingPriority::Ball });
		Data.DrawingQueue.push({ [this] {this->DrawBorders(); }, DrawingPriority::Borders });
		Data.DrawingQueue.push({ [this] {this->DrawScore(); }, DrawingPriority::Score });
		Data.DrawingQueue.push({ [this] {this->DrawPaddle(Left); }, DrawingPriority::Paddle });
		Data.DrawingQueue.push({ [this] {this->DrawPaddle(Right); }, DrawingPriority::Paddle });		
	}

