#ifndef LOGO
#define LOGO

#include "eCurses.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

#define MOVEMENT_SPEED 180
#define SCALE_X 4
#define SCALE_Y 3
#define LOGOCOLOR 'l'

constexpr unsigned BaseX = (150 - 28*SCALE_X) / 2;
constexpr unsigned BaseY = (40 - 8* SCALE_Y) / 2;

struct LogoElement{
	unsigned CurrentX;
	unsigned CurrentY;

	unsigned FinalX;
	unsigned FinalY;

	LogoElement(unsigned FinalRelativeX, unsigned FinalRelativeY) : FinalX{ FinalRelativeX + BaseX}, FinalY{ FinalRelativeY + BaseY }
	{
		CurrentX = std::rand() % 150;
		CurrentY = std::rand() % 40;
	}
};

class Logo
{
public:
	void DrawLogo();

	Logo();

private:

	void AddElement(unsigned X, unsigned Y);

	std::vector<LogoElement> Elements;

};

#endif