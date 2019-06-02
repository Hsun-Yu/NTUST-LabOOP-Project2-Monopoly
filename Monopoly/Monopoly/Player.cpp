#include "Player.h"
#include "Game.h"


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

	if (Player::property.loanCount > 0)
		Player::property.loanCount--;

	if (Player::property.loanCount == 0 && Player::property.loan != 0)
	{
		cout << "因為你還沒還完款，所以你把所有房產以及股票賣掉，來還款" << endl;

		for (int i = 0; i < Player::property.localIds.size(); i)
		{
			Player::property.money += (Game::locals[Player::property.localIds[i]].priceOfLevel[0] / 2);
			Player::property.localIds.erase(Player::property.localIds.begin());
		}

		for (int i = 0; i < Player::property.componyIds.size(); i)
		{
			Player::property.money += Game::companys[Player::property.componyIds[i]].stockPrice;
			Player::property.componyIds.erase(Player::property.componyIds.begin());
		}

		Player::property.money += Player::property.bankMoney;
		Player::property.bankMoney = 0;

		Player::property.money -= Player::property.loan;
	}
}

void Player::checkAlive()
{
	if (Player::property.money < 0)
		alive = false;
}

void Player::goPosition(int number)
{
	vector<string> Board;
	Board = {
			" _________________ " ,
			"|                 |" ,
			"|     你經過了    |" ,
			"|                 |" ,
			"|  ＜  地 球  ＞  |" ,
			"|                 |" ,
			"|  獲得 $ 2000  ! |" ,
			"|                 |" ,
			"|＿＿＿＿＿＿＿＿_|"
	};
	Player::position += number;
	if (Player::position > 27)
	{
		Player::position %= 28;
		for (int i = 0; i < Board.size(); i++)
		{
			Game::setCursorXY(50, 16 + i);
			cout << Board[i];
		}
		Sleep(3000);
		Player::property.money += 2000;
	}
}

