#include "Local.h"



Local::Local()
{

}

Local::~Local()
{

}

int Local::getNowPriceOfLevel()
{
	return Local::priceOfLevel[Local::level];
}

