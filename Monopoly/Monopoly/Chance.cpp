#include "Chance.h"


Chance::~Chance()
{
}

void GetMoneyChance::method(Player& player)
{
	player.property.money += 20000;
}

void StopChance::method(Player& player)
{
	player.stop += 2;
}
