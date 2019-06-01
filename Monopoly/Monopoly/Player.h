#include <string>
#include <vector>
#include "Property.h"
using namespace std;

#pragma once
class Player
{
public:
	Player();
	~Player();
	int Id;
	string name;
	Property property;
	int position;
	int stop = 0;
	bool alive = true;
	bool inBlack = false;
	void finishARound();
	void checkAlive();
	void goPosition(int number);
};
