#ifndef COMMONSTRUCTS
#define COMMONSTRUCTS

#include <chrono>

namespace CS
{
	struct BallInfo {
		int PrevPosX;
		int PrevPosY;
		int PosX;
		int PosY;
		int NextPosX;
		int NextPosY;
	};

	struct Border {
		int Padding;
		int Lenght;
	};

	struct PaddleInfo {
		int PosX;
		int PosY;
		int Lenght;
	};

	struct BackgroundElementInfo {
		std::chrono::system_clock::time_point LastMoveTime;
		int MovementSpeed;
		int PosX;
		int PosY;
	};
}


#endif
