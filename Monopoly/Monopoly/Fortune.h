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
	SolarWindFortune() :Fortune(1, "危險！！遇到太陽風暴，先撤退 3 格吧") {}
	virtual void method(Player& player);
};

class DoraemonFortune : public Fortune
{
public:
	DoraemonFortune() :Fortune(2, "突發狀況！！遭受外星人飛船攻擊，趕快回地球") {}
	virtual void method(Player& player);
};

class TimeTunnelFortune : public Fortune
{
public:
	TimeTunnelFortune() :Fortune(3, "啊啊啊！！掉進了時空隧道，被傳送至隨機位置") {}
	virtual void method(Player& player);
};

class ChangePropertyFortune : public Fortune
{
public:
	ChangePropertyFortune() :Fortune(4, "哈哈哈！！拿錯錢包了，與一位玩家交換錢包"){}
	virtual void method(Player& player);
};