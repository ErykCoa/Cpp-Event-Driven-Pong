#ifndef BALL_MANAGEMENT
#define BALL_MANAGEMENT


#include "enums.h"
#include <string>
#include "time.h"
#include "DataBus.h"
#include "CommonEvents.h"
#include "Defines.h"
#include <chrono>

class ball_management
{

public:

	int GetBallMovementSpeed();
	void SetBallMovementSpeed(int MovementSpeed);
	void GetCurrentBallPos(int& X, int& Y);
	void GetNextBallPos(int& X, int& Y);
	void BallMovement();

	ball_management(DataBus& Data);
	~ball_management();
	
private:

	DataBus& Data;

	std::chrono::system_clock::time_point LastBallMovementTime;

	struct {
		float MovementSpeedMultiplier;
		int MovementSpeed;
		int PosX;
		int PosY;
		int DirectionMaxIndex;
		int DirectionIndex;
		int* DirectionX;
		int* DirectionY;
	} Ball;

	void UpdateBallInfo();

	bool ScoreCheck();
	
	void BallRandDirection();
	
	void BallPositionAfterScore(Player Player);

	Player PaddleCollision();

	bool BorderCollision();

	void CollisionCheck();
	void BallBounce(BounceDimension);

	inline void UpdateLastBallMovementTime();
};


#endif