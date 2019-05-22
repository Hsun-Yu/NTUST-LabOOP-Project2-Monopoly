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
	string name;
	int nowType;
	vector<int> priceOfType;
};

