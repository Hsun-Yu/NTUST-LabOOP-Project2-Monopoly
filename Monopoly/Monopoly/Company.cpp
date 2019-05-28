#include "Company.h"



Company::Company()
{
}


Company::~Company()
{
}

void Company::updateStockPrice()
{
	srand(time(NULL));
	Company::stockPrice += (rand() % Company::stockPrice - (Company::stockPrice / 2));
}
