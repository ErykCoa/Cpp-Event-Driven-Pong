// PongCpp.cpp : Defines the entry point for the console application.
//

#include "window_management.h"


int main()
{
	/*WINDOW* Screen = initscr(); // Zainicjalizowanie ekranu
	noecho(); // nie wypisywanie znaku wchodzacego
	keypad(Screen, true); // czytanie znakow takich jak strzalki
	raw(); // wylaczenie ctrl+z ctrl+c
	curs_set(0); // ukrycie command prompt
	start_color(); // obsluga kolorow
	init_pair(Left, COLOR_BLUE, COLOR_WHITE);


	mvprintw(15, 60, " ");
	attron(COLOR_PAIR(Left) | A_BOLD);
	mvprintw(15, 60, "O");
	attroff(COLOR_PAIR(Left) | A_BOLD);
	refresh();
	*/

	{int tmp[]{ 1,1,-1,-1 };

	window_management pong{ tmp };

	pong.StartGame();

	}

    return 0;
}

