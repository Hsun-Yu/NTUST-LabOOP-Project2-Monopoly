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

