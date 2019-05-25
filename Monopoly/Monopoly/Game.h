#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <MMSystem.h>
#include <filesystem>
#include <algorithm>
#include <sstream>
#include <time.h>

#include "Player.h"
#include "Local.h"
#include "Fortune.h"
#include "Chance.h"
#include "Bank.h"
using namespace std;

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
	void enterScreen();
	void startGame();
	void selectPlayer();
	void showHowManyPlayer(int);
	void selectRound();
	void loadGame();
	vector<string> get_all_files_names_within_folder(string folder);
	vector<string> allFileName;
	string fileName;
	void InGame();
	void markPlayerAndLocalPosition(vector<Player> players);
	void processMarkLocalPosition(int);
	void processMarkPlayerPosition(int, int);
	void settingGame();
	void setCursorXY(int x, int y);
	void moveCursor(int x, int y);
	void setTextStyle(int color, int backgroundColor);
	void menu();
	void displayTemplate();
	void displayMap();
	void optionUp();
	void optionDown();
	void showOption(vector<string>);
	void rollDice();
	void showDice();
	void moveCharacter();
	void changeplayerState();
	void deleteBeforePlace();
	void showPlayerState();
	void showRound();
	int howManyPlayer;
	int diceNumber;
	void processFile(string filename);

private:
	static HANDLE outputHandle;
	static COORD cursorXY; //cursor position on whole window
	bool isInGame;

	vector<Player> players;
	vector<Local> locals;

	vector<Chance> chances;
	vector<Fortune> fortunes;
	string mapName;
	int round;
	int howManyRound;
	Bank bank;

	int playerState;
};

