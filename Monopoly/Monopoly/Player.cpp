#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}

void Player::finishARound()
{
	if(stop > 0)
		Player::stop--;
}

void Player::checkAlive()
{
	if (Player::property.getAllProperty() < 0)
		alive = false;
}

void Player::goPosition(int number)
{
	Player::position += number;
	if (Player::position > 27)
	{
		Player::position %= 28;
		Player::property.money += 5000;
	}
}

