#include "ball_management.h"


ball_management::ball_management(DataBus& Data) : Data{Data}
{
	srand((unsigned)time(NULL));

	Ball.MovementSpeedMultiplier = 1;
	Ball.MovementSpeed = 20;

	Ball.PosX = Data.ScreenX / 2;
	Ball.PosY = Data.ScreenY / 2;

	Ball.DirectionIndex = 0;
	Ball.DirectionMaxIndex = 4;

	Ball.DirectionX = new int[Ball.DirectionMaxIndex+1];
	Ball.DirectionY = new int[Ball.DirectionMaxIndex+1];

	memset(Ball.DirectionX, 0, sizeof(int)*(Ball.DirectionMaxIndex+1));
	memset(Ball.DirectionY, 0, sizeof(int)*(Ball.DirectionMaxIndex+1));

	Ball.DirectionX[0] = -1;
	Ball.DirectionX[1] = -1;
	Ball.DirectionX[2] = -1;
	Ball.DirectionX[3] = -1;
	Ball.DirectionX[4] = -1;
	Ball.DirectionY[0] = 1;	

	UpdateBallInfo();

	UpdateLastBallMovementTime();
}


ball_management::~ball_management()
{
	delete[] Ball.DirectionX;
	delete[] Ball.DirectionY;
}

void ball_management::BallMovement()
{
	auto TimePeriod = std::chrono::system_clock::now() - LastBallMovementTime;
	while (TimePeriod > std::chrono::milliseconds(1000 / Ball.MovementSpeed))
	{
		Data.Events.Fire(CE::BallHasMoved());
		
		CollisionCheck();

		if (Ball.DirectionX[Ball.DirectionIndex]) Ball.PosX += Ball.DirectionX[Ball.DirectionIndex];
		if (Ball.DirectionY[Ball.DirectionIndex]) Ball.PosY += Ball.DirectionY[Ball.DirectionIndex];

		if (++Ball.DirectionIndex > Ball.DirectionMaxIndex) Ball.DirectionIndex = 0;

		UpdateBallInfo();

		UpdateLastBallMovementTime();

		TimePeriod -= std::chrono::milliseconds(1000 / Ball.MovementSpeed);
	}
}

void ball_management::CollisionCheck()
{
	switch (PaddleCollision())
	{
	case Left: BallBounce(X); Data.LastPlayer = Left; break;
	case Right: BallRandDirection(); BallBounce(X); Data.LastPlayer = Right; break;
	default: ScoreCheck(); 
	}

	if (BorderCollision()) BallBounce(Y);
}

void ball_management::BallBounce(BounceDimension Dimension) {
	if (!Dimension) for (int i = 5; i--;) // Dimension == X
	{
		Ball.DirectionX[i] *= -1;
	}
	else for (int i = 5; i--;) // Dimension == Y
	{
		Ball.DirectionY[i] *= -1;
	}
}


inline void ball_management::UpdateLastBallMovementTime()
{
	LastBallMovementTime = std::chrono::system_clock::now();
}

int ball_management::GetBallMovementSpeed()
{
	return Ball.MovementSpeed;
}

void ball_management::SetBallMovementSpeed(int MovementSpeed)
{
	Ball.MovementSpeed = static_cast<int>(MovementSpeed * Ball.MovementSpeedMultiplier);
}

void ball_management::GetCurrentBallPos(int & X, int & Y)
{
	X = Ball.PosX;
	Y = Ball.PosY;
}

void ball_management::GetNextBallPos(int & X, int & Y)
{
	X = Ball.PosX + Ball.DirectionX[Ball.DirectionIndex];
	Y = Ball.PosY + Ball.DirectionY[Ball.DirectionIndex];
}

