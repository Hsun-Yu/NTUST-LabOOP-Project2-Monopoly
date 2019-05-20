#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <MMSystem.h>

#define BLACK 0
#define BLACK2 FOREGROUND_INTENSITY
#define WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define GRAY FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
#define RED FOREGROUND_RED
#define GREEN FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define BLUE FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define CYAN FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define PURPLE FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define GOLD FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define KHIKI FOREGROUND_RED | FOREGROUND_GREEN
#define LIGHTRED FOREGROUND_RED | FOREGROUND_INTENSITY

class Game
{
public:
	Game();
	~Game();
	void setTextStyle(int color, int backgroundColor);
	void enterScreen();
	void initialize();

private:
	bool whoPlay;	//red true, black false
	bool AIType;	//AI Type: true

	static HANDLE outputHandle;
	static COORD cursorXY; //cursor position on whole window

	bool isInGame;
};

