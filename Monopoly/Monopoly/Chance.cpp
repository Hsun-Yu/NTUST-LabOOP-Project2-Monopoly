#include "Chance.h"
#include "Game.h"

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

void GetStockChance::method(Player& player)
{
	//srand(time(NULL));
	int companysId = rand() % Game::companys.size();
	player.property.componyIds.push_back(companysId + 1);
	if (companysId == 0)
		cout << "A";
	else if (companysId == 1)
		cout << "B";
	else if (companysId == 2)
		cout << "C";
	else
		cout << "D";
}
