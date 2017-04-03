#ifndef ECURSES
#define ECURSES

#include <string>
#include "curses.h"
#include "enums.h"

namespace ecur
{

	template<AlignType Align = AlignType::Centered>
	static void DrawLineOfText(WINDOW* const Screen, unsigned Y, unsigned AlignValue, std::string String, char ColorPair = 0, int AdFormatOptions = 0);

	template<AlignType Align = AlignType::Centered>
	static void DrawChar(WINDOW* const Screen, unsigned Y, unsigned AlignValue, char Char, char ColorPair = 0, int AdFormatOptions = 0);

	template<>
	static void DrawLineOfText<AlignType::Centered>(WINDOW* const Screen, unsigned Y, unsigned AlignValue, std::string String, char ColorPair, int AdFormatOptions)
	{
		attron(COLOR_PAIR(ColorPair) | AdFormatOptions);
		mvwprintw(Screen, Y, (Screen->_maxx - String.length()) / 2, String.c_str());
		attroff(COLOR_PAIR(ColorPair) | AdFormatOptions);
	}

	template<>
	static void DrawLineOfText<AlignType::Left>(WINDOW* const Screen, unsigned Y, unsigned AlignValue, std::string String, char ColorPair, int AdFormatOptions)
	{
		attron(COLOR_PAIR(ColorPair) | AdFormatOptions);
		mvwprintw(Screen, Y, AlignValue, String.c_str());
		attroff(COLOR_PAIR(ColorPair) | AdFormatOptions);
	}	
	
	template<>
	static void DrawLineOfText<AlignType::Right>(WINDOW* const Screen, unsigned Y, unsigned AlignValue, std::string String, char ColorPair, int AdFormatOptions)
	{
		attron(COLOR_PAIR(ColorPair) | AdFormatOptions);
		mvwprintw(Screen, Y, (Screen->_maxx - AlignValue) - String.length(), String.c_str());
		attroff(COLOR_PAIR(ColorPair) | AdFormatOptions);
	}

	template<>
	static void DrawChar<AlignType::Centered>(WINDOW* const Screen, unsigned Y, unsigned AlignValue, char Char, char ColorPair, int AdFormatOptions)
	{
		attron(COLOR_PAIR(ColorPair) | AdFormatOptions);
		mvwaddch(Screen, Y, (Screen->_maxx - 1) / 2, Char);
		attroff(COLOR_PAIR(ColorPair) | AdFormatOptions);
	}

	template<>
	static void DrawChar<AlignType::Left>(WINDOW* const Screen, unsigned Y, unsigned AlignValue, char Char, char ColorPair, int AdFormatOptions)
	{
		attron(COLOR_PAIR(ColorPair) | AdFormatOptions);
		mvwaddch(Screen, Y, AlignValue, Char);
		attroff(COLOR_PAIR(ColorPair) | AdFormatOptions);
	}

	template<>
	static void DrawChar<AlignType::Right>(WINDOW* const Screen, unsigned Y, unsigned AlignValue, char Char, char ColorPair, int AdFormatOptions)
	{
		attron(COLOR_PAIR(ColorPair) | AdFormatOptions);
		mvwaddch(Screen, Y, (Screen->_maxx - AlignValue) - 1, Char);
		attroff(COLOR_PAIR(ColorPair) | AdFormatOptions);
	}

}
#endif