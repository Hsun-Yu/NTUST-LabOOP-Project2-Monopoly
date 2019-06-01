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

string Company::getNameById(const vector<Company>& comps, int id)
{
	for (int i = 0; i < comps.size(); i++)
	{
		if (comps[i].Id == id)
		{
			return comps[i].name;
		}
	}
}