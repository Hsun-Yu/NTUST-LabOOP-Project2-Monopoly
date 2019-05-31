#include <string>

using namespace std;
#include "Player.h"
#pragma once
class Fortune
{
public:
	Fortune();
	~Fortune();
	string name;
	virtual void method(Player & player){}
};