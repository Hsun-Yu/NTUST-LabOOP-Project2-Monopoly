#include <vector>

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
	string description;
	int stockPrice;
};

