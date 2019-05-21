#include "Game.h"

using namespace std;

HANDLE Game::outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
COORD Game::cursorXY;

Game::Game()
{
	Game::enterScreen();

}


Game::~Game()
{
}

void Game::setTextStyle(int color, int backgroundColor)
{
	SetConsoleTextAttribute(Game::outputHandle, color | (backgroundColor * 16));
}

void Game::enterScreen()
{
	PlaySound("Music\\background_sound.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	system("cls");
	cout << "                  __  __                                                            __            " << endl;
	cout << "                  F  \\/  ]      ____      _ ___       ____      _ ___       ____     LJ    _    _  " << endl;
	cout << "                 J |\\__/| L    F __ J    J '__ J     F __ J    J '__ J     F __ J    FJ   J |  | L " << endl;
	cout << "                 | |`--'| |   | |--| |   | |__| |   | |--| |   | |--| |   | |--| |  J  L  | |  | | " << endl;
	cout << "                 F L    J J   F L__J J   F L  J J   F L__J J   F L__J J   F L__J J  J  L  F L__J J " << endl;
	cout << "                J__L    J__L J\\______/F J__L  J__L J\\______/F J  _____/L J\\______/F J__L  )-____  L" << endl;
	cout << "                |__L    J__|  J______F  |__L  J__|  J______F  |_J_____F   J______F  |__| J\\______/F" << endl;
	cout << "                                                              L_J                         J______F " << endl;

	cout << endl << endl << endl;
	cout << "                                               ＿＿＿＿＿＿＿＿ " << endl;
	cout << "                                              |                |" << endl;
	cout << "                                              |    開始遊戲    |" << endl;
	cout << "                                              |＿＿＿＿＿＿＿＿|" << endl;
	cout << "                                              |                |" << endl;
	cout << "                                              |    載入遊戲    |" << endl;
	cout << "                                              |＿＿＿＿＿＿＿＿|" << endl;
	cout << "                                              |                |" << endl;
	cout << "                                              |      設定      |" << endl;
	cout << "                                              |＿＿＿＿＿＿＿＿|" << endl;
	cout << "                                              |                |" << endl;
	cout << "                                              |    離開遊戲    |" << endl;
	cout << "                                              |＿＿＿＿＿＿＿＿|" << endl;
	cout << endl << endl << endl;
	cout << "倉頡輸入法" << endl;
}
void Game::initialize()
{
}
void Game::setCursorXY(int x, int y)
{
	Game::cursorXY.X = x;
	Game::cursorXY.Y = y;
	SetConsoleCursorPosition(Game::outputHandle, Game::cursorXY);
}

void Game::moveCursor(int x, int y)
{
	Game::setCursorXY(Game::cursorXY.X + x, Game::cursorXY.Y + y);
}

void Game::menu()
{
}

void Game::display()
{
}

void Game::menuUp()
{
}

void Game::menuDown()
{
}

void Game::menuLeft()
{
}

void Game::menuRight()
{
}
