#include "Bank.h"

bool deposit(Property & p, unsigned int howmuch)
{
	if (p.money - howmuch >= 0) //deposite success
	{
		p.money -= howmuch;
		p.bankMoney += howmuch;
		return true;
	}
	else	//deposite error
		return false;
}

bool withdrawal(Property & p, unsigned int howmuch)
{
	if (p.bankMoney - howmuch >= 0)
	{
		p.bankMoney -= howmuch;
		p.money += howmuch;
	}
	else
		return false;
}
