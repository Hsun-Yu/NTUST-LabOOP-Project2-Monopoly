#include <string>

#include "Player.h"

using namespace std;

#pragma once
class Tool
{
public:
	Tool();
	~Tool();
	string name;
	int price;
	virtual void method(Player& player) {}
};

