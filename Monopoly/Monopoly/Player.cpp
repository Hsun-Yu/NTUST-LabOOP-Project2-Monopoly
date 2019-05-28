#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}

void Player::checkAlive()
{
	if (Player::property.getAllProperty() < 0)
		alive = false;
}

