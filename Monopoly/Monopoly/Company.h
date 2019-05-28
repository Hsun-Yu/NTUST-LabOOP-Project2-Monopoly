#include <vector>
#include <time.h>

using namespace std;

#pragma once
class Company
{
public:
	Company();
	~Company();

	void updateStockPrice();
	int Id;
	string name;
	int stockPrice;

};

