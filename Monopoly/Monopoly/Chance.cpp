#include "Chance.h"
#include "Game.h"

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

void GetStockChance::method(Player& player)
{
	srand(time(NULL));
	int companysId = rand() % Game::companys.size();
	player.property.componyIds.push_back(companysId);
}