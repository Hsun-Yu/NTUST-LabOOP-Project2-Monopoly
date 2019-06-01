#include <vector>

using namespace std;

#pragma once
class Property
{
public:
	Property();
	~Property();
	int money;
	//int ---localId
	vector<int> localIds;

	//int ---componyId
	vector<int> componyIds;

	vector<int> toolIds;


	int loan = 0;
	int loanCount = 0;

	int bankMoney;
	bool isMyLocal(int localId);
	int getHowManyTool(int toolId);
	int getAllProperty();
};

