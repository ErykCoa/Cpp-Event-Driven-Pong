#ifndef PADDLES_MANAGEMENT
#define PADDLES_MANAGEMENT

#include "eCurses.h"
#include "enums.h"
#include "DataBus.h"

class paddles_management
{
public:
	void MovePaddle(CommandType Command);
	void UpdatePaddlesSize();
	void UpdatePaddlesInfo();
	void UpdatePaddlesAfterWindowResize() {};

	paddles_management(DataBus& Data);
	~paddles_management();
private:

	struct {
		int PosX;
		int PosY;
		int Lenght;
	}PaddleLeft, PaddleRight;

	DataBus& Data;

	bool IsCommandCorrect(CommandType Command);
};

#endif