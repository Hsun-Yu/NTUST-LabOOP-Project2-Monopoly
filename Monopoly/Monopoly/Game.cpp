#include "Game.h"

HANDLE Game::outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
COORD Game::cursorXY;

vector<Local> Game::locals;
vector<Player> Game::players;
vector<Chance*> Game::chances;
vector<Fortune*> Game::fortunes;
vector<Company> Game::companys;
vector<Tool*> Game::tools;

Game::Game()
{
	Game::players.clear();
	Game::chances.clear();
	Game::fortunes.clear();
	Game::companys.clear();
	Game::tools.clear();
	Game::locals.clear();

	Game::tools.push_back(new RoadblockTool());
	Game::tools.push_back(new BombTool());
	Game::tools.push_back(new RoadblockTool());
	Game::tools.push_back(new ChooseWhereToGoTool());

	Game::fortunes.push_back(new SolarWindFortune());
	Game::fortunes.push_back(new BackToEarthFortune());
	Game::fortunes.push_back(new TimeTunnelFortune());
	Game::fortunes.push_back(new ChangePropertyFortune());
	
	Game::companys.push_back(CompanyA());
	Game::companys.push_back(CompanyB());
	Game::companys.push_back(CompanyC());
	Game::companys.push_back(CompanyD());

	Game::chances.push_back(new GetStockChance());
	Game::chances.push_back(new GetMoneyChance());
	Game::chances.push_back(new StopChance());

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
				_tmp.property.money = 10000;
				_tmp.position = 0;
				tmp.push_back(_tmp);
			}
			Game::players = tmp;
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

void Game::selectCharacter()
{
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
			Game::playerState = 0;
			Game::round = 1;
			Game::tmpRound = 1;
			Game::allShowOnTheMap();
			//Game::displayTemplate();
			//Game::displayMap();
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
			Game::round = 1;
			Game::tmpRound = 1;
			Game::allShowOnTheMap();
			/*Game::displayTemplate();
			Game::displayMap();*/
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
	while (1)
	{
		Game::allShowOnTheMap();  //markPlayerAndLocalPosition() && showPlayerState() && showRound() && displayMap()
		Game::checkWhoWin();
		Game::useToolYesOrNo();
		while (1)
		{
			Game::setCursorXY(109, 24);
			char c = _getch();
			if (c == 13) //Enter
			{
				Game::rollDice();
				Game::moveCharacter();
				Game::allShowOnTheMap();

				vector<string>Board;
				Board = {
			" __________ " ,
			"|          |" ,
			"|   銀行   |" ,
			"|__________|",
				"",
				"請按 Backspace",
				"",
			" __________ " ,
			"|          |" ,
			"| 玩家資訊 |" ,
			"|__________|",
				"",
				"  請按 Tab  ",
				"",
				" __________ " ,
			"|          |" ,
			"|   選單   |" ,
			"|__________|",
				"",
				"  請按 Esc  ",
				"",
			" __________ " ,
			"|          |" ,
			"|   換人   |" ,
			"|__________|",
				"",
				" 請按 Enter  " };
				for (int i = 0; i < Board.size(); i++)
				{
					Game::setTextStyle(GOLD, BLACK);
					Game::setCursorXY(104, 1 + i);
					cout << Board[i] << endl;
				}

				while (1)
				{
					Game::setCursorXY(109, 24);
					char c = _getch();
					if (c == 13) //Enter
					{
						Game::changeplayerState();
						break;
					}
					else if (c == 27) //esc
					{
						Game::menu();
					}
					else if (c == 9) //tab
					{
						Game::showPlayerProperty();
					}
					else if (c == 8) //backspace
					{
						Game::bankMenu();
					}
					else
						continue;
				}
				break;
			}
			else if (c == 27) //esc
			{
				Game::menu();
			}
			else if (c == 9) //tab
			{
				Game::showPlayerProperty();
			}
			else if (c == 8) //backspace
			{
				Game::bankMenu();
			}
			else
				continue;
		}
	}
}

void Game::markPlayerAndLocalPosition(vector<Player> players)
{
	for (int i = 0; i < Game::howManyPlayer; i++)
	{

		int backbroundColour;
		if (i == 0)
			backbroundColour = RED;
		else if (i == 1)
			backbroundColour = GREEN;
		else if (i == 2)
			backbroundColour = BLUE;
		else if (i == 3)
			backbroundColour = KHIKI;

		for (int j = 0; j < players[i].property.localIds.size(); j++)
		{
			Game::setTextStyle(WHITE, backbroundColour);
			Game::processMarkLocalPosition(players[i].property.localIds[j]);
			cout << " LEVEL:";

			cout << Game::locals[players[i].property.localIds[j]].level;
		}

		if (i == 0)
			Game::setTextStyle(RED, BLACK);
		else if (i == 1)
			Game::setTextStyle(GREEN, BLACK);
		else if (i == 2)
			Game::setTextStyle(BLUE, BLACK);
		else if (i == 3)
			Game::setTextStyle(KHIKI, BLACK);
		Game::processMarkPlayerPosition(i, players[i].position);
		cout << "✈"; 
	}
}

