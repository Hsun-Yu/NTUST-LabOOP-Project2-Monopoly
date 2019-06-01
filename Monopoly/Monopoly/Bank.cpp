#include "Bank.h"

void deposit(Property & p, unsigned int howmuch)
{
	if (p.money - howmuch >= 0) //deposite success
	{
		p.money -= howmuch;
		p.bankMoney += howmuch;
	}
}

void withdrawal(Property & p, unsigned int howmuch)
{
	if (p.bankMoney - howmuch >= 0)
	{
		p.bankMoney -= howmuch;
		p.money += howmuch;
	}
}

void loanMoney(Property& p, unsigned int howmuch) 
{
	if (p.getAllProperty() >= howmuch)
	{
		p.loan += howmuch;
		p.loanCount = 3;
	}
}
