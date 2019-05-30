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

	int bankMoney;

	bool isMyLocal(int localId);
	int getAllProperty();
};

