﻿#include "Game.h"

HANDLE Game::outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
COORD Game::cursorXY;

vector<Local> Game::locals;
vector<Player> Game::players;
vector<Chance*> Game::chances;
vector<Fortune*> Game::fortunes;
vector<Company> Game::companys;
vector<Tool*> Game::tools;
 

void Game::initialGame()
{
	srand(time(NULL));

	Game::players.clear();
	Game::chances.clear();
	Game::fortunes.clear();
	Game::companys.clear();
	Game::tools.clear();
	Game::locals.clear();

	Game::tools.push_back(new Tool());
	Game::tools.push_back(new RoadblockTool());
	Game::tools.push_back(new BombTool());
	Game::tools.push_back(new ToBlackHoleTool());
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
}

Game::Game()
{
	PlaySound("Music\\background_sound.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
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
	Game::initialGame();
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
				_tmp.property.toolIds.push_back(1);
				_tmp.property.toolIds.push_back(2);
				_tmp.property.toolIds.push_back(3);
				_tmp.property.toolIds.push_back(4);
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
	Game::initialGame();

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
	while (Game::isInGame)
	{
		if (Game::playerState == 0)
			Game::resetCompanyStock();

		Game::allShowOnTheMap();  //markPlayerAndLocalPosition() && showPlayerState() && showRound() && displayMap()
		Game::checkWhoWin();

		int toolCount = 0;
		for (int i = 1; i <= Game::tools.size(); i++)
			toolCount += Game::players[Game::playerState].property.getHowManyTool(i);
		if (Game::locals[Game::players[Game::playerState].position].localType == 1 &&
			Game::locals[Game::players[Game::playerState].position].toolId == 0 && toolCount != 0)
		{
			Game::useToolYesOrNo();
			Game::allShowOnTheMap();  //markPlayerAndLocalPosition() && showPlayerState() && showRound() && displayMap()
		}

		while (1)
		{
			Game::setCursorXY(109, 24);
			char c = ' ';
			
			if (!useSuperDice)
				c = _getch();
			if (c == 13 || useSuperDice) //Enter
			{
				if (useSuperDice)
					useSuperDice = false;
				else
				{
					Game::rollDice();
					Game::moveCharacter();
				}
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
			"| 結束回合 |" ,
			"|__________|",
				"",
				" 請按 Enter  " };
				for (int i = 0; i < Board.size(); i++)
				{
					Game::setTextStyle(GOLD, BLACK);
					Game::setCursorXY(104, 1 + i);
					cout << Board[i] << endl;
				}

				int compreset = 1;
				while (1)
				{
					if (compreset && Game::playerState == 0)
					{
						Game::resetCompanyStock();
						compreset = 0;
					}

					Game::setCursorXY(109, 24);
					char c = _getch();
					if (c == 13) //Enter
					{
						Game::changeplayerState();
						compreset = 1;
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
		if (Game::players[i].alive)
			cout << "✈";
		else
			cout << "☠";
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
	//srand(time(NULL));
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
	if (Game::players[playerState].inBlack)
	{
		if (Game::diceNumber < 5)
		{
			vector <string> Board;
			Board = {
				" _________________ " ,
			"|                 |" ,
			"|    你骰到了     |" ,
			"|                 |" ,
			"|     ＜  ＞      |" ,
			"|                 |" ,
			"|  還是逃不出去   |" ,
			"|                 |" ,
			"|＿＿＿＿＿＿＿＿_|"
			};
			Game::setTextStyle(WHITE, BLACK);
			for (int i = 0; i < Board.size(); i++)
			{
				Game::setCursorXY(50, 16 + i);
				cout << Board[i];
			}
			Game::setTextStyle(GOLD, BLACK);
			Game::setCursorXY(59, 20);
			cout << Game::diceNumber;
			Sleep(5000);
			return;
		}
		else
		{
			Game::players[playerState].inBlack = false;
			vector <string> Board;
			Board = {
				" _________________ " ,
			"|                 |" ,
			"|    你骰到了     |" ,
			"|                 |" ,
			"|     ＜  ＞      |" ,
			"|                 |" ,
			"|   成功逃出 !!   |" ,
			"|                 |" ,
			"|＿＿＿＿＿＿＿＿_|"
			};
			Game::setTextStyle(WHITE, BLACK);
			for (int i = 0; i < Board.size(); i++)
			{
				Game::setCursorXY(50, 16 + i);
				cout << Board[i];
			}
			Game::setTextStyle(GOLD, BLACK);
			Game::setCursorXY(59, 20);
			cout << Game::diceNumber;
			Sleep(5000);
			Game::moveCharacter();
			return;
		}
	}


	Game::deleteBeforePlace();
	Game::players[playerState].goPosition(diceNumber);
	Game::changeRound();
	int localId = Game::players[playerState].position;
	Game::allShowOnTheMap();

	if (Game::locals[localId].toolId != 0)
	{
		vector <string> toolBoard;
		toolBoard = {
			" _________________ " ,
		"|                 |" ,
		"|    你踩到了     |" ,
		"|                 |" ,
		"| ＜          ＞  |" ,
		"|                 |" ,
		"|                 |" ,
		"|                 |" ,
		"|＿＿＿＿＿＿＿＿_|"
		};

		int toolID = Game::locals[localId].toolId;

		Game::setTextStyle(WHITE, BLACK);
		for (int i = 0; i < toolBoard.size(); i++)
		{
			Game::setCursorXY(50, 16 + i);
			cout << toolBoard[i];
		}

		Game::setTextStyle(GOLD, BLACK);
		if (tools[toolID]->name.size() > 8)
		{
			Game::setCursorXY(54, 20);
		}
		else
		{
			Game::setCursorXY(57, 20);
		}
		cout << tools[toolID]->name;

		Game::setCursorXY(54, 22);
		Game::tools[Game::locals[localId].toolId]->method(Game::players[playerState]);

		Sleep(3000);

		Game::locals[localId].setToDefaultTool();

		if (localId != Game::players[playerState].position)
		{
			if (toolID == 3 || toolID == 2)
				diceNumber = 0;
			Game::moveCharacter();
			return;
		}
	}

	localId = Game::players[playerState].position;

	if (Game::locals[localId].localType == 1)
	{
		if (Game::locals[localId].level == 0)
		{
			if (Game::players[playerState].property.money >= locals[localId].getNowPriceOfLevel())
			{
				Game::buyLocal();
				return;
			}
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
				Game::setTextStyle(WHITE, BLACK);
				for (int i = 0; i < 8; i++)
				{
					Game::setCursorXY(50, 16 + i);
					cout << Board[i];
				}
				if (Game::locals[localId].name.size() > 10) //四個字
					Game::setCursorXY(55, 20);
				else if (Game::locals[localId].name.size() > 8) //三個字
					Game::setCursorXY(56, 20);
				else
					Game::setCursorXY(57, 20);
				cout << Game::locals[localId].name;
				Game::setTextStyle(GOLD, BLACK);
				for (int i = 8; i < Board.size(); i++)
				{
					Game::setCursorXY(50, 16 + i);
					cout << Board[i];
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

				if (Game::locals[localId].name.size() > 10) //四個字
					Game::setCursorXY(55, 20);
				else if (Game::locals[localId].name.size() > 8) //三個字
					Game::setCursorXY(56, 20);
				else
					Game::setCursorXY(57, 20);

				cout << Game::locals[localId].name;
				Game::setTextStyle(GOLD, BLACK);
				Game::setCursorXY(56, 24);
				cout << "＄" << Game::locals[localId].getNowPriceOfLevel();
				Sleep(3000);
				Game::getFee();
			}
			else
			{
				vector<string> UpgradeBoard;
				UpgradeBoard = {
				" _________________ " ,
				"|                 |" ,
				"|你走到了 自己的地|" ,
				"|                 |" ,
				"| ＜     　   ＞  |" ,
				"|                 |" ,
				"|  房產等級提升 ！|" ,
				"|                 |" ,
				"|                 |" ,
				"|＿＿＿＿＿＿＿＿_|"
				};
				Game::setTextStyle(WHITE, BLACK);
				for (int i = 0; i < UpgradeBoard.size(); i++)
				{
					Game::setCursorXY(50, 16 + i);
					cout << UpgradeBoard[i];
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
				int nowLevel = Game::locals[Game::players[Game::playerState].position].level;
				if (nowLevel < 5)
				{
					Game::setTextStyle(GOLD, BLACK);
					Game::setCursorXY(56, 24);
					cout << nowLevel << " → " << nowLevel + 1;
				}
				Game::upgrate();
				Sleep(5000);
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
		//srand(time(NULL));
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
		Sleep(1000);
		//srand(time(NULL));
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
		Game::setCursorXY(42, 24);
		cout << Game::chances[r]->name;
		Sleep(5000);
		Game::setCursorXY(54, 25);
		Game::setTextStyle(CYAN, BLACK);
		Game::chances[r]->method(Game::players[Game::playerState]);
		if (r == 0)
		{
			Game::setCursorXY(47, 25);
			cout << "得到了 ";
			Game::setCursorXY(56, 25);
			cout << "公司的一張股票 ！";
			Sleep(5000);
		}
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
			" ___________________________ " ,
		"|                           |" ,
		"|         你走到了          |" ,
		"|                           |" ,
		"|       ＜ 太空站 ＞        |" ,
		"|                           |" ,
		"|      可以 存款、貸款      |" ,
		"|                           |" ,
		"|       買股票、買道具      |" ,
		"|                           |" ,
		"|＿＿＿＿＿＿＿＿＿＿＿＿＿_|"
		};
		Game::setTextStyle(GOLD, BLACK);
		for (int i = 0; i < Board.size(); i++)
		{
			Game::setCursorXY(45, 16 + i);
			cout << Board[i];
		}
		Sleep(5000);
		Game::spaceStation();
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
		vector<string> BlackHoleBoard;
		BlackHoleBoard = {
		" ____________________________________________" ,
	"|                                            |" ,
	"|                                            |" ,
	"|                                            |" ,
	"|                                            |" ,
	"|＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿|"
		};
		for (int i = 0; i < Board.size(); i++)
		{
			Game::setCursorXY(50, 16 + i);
			cout << Board[i];
		}
		for (int i = 0; i < BlackHoleBoard.size(); i++)
		{
			Game::setCursorXY(38, 22 + i);
			cout << BlackHoleBoard[i];
		}
		Game::setTextStyle(GOLD, BLACK);
		Game::setCursorXY(48, 24);
		cout << "被神秘的力量吸到白洞";
		Game::setCursorXY(44, 25);
		cout << "下一回合需要骰到五、六點才能出來",
		Game::blackHole();
	}
}

void Game::changeplayerState()
{
	Game::players[Game::playerState].checkAlive();
	if (Game::playerState < Game::howManyPlayer - 1)
		Game::playerState += 1;
	else
		Game::playerState = 0;

	if (Game::players[Game::playerState].stop > 0 || !Game::players[Game::playerState].alive)
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
	ofstream fileout("Basemap\\initial2.txt");
	string str;

	//process game information
	file >> Game::mapName;
	file >> Game::howManyRound;
	file >> Game::howManyPlayer;
	
	fileout << Game::mapName << " ";
	fileout << Game::howManyRound << " ";
	fileout << Game::howManyPlayer << "　";
	
	//process local information
	for (int i = 0; i <= 27; i++)
	{
		fileout << "\n";
		Local l;
		file >> l.Id;
		file >> l.name;
		file >> l.localType;
	
		fileout << l.Id << " ";
		fileout << l.name << " ";
		fileout << l.localType << " ";
		
		if (l.localType == 1)
		{
			vector<int> price;
			for (int j = 0; j < 5; j++)
			{
				int p = 0;
				file >> p;
				fileout << p << " ";
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
			else if (type == -5)//load
			{
				p.property.loan = id;
				iss >> p.property.loanCount;
			}
		}
		Game::players.push_back(p);
	}
	file.close();


	//TODO :testing
	//Game::locals[2].tool = new RoadblockTool();
}

void Game::resetCompanyStock()
{
	int price;
	for (int i = 0; i < Game::companys.size(); i++)
	{
		price = Game::companys[i].updateStockPrice();
	}
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
				return;
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
		"｜　　    現金　   $  　                            ｜",
		"｜　　　　　 　   　　　                            ｜",
		"｜　　    存款　   $　                              ｜",
		"｜　　　　　 　   　　　                            ｜",
		"｜　　    貸款　   $　                              ｜",
		"｜　　　　　 　   　　　                            ｜",
		"｜　　  總資產　   $                　              ｜",
		"｜＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿｜",
		"｜　　　　　 　   　　　                            ｜",
		"｜　道具　　　　 　   　　　                        ｜",
		"｜　　　　　 　   　　　                            ｜",
		"｜　  ⚐    路障 x　　　     ☢    炸彈 x            ｜",
		"｜　　　　　 　   　　　                            ｜",
		"｜　 ♨    黑洞傳送器 x　　 ㊙    遙控骰子 x　      ｜",
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
	Game::setCursorXY(58, 16);
	cout << Game::players[Game::playerState].property.money;
	Game::setCursorXY(58, 18);
	cout << Game::players[Game::playerState].property.bankMoney;
	Game::setCursorXY(58, 20);
	cout << Game::players[Game::playerState].property.loan;

	if (Game::players[Game::playerState].property.loanCount > 0)
	{
		cout << " (還款期限剩餘" << Game::players[Game::playerState].property.loanCount << "回合)";
	}

	Game::setCursorXY(58, 22);
	cout << Game::players[Game::playerState].property.getAllProperty();

	Game::setCursorXY(50, 27);
	cout << Game::players[Game::playerState].property.getHowManyTool(1);

	Game::setCursorXY(73, 27);
	cout << Game::players[Game::playerState].property.getHowManyTool(2);

	Game::setCursorXY(56, 29);
	cout << Game::players[Game::playerState].property.getHowManyTool(3);

	Game::setCursorXY(77, 29);
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
				//Game::changeplayerState();
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
	Game::players[playerState].property.money -= Game::locals[Game::players[playerState].position].getNowPriceOfLevel();
	for (int i = 0; i < Game::players.size(); i++)
	{
		if (Game::players[i].property.isMyLocal(Game::players[playerState].position))
			Game::players[i].property.money += Game::locals[Game::players[playerState].position].getNowPriceOfLevel();
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
"|＿＿＿＿＿＿＿＿|" ,
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
				return;
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
	int toolId = 0;
	Game::allShowOnTheMap();
	vector <string> Board;
	Board = { 
	"|                |" ,
	"|使用道具成功！！|" ,
	"|＿＿＿＿＿＿＿＿|" };
	vector<string> option;
	option = { " ＿＿＿＿＿＿＿＿ " ,
	"|                |" ,
	"|    路障 x ",
	"|＿＿＿＿＿＿＿＿|",
	"|                |" ,
	"|    炸彈 x " ,
	"|＿＿＿＿＿＿＿＿|" ,
	"|                |" ,
	"| 黑洞傳送器 x " ,
	"|＿＿＿＿＿＿＿＿|" ,
	"|                |",
	"|  遙控骰子 x " ,
	"|＿＿＿＿＿＿＿＿|" };
	std::string s1 = std::to_string(Game::players[Game::playerState].property.getHowManyTool(1));
	s1 += "    |";
	std::string s2 = std::to_string(Game::players[Game::playerState].property.getHowManyTool(2));
	s2 += "    |";
	std::string s3 = std::to_string(Game::players[Game::playerState].property.getHowManyTool(3));
	s3+= " |";
	std::string s4 = std::to_string(Game::players[Game::playerState].property.getHowManyTool(4));
	s4+= "  |";
	option[2] += s1;
	option[5] += s2;
	option[8] += s3;
	option[11] += s4;
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
			if (Game::cursorXY.Y == 17) //路障
			{
				toolId = 1;
			}
			else if (Game::cursorXY.Y == 20) //炸彈
			{
				toolId = 2;
			}
			else if (Game::cursorXY.Y == 23) //黑洞傳送器
			{
				toolId = 3;
			}
			else if (Game::cursorXY.Y == 26)//遙控骰子
			{
				toolId = 4;
			}

			if (Game::players[Game::playerState].property.getHowManyTool(toolId) != 0)
			{
				for (int i = 0; i < Game::players[Game::playerState].property.toolIds.size(); i++)
				{
					if (Game::players[Game::playerState].property.toolIds[i] == toolId)
					{
						Game::players[Game::playerState].property.toolIds.erase(
							Game::players[Game::playerState].property.toolIds.begin() + i);
						break;
					}
				}
				if (toolId != 4 && toolId >= 1)
					Game::locals[Game::players[Game::playerState].position].toolId = toolId;
				else
				{
					Game::allShowOnTheMap();
					vector<string> Board;
					Game::setTextStyle(WHITE, BLACK);
					Board = {
						" ________________ " ,
						"|                |" ,
						"| 請問你要走幾步 |" ,
						"|________________|" ,
						"|                |" ,
						"|  ＜  　　　＞  |" ,
						"|________________|"
					};
					for (int i = 0; i < Board.size(); i++)
					{
						Game::setCursorXY(50, 16 + i);
						cout << Board[i];
					}

					int select = 1;
					Game::setTextStyle(GOLD, BLACK);
					Game::setCursorXY(59, 21);
					cout << select;

					while (1)
					{
						char c = _getch();
						if (c == 13) //Enter
						{
							break;
						}
						else if (c == 27) //esc
						{
							select = -1;
							break;
						}
						else
						{
							switch (c)
							{
							case 75: //左

								if (select - 1 > 0)
								{
									Game::setTextStyle(GOLD, BLACK);
									Game::setCursorXY(59, 21);
									cout << --select;
								}
								break;
							case 77: //右
								if (select + 1 <= 6)
								{
									Game::setTextStyle(GOLD, BLACK);
									Game::setCursorXY(59, 21);
									cout << ++select;
								}
								break;
							default:
								break;
							}
						}
					}

					if (select > 0)
					{
						Game::diceNumber = select;
						Game::moveCharacter();
						useSuperDice = true;
					}
				}
			}
			else
				Game::useTool();
			break;
		}
		else if (c == 27) //esc
		{
			Game::allShowOnTheMap();
			return;
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

void Game::buyTool(int toolId)
{
	vector<string> Board;
	Game::setTextStyle(WHITE, BLACK);
	Board = {
		" ________________ " ,
		"|                |" ,
		"| 請問你要買幾個 |" ,
		"|________________|" ,
		"|                |" ,
		"|  每個 $        |" ,
		"|                |" ,
		"|  ＜  　　　＞  |" ,
		"|                |" ,
		"|擁有金錢 $      |" ,
		"|                |" ,
		"|                |" ,
		"|________________|"
	};
	for (int i = 0; i < Board.size(); i++)
	{
		Game::setCursorXY(51, 15 + i);
		cout << Board[i];
	}

	Game::setCursorXY(62, 20);
	cout << Game::tools[toolId]->price;
	Game::setCursorXY(63, 24);
	cout << Game::players[Game::playerState].property.money;

	int select = 1;
	Game::setTextStyle(GOLD, BLACK);
	Game::setCursorXY(59, 22);
	cout << select;

	while (1)
	{
		char c = _getch();
		if (c == 13) //Enter
		{
			Game::setTextStyle(GOLD, BLACK);
			Game::setCursorXY(55, 26);
			if (Game::tools[toolId]->price * select > Game::players[Game::playerState].property.money)
			{
				cout << "你的錢不夠 !";
				Sleep(3000);
				Game::whichToolWantBuy();
				return;
			}
			else
			{
				Game::players[Game::playerState].property.money -= Game::tools[toolId]->price * select;
				for (int i = 0; i < select; i++)
				{
					Game::players[Game::playerState].property.toolIds.push_back(toolId);
				}
				cout << "購買成功 !!";
				Sleep(3000);
				Game::allShowOnTheMap();
				Game::whichToolWantBuy();
				return;
			}
		}
		else if (c == 27) //esc
		{
			Game::whichToolWantBuy();
			return;
		}
		else
		{
			switch (c)
			{
			case 75: //左

				if (select - 1 > 0)
				{
					Game::setTextStyle(GOLD, BLACK);
					Game::setCursorXY(59, 22);
					cout << --select;
				}
				break;
			case 77: //右
				if (select + 1 <= 3)
				{
					Game::setTextStyle(GOLD, BLACK);
					Game::setCursorXY(59, 22);
					cout << ++select;
				}
				break;
			default:
				break;
			}
		}
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
	Game::showTool();
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

	ifstream file("Basemap\\initial2.txt", ios::binary);
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
			savefile << buffer;
		}
		i++;
	}
	file.close();
	
	savefile << "\r\n" << "playerstate " << Game::playerState << "\r\n";

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
		savefile << "-4 " << Game::players[i].property.bankMoney << " ";
		savefile << "-5 " << Game::players[i].property.loan << " " << Game::players[i].property.loanCount << "\r\n";
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
	return;
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
	"|      提款      |" ,
	"|＿＿＿＿＿＿＿＿|" ,
	"|                |" ,
	"|     賣股票     |" ,
	"|＿＿＿＿＿＿＿＿|" ,
	"|                |",
	"|      還款      |" ,
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
				vector<string> howManyPlayerBoard;
				if (Game::players[Game::playerState].property.localIds.size() != 0)
				{
					Game::allShowOnTheMap();
					vector<string> Board;
					Game::setTextStyle(WHITE, BLACK);
					Board = {
						" ________________ " ,
						"|                |" ,
						"| 選擇要賣的土地 |" ,
						"|________________|" ,
						"|                |" ,
						"|  ＜  　　　＞  |" ,
						"|________________|"
					};
					for (int i = 0; i < Board.size(); i++)
					{
						Game::setCursorXY(50, 16 + i);
						cout << Board[i];
					}

					int select = 0;
					Game::setTextStyle(GOLD, BLACK);
					Game::setCursorXY(56, 21);
					cout << Game::locals[Game::players[Game::playerState].property.localIds[select]].name;
						
					while (1)
					{
						char c = _getch();
						if (c == 13) //Enter
						{
							break;
						}
						else if (c == 27) //esc
						{
							select = -1;
							break;
						}
						else
						{
							switch (c)
							{
							case 75: //左
								
								if (select - 1 >= 0)
								{
									Game::setTextStyle(WHITE, BLACK);
									for (int i = 0; i < Board.size(); i++)
									{
										Game::setCursorXY(50, 16 + i);
										cout << Board[i];
									}
									Game::setTextStyle(GOLD, BLACK);
									Game::setCursorXY(56, 21);
									string s = Game::locals[Game::players[Game::playerState].property.localIds[--select]].name;
									cout << setprecision(3);
									cout << s;
								}
								break;
							case 77: //右
								if (select + 1 < Game::players[Game::playerState].property.localIds.size())
								{
									Game::setTextStyle(WHITE, BLACK);
									for (int i = 0; i < Board.size(); i++)
									{
										Game::setCursorXY(50, 16 + i);
										cout << Board[i];
									}
									Game::setTextStyle(GOLD, BLACK);
									Game::setCursorXY(56, 21);
									string s = Game::locals[Game::players[Game::playerState].property.localIds[++select]].name;
									cout << setprecision(3);
									cout << s;
								}
								break;
							default:
								break;
							}
						}
					}

					if (select >= 0)
					{
						int localId = Game::players[Game::playerState].property.localIds[select];

						Game::players[Game::playerState].property.money += Game::locals[localId].priceOfLevel[0] / 2;
						Game::locals[Game::players[Game::playerState].property.localIds[select]].level = 0;
						Game::players[Game::playerState].property.localIds.erase(Game::players[Game::playerState].property.localIds.begin() + select);
						
						allShowOnTheMap();
						return;
					}
					else
					{
						Game::bankMenu();
						return;
					}

				}
			}
			else if (Game::cursorXY.Y == 20) //提款
			{
				if (Game::players[Game::playerState].property.bankMoney > 0)
				{
					allShowOnTheMap();
					vector<string> Board;
					Board = {
					" _________________ " ,
					"|                 |" ,
					"| 請輸入 提多少錢 |" ,
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
					Game::setCursorXY(55, 20);
					int howmush = 0;
					cin >> howmush;

					if (howmush <= Game::players[Game::playerState].property.bankMoney)
					{
						withdrawal(Game::players[Game::playerState].property, howmush);
						Game::allShowOnTheMap();
						return;
					}
					else
					{
						allShowOnTheMap();
						vector<string> Board;
						Board = {
						" _________________ " ,
						"|                 |" ,
						"| 你沒有這麼多錢！ |" ,
						"|＿＿＿＿＿＿＿＿_|" ,
						};
						Game::setTextStyle(WHITE, BLACK);
						for (int i = 0; i < Board.size(); i++)
						{
							Game::setCursorXY(50, 16 + i);
							cout << Board[i];
						}
						Sleep(5000);
						Game::bankMenu();
						return;
					}
				}
			}
			else if (Game::cursorXY.Y == 23) //賣股票
			{

				int company_total = Game::players[Game::playerState].property.componyIds.size();

				if (company_total != 0)
				{
					int company_n = 0;
					int stockId = Game::players[Game::playerState].property.componyIds[company_n];

					vector<string> selectCompanyBoard;
					selectCompanyBoard = {
						" ________________ " ,
						"|                |" ,
						"|    選擇公司    |" ,
						"|________________|" ,
						"|                |" ,
						"| ＜    １    ＞ |" ,
						"|________________|" };

					for (int i = 0; i < selectCompanyBoard.size(); i++)
					{
						Game::setTextStyle(CYAN, BLACK);
						Game::setCursorXY(51, 21 + i);
						cout << selectCompanyBoard[i] << endl;
					}

					Game::setCursorXY(56, 26);
					cout << Company::getCompanyById(Game::companys, stockId).name;

					while (1)
					{
						Game::setCursorXY(56, 26);
						char c = _getch();
						if (c == 13)
						{
							break;
						}
						else
						{
							switch (c)
							{
							case 75: 
								company_n = company_n <= 0 ? 0 : company_n - 1;
								
								break;
							case 77:
								company_n = company_n >= (company_total - 1) ? (company_total - 1) : company_n + 1;

								break;
							default:
								break;
							}
						}

						Game::setCursorXY(56, 26);
						stockId = Game::players[Game::playerState].property.componyIds[company_n];
						cout << Company::getCompanyById(Game::companys, stockId).name;
					}

					Game::players[Game::playerState].property.money += Game::companys[stockId - 1].stockPrice;
					Game::players[Game::playerState].property.componyIds.erase(Game::players[Game::playerState].property.componyIds.begin() + stockId - 1);
					/*for (int i = 0; i < Game::players[Game::playerState].property.componyIds.size(); i++)
					{
						if (Game::players[Game::playerState].property.componyIds[i] == stockId)
						{
							Game::players[Game::playerState].property.componyIds.erase(Game::players[Game::playerState].property.componyIds.begin() + i);
							break;
						}
					}*/
				}
				else
				{
					Game::setCursorXY(55, 23);
					cout << "你沒有股票";
				}
				Game::allShowOnTheMap();
				return;
			}
			else //還款
			{
				Game::allShowOnTheMap();
				vector<string> Board;
				Game::setTextStyle(WHITE, BLACK);
				Board = {
					" _________________ " ,
					"|                 |" ,
					"|一件還清:        |" ,
					"|_________________|" ,
					"|                 |" ,
					"|    ＜Enter＞    |" ,
					"|_________________|"
				};
				Game::setTextStyle(GOLD, BLACK);
				for (int i = 0; i < Board.size(); i++)
				{
					Game::setCursorXY(50, 16 + i);
					cout << Board[i];
				}
				Game::setCursorXY(61, 18);
				Game::setTextStyle(BLUE, BLACK);
				cout << "$" << Game::players[Game::playerState].property.loan;
				Game::setCursorXY(55, 21);

				char ccc;
				while (1)
				{
					ccc = _getch();
					if (ccc == 13)
					{
						if (Game::players[Game::playerState].property.loan > Game::players[Game::playerState].property.money)
						{
							Game::setTextStyle(RED, BLACK);
							cout << "你的錢不夠";
						}
						else
						{
							Game::players[Game::playerState].property.money -= Game::players[Game::playerState].property.loan;
							Game::players[Game::playerState].property.loan = 0;
							Game::players[Game::playerState].property.loanCount = 0;
							Game::setTextStyle(GOLD, BLACK);
							cout << "還款成功";
						}
						Game::allShowOnTheMap();
						return;
					}
					else
						break;
				}
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
			case 27://Esc
				Game::allShowOnTheMap();
				return;
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

void Game::blackHole()
{
	Sleep(5000);
	Game::players[Game::playerState].position = 7;
	Game::players[Game::playerState].inBlack = true;
	Game::allShowOnTheMap();
}

void Game::showTool()
{
	Game::setTextStyle(CYAN, BLACK);
	for (int i = 0; i < 28; i++)
	{
		processMarkToolPosition(i);
		if (Game::locals[i].toolId == 1) //路障
		{
			cout << "⚐";
		}
		else if (Game::locals[i].toolId == 2) //炸彈
		{
			cout << "☢";
		}
		else if (Game::locals[i].toolId == 3) //黑洞傳送器
		{
			cout << "♨";
		}
		else
		{
		}
	}
}

void Game::processMarkToolPosition(int localId)
{
	if (localId >= 0 && localId <= 7)
	{
		Game::setCursorXY(26, 10 + 4 * localId);
	}
	else if (localId >= 8 && localId <= 14)
	{
		Game::setCursorXY(36 + 10 * (localId - 8), 38);
	}
	else if (localId >= 15 && localId <= 21)
	{
		Game::setCursorXY(96, 34 - 4 * (localId - 15));
	}
	else
	{
		Game::setCursorXY(86 - 10 * (localId - 22), 10);
	}
}

void Game::spaceStation()
{
	vector<string> option;
	option = { " ＿＿＿＿＿＿＿＿ " ,
	"|                |" ,
	"|      存款      |" ,
	"|＿＿＿＿＿＿＿＿|",
	"|                |" ,
	"|      貸款      |" ,
	"|＿＿＿＿＿＿＿＿|" ,
	"|                |" ,
	"|     買股票     |" ,
	"|＿＿＿＿＿＿＿＿|" ,
	"|                |",
	"|     買道具     |" ,
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
			if (Game::cursorXY.Y == 17) //存款
			{
				allShowOnTheMap();
				vector<string> Board;
				Board = {
				" _________________ " ,
				"|                 |" ,
				"| 請輸入 存多少錢 |" ,
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
				Game::setCursorXY(55, 20);
				int howmuch = 0;
				cin >> howmuch;

				if (howmuch <= Game::players[Game::playerState].property.money)
				{
					deposit(Game::players[Game::playerState].property, howmuch);
					vector<string> Board;
					Board = {
					"|＿＿＿＿＿＿＿＿_|" ,
					"|                 |" ,
					"|    存款成功！   |" ,
					"|＿＿＿＿＿＿＿＿_|" ,
					};
					Game::setTextStyle(GOLD, BLACK);
					for (int i = 0; i < Board.size(); i++)
					{
						Game::setCursorXY(50, 23 + i);
						cout << Board[i];
					}
				}
				else
				{
					vector<string> Board;
					Board = {
					"|＿＿＿＿＿＿＿＿_|" ,
					"|                 |" ,
					"| 你沒有這麼多錢！|" ,
					"|＿＿＿＿＿＿＿＿_|" ,
					};
					Game::setTextStyle(GOLD, BLACK);
					for (int i = 0; i < Board.size(); i++)
					{
						Game::setCursorXY(50, 23 + i);
						cout << Board[i];
					}
				}
				Game::setCursorXY(60, 25);
				Sleep(3000);
				Game::allShowOnTheMap();
				Game::spaceStation();
				return;
			}
			else if (Game::cursorXY.Y == 20) //貸款
			{
				allShowOnTheMap();
				vector<string> Board;
				Board = {
				" _________________ " ,
				"|                 |" ,
				"| 請輸入 貸多少錢 |" ,
				"|                 |" ,
				"|  \"           \"  |" ,
				"|   -----------   |" ,
				"|   上限:         |" ,
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
				Game::setCursorXY(59, 22);
				cout << Game::players[Game::playerState].property.getAllProperty();
				Game::setCursorXY(55, 20);
				int howmuch = 0;
				cin >> howmuch;

				if (howmuch <= Game::players[Game::playerState].property.getAllProperty() && 
					Game::players[Game::playerState].property.loanCount == 0)
				{
					loanMoney(Game::players[Game::playerState].property, howmuch);
					vector<string> Board;
					Board = {
					"|＿＿＿＿＿＿＿＿_|" ,
					"|                 |" ,
					"|    貸款成功！   |" ,
					"|＿＿＿＿＿＿＿＿_|" ,
					};
					Game::setTextStyle(GOLD, BLACK);
					for (int i = 0; i < Board.size(); i++)
					{
						Game::setCursorXY(50, 23 + i);
						cout << Board[i];
					}
				}
				else
				{
					vector<string> Board;
					Board = {
					"|＿＿＿＿＿＿＿＿_|" ,
					"|                 |" ,
					"|   貸款失敗！ |" ,
					"|＿＿＿＿＿＿＿＿_|" ,
					};
					Game::setTextStyle(GOLD, BLACK);
					for (int i = 0; i < Board.size(); i++)
					{
						Game::setCursorXY(50, 23 + i);
						cout << Board[i];
					}
				}
				Game::setCursorXY(60, 25);
				Sleep(3000);
				Game::allShowOnTheMap();
				Game::spaceStation();
				return;
			}
			else if (Game::cursorXY.Y == 23) //買股票
			{
				Game::whichStockWantBuy();
				return;
			}
			else if(Game::cursorXY.Y == 26) //買道具
			{
				Game::whichToolWantBuy();
				Game::spaceStation();
				return;
			}
		}
		else if (c == 27) //esc
		{
			Game::allShowOnTheMap();
			return;
		}
		else
		{
			switch (c)
			{
			case 72://上
				menuUp();
				showMenuOption(option);
				break;
			case 80://下
				menuDown();
				showMenuOption(option);
				break;
			default:
				break;
			}
		}
	}
}
void Game::whichStockWantBuy()
{
	int company_n = 0;

	vector<string> selectCompanyBoard;
	selectCompanyBoard = {
		"|＿＿＿＿＿＿＿＿|" ,
		"|                |" ,
		"|    選擇公司    |" ,
		"|________________|" ,
		"|                |" ,
		"| ＜          ＞ |" ,
		"|＿＿＿＿＿＿＿＿|" };

	Game::setTextStyle(GOLD, BLACK);
	for (int i = 0; i < selectCompanyBoard.size(); i++)
	{
		Game::setCursorXY(51, 18 + i);
		cout << selectCompanyBoard[i] << endl;
	}

	Game::setCursorXY(56, 23);
	cout << Game::companys[company_n].name;

	while (1)
	{
		Game::setCursorXY(56, 23);
		char c = _getch();
		if (c == 13)
		{
			Game::buyStock(company_n);
			break;
		}
		else
		{
			switch (c)
			{
			case 75:
				company_n = company_n <= 0 ? 0 : company_n - 1;

				break;
			case 77:
				company_n = company_n >= (Game::companys.size() - 1) ? (Game::companys.size() - 1) : company_n + 1;

				break;
			default:
				break;
			}
		}

		Game::setCursorXY(56, 23);
		cout << Game::companys[company_n].name;

	}
	Game::spaceStation();
	return;
}
void Game::buyStock(int company_n)
{
	vector<string> Board;
	Game::setTextStyle(WHITE, BLACK);
	Board = {
		" ________________ " ,
		"|                |" ,
		"| 請問你要買幾張 |" ,
		"|________________|" ,
		"|                |" ,
		"|  每張 $        |" ,
		"|                |" ,
		"|  ＜  　　　＞  |" ,
		"|                |" ,
		"|擁有存款 $      |" ,
		"|                |" ,
		"|                |" ,
		"|________________|"
	};
	for (int i = 0; i < Board.size(); i++)
	{
		Game::setCursorXY(51, 15 + i);
		cout << Board[i];
	}

	Game::setCursorXY(62, 20);
	cout << Game::companys[company_n].stockPrice;
	Game::setCursorXY(63, 24);
	cout << Game::players[Game::playerState].property.bankMoney;

	int select = 1;
	Game::setTextStyle(GOLD, BLACK);
	Game::setCursorXY(59, 22);
	cout << select;

	while (1)
	{
		char c = _getch();
		if (c == 13) //Enter
		{
			Game::setTextStyle(GOLD, BLACK);
			Game::setCursorXY(55, 26);
			if (Game::Game::companys[company_n].stockPrice * select > Game::players[Game::playerState].property.bankMoney)
			{
				cout << "你的錢不夠 !";
				Sleep(3000);
				Game::spaceStation();
				return;
			}
			else
			{
				Game::players[Game::playerState].property.bankMoney -= Game::companys[company_n].stockPrice * select;
				for (int i = 0; i < select; i++)
				{
					Game::players[Game::playerState].property.componyIds.push_back(company_n + 1);
				}
				cout << "購買成功 !!";
				Sleep(3000);
				Game::allShowOnTheMap();
				Game::spaceStation();
				return;
			}
		}
		else if (c == 27) //esc
		{
			Game::whichStockWantBuy();
			return;
		}
		else
		{
			switch (c)
			{
			case 75: //左

				if (select - 1 > 0)
				{
					Game::setTextStyle(GOLD, BLACK);
					Game::setCursorXY(59, 22);
					cout << --select;
				}
				break;
			case 77: //右
				if (select + 1 <= 9)
				{
					Game::setTextStyle(GOLD, BLACK);
					Game::setCursorXY(59, 22);
					cout << ++select;
				}
				break;
			default:
				break;
			}
		}
	}
}

void Game::whichToolWantBuy()
{
	vector<string> option;
	option = { " ＿＿＿＿＿＿＿＿ " ,
	"|                |" ,
	"|  ⚐  路障       |" ,
	"|＿＿＿＿＿＿＿＿|",
	"|                |" ,
	"| ☢  炸彈       |" ,
	"|＿＿＿＿＿＿＿＿|" ,
	"|                |" ,
	"| ♨  黑洞傳送器 |" ,
	"|＿＿＿＿＿＿＿＿|" ,
	"|                |",
	"| ㊙  遙控骰子   |" ,
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
			if (Game::cursorXY.Y == 17) //路障
			{
				Game::buyTool(1);
			}
			else if (Game::cursorXY.Y == 20) //炸彈
			{
				Game::buyTool(2);
			}
			else if (Game::cursorXY.Y == 23) //黑洞傳送器
			{
				Game::buyTool(3);
			}
			else //遙控骰子
			{
				Game::buyTool(4);
			}
		}
		else if (c == 27) //esc
		{
			//Game::spaceStation();
			return;
		}
		else
		{
			switch (c)
			{
			case 72://上
				menuUp();
				showMenuOption(option);
				break;
			case 80://下
				menuDown();
				showMenuOption(option);
				break;
			default:
				break;
			}
		}
	}
}

bool compareInterval(Player p1, Player p2)
{
	return (p1.property.getAllProperty() > p2.property.getAllProperty());
}

void Game::checkWhoWin()
{
	if (Game::round >= Game::howManyRound)
	{
		vector<Player> checkList = Game::players;
		sort(checkList.begin(), checkList.end(), compareInterval);
		Game::endOfGame(checkList[0]);
	}
	else
	{
		if (Game::howManyPlayer == 1)
			return;
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
}

void Game::endOfGame(Player winner)
{
	system("cls");

	Game::setTextStyle(KHIKI, BLACK);
	int max = 0, maxID;
	for (int i = 0; i < Game::howManyPlayer; i++)
	{
		Game::setCursorXY(40, 2 + i * 2);
		cout << "P " << i + 1 << "         結算總資產  :   $ " << Game::players[i].property.getAllProperty();
		if (Game::players[i].property.getAllProperty() > max)
		{
			max = Game::players[i].property.getAllProperty();
			maxID = i;
		}
	}
	Game::setCursorXY(77, 2 + maxID * 2);
	cout << "★";

	ifstream inputS("Image\\CHIKA.txt");
	string str;
	Game::setTextStyle(WHITE, BLACK);
	int i = 0;
	while (getline(inputS, str))
	{
		Game::setCursorXY(26, 20 + i);
		cout << str << endl;
		i++;
	}
	Game::setCursorXY(85, 35);
	cout << "恭喜你勝利 咚搭呦 ~";
	vector<string> p1;
	p1 = { "    ___      __        _    _        __        _  _   ",
	"   F _ \",   / J       F L  J J       FJ       F L L]  ",
	"  J `-' |   LFJ      J J .. L L     J  L     J   \\| L ",
	"  |  __/F   J  L     | |/  \\| |     |  |     | |\\   | ",
	"  F |__/    J  L     F   /\\   J     F  J     F L\\\\  J ",
	" J__|       J__L    J___//\\\\___L   J____L   J__L \\\\__L",
	" |__L       |__|    |___/  \\___|   |____|   |__L  J__|",
	"                                                     "};
	vector<string> p2;
	p2 = { "    ___         ____       _    _        __          _  _   ",
	"   F _ \",     / _  `.     F L  J J       FJ         F L L]  ",
	"  J `-' |    J_/-7 .'    J J .. L L     J  L       J   \\| L ",
	"  |  __/F    `-:'.'.'    | |/  \\| |     |  |       | |\\   | ",
	"  F |__/     .' ;_J__    F   /\\   J     F  J       F L\\\\  J ",
	" J__|       J________L  J___//\\\\___L   J____L     J__L \\\\__L",
	" |__L       |________|  |___/  \\___|   |____|     |__L  J__|",
	"                                                           "};
	vector<string> p3;
	p3 = { "    ___         ____       _    _        __          _  _   ",
	"   F _ \",     F___ J      F L  J J       FJ         F L L]  ",
	"  J `-' |     `-__| L    J J .. L L     J  L       J   \\| L ",
	"  |  __/F      |__  (    | |/  \\| |     |  |       | |\\   | ",
	"  F |__/    .-____]  J   F   /\\   J     F  J       F L\\\\  J ",
	" J__|       J\\______/F  J___//\\\\___L   J____L     J__L \\\\__L",
	" |__L        J______F   |___/  \\___|   |____|     |__L  J__|",
	"                                                           " };
	vector<string> p4;
	p4 = { "    ___        _  _       _    _        __          _  _   ",
	"   F _ \",    FJ  L]      F L  J J       FJ         F L L]  ",
	"  J `-' |   J |__| L    J J .. L L     J  L       J   \\| L ",
	"  |  __/F   |____  |    | |/  \\| |     |  |       | |\\   | ",
	"  F |__/    L____J  J   F   /\\   J     F  J       F L\\\\  J ",
	" J__|            J__L  J___//\\\\___L   J____L     J__L \\\\__L",
	" |__L            J__|  |___/  \\___|   |____|     |__L  J__|",
	"                                                          " };

	Game::setTextStyle(KHIKI, BLACK);
	if (winner.Id + 1 == 1)
	{
		for (int i = 0; i < p1.size(); i++)
		{
			Game::setCursorXY(28, 11 + i);
			cout << p1[i];
		}
	}
	else if(winner.Id + 1 == 2)
	{
		for (int i = 0; i < p2.size(); i++)
		{
			Game::setCursorXY(28, 11 + i);
			cout << p2[i];
		}
	}
	else if (winner.Id + 1 == 3)
	{
		for (int i = 0; i < p3.size(); i++)
		{
			Game::setCursorXY(28, 11 + i);
			cout << p3[i];
		}
	}
	else
	{
		for (int i = 0; i < p4.size(); i++)
		{
			 Game::setCursorXY(28, 11 + i);
			cout << p4[i];
		}
	}

	Sleep(50000);
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
			if (!Game::players[i].alive)
			{
				Game::setTextStyle(GRAY, BLACK);
				color = "－－－－－－－－－";
			}
			cout << color;
		}
		else if (i + 1 == 2)
		{
			cout << "２Ｐ"; 
			Game::setTextStyle(GREEN, GREEN);
			Game::setCursorXY(20 + i * 20, 2);
			if (!Game::players[i].alive)
			{
				Game::setTextStyle(GRAY, BLACK);
				color = "－－－－－－－－－";
			}
			cout << color;
		}
		else if (i + 1 == 3)
		{
			cout << "３Ｐ";
			Game::setTextStyle(BLUE, BLUE);
			Game::setCursorXY(20 + i * 20, 2);
			if (!Game::players[i].alive)
			{
				Game::setTextStyle(GRAY, BLACK);
				color = "－－－－－－－－－";
			}
			cout << color;
		}
		else
		{
			cout << "４Ｐ ";
			Game::setTextStyle(KHIKI, KHIKI);
			Game::setCursorXY(20 + i * 20, 2);
			if (!Game::players[i].alive)
			{
				Game::setTextStyle(GRAY, BLACK);
				color = "－－－－－－－－－";
			}
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
		if(Game::locals[i].name.size() > 10) //四個字
			Game::setCursorXY(20, 9 + i * 4);
		else if (Game::locals[i].name.size() > 8) //三個字
			Game::setCursorXY(21, 9 + i * 4);
		else
			Game::setCursorXY(22, 9 + i * 4);
		cout << Game::locals[i].name;
	}
	for (int i = 8; i < 15; i++)
	{
		if (Game::locals[i].name.size() > 10) //四個字
			Game::setCursorXY(30 + 10 * (i - 8), 37);
		else if (Game::locals[i].name.size() > 8) //三個字
			Game::setCursorXY(31 + 10 * (i - 8), 37);
		else
			Game::setCursorXY(32 + 10 * (i - 8), 37);
		cout << Game::locals[i].name ;
	}
	for (int i = 15; i < 22; i++)
	{
		if (Game::locals[i].name.size() > 10) //四個字
			Game::setCursorXY(90, 37 - (i - 14) * 4);
		else if (Game::locals[i].name.size() > 8) //三個字
			Game::setCursorXY(91, 37 - (i - 14) * 4);
		else
			Game::setCursorXY(92, 37 - (i - 14) * 4);
		cout << Game::locals[i].name;
	}
	Game::setCursorXY(51, 9);
	for (int i = 27; i > 21; i--)
	{
		if (Game::locals[i].name.size() > 10) //四個字
			Game::setCursorXY(30 - 10 * (i - 27), 9);
		else if (Game::locals[i].name.size() > 8) //三個字
			Game::setCursorXY(31 - 10 * (i - 27), 9);
		else
			Game::setCursorXY(32 - 10 * (i - 27), 9);
		cout << Game::locals[i].name ;
	}

	for (int i = 0; i < Game::companys.size(); i++)
	{
		setTextStyle(GOLD, BLACK);
		setCursorXY(0, 10 + i * 3);
		cout << Game::companys[i].name << "股價:";

		setTextStyle(WHITE, BLACK);
		setCursorXY(2, 11 + i * 3);
		cout << Game::companys[i].stockPrice << "元";
	}
}