bool ball_management::ScoreCheck()
{
	if (Ball.PosX + Ball.DirectionX[Ball.DirectionIndex] == Data.PaddleLeftInfo.PosX)
	{ 
		Data.LastPlayer = Left;
		Data.ScoreRight++;
		BallPositionAfterScore(Left);
		BallRandDirection();
		Data.Events.Fire(CE::ScoreHasChanged());
		return 1; 
	}

	if (Ball.PosX + Ball.DirectionX[Ball.DirectionIndex] == Data.PaddleRightInfo.PosX)
	{ 
		Data.LastPlayer = Right;
		Data.ScoreLeft++;
		BallPositionAfterScore(Right);
		BallRandDirection();
		Data.Events.Fire(CE::ScoreHasChanged());
		return 1; 
	}

	return 0;
}

void ball_management::BallPositionAfterScore(Player Player) {
	
	if (Player == Right) {
		Ball.PosY = Data.PaddleRightInfo.PosY;
		Ball.PosX = Data.PaddleRightInfo.PosX - 2;
	}
	else if (Player == Left) {
		Ball.PosY = Data.PaddleLeftInfo.PosY;
		Ball.PosX = Data.PaddleLeftInfo.PosX + 2;
	}
}

Player ball_management::PaddleCollision()
{
	if (Ball.PosX + Ball.DirectionX[Ball.DirectionIndex] == Data.PaddleLeftInfo.PosX)
	for (int i = Data.PaddleLeftInfo.Lenght; i--; )
	{
		if (Ball.PosY + Ball.DirectionY[Ball.DirectionIndex] == Data.PaddleLeftInfo.PosY - Data.PaddleLeftInfo.Lenght / 2 + i)
		{
			return Left;
		}
		
	}
	else if (Ball.PosX + Ball.DirectionX[Ball.DirectionIndex] == Data.PaddleRightInfo.PosX)
	for (int i = Data.PaddleRightInfo.Lenght; i--;)
	{

		if (Ball.PosY + Ball.DirectionY[Ball.DirectionIndex] == Data.PaddleRightInfo.PosY - Data.PaddleRightInfo.Lenght / 2 + i)
		{ 
			return Right;
		}
	}

	return None;
}

bool ball_management::BorderCollision()
{
	if ((Ball.PosY + Ball.DirectionY[Ball.DirectionIndex] == Data.BorderUp.Padding) || (Ball.PosY + Ball.DirectionY[Ball.DirectionIndex] == Data.ScreenY - Data.BorderDown.Padding - 1))
	{ 
		return 1; 
	}
	return 0;
}

void ball_management::BallRandDirection()
{

	if (rand() % 2) {
		Ball.DirectionX[0] = 0;
		Ball.DirectionX[1] = 0;
	}
	else if (rand() % 2) {
		Ball.DirectionX[0] = 0;
		Ball.DirectionX[1] = 1;
	}
	else {
		Ball.DirectionX[0] = 1;
		Ball.DirectionX[1] = 1;
	}

	Ball.DirectionX[2] = 1;
	Ball.DirectionX[3] = 1;
	Ball.DirectionX[4] = 1;

	Ball.DirectionY[0] = 0;
	Ball.DirectionY[1] = 0;

	if (rand() % 2) {
		Ball.DirectionY[2] = 0;
		Ball.DirectionY[3] = 1;
		Ball.DirectionY[4] = 1;
	}
	else if (rand() % 2) {
		Ball.DirectionY[2] = 0;
		Ball.DirectionY[3] = 1;
		Ball.DirectionY[4] = 0;
	}
	else if (rand() % 2) {
		Ball.DirectionY[2] = 1;
		Ball.DirectionY[3] = 1;
		Ball.DirectionY[4] = 1;
	}
	else {
		Ball.DirectionY[2] = 0;
		Ball.DirectionY[3] = 1;
		Ball.DirectionY[4] = 0;
	}

	if (rand() % 2) for (int i = 5; i--;) Ball.DirectionY[i] *= -1;
}

void ball_management::UpdateBallInfo()
{
	Data.BallInfo.PrevPosX = Data.BallInfo.PosX;
	Data.BallInfo.PrevPosY = Data.BallInfo.PosY;
	GetCurrentBallPos(Data.BallInfo.PosX, Data.BallInfo.PosY);
	GetNextBallPos(Data.BallInfo.NextPosX, Data.BallInfo.NextPosY);

}