void Game::processMarkLocalPosition(int localId)
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

void Game::processMarkPlayerPosition(int ID, int position)
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
	Game::diceNumber = rand() % (6) + 1;
	showDice();
}

void Game::showDice()
{
	fstream file ;
	string diceFile = "Dice\\dice";
	string dice;
	if (Game::diceNumber == 1)
		dice = "1.txt";
	else if(Game::diceNumber == 2)
		dice = "2.txt";
	else if (Game::diceNumber == 3)
		dice = "3.txt";
	else if (Game::diceNumber == 4)
		dice = "4.txt";
	else if (Game::diceNumber == 5)
		dice = "5.txt";
	else
		dice= "6.txt";
	diceFile += dice;
	file.open(diceFile);
	Game::setCursorXY(0, 0);
	string str;
	int i = 0;
	Game::setTextStyle(WHITE, BLACK);
	while (getline(file, str))
	{
		Game::setCursorXY(105, 29 + i);
		cout << str << endl;
		i++;
	}
	file.close();
}

void Game::moveCharacter()
{
	Game::deleteBeforePlace();
	Game::players[playerState].goPosition(diceNumber);
	Game::changeRound();
	int localId = Game::players[playerState].position;
	Game::allShowOnTheMap();

	if (Game::locals[localId].localType == 1)
	{
		if (Game::locals[localId].tool->id != 0)
		{
			//Do something if has tool
			Game::locals[localId].tool->method(Game::players[playerState]);
			Game::locals[localId].setToDefaultTool();

			if (localId != Game::players[playerState].position)
				Game::allShowOnTheMap();
		}

		localId = Game::players[playerState].position;

		if (Game::locals[localId].level == 0)
		{
			if (Game::players[playerState].property.money >= locals[localId].getNowPriceOfLevel())
				Game::buyLocal();
			else
			{
				vector<string>Board;
				Board = {
			" _________________ " ,
			"|                 |" ,
			"|    你走到了     |" ,
			"|                 |" ,
			"| ＜     　   ＞  |" ,
			"|                 |" ,
			"|你沒有錢 可以購買|" ,
			"|                 |" ,
			"|＿＿＿＿＿＿＿＿_|" ,
			"|                 |" ,
			"|      確 定      |" ,
			"|＿＿＿＿＿＿＿＿_|" ,
				};
				for (int i = 0; i < 8; i++)
				{
					Game::setCursorXY(50, 16 + i);
					cout << Board[i];
				}
				Game::setTextStyle(GOLD, BLACK);
				for (int i = 8; i < Board.size(); i++)
				{
					Game::setCursorXY(50, 16 + i);
					cout << Board[i];
				}
				Game::setTextStyle(WHITE, BLACK);
				if (Game::locals[localId].name.size() < 8)
				{
					Game::setCursorXY(57, 20);
					cout << Game::locals[localId].name;
				}
				else
				{
					Game::setCursorXY(56, 20);
					cout << Game::locals[localId].name;
				}
				while (1)
				{
					Game::setCursorXY(59, 26);
					char c = _getch();
					if (c == 13) //Enter
					{
						return;
					}
					else
						continue;
				}
			}
		}
		else //Get fee or upgrate
		{
			if (!Game::players[playerState].property.isMyLocal(localId)) //Get fee
			{
				vector<string> FeeBoard;
				FeeBoard = {
					" _________________ " ,
				"|                 |" ,
				"|    你走到了     |" ,
				"|                 |" ,
				"| ＜     　   ＞  |" ,
				"|                 |" ,
				"|  需要交過路費   |" ,
				"|                 |" ,
				"|                 |" ,
				"|＿＿＿＿＿＿＿＿_|"
				};
				Game::setTextStyle(WHITE, BLACK);
				for (int i = 0; i < FeeBoard.size(); i++)
				{
					Game::setCursorXY(50, 16 + i);
					cout << FeeBoard[i];
				}
				if (Game::locals[localId].name.size() < 8)
				{
					Game::setCursorXY(57, 20);
					cout << Game::locals[localId].name;
				}
				else
				{
					Game::setCursorXY(56, 20);
					cout << Game::locals[localId].name;
				}
				Game::setTextStyle(GOLD, BLACK);
				Game::setCursorXY(56, 24);
				cout << "＄" << Game::locals[localId].getNowPriceOfLevel();
				Sleep(3000);
				Game::getFee();
			}
			else
			{
				Game::upgrate();
			}
		}
	}
	else if (Game::locals[localId].localType == -1) //命運
	{
	vector<string> Board;
	Game::setTextStyle(WHITE, BLACK);
	Board = {
		" _________________ " ,
	"|                 |" ,
	"|    你走到了     |" ,
	"|                 |" ,
	"|  ＜  命運  ＞   |" ,
	"|＿＿＿＿＿＿＿＿_|"
	};
	for (int i = 0; i < Board.size(); i++)
	{
		Game::setCursorXY(50, 16 + i);
		cout << Board[i];
	}
	Sleep(1000);
		srand(time(NULL));
		int r = rand() % Game::fortunes.size();
		vector<string> FortuneBoard;
		FortuneBoard = {
		" ____________________________________________" ,
	"|                                            |" ,
	"|                                            |" ,
	"|                                            |" ,
	"|＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿|"
		};
		for (int i = 0; i < FortuneBoard.size(); i++)
		{
			Game::setCursorXY(38, 22 + i);
			cout << FortuneBoard[i];
		}
		Sleep(1000);
		Game::setTextStyle(GOLD, BLACK);
		Game::setCursorXY(40, 24);
		cout << Game::fortunes[r]->name;
		Sleep(5000);
		Game::fortunes[r]->method(Game::players[Game::playerState]);

		Game::allShowOnTheMap();
		Game::diceNumber = 0;
		if(localId != Game::players[Game::playerState].position)
			Game::moveCharacter();
	}
	else if (Game::locals[localId].localType == -2) //機會	
	{
	vector<string> Board;
	Game::setTextStyle(WHITE, BLACK);
	Board = {
		" _________________ " ,
	"|                 |" ,
	"|    你走到了     |" ,
	"|                 |" ,
	"|  ＜  機會  ＞   |" ,
	"|＿＿＿＿＿＿＿＿_|"
	};
	for (int i = 0; i < Board.size(); i++)
	{
		Game::setCursorXY(50, 16 + i);
		cout << Board[i];
	}
		srand(time(NULL));
		int r = rand() % Game::chances.size();
		vector<string> ChanceBoard;
		ChanceBoard = {
		" ____________________________________________" ,
	"|                                            |" ,
	"|                                            |" ,
	"|                                            |" ,
	"|＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿|"
		};
		for (int i = 0; i < ChanceBoard.size(); i++)
		{
			Game::setCursorXY(38, 22 + i);
			cout << ChanceBoard[i];
		}
		Sleep(1000);
		Game::setTextStyle(GOLD, BLACK);
		Game::setCursorXY(40, 24);
		cout << Game::chances[r]->name;
		Sleep(5000);
		Game::chances[r]->method(Game::players[Game::playerState]);

		Game::allShowOnTheMap();
		Game::diceNumber = 0;
		if (localId != Game::players[Game::playerState].position)
			Game::moveCharacter();
	}
	else if (Game::locals[localId].localType == -4) //太空站
	{
	vector<string> Board;
	Game::setTextStyle(WHITE, BLACK);
	Board = {
		" _________________ " ,
	"|                 |" ,
	"|    你走到了     |" ,
	"|                 |" ,
	"|  ＜ 太空站 ＞   |" ,
	"|＿＿＿＿＿＿＿＿_|"
	};
	for (int i = 0; i < Board.size(); i++)
	{
		Game::setCursorXY(50, 16 + i);
		cout << Board[i];
	}
	}
	else if (Game::locals[localId].localType == -5) //黑洞
	{
	vector<string> Board;
	Game::setTextStyle(WHITE, BLACK);
	Board = {
		" _________________ " ,
	"|                 |" ,
	"|    你走到了     |" ,
	"|                 |" ,
	"|  ＜  黑洞  ＞   |" ,
	"|＿＿＿＿＿＿＿＿_|"
	};
	for (int i = 0; i < Board.size(); i++)
	{
		Game::setCursorXY(50, 16 + i);
		cout << Board[i];
	}
	}
}

