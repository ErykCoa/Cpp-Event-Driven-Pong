#pragma once

#include <stdlib.h>

enum Player { Left = 'L', Right = 'R', None = 'N' };

enum Environment { ColorVar = 'c',  Border = 'B', Background = 'b', Score = 'S', Title = 'T', Text = 't', SelectedText = 's', SelectedField = 'f' };

enum BounceDimension { X = 0, Y};

enum BallType { Normal = 0, Large };

enum CommandType : int { Nothing = NULL, Accept, ChangeBallSize, PaddleLeftMoveUp, PaddleLeftMoveDown, PaddleRightMoveUp, PaddleRightMoveDown, Exit, CommandTypeEnding };

enum SelectedGameMode { NoneMode, MainMenu, SinglePlayer, MultiPlayer, AITest, BasicAI };

enum class SelectedMenuScreen { None = 0, MainMenu, ConfiguratonMenu};

enum class AlignType {Centered, Left, Right};

enum class DrawingPriority { Defult = 0, Background = 10, Ball = 9,  Borders = 8, Score = 7, Paddle = -1, Overlay = -5, Message = -6};

enum EventId { ErrorMessage, ScoreHasChanged, BallHasMoved, ChangeGameMode, NewUserCommand, PrepareFrame, RenderFrame };

enum class EventState { Handled, Pending };

enum class HandlerReturnCall { Failed, Succeed, StopHandlingEvent, HandledCompletely};
