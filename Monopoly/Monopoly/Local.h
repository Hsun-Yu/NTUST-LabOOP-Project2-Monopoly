#include <string>
#include <vector>
#include "Tool.h"

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

	void setToDefaultTool();

	int toolId;
};