void Game::changeplayerState()
{
	if (Game::playerState < Game::howManyPlayer - 1)
		Game::playerState += 1;
	else
		Game::playerState = 0;

	if (Game::players[Game::playerState].stop > 0)
		Game::changeplayerState();
}

void Game::changeRound()
{
	if (Game::tmpRound % Game::howManyPlayer == 0)
	{
		//new round
		for(int i = 0; i < Game::players.size(); i++)
			Game::players[i].finishARound();
		Game::round++;
		//Game::allShowOnTheMap();
		//Game::displayTemplate();
		//Game::displayMap();
	}
	Game::tmpRound++;
}

void Game::deleteBeforePlace()
{
	Game::processMarkPlayerPosition(Game::playerState, Game::players[playerState].position);
	cout << "＿";
}

void Game::showPlayerState()
{
	Game::setCursorXY(34,6);
	if (Game::playerState == 0)
	{
		Game::setTextStyle(RED, BLACK);
		cout << "１Ｐ";
	}
	else if (Game::playerState == 1)

	{
		Game::setTextStyle(GREEN, BLACK);
		cout << "２Ｐ";
	}
	else if (Game::playerState == 2)
	{
		Game::setTextStyle(BLUE, BLACK);
		cout << "３Ｐ";
	}
	else
	{
		Game::setTextStyle(KHIKI, BLACK);
		cout << "４Ｐ";
	}
}

