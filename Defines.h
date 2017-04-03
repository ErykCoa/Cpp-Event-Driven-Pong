#ifndef DEFINES
#define DEFINES

#include <chrono>

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define FOREGROUND_ELEMENT_MOVEMENTSPEED 200
#define BACKGROUND_ELEMENT_MOVEMENTSPEED 100

#define BASE_BASIC_AI_SEARCH_RANGE 15

#define BASE_BALL_MOVEMENT_SPEED 120

#define STANDARD_USER_INPUT_DELAY std::chrono::milliseconds(20)
#define STANDARD_MAIN_MENU_USER_INPUT_DELAY std::chrono::milliseconds(100)

#define STANDARD_MAIN_MENU_GAME_TEMPO 140

#define MAX_MSG_LENGTH 60

#endif