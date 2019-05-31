#include <string>

#include "Player.h"

using namespace std;

#pragma once
class Tool
{
public:
	Tool();
	Tool(int id, string name, int price);
	~Tool();
	int id;
	string name;
	int price;
	virtual void method(Player& player) {};
};

class RoadblockTool : public Tool
{
public:
	RoadblockTool();
	virtual void method(Player& player);
};

class BombTool : public Tool
{
public:
	BombTool();
	virtual void method(Player& player);
};

class ToBlackHoleTool : public Tool
{
public:
	ToBlackHoleTool();
	virtual void method(Player& player);
};

class DoubleFeeTool : public Tool
{
public:
	DoubleFeeTool();
	virtual void method(Player& player);
};

