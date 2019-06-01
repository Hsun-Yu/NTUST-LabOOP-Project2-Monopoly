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

void DoraemonFortune::method(Player& player)
{
	int position;
	system("cls");
	cout << "請輸入你想去哪" << endl;
	cin >> position;
	player.position = position;
}

void TimeTunnelFortune::method(Player& player)
{
	player.position = rand() % 28;
	cout << "你被傳送到了位置" << player.position << endl;
}
