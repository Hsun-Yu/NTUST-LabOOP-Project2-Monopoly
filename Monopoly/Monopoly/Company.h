#include <vector>
#include <time.h>

using namespace std;

#pragma once
class Company
{
public:
	Company();
	Company(int id, string name, int stockPrice) : Id(id), name(name), stockPrice(stockPrice){}
	~Company();

	void updateStockPrice();
	int Id;
	string name;
	int stockPrice;
	static string getNameById(const vector<Company>&, int);
};

class CompanyA : public Company
{
public:
	CompanyA() :Company(1, "CompanyA", 1000) {}
};

class CompanyB : public Company
{
public:

	CompanyB() :Company(2, "CompanyB", 1000) {}
};

class CompanyC : public Company
{
public:

	CompanyC() :Company(3, "CompanyC", 1000) {}
};

class CompanyD : public Company
{
public:

	CompanyD() :Company(4, "CompanyD", 1000) {}
};
