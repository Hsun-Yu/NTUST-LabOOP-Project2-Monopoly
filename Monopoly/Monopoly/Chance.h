#pragma once
class Chance
{
public:
	Chance();
	~Chance();
	string name;
	virtual void method(Player& player) {}
};