void Game::showRound()
{
	Game::setTextStyle(CYAN, BLACK);
	Game::setCursorXY(91, 6);
	cout << Game::round;
	Game::setCursorXY(93, 6);
	cout << " / " << Game::howManyRound;
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
			l.priceOfLevel = price;
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
		int id;

		int type = -1;
		while (iss >> id)
		{
			if (id < 0)
			{
				type = id;
				continue;
			}

			if (type == -1)//local
			{
				p.property.localIds.push_back(id);
				int localPriceType;
				iss >> localPriceType;
				Game::locals[id].level = localPriceType;
			}
			else if (type == -2)//compony
				p.property.componyIds.push_back(id);
			else if (type == -3)//tool
				p.property.toolIds.push_back(id);
			else if (type == -4)//bank money
				p.property.bankMoney = id;
		}
		Game::players.push_back(p);
	}
	file.close();


	//TODO :testing
	//Game::locals[2].tool = new RoadblockTool();
}

void Game::resetCompanyStock()
{
	for (int i = 0; i < Game::companys.size(); i++)
		Game::companys[i].updateStockPrice();
}

void Game::menu()
{
	Game::setTextStyle(CYAN, BLACK);
	vector<string> option;
	option = { " ＿＿＿＿＿＿＿＿ " ,
	"|                |" ,
	"|    繼續遊戲    |",
	"|＿＿＿＿＿＿＿＿|",
	"|                |" ,
	"|    儲存遊戲    |" ,
	"|＿＿＿＿＿＿＿＿|" ,
	"|                |" ,
	"|    回主選單    |" ,
	"|＿＿＿＿＿＿＿＿|" ,
	"|                |",
	"|    離開遊戲    |" ,
	"|＿＿＿＿＿＿＿＿|" };

	Game::setTextStyle(GOLD, BLACK);
	for (int i = 0; i < 4; i++)
	{
		Game::setCursorXY(51, 15 + i);
		cout << option[i];
	}
	Game::setTextStyle(WHITE, BLACK);
	for (int i = 4; i < 13; i++)
	{
		Game::setCursorXY(51, 15 + i);
		cout << option[i] << endl;
	}
	Game::setCursorXY(59, 17);
	while (1)
	{
		char c = _getch();
		if (c == 13) //Enter
		{
			if (Game::cursorXY.Y == 17) //繼續遊戲
			{
				//Game::displayTemplate();
				Game::allShowOnTheMap();
				//Game::showDice();
				Game::InGame();
			}
			else if (Game::cursorXY.Y == 20) //儲存遊戲
			{
				vector<string> Board;
				Board = {
		" _________________ " ,
		"|                 |" ,
		"| 請輸入 存檔名稱 |" ,
		"|                 |" ,
		"|  \"           \"  |" ,
		"|   -----------   |" ,
		"|                 |" ,
		"|＿＿＿＿＿＿＿＿_|" ,
		"|                 |" ,
		"|  輸入完按Enter  |" ,
		"|＿＿＿＿＿＿＿＿_|" ,
				};
				Game::setTextStyle(WHITE, BLACK);
				for (int i = 0; i < 7; i++)
				{
					Game::setCursorXY(50, 16 + i);
					cout << Board[i];
				}
				Game::setTextStyle(GOLD, BLACK);
				for (int i = 7; i < Board.size(); i++)
				{
					Game::setCursorXY(50, 16 + i);
					cout << Board[i];
				}
				Game::saveGame();
			}
			else if (Game::cursorXY.Y == 23) //回主選單
			{
				Game::enterScreen();
			}
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
				Game::menuUp();
				Game::showMenuOption(option);
				break;
			case 80://下
				Game::menuDown();
				Game::showMenuOption(option);
				break;
			default:
				break;
			}
		}
	}
}

void Game::menuUp()
{
	if (Game::cursorXY.Y == 17)
	{
	}
	else
	{
		Game::cursorXY.Y -= 3;
	}
}

void Game::menuDown()
{
	if (Game::cursorXY.Y == 26)
	{
	}
	else
	{
		Game::cursorXY.Y += 3;
	}
}

void Game::showMenuOption(vector<string> option)
{
	int y = Game::cursorXY.Y;
	Game::setTextStyle(WHITE, BLACK);
	for (int i = 0; i < 13; i++)
	{
		Game::setCursorXY(51, 15 + i);
		cout << option[i] << endl;
	}
	Game::setTextStyle(GOLD, BLACK);

	for (int i = 0; i < 4; i++)
	{
		Game::setCursorXY(51, y - 2 + i);
		cout << option[y - 17 + i] << endl;
	}
	Game::setCursorXY(59, y);
}

