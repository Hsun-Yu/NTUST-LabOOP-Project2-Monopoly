#include "Game.h"

HANDLE Game::outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
COORD Game::cursorXY;

Game::Game()
{
	// PlaySound("Music\\background_sound.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
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
	system("cls");
	vector <string> title;
	title = { "                  __  __                                                            __            " ,
	"                  F  \\/  ]      ____      _ ___       ____      _ ___       ____     LJ    _    _  " ,
	"                 J |\\__/| L    F __ J    J '__ J     F __ J    J '__ J     F __ J    FJ   J |  | L " ,
	"                 | |`--'| |   | |--| |   | |__| |   | |--| |   | |--| |   | |--| |  J  L  | |  | | " ,
	"                 F L    J J   F L__J J   F L  J J   F L__J J   F L__J J   F L__J J  J  L  F L__J J " ,
	"                J__L    J__L J\\______/F J__L  J__L J\\______/F J  _____/L J\\______/F J__L  )-____  L" ,
	"                |__L    J__|  J______F  |__L  J__|  J______F  |_J_____F   J______F  |__| J\\______/F" ,
	"                                                              L_J                         J______F " };
	for (int i = 0; i < title.size(); i++)
	{
		Game::setTextStyle(KHIKI, BLACK);
		cout << title[i] << endl;
	}

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
			if (Game::cursorXY.Y == 15)
				Game::startGame();
			else if (Game::cursorXY.Y == 18)
				Game::loadGame();
			else if (Game::cursorXY.Y == 21)
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
				optionUp();
				showOption(option);
				break;
			case 80://下
				optionDown();
				showOption(option);
				break;
			default:
				break;
			}
		}
	}
}
void Game::startGame()
{
	Game::howManyPlayer = 1;
	vector<string> howManyPlayerBoard;
	howManyPlayerBoard = {
		" ________________ " ,
		"|                |" ,
		"|    遊玩人數    |" ,
		"|________________|" ,
		"|                |" ,
		"|    ＜ １ ＞    |" ,
		"|________________|" };
	for (int i = 0; i < howManyPlayerBoard.size(); i++)
	{
		Game::setTextStyle(CYAN, BLACK);
		Game::setCursorXY(46, 15 + i);
		cout << howManyPlayerBoard[i] << endl;
	}
	while (1)
	{
		Game::setCursorXY(54, 20);
		char c = _getch();
		if (c == 13) //Enter
		{
			Game::displayTemplate();
			Game::fileName = "initial.txt";
			Game::processTxtInformation(Game::fileName);
			Game::whoPlayer = 0;
			Game::displayMap();
		}
		else if (c == 27) //esc
		{
			Game::enterScreen();
		}
		else
		{
			switch (c)
			{
			case 75: //左
				if (howManyPlayer != 1)
					howManyPlayer--;
				showHowManyPlayer(howManyPlayer);
				break;
			case 77: //右
				if (howManyPlayer != 4)
					howManyPlayer++;
				showHowManyPlayer(howManyPlayer);
				break;
			default:
				break;
			}
		}
	}
}

void Game::showHowManyPlayer(int howManyPlayer)
{
	Game::setCursorXY(54, 20);
	if (howManyPlayer == 1)
		cout << "１" << endl;
	else if (howManyPlayer == 2)
		cout << "２" << endl;
	else if (howManyPlayer == 3)
		cout << "３" << endl;
	else
		cout << "４" << endl;
}

void Game::loadGame()
{
	vector<string> whichFileWantLoad;

	whichFileWantLoad = {
		" ________________ " ,
		"|                |" ,
		"|＜            ＞|" ,
		"|________________|" };
	for (int i = 0; i < whichFileWantLoad.size(); i++)
	{
		Game::setTextStyle(CYAN, BLACK);
		Game::setCursorXY(46, 18 + i);
		cout << whichFileWantLoad[i] << endl;
		string folder = "Basemap";
		allFileName = get_all_files_names_within_folder(folder);
		Game::setCursorXY(50, 20);
		cout << allFileName[0];
	}
	int index = 0;
	while (1)
	{
		Game::setCursorXY(54, 20);
		char c = _getch();
		if (c == 13) //Enter
		{
			Game::processTxtInformation(allFileName[index]);
			Game::displayTemplate();
			Game::displayMap();
		}
		else if (c == 27) //esc
		{
			Game::enterScreen();
		}
		else
		{
			switch (c)
			{
			case 75: //左
				if (index != 0)
				{
					index--;
					Game::setCursorXY(46, 20);
					cout << "|＜" << allFileName[index];
					for (int i = 0; i < 12 - allFileName[index].size(); i++)
						cout << " ";
					cout << "＞|";
					string name = allFileName[index];
					Game::fileName = name;
				}
				break;
			case 77: //右
				if (index != allFileName.size() - 1)
				{
					index++;
					Game::setCursorXY(46, 20);
					cout << "|＜" << allFileName[index];
					for (int i = 0; i < 12 - allFileName[index].size(); i++)
						cout << " ";
					cout << "＞|";
					string name = allFileName[index];
					Game::fileName = name;
				}
				break;
			default:
				break;
			}
		}
	}
}

