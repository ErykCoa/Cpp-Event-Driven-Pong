#include "Logo.h"


Logo::Logo()
{
	std::srand(std::time(0));

	init_pair(LOGOCOLOR, COLOR_WHITE, COLOR_WHITE);

	AddElement(0, 0);
	AddElement(1, 0);
	AddElement(2, 0);
	AddElement(3, 0);
	AddElement(4, 0);
	AddElement(8, 0);
	AddElement(9, 0);
	AddElement(10, 0);
	AddElement(11, 0);
	AddElement(12, 0);
	AddElement(15, 0);
	AddElement(21, 0);
	AddElement(24, 0);
	AddElement(25, 0);
	AddElement(26, 0);
	AddElement(27, 0);

	AddElement(0, 1);
	AddElement(5, 1);
	AddElement(7, 1);
	AddElement(13, 1);
	AddElement(15, 1);
	AddElement(16, 1);
	AddElement(21, 1);
	AddElement(23, 1);

	AddElement(0, 2);
	AddElement(5, 2);
	AddElement(7, 2);
	AddElement(13, 2);
	AddElement(15, 2);
	AddElement(16, 2);
	AddElement(17, 2);
	AddElement(21, 2);
	AddElement(23, 2);

	AddElement(0, 3);
	AddElement(5, 3);
	AddElement(7, 3);
	AddElement(13, 3);
	AddElement(15, 3);
	AddElement(17, 3);
	AddElement(18, 3);
	AddElement(21, 3);
	AddElement(23, 3);

	AddElement(0, 4);
	AddElement(1, 4);
	AddElement(2, 4);
	AddElement(3, 4);
	AddElement(4, 4);
	AddElement(7, 4);
	AddElement(13, 4);
	AddElement(15, 4);
	AddElement(18, 4);
	AddElement(19, 4);
	AddElement(21, 4);
	AddElement(23, 4);
	AddElement(26, 4);
	AddElement(27, 4);

	AddElement(0, 5);
	AddElement(7, 5);
	AddElement(13, 5);
	AddElement(15, 5);
	AddElement(19, 5);
	AddElement(20, 5);
	AddElement(21, 5);
	AddElement(23, 5);
	AddElement(28, 5);

	AddElement(0, 6);
	AddElement(7, 6);
	AddElement(13, 6);
	AddElement(15, 6);
	AddElement(20, 6);
	AddElement(21, 6);
	AddElement(24, 6);
	AddElement(28, 6);

	AddElement(0, 7);
	AddElement(8, 7);
	AddElement(9, 7);
	AddElement(10, 7);
	AddElement(11, 7);
	AddElement(12, 7);
	AddElement(15, 7);
	AddElement(21, 7);
	AddElement(25, 7);
	AddElement(26, 7);
	AddElement(27, 7);
}


void Logo::DrawLogo()
{
	unsigned MovingElements = Elements.size();
	int YMoveCounter = 0;
	attron(COLOR_PAIR(LOGOCOLOR) | A_BOLD);

	while (MovingElements)
	{
		MovingElements = 0;

		refresh();
		erase();

		for (LogoElement& Elem : Elements)
		{
			if (Elem.CurrentX != Elem.FinalX || Elem.CurrentY != Elem.FinalY)
			{
				if (Elem.CurrentX > Elem.FinalX) --Elem.CurrentX;
				else if (Elem.CurrentX < Elem.FinalX) ++Elem.CurrentX;

				if (!YMoveCounter)
				{
					if (Elem.CurrentY > Elem.FinalY) --Elem.CurrentY;
					else if (Elem.CurrentY < Elem.FinalY) ++Elem.CurrentY;
				}

				++MovingElements;
			}
			mvaddch(Elem.CurrentY, Elem.CurrentX, ' ');
		}

		YMoveCounter = (++YMoveCounter % 4);
		
		std::this_thread::sleep_for(std::chrono::milliseconds(1000/MOVEMENT_SPEED));
	}

	attroff(COLOR_PAIR(LOGOCOLOR) | A_BOLD);

	mvprintw(41 - BaseY, 136 - BaseX, "SIMULATOR 2016");
	refresh();
	erase();


	std::this_thread::sleep_for(std::chrono::milliseconds(1500));

}

void Logo::AddElement(unsigned X, unsigned Y)
{
	for (int i = 0; i < SCALE_X; ++i)
		for (int j = 0; j < SCALE_Y; ++j)
			Elements.push_back(LogoElement(X * SCALE_X + i, Y * SCALE_Y  +j));

}