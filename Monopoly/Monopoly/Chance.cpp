#include "Chance.h"


Chance::~Chance()
{
}

void GetMoneyChance::method(Player& player)
{
	player.property.money += 10000;
}

void StopChance::method(Player& player)
{
	player.stop += 1;
}
