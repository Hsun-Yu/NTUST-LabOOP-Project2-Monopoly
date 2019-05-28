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

	bool isMyLocal(int localId);
};

