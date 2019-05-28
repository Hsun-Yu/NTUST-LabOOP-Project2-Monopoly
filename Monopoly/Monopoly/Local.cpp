#include "Local.h"



Local::Local()
{

}

Local::~Local()
{

}

int Local::getNowPriceOfLevel()
{
	if (Local::localType == 1)
		return Local::priceOfLevel[Local::level];
	else
		return 0;
}