void Game::showPlayerProperty()
{
	Game::setTextStyle(GOLD, BLACK);
	vector<string>board;
	board = {
		" ＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿",
		"｜　　　　　 　   　　　                            ｜",
		"｜　Player       　　 　   　　   　    Esc 關閉視窗｜",
		"｜　　　　　 　   　　　                            ｜",
		"｜　　         現金　     $　                       ｜",
		"｜　　　　　 　   　　　                            ｜",
		"｜　　         存款　     $　                       ｜",
		"｜　　　　　 　   　　　                            ｜",
		"｜　　         貸款　     $　                       ｜",
		"｜　　　　　 　   　　　                            ｜",
		"｜　　       總資產　     $　                       ｜",
		"｜＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿｜",
		"｜　　　　　 　   　　　                            ｜",
		"｜　道具　　　　 　   　　　                        ｜",
		"｜　　　　　 　   　　　                            ｜",
		"｜　    路障 x　　　 　   　 炸彈 x                 ｜",
		"｜　　　　　 　   　　　                            ｜",
		"｜　    黑洞傳送器 x　　     過路費加倍券 x　       ｜",
		"｜　　　　　 　   　　　                            ｜",
		"｜　股票　　　　 　   　　　                        ｜",
		"｜　　　　　 　   　　　                            ｜",
		"｜　    A股 x　   B股 x       C股 x       D股 x     ｜",
		"｜＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿｜"
	};
	for (int i = 0; i < board.size(); i++)
	{
		Game::setCursorXY(32, 12 + i);
		cout << board[i] << endl;
	}
	Game::setCursorXY(45, 14);
	if (Game::playerState == 0)
	{
		Game::setTextStyle(RED, BLACK);
		cout << "１Ｐ";
	}
	else if (Game::playerState == 1)

	{
		Game::setTextStyle(GREEN, BLACK);
		cout << "２Ｐ";
	}
	else if (Game::playerState == 2)
	{
		Game::setTextStyle(BLUE, BLACK);
		cout << "３Ｐ";
	}
	else
	{
		Game::setTextStyle(KHIKI, BLACK);
		cout << "４Ｐ";
	}
	Game::setCursorXY(62, 16);
	cout << Game::players[Game::playerState].property.money;
	Game::setCursorXY(62, 18);
	cout << Game::players[Game::playerState].property.bankMoney;
	Game::setCursorXY(62, 20);
	//貸款
	Game::setCursorXY(62, 22);
	cout << Game::players[Game::playerState].property.getAllProperty();

	Game::setCursorXY(48, 27);
	cout << Game::players[Game::playerState].property.getHowManyTool(1);

	Game::setCursorXY(68, 27);
	cout << Game::players[Game::playerState].property.getHowManyTool(2);

	Game::setCursorXY(54, 29);
	cout << Game::players[Game::playerState].property.getHowManyTool(3);

	Game::setCursorXY(76, 29);
	cout << Game::players[Game::playerState].property.getHowManyTool(4);

	for (int i = 0, x = 46; i < 4; i++)
	{
		Game::setCursorXY(47 + i * 11, 33);
		cout << count(
			Game::players[Game::playerState].property.componyIds.begin(),
			Game::players[Game::playerState].property.componyIds.end(),
			i + 1);
	}


	Game::setCursorXY(77, 14);

	while (1)
	{
		char c = _getch();
		if (c == 27) //Esc
		{
			//Game::displayTemplate();
			Game::allShowOnTheMap();
			//Game::showDice();
			//Game::InGame();
			return;
		}
		else
		{
			continue;
		}
	}
}

void Game::buyLocal()
{
	Game::markPlayerAndLocalPosition(Game::players);
	vector<string>Board;
	Board = {
" _________________ " ,
"|                 |" ,
"|    你走到了     |" ,
"|                 |" ,
"| ＜     　   ＞  |" ,
"|                 |" ,
"|                 |" ,
"|    要購買嗎     |" ,
"|＿＿＿＿＿＿＿＿_|" ,
	"|        |        |",
	"|   是   |   否   |" ,
	"|＿＿＿＿|＿＿＿＿|"
	};

	vector<string> Yes;
	Yes = {
	"|＿＿＿＿",
	"|        |",
	"|   是   |",
	"|＿＿＿＿|"
	};
	vector<string> No;
	No = {
"＿＿＿＿_|",
 "|        |",
 "|   否   |" ,
"|＿＿＿＿|"
	};
	Game::setTextStyle(WHITE, BLACK);
	for (int i = 0; i < Board.size(); i++)
	{
		Game::setCursorXY(50, 16 + i);
		cout << Board[i];
	}
	int localId = Game::players[playerState].position;
	if (Game::locals[localId].name.size() < 8)
	{
		Game::setCursorXY(57, 20);
		cout << Game::locals[localId].name;
	}
	else
	{
		Game::setCursorXY(56, 20);
		cout << Game::locals[localId].name;
	}
	Game::setCursorXY(56, 22);
	cout << "＄" <<Game::locals[localId].getNowPriceOfLevel();
	Game::setTextStyle(GOLD, BLACK);
	for (int i = 0; i < Yes.size(); i++)
	{
		Game::setCursorXY(50, 24 + i);
		cout << Yes[i];
	}
	Game::setTextStyle(WHITE, BLACK);
	Game::setCursorXY(54, 26);
	while (1)
	{
		char c = _getch();
		if (c == 13) //Enter
		{
			if (Game::cursorXY.X == 54) //Yes
			{
				Game::players[playerState].property.localIds.push_back(localId);
				Game::players[playerState].property.money -= locals[localId].getNowPriceOfLevel();
				Game::locals[localId].level++;
				Game::allShowOnTheMap();
				//Game::displayTemplate();
				//Game::showDice();
				//Game::InGame();
				return;
			}
			else//No
			{
				Game::changeplayerState();
				Game::allShowOnTheMap();
				//Game::displayTemplate();
				//Game::showDice();
				//Game::InGame();
				return;
			}
		}
		else
		{
			switch (c)
			{
			case 75://左
				Game::choiceLeft();
				Game::showChoice(Yes,No);
				break;
			case 77://右
				Game::choiceRight();
				Game::showChoice(Yes,No);
				break;
			default:
				break;
			}
		}
	}
}

