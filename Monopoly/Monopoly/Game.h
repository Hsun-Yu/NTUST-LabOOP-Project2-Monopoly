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
#include "Company.h"
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
	void selectCharacter();
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
	void moveCursor(int x, int y);
	static void setTextStyle(int color, int backgroundColor);
	void menu();
	void menuUp();
	void menuDown();
	void showMenuOption(vector<string>);
	void displayTemplate();
	void displayMap();
	void optionUp();
	void optionDown();
	void showOption(vector<string>);
	void rollDice();
	void showDice();
	void moveCharacter();
	void changeplayerState();
	void changeRound();
	void deleteBeforePlace();
	void showPlayerState();
	void showRound();
	void processFile(string filename);
	void resetCompanyStock();
	void showPlayerProperty();
	void buyLocal();
	void getFee();
	void upgrate();
	void useToolYesOrNo();
	void useTool();
	void whichToolWantBuy();
	void buyTool(int toolId);
	void choiceLeft();
	void choiceRight();
	void showChoice(vector<string>, vector<string>);
	void allShowOnTheMap();
	void saveGame();
	void bankMenu();
	void sellLocal();
	void blackHole();
	void showTool();
	void processMarkToolPosition(int );
	void spaceStation();
	void whichStockWantBuy();
	void buyStock(int );
	
	void checkWhoWin();
	void endOfGame(Player winnner);

	void initialGame();

	static vector<Player> players;
	static vector<Local> locals;
	static vector<Company> companys;
	static vector<Tool*> tools;
	 
	static vector<Chance*> chances;
	static vector<Fortune*> fortunes;

	static void setCursorXY(int x, int y);
private:
	static HANDLE outputHandle;
	static COORD cursorXY; //cursor position on whole window
	bool isInGame = true;
	bool useSuperDice = false;

	string mapName;
	int round;
	int tmpRound;
	int howManyRound;


	int playerState;

	int howManyPlayer;
	int diceNumber;
};

