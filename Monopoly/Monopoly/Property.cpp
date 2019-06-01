#include "Property.h"
#include "Game.h"


Property::Property()
{
}


Property::~Property()
{
}

bool Property::isMyLocal(int localId)
{
	for (int i = 0; i < Property::localIds.size(); i++)
	{
		if (Property::localIds[i] == localId)
			return true;
	}
	return false;
}


int Property::getHowManyTool(int toolId)
{
	return count(Property::toolIds.begin(), Property::toolIds.end(), toolId);
}

int Property::getAllProperty()
{
	int property = Property::money + Property::bankMoney;
	for (int i = 0; i < Property::localIds.size(); i++)
		property += (Game::locals[Property::localIds[i]].priceOfLevel[0]);

	return property;
}