void Game::getFee()
{
	if (Game::locals[Game::players[playerState].position].getNowPriceOfLevel() > Game::players[playerState].property.money)
	{
		return;
	}
	else
	{
		Game::players[playerState].property.money -= Game::locals[Game::players[playerState].position].getNowPriceOfLevel();
		for (int i = 0; i < Game::players.size(); i++)
		{
			if (Game::players[i].property.isMyLocal(Game::players[playerState].position))
				Game::players[i].property.money += Game::locals[Game::players[playerState].position].getNowPriceOfLevel();
		}
	}
}

void Game::upgrate()
{
	if (Game::locals[Game::players[Game::playerState].position].level < 5)
		Game::locals[Game::players[Game::playerState].position].level++;
}

void Game::useToolYesOrNo()
{
	vector<string> Board;
	Board = {
" _________________ " ,
"|                 |" ,
"|    現在位置     |" ,
"|                 |" ,
"| ＜     　   ＞  |" ,
"|                 |" ,
"|                 |" ,
"|  要使用道具嗎   |" ,
"|＿＿＿＿＿＿＿＿_|" ,
	"|        |        |",
	"|   是   |   否   |" ,
	"|＿＿＿＿|＿＿＿＿|"
	};
	vector<string> Yes;
	Yes = {
	"|＿＿＿＿",
	"|        |",
	"|   是   |",
	"|＿＿＿＿|"
	};
	vector<string> No;
	No = {
"＿＿＿＿_|",
 "|        |",
 "|   否   |" ,
"|＿＿＿＿|"
	};
	Game::setTextStyle(WHITE, BLACK);
	for (int i = 0; i < Board.size(); i++)
	{
		Game::setCursorXY(50, 16 + i);
		cout << Board[i];
	}
	int localId = Game::players[playerState].position;
	if (Game::locals[localId].name.size() < 8)
	{
		Game::setCursorXY(57, 20);
		cout << Game::locals[localId].name;
	}
	else
	{
		Game::setCursorXY(56, 20);
		cout << Game::locals[localId].name;
	}
	Game::setTextStyle(GOLD, BLACK);
	for (int i = 0; i < No.size(); i++)
	{
		Game::setCursorXY(59, 24 + i);
		cout << No[i];
	}
	Game::setTextStyle(WHITE, BLACK);
	Game::setCursorXY(63, 26);
	while (1)
	{
		char c = _getch();
		if (c == 13) //Enter
		{
			if (Game::cursorXY.X == 54) //Yes
			{
				Game::useTool();
			}
			else//No
			{
				Game::allShowOnTheMap();
				return;
			}
		}
		else
		{
			switch (c)
			{
			case 75://左
				Game::choiceLeft();
				Game::showChoice(Yes, No);
				break;
			case 77://右
				Game::choiceRight();
				Game::showChoice(Yes, No);
				break;
			default:
				break;
			}
		}
	}
}

void Game::useTool()
{
	//TODO:
}

void Game::buyTool(int toolId)
{
	if (Game::tools[toolId]->price > Game::players[Game::playerState].property.money)
	{
		//TODO (Layout):沒有錢了
	}
	else
	{
		Game::players[Game::playerState].property.money -= Game::tools[toolId]->price;
		Game::players[Game::playerState].property.toolIds.push_back(toolId);
	}
}

void Game::choiceLeft()
{
	if (Game::cursorXY.X == 54)
	{
	}
	else
	{
		Game::cursorXY.X -= 9;
	}
}

void Game::choiceRight()
{
	if (Game::cursorXY.X == 63)
	{
	}
	else
	{
		Game::cursorXY.X += 9;
	}
}

