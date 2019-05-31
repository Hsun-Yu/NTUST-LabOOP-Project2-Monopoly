#include "Property.h"



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

