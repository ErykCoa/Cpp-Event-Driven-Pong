#ifndef IGAME
#define IGAME

#include "enums.h"

class IGame
{
public:
	virtual void StartGame() =0;
	virtual ~IGame() {};
};

#endif