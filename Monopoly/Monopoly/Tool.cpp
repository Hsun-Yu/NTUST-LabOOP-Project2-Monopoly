#include "Tool.h"



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
	cout <<"休息一回合!";
	player.stop += 1;
}

BombTool::BombTool():Tool(2, "炸彈", 1000)
{}

void BombTool::method(Player & player)
{
	cout << " 後退三步!";
	player.position -= 3;
	if (player.position < 0)
		player.position += 28;
}

ToBlackHoleTool::ToBlackHoleTool():Tool(3, "黑洞傳送器", 1000)
{
}

void ToBlackHoleTool::method(Player& player)
{
	cout << "傳送至黑洞!";
	player.position = 21;
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
