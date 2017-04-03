#ifndef IUSERINPUT
#define IUSERINPUT

#include "enums.h"
#include <chrono>

class IUserInput
{
public:
	virtual void ChangeControlAssignment(CommandType Command, char Key) = 0;
	virtual char GetControlAssignment(CommandType Command) = 0;
	virtual void SendUserInput(CommandType Command) = 0;
	virtual std::chrono::milliseconds UserInputDelay() = 0;
};

#endif