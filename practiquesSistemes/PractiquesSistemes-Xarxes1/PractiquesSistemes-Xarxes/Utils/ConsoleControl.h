#pragma once
#include <mutex>
#include <iostream>
#include <sstream>
#include <windows.h>
#include <conio.h>


static class ConsoleControl
{
private:

	HANDLE _console = GetStdHandle(STD_OUTPUT_HANDLE);
	std::mutex* _consoleMutex = new std::mutex;
	static ConsoleControl GetInstance();

	static HANDLE GetConsole();


public:

	enum ConsoleColor
	{
		BLACK, DARKBLUE, DARKGREEN, DARKCYAN, DARKRED, DARKMAGENTA, DARKYELLOW, LIGHTGRAY,
		DARKGRAY, BLUE, CYAN, RED, MAGENTA, YELLOW, WHITE
	};

	static void SetColor(ConsoleColor textColor = WHITE, ConsoleColor backgroundColor = BLACK);

	static void SetPosition(short int x, short int y);

	static void Clear();

	static void FillWithCharacter(char character, ConsoleColor textColor, ConsoleColor backgroundColor);

	static void ClearKeyBuffer();

	static int ReadNextKey();

	static int WaitForReadNextKey();

	static char WaitForReadNextChar();

	static void Lock();

	static void Unlock();

};

using CC = ConsoleControl; //Para poder usar CC envez de ConsoleControl [Es mas rapido y comodo]

