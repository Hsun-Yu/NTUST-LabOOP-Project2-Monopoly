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

DoubleFeeTool::DoubleFeeTool():Tool(4, "過路費加倍卷", 2000)
{
}

