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
	string name;
	Property property;
	int position;
};
