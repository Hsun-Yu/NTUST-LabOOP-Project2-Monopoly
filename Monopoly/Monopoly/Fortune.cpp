#include "Fortune.h"
#include "Game.h"

Fortune::Fortune()
{
	Fortune::id = 0;
	Fortune::name = "";
}

Fortune::Fortune(int id, string name):id(id), name(name)
{
}


Fortune::~Fortune()
{
}

void SolarWindFortune::method(Player& player)
{
	player.position -= 3;
}

void BackToEarthFortune::method(Player& player)
{
	player.position = 0;
}

void TimeTunnelFortune::method(Player& player)
{
	player.position = rand() % 28;
	cout << "你被傳送到了位置" << player.position << endl;
}

void ChangePropertyFortune::method(Player& player)
{
	srand(time(NULL));
	int whoId = rand() % Game::players.size();
	while (whoId == player.Id)
		whoId = rand() % Game::players.size();
	Property p = player.property;
	player.property = Game::players[whoId].property;
	Game::players[whoId].property = p;

	cout << "你與P" << whoId + 1 << "交換了錢包" << endl;
	Sleep(5000);
}