void Game::showChoice( vector<string> Yes, vector<string> No)
{
	int x = Game::cursorXY.X;
	if (x == 54)
	{
		Game::setTextStyle(GOLD, BLACK);
		for (int i = 0; i < Yes.size(); i++)
		{
			Game::setCursorXY(50, 24 + i);
			cout << Yes[i];
		}
		Game::setTextStyle(WHITE, BLACK);
		for (int i = 0; i < No.size(); i++)
		{
			Game::setCursorXY(59, 24 + i);
			cout << No[i];
		}
		Game::setCursorXY(x, 26);
	}
	else
	{
		Game::setTextStyle(GOLD, BLACK);
		for (int i = 0; i < No.size(); i++)
		{
			Game::setCursorXY(59, 24 + i);
			cout << No[i];
		}
		Game::setTextStyle(WHITE, BLACK);
		for (int i = 0; i < Yes.size(); i++)
		{
			Game::setCursorXY(50, 24 + i);
			cout << Yes[i];
		}
	}
	Game::setCursorXY(x, 26);
}

void Game::allShowOnTheMap()
{
	Game::displayTemplate();
	Game::markPlayerAndLocalPosition(Game::players);
	Game::showPlayerState();
	Game::showRound();
	Game::displayMap();
	Game::showDice();
	vector<string>Board;
	Board = {
" __________ " ,
"|          |" ,
"|   銀行   |" ,
"|__________|",
	"",
	"請按 Backspace",
	"",
" __________ " ,
"|          |" ,
"| 玩家資訊 |" ,
"|__________|",
	"",
	"  請按 Tab  ",
	"",
	" __________ " ,
"|          |" ,
"|   選單   |" ,
"|__________|",
	"",
	"  請按 Esc  ",
	"",
" __________ " ,
"|          |" ,
"|  擲骰子  |" ,
"|__________|",
	"",
	" 請按 Enter  " };
	for (int i = 0; i < Board.size(); i++)
	{
		Game::setTextStyle(GOLD, BLACK);
		Game::setCursorXY(104, 1 + i);
		cout << Board[i] << endl;
	}
}

void Game::saveGame()
{
	string name = "Basemap\\";
	string inputFileName;
	Game::setTextStyle(WHITE, BLACK);
	Game::setCursorXY(55, 20);
	cin >> inputFileName;
	name += inputFileName;
	name += ".txt";

	ifstream file("Basemap\\initial.txt", ios::binary);
	ofstream savefile(name, ios::binary);
	savefile << Game::mapName << " ";
	savefile << Game::howManyRound << " ";
	savefile << Game::howManyPlayer << "\r\n";
	string buffer;
	int i = 0;
	while (getline(file,buffer))
	{
		if (i != 0)
		{
			savefile << buffer << "\r\n";
		}
		i++;
	}
	file.close();
	
	savefile << "playerstate " << Game::playerState << "\r\n";

	for (int i = 0; i < Game::howManyPlayer; i++)
	{
		savefile << i << " " << Game::players[i].position << " " << Game::players[i].property.money << " -1 ";
		for (int j = 0; j < Game::players[i].property.localIds.size(); j++)
		{
			savefile << Game::players[i].property.localIds[j] << " " << Game::locals[players[i].property.localIds[j]].level << " ";
		}
		savefile << "-2 ";
		for (int k = 0 ; k < Game::players[i].property.componyIds.size() ; k++)
		{
			savefile << Game::players[i].property.componyIds[k] << " ";
		}
		savefile << "-3 ";
		for (int l = 0; l < Game::players[i].property.toolIds.size() ; l++)
		{
			savefile << Game::players[i].property.toolIds[l] << " ";
		}
		savefile << "-4 " << Game::players[i].property.bankMoney << "\r\n";
	}
	savefile.close();

	vector<string> Board;
	Game::setTextStyle(GOLD, BLACK);
	Board = {
	"|＿＿＿＿＿＿＿＿_|" ,
		"|                 |" ,
		"|     儲存成功    |" ,
		"|＿＿＿＿＿＿＿＿_|" ,
	};
	for (int i = 0; i < Board.size(); i++)
	{
		Game::setCursorXY(50, 26 + i);
		cout << Board[i];
	}
	Sleep(3000);
	//Game::displayTemplate();
	Game::allShowOnTheMap();
	//Game::showDice();
	Game::InGame();
}

