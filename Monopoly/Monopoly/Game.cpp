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

	Game::setCursorXY(0, 30);
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
	Game::fileName = "initial.txt";
	Game::processFile(Game::fileName);
	Game::selectPlayer();
	Game::playerState = 0;
	Game::InGame();
}

void Game::selectPlayer()
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
			vector<Player>tmp;
			for (int i = 0; i < Game::howManyPlayer; i++)
			{
				Player _tmp;
				_tmp.Id = i;
				_tmp.name = "  ";
				_tmp.property.money = 30000;
				_tmp.position = 0;
				tmp.push_back(_tmp);
			}
			Game::selectRound();
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

void Game::selectRound()
{
	Game::howManyRound= 20;
	vector<string> howManyRoundBoard;
	howManyRoundBoard = {
" ________________ " ,
"|                |" ,
"|    回合數量    |" ,
"|________________|" ,
"|                |" ,
"|    ＜ 20 ＞    |" ,
"|________________|" };
	for (int i = 0; i < howManyRoundBoard.size(); i++)
	{
		Game::setTextStyle(BLUE, BLACK);
		Game::setCursorXY(46, 21 + i);
		cout << howManyRoundBoard[i] << endl;
	}
	while (1)
	{
		Game::setCursorXY(54, 26);
		char c = _getch();
		if (c == 13) //Enter
		{
			Game::displayTemplate();
			Game::displayMap();
			Game::InGame();
		}
		else if (c == 27) //esc
		{
			vector<string> back;
			back = {
			"|＿＿＿＿＿＿＿＿|",
			"|                |" ,
			"|    離開遊戲    |" ,
			"|＿＿＿＿＿＿＿＿|",
			"                   " ,
			"                   " ,
			"                   " ,
			"                   " };
			Game::setTextStyle(CYAN, BLACK);
			Game::setCursorXY(46, 21);
			cout << back[0] << endl;

			Game::setTextStyle(WHITE, BLACK);
			for (int i = 1; i < 8; i++)
			{
				Game::setCursorXY(46, 21 + i);
				cout << back[i] << endl;
			}
			Game::setCursorXY(54, 20);
			Game::selectPlayer();
		}
		else
		{
			switch (c)
			{
			case 75: //左
				if (howManyRound != 10)
					Game::howManyRound -= 10;
				Game::setCursorXY(54, 26);
				cout << howManyRound;
				break;
			case 77: //右
				if (howManyRound != 50)
					Game::howManyRound += 10;
				Game::setCursorXY(54, 26);
				cout << Game::howManyRound;
				break;
			default:
				break;
			}
		}
	}
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
	Game::fileName = allFileName[0];
	int index = 0;
	while (1)
	{
		Game::setCursorXY(54, 20);
		char c = _getch();
		if (c == 13) //Enter
		{
			Game::processFile(allFileName[index]);
			Game::displayTemplate();
			Game::displayMap();
			Game::InGame();
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

void Game::InGame()
{
	Game::markPlayerAndLocalPosition(Game::players);
	Game::setTextStyle(WHITE, BLACK);
	Game::rollDice();
}

void Game::markPlayerAndLocalPosition(vector<Player> players)
{
	for (int i = 0; i < Game::howManyPlayer; i++)
	{
		if (i == 0)
			Game::setTextStyle(RED, RED);
		else if (i == 1)
			Game::setTextStyle(GREEN, GREEN);
		else if (i == 2)
			Game::setTextStyle(BLUE, BLUE);
		else if (i == 3)
			Game::setTextStyle(GOLD, GOLD);

		for (int j = 0; j < players[i].property.localIds.size(); j++)
		{
			Game::pocessMarkLocalPosition(players[i].property.localIds[j]);
			cout << "        ";
		}

		if (i == 0)
			Game::setTextStyle(RED, BLACK);
		else if (i == 1)
			Game::setTextStyle(GREEN, BLACK);
		else if (i == 2)
			Game::setTextStyle(BLUE, BLACK);
		else if (i == 3)
			Game::setTextStyle(GOLD, BLACK);
		Game::pocessPlayerLocalPosition(i, players[i].position);
		cout << "✈";
	}
}

void Game::pocessMarkLocalPosition(int localId)
{
	if (localId >= 0 && localId <= 7)
	{
		Game::setCursorXY(20, 8 + 4 * localId);
	}
	else if (localId >= 8 && localId <= 14)
	{
		Game::setCursorXY(30 + 10* (localId - 8), 36);
	}
	else if (localId >= 15 && localId <= 21)
	{
		Game::setCursorXY(90, 32 - 4 * (localId - 15));
	}
	else
	{
		Game::setCursorXY(80 - 10 * (localId - 22), 8);
	}
}

void Game::pocessPlayerLocalPosition(int ID, int position)
{
	if (position >= 0 && position <= 7)
	{
		Game::setCursorXY(20 + 2 * ID, 11 + 4 * position);
	}
	else if (position >= 8 && position <= 14)
	{
		Game::setCursorXY(30 + 10 * (position - 8) + 2 * ID, 39);
	}
	else if (position >= 15 && position <= 21)
	{
		Game::setCursorXY(90 + 2 * ID, 35 - 4 * (position - 15));
	}
	else
	{
		Game::setCursorXY(80 - 10 * (position - 22) + 2 * ID, 11);
	}
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

void Game::rollDice()
{
	srand(time(NULL));
	showDice(rand() % (6 - 2) +1);
}

void Game::showDice(int number)
{
	fstream file ;
	string diceFile = "Dice\\dice";
	string diceNumber;
	if (number == 1)
		diceNumber = "1.txt";
	else if(number == 2)
		diceNumber = "2.txt";
	else if (number == 3)
		diceNumber = "3.txt";
	else if (number == 4)
		diceNumber = "4.txt";
	else if (number == 5)
		diceNumber = "5.txt";
	else
		diceNumber = "6.txt";
	diceFile += diceNumber;
	file.open(diceFile);
	Game::setCursorXY(0, 0);
	string str;
	while (getline(file, str))
	{
		cout << str << endl;
	}
	file.close();
}

void Game::processFile(string filename)
{
	string _fileName = "Basemap\\" + filename;
	ifstream file(_fileName);
	string str;

	//process game information
	file >> Game::mapName;
	file >> Game::howManyRound;
	file >> Game::howManyPlayer;
	
	//process local information
	for (int i = 0; i <= 27; i++)
	{
		Local l;
		file >> l.Id;
		file >> l.name;
		file >> l.localType;
		if (l.localType == 1)
		{
			vector<int> price;
			for (int j = 0; j < 5; j++)
			{
				int p = 0;
				file >> p;
				price.push_back(p);
			}
			l.priceOfType = price;
		}
		Game::locals.push_back(l);
	}

	//process player information
	file >> str;
	file >> Game::playerState;

	vector<Player> foo; //避免因為切換startGame和loadGame 所產生players push_back的問題
	Game::players = foo;

	for (int i = 0; i < Game::howManyPlayer; i++)
	{
		Player p;
		file >> p.Id;
		file >> p.position;
		
		file >> p.property.money;
		getline(file, str);
		istringstream iss(str);
		int localId;
		while (iss >> localId)
		{
			p.property.localIds.push_back(localId);
			int localPriceType;
			iss >> localPriceType;
			Game::locals[localId].nowPriceType = localPriceType;
		}
		Game::players.push_back(p);
	}
	file.close();
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
	cout << Game::howManyPlayer << " Player" << "  file: " << Game::fileName;

}

void Game::displayMap()
{
	Game::setCursorXY(24, 2);
	string color = "　　　　　　      ";
	for (int i = 0; i < Game::howManyPlayer; i++)
	{
		Game::setTextStyle(WHITE, BLACK);
		Game::setCursorXY(27 + i * 20, 1);
		if (i + 1 == 1)
		{
			cout << "１Ｐ";
			Game::setTextStyle(RED, RED);
			Game::setCursorXY(20 + i * 20, 2);
			cout << color;
		}
		else if (i + 1 == 2)
		{
			cout << "２Ｐ";
			Game::setTextStyle(GREEN, GREEN);
			Game::setCursorXY(20 + i * 20, 2);
			cout << color;
		}
		else if (i + 1 == 3)
		{
			cout << "３Ｐ";
			Game::setTextStyle(BLUE, BLUE);
			Game::setCursorXY(20 + i * 20, 2);
			cout << color;
		}
		else
		{
			cout << "４Ｐ";
			Game::setTextStyle(GOLD, GOLD);
			Game::setCursorXY(20 + i * 20, 2);
			cout << color;
		}
	}
	Game::setTextStyle(WHITE, BLACK);
	for (int i = 0; i < Game::howManyPlayer; i++)
	{
		Game::setCursorXY(23 + i * 20, 3);
		cout << "＄" << Game::players[i].property.money;
	}

	for (int i = 0; i < 8; i++)
	{
		Game::setCursorXY(21, 9 + i * 4);
		cout << Game::locals[i].name;
	}
	Game::setCursorXY(31, 37);
	for (int i = 8; i < 15; i++)
	{
		cout << Game::locals[i].name << " ｜ ";
	}
	for (int i = 15; i < 22; i++)
	{
		Game::setCursorXY(91, 37 - (i - 14) * 4);
		cout << Game::locals[i].name;
	}
	Game::setCursorXY(32, 9);
	for (int i = 27; i > 25; i--)
	{
		cout << Game::locals[i].name << "  ｜  ";
	}
	Game::setCursorXY(51, 9);
	for (int i = 25; i > 21; i--)
	{
		cout << Game::locals[i].name << " ｜ ";
	}
}