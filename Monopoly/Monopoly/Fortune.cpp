#include "Fortune.h"



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