#include <string>
#include <iostream>

using namespace std;
#include "Player.h"
#pragma once
class Fortune
{
public:
	Fortune();
	Fortune(int id, string name);
	~Fortune();
	int id;
	string name;
	virtual void method(Player & player){}
};

class SolarWindFortune : public Fortune
{
public:
	SolarWindFortune() :Fortune(1, "遇到太陽風暴倒退3格") {}
	virtual void method(Player& player);
};

class DoraemonFortune : public Fortune
{
public:
	DoraemonFortune() :Fortune(2, "遇到多拉A夢，借用任意門到你想去的位置") {}
	//TODO : 詢問想去的位置
	virtual void method(Player& player);
};

class TimeTunnelFortune : public Fortune
{
public:
	TimeTunnelFortune() :Fortune(3, "阿阿阿!!!!掉進了時空隧道，將被傳送至隨機位置") {}
	virtual void method(Player& player);
};

class ChangePropertyFortune : public Fortune
{
public:
	ChangePropertyFortune() :Fortune(4, "哈哈哈!!你拿錯錢包了，跟隨機玩家交換錢包"){}
	virtual void method(Player& player);
};