vector<string> Game::get_all_files_names_within_folder(string folder)
{
	vector<string> names;
	string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
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

void Game::optionUp(void)
{
	if (Game::cursorXY.Y == 15)
	{ }
	else
	{
		moveCursor(0, -3);
	}
}

void Game::optionDown(void)
{
	if (Game::cursorXY.Y == 24)
	{}
	else
	{
		Game::cursorXY.Y += 3;
	}
}

void Game::showOption(vector<string> option)
{
	int y = Game::cursorXY.Y;
	Game::setTextStyle(WHITE, BLACK);
	for (int i = 0; i < 13; i++)
	{
		Game::setCursorXY(46, 12 + i);
		cout << option[i] << endl;
	}
	Game::setTextStyle(GOLD, BLACK);

	for (int i = 0; i < 4; i++)
	{
		Game::setCursorXY(46, y - 3 + i);
		cout << option[y - 15 + i] << endl;
	}
	Game::setCursorXY(54, y);
}

void Game::menu()
{
}

void Game::displayTemplate()
{
	system("cls");

	ifstream inputBasemap_template("Basemap_template\\base.txt");
	string str;
	vector <string> item;

	Game::setTextStyle(WHITE, BLACK);
	while (getline(inputBasemap_template, str))
	{
		cout << str << endl;
	}
	inputBasemap_template.close();
	cout << Game::howManyPlayer << " Player";

}
void Game::processTxtInformation(string fileName)
{
	string _fileName = "Basemap\\";
	_fileName += fileName;
	ifstream file(_fileName);
	string str;
	vector<string> item;
	while (getline(file, str))
	{
		item.push_back(str);
	}
	file.close();
	Game::processPlayerRoundName(item[0]);
	Game::processLocalinformation(item);
	Game::processPlayerInformation(item);
}

void Game::processPlayerRoundName(string item)
{
	string str;
	vector <string> information;
	for (int i = 0; i < item.size(); i++)
	{
		if (item[i] != ' ')
		{
			str += item[i];
			if (i == item.size() - 1)
			{
				information.push_back(str);
				str.erase(0, str.size());
			}
		}
		else
		{
			information.push_back(str);
			str.erase(0, str.size());
		}
	}
	Game::mapName = information[0];
	if (Game::fileName != "initial.txt")
	{
		Game::round = stoi(information[1]);
		Game::howManyPlayer = stoi(information[2]);
	}
}

void Game::processLocalinformation(vector<string> item)
{
	vector<vector<string>> tmp;
	vector<string> space = { " "," "," "," "," "," "," "," " };
	for (int i = 0; i < 28; i++)
	{
		tmp.push_back(space);
	}
	for (int i = 1; i < 29; i++)
	{
		string str;
		vector<string> information;
		for (int j = 0; j < item[i].size(); j++)
		{
			if (item[i][j] != ' ')
			{
				str += item[i][j];
				if (i == item[i].size() - 1)
				{
					information.push_back(str);
					str.erase(0, str.size());
				}
			}
			else
			{
				information.push_back(str);
				str.erase(0, str.size());
			}
		}
		int k = 0;
		for (; k < information.size(); k++)
		{
			tmp[i - 1][k] = information[k];
		}
		tmp[i - 1][k] = str;
	}
	Game::localInformation = tmp;
}

void Game::processPlayerInformation(vector<string> item)
{
	vector<vector<string>> tmp;
	vector <string> space;
	for (int i = 0; i < 59; i++)
	{
		space.push_back(" ");
	}
	for (int i = 0; i < 5; i++)
	{
		tmp.push_back(space);
	}
	for (int i = 29; i < item.size(); i++)
	{
		string str;
		vector<string> information;
		for (int j = 0; j < item[i].size(); j++)
		{
			if (item[i][j] != ' ')
			{
				str += item[i][j];
				if (i == item[i].size() - 1)
				{
					information.push_back(str);
					str.erase(0, str.size());
				}
			}
			else
			{
				information.push_back(str);
				str.erase(0, str.size());
			}
		}
		int k = 0;
		for (; k < information.size(); k++)
		{
			tmp[i - 29][k] = information[k];
		}
		tmp[i - 29][k] = str;
	}
	if (Game::fileName != "initial.txt")
		Game::whoPlayer = stoi(tmp[0][1]);
	for (int i = 0; i < tmp.size(); i++)
	{
		if (i == 0)
		{
			tmp.erase(tmp.begin() + i);
		}
	}
	Game::playerInformation = tmp;
}

void Game::displayMap()
{
	Game::setCursorXY(24, 2);
	for (int i = 0; i < Game::howManyPlayer; i++)
	{
		Game::setCursorXY(27 + i * 20, 2);
		if(i + 1 == 1)
			cout << "１Ｐ" << endl;
		else if ( i + 1 == 2)
			cout << "２Ｐ" << endl;
		else if (i + 1 == 3)
			cout << "３Ｐ" << endl;
		else
			cout << "４Ｐ" << endl;
	}

	for (int i = 0; i < 8; i++)
	{
		Game::setCursorXY(21, 9 + i * 4);
		cout << localInformation[i][1];
	}
	Game::setCursorXY(31, 37);
	for (int i = 8; i < 15; i++)
	{
		cout << localInformation[i][1] << " ｜ ";
	}
	for (int i = 15; i < 22; i++)
	{
		Game::setCursorXY(91, 37 - (i - 14) * 4);
		cout << localInformation[i][1];
	}
	Game::setCursorXY(32, 9);
	for (int i = 27; i > 25; i--)
	{
		cout << localInformation[i][1] << "  ｜  ";
	}
	Game::setCursorXY(51, 9);
	for (int i = 25; i > 21; i--)
	{
		cout << localInformation[i][1] << " ｜ ";
	}
}