#include <string>

using namespace std;

#include <vector>

using namespace std;
#pragma once
class Local
{
public:
	Local();
	~Local();
	int Id;
	int localType;
	int level = 0;
	string name;
	vector<int> priceOfLevel;

	int getNowPriceOfLevel();
};

