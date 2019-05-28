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


