#include "Company.h"



Company::Company()
{
}


Company::~Company()
{
}

int Company::updateStockPrice()
{
	Company::stockPrice += (rand() % Company::stockPrice - (Company::stockPrice / 2));
	return Company::stockPrice;
}

Company Company::getCompanyById(const vector<Company>& comps, int id)
{
	for (int i = 0; i < comps.size(); i++)
	{
		if (comps[i].Id == id)
		{
			return comps[i];
		}
	}
}