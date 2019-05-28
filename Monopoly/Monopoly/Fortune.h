#include <string>

using namespace std;

#pragma once
class Fortune
{
public:
	Fortune();
	~Fortune();
	string name;
	virtual void method(Player & player){}
};

