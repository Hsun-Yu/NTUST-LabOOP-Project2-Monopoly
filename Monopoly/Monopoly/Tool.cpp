#include "Tool.h"
#include "Game.h"


Tool::Tool()
{
	Tool::price = 0;
	Tool::name = "";
}

Tool::Tool(int id, string name, int price)
{
	Tool::id = id;
	Tool::name = name;
	Tool::price = price;
}


Tool::~Tool()
{
}

RoadblockTool::RoadblockTool():Tool(1, "路障", 500)
{}

void RoadblockTool::method(Player & player)
{
	player.stop += 2;
}

BombTool::BombTool():Tool(2, "炸彈", 1000)
{}

void BombTool::method(Player & player)
{
	player.position -= 3;
}

ToBlackHoleTool::ToBlackHoleTool():Tool(3, "黑洞傳送器", 1000)
{
}

void ToBlackHoleTool::method(Player& player)
{
	player.position = 21;
}

DoubleFeeTool::DoubleFeeTool():Tool(5, "過路費加倍卷", 2000)
{
}

ChooseWhereToGoTool::ChooseWhereToGoTool():Tool(4, "遙控骰子", 2000)
{
}

void ChooseWhereToGoTool::method(Player& player)
{
	int choosNum = 0;
	system("cls");
	cout << "選擇走幾步(輸入數字):" << endl;
	cin >> choosNum;
	player.position += choosNum;
}

void DoubleFeeTool::method(Player& player)
{
	player.property.money -= Game::locals[player.position].getNowPriceOfLevel();

	for (int i = 0; i < Game::players.size(); i++)
	{
		if (Game::players[i].property.isMyLocal(player.position))
			Game::players[i].property.money += Game::locals[player.position].getNowPriceOfLevel();
	}
}