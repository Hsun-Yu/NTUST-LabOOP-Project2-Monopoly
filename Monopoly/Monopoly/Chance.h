#include "Player.h"

#pragma once
class Chance
{
public:
	Chance() :id(0), name(""){};
	Chance(int id, string name) :id(id), name(name) {};
	~Chance();
	int id;
	string name;
	virtual void method(Player& player) {}
};

class GetStockChance : public Chance
{
public:
	GetStockChance():Chance(1, "遇見好心外星人，送你隨機一張股票！！"){}
	virtual void method(Player& player);
};

class GetMoneyChance : public Chance
{
public:
	GetMoneyChance() :Chance(2, "執行任務成功，得到10000元！！") {}
	virtual void method(Player& player);
};

class StopChance : public Chance
{
public:
	StopChance() :Chance(3, "飛船壞掉了，暫停一回合！！") {}
	virtual void method(Player& player);
};