void Game::bankMenu()
{
	vector<string>Board;
	vector<string> option;
	option = { " ＿＿＿＿＿＿＿＿ " ,
	"|                |" ,
	"|      賣地      |",
	"|＿＿＿＿＿＿＿＿|",
	"|                |" ,
	"|    存款提款    |" ,
	"|＿＿＿＿＿＿＿＿|" ,
	"|                |" ,
	"|     賣股票     |" ,
	"|＿＿＿＿＿＿＿＿|" ,
	"|                |",
	"|    繼續遊戲    |" ,
	"|＿＿＿＿＿＿＿＿|" };

	Game::setTextStyle(GOLD, BLACK);
	for (int i = 0; i < 4; i++)
	{
		Game::setCursorXY(51, 15 + i);
		cout << option[i];
	}
	Game::setTextStyle(WHITE, BLACK);
	for (int i = 4; i < option.size(); i++)
	{
		Game::setCursorXY(51, 15 + i);
		cout << option[i] << endl;
	}
	Game::setCursorXY(59, 17);
	while (1)
	{
		char c = _getch();
		if (c == 13) //Enter
		{
			if (Game::cursorXY.Y == 17) //賣地
			{
				//TODO:顯示要選什麼地要賣 localId放選擇的
				int localId = 0;

				Game::players[Game::playerState].property.money += Game::locals[localId].priceOfLevel[0] / 2;
				for (int i = 0; i < Game::players[Game::playerState].property.localIds.size(); i++)
				{
					if (Game::players[Game::playerState].property.localIds[i] == localId)
					{
						Game::players[Game::playerState].property.localIds.erase(Game::players[Game::playerState].property.localIds.begin() + i);
						break;
					}
				}
			}
			else if (Game::cursorXY.Y == 20) //提款
			{
				//TODO:詢問要提多少 howmush放選擇的
				int howmush = 0;
				withdrawal(Game::players[Game::playerState].property, howmush);
			}
			else if (Game::cursorXY.Y == 23) //放道具
			{
				//TODO:詢問要放什麼道具 toolId放選擇的
				int toolId = 0;

				Game::locals[Game::players[Game::playerState].position].tool = Game::tools[toolId];

				for (int i = 0; i < Game::players[Game::playerState].property.toolIds.size(); i++)
				{
					if (Game::players[Game::playerState].property.toolIds[i] == toolId)
					{
						Game::players[Game::playerState].property.toolIds.erase(Game::players[Game::playerState].property.toolIds.begin() + i);
						break;
					}
				}
			}
			else if (Game::cursorXY.Y == 26) //賣股票
			{
				//TODO:詢問要賣哪個股票 stockId放選擇的
				int stockId = 0;
				
				Game::players[Game::playerState].property.money += Game::companys[stockId].stockPrice;
				for (int i = 0; i < Game::players[Game::playerState].property.componyIds.size(); i++)
				{
					if (Game::players[Game::playerState].property.componyIds[i] == stockId)
					{
						Game::players[Game::playerState].property.componyIds.erase(Game::players[Game::playerState].property.componyIds.begin() + i);
						break;
					}
				}
			}
			else //繼續遊戲
			{
				//TODO:
			}
		}
		else
		{
			switch (c)
			{
			case 72://上
				Game::menuUp();
				Game::showMenuOption(option);
				break;
			case 80://下
				Game::menuDown();
				Game::showMenuOption(option);
				break;
			default:
				break;
			}
		}
	}
}

void Game::sellLocal()
{
	
}

bool compareInterval(Player p1, Player p2)
{
	return (p1.property.getAllProperty() > p2.property.getAllProperty());
}

void Game::checkAlive()
{
	for (int i = 0; i < players.size(); i++)
		players[i].checkAlive();
}

void Game::checkWhoWin()
{
	if (Game::round > Game::howManyRound)
	{
		vector<Player> checkList = Game::players;
		sort(checkList.begin(), checkList.end(), compareInterval);
		Game::endOfGame(checkList[0]);
	}
	else
	{
		vector<Player> checkList;
		for (int i = 0; i < Game::players.size(); i++)
		{
			if (Game::players[i].alive)
				checkList.push_back(Game::players[i]);
		}

		if (checkList.size() == 1)
			Game::endOfGame(checkList[0]);
	}
}

void Game::endOfGame(Player winner)
{
	system("cls");
	cout << "P" << winner.Id+1 << " WIN" << endl;
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
			cout << "４Ｐ ";
			Game::setTextStyle(KHIKI, KHIKI);
			Game::setCursorXY(20 + i * 20, 2);
			cout << color;
		}
	}
	Game::setTextStyle(WHITE, BLACK);
	for (int i = 0; i < Game::howManyPlayer; i++)
	{
		Game::setCursorXY(23 + i * 20, 3);
		cout << "＄" << Game::players[i].property.money;
		if (Game::players[i].stop > 0)
			cout << " Stop *" << Game::players[i].stop;
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






/*======================================================================================================*/
/*===========================================Other Class function=======================================*/
int Property::getAllProperty()
{
	int property = Property::money + Property::bankMoney;
	for (int i = 0; i < Property::localIds.size(); i++)
		property += (Game::locals[Property::localIds[i]].priceOfLevel[0]);

	return property;
}

void ChangePropertyFortune::method(Player& player)
{
	srand(time(NULL));
	int whoId = rand() % Game::players.size();
	while(whoId == player.Id)
		whoId = rand() % Game::players.size();
	Property p = player.property;
	player.property = Game::players[whoId].property;
	Game::players[whoId].property = p;

	Game::setCursorXY(45, 25);
	cout << "你與P" << whoId + 1 << "交換了錢包" << endl;
	Sleep(5000);
}

void GetStockChance::method(Player& player)
{
	srand(time(NULL));
	int companysId = rand() % Game::companys.size();
	player.property.componyIds.push_back(companysId);
}