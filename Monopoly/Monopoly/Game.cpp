#include "Game.h"

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
	// PlaySound("Music\\background_sound.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	system("cls");
	cout << "                  __  __                                                            __            " << endl;
	cout << "                  F  \\/  ]      ____      _ ___       ____      _ ___       ____     LJ    _    _  " << endl;
	cout << "                 J |\\__/| L    F __ J    J '__ J     F __ J    J '__ J     F __ J    FJ   J |  | L " << endl;
	cout << "                 | |`--'| |   | |--| |   | |__| |   | |--| |   | |--| |   | |--| |  J  L  | |  | | " << endl;
	cout << "                 F L    J J   F L__J J   F L  J J   F L__J J   F L__J J   F L__J J  J  L  F L__J J " << endl;
	cout << "                J__L    J__L J\\______/F J__L  J__L J\\______/F J  _____/L J\\______/F J__L  )-____  L" << endl;
	cout << "                |__L    J__|  J______F  |__L  J__|  J______F  |_J_____F   J______F  |__| J\\______/F" << endl;
	cout << "                                                              L_J                         J______F " << endl;

	vector<string> option;
	option = { " ＿＿＿＿＿＿＿＿ " ,
	"|                |" ,
	"|    開始遊戲    |",
	"|＿＿＿＿＿＿＿＿|",
	"|                |" ,
	"|    載入遊戲    |" ,
	"|＿＿＿＿＿＿＿＿|" ,
	"|                |" ,
	"|      設定      |" ,
	"|＿＿＿＿＿＿＿＿|" ,
	"|                |",
	"|    離開遊戲    |" ,
	"|＿＿＿＿＿＿＿＿|" };
	Game::setTextStyle(GOLD, BLACK);
	for (int i = 0; i < 4; i++)
	{
		Game::setCursorXY(46, 12 + i); //起始點 (46,12) 
		cout << option[i] << endl;
	}
	Game::setTextStyle(WHITE, BLACK);
	for (int i = 4; i < 13; i++)
	{
		Game::setCursorXY(46, 12 + i);
		cout << option[i] << endl;
	}

	Game::setCursorXY(0, 28);
	cout << "倉頡輸入法：" << endl;
	Game::setCursorXY(54, 15);
	while (1)
	{
		char c = _getch();
		if (c == 13) //Enter
		{
			if (markPosition.y == 15)
				Game::startGame();
			else if (markPosition.y == 18)
				Game::loadGame();
			else if (markPosition.y == 21)
				Game::settingGame();
			else
			{
				exit(1);
			}
		}
		else
		{
			switch (c)
			{
			case 72://上
				markPosition = optionUp(markPosition);
				showOption(markPosition, option);
				break;
			case 80://下
				markPosition = optionDown(markPosition);
				showOption(markPosition, option);
				break;
			default:
				break;
			}
		}
	}
}
void Game::startGame()
{
	Game::display();
}

void Game::loadGame()
{
}

void Game::settingGame()
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

Position Game::optionUp(Position markPosition)
{
	if (markPosition.y == 15)
		return markPosition;
	else
	{
		markPosition.y -= 3;
		moveCursor(0, -3);
	}
	return markPosition;
}

Position Game::optionDown(Position markPosition)
{
	if (markPosition.y == 24)
		return markPosition;
	else
	{
		markPosition.y += 3;
		moveCursor(0, 3);
	}
	return markPosition;
}

void Game::showOption(Position markPosition, vector<string> option)
{
	Game::setTextStyle(WHITE, BLACK);
	for (int i = 0; i < 13; i++)
	{
		Game::setCursorXY(46, 12 + i);
		cout << option[i] << endl;
	}
	Game::setTextStyle(GOLD, BLACK);

	for (int i = 0; i < 4; i++)
	{
		Game::setCursorXY(46, markPosition.y - 3 + i);
		cout << option[markPosition.y - 15 + i] << endl;
	}
	Game::setCursorXY(markPosition.x, markPosition.y);
}

void Game::menu()
{
}

void Game::display()
{
	system("cls");

	ifstream inputS("Basemap\\basemap_template.txt");
	string str;

	Game::setTextStyle(WHITE, BLACK);
	while (getline(inputS, str))
	{
		cout << str << endl;
	}

	inputS.close();
}