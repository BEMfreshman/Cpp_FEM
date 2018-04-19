#include "abastractelementprop.h"

EProp::EProp(int id)
{
	this->id = id;
}

EProp::~EProp()
{

}

int EProp::GetId()
{
	return id;
}

int EProp::hasProp(EPropVar EP)
{
	map<EPropVar, double>::iterator it;

	it = EPropd.find(EP);

	return it != EPropd.end();
}

int EProp::GetValue(EPropVar EP, double *Value)
{
	if (hasProp(EP) == 0)
	{
		return 0;
	}
	else
	{
		map<EPropVar, double>::iterator it = EPropd.find(EP);
		(*Value) = it->second;
		return 1;
	}
}

int EProp::__SetValue(EPropVar EP, double Value)
{
	if (hasProp(EP) == 1)
	{
		map<EPropVar, double>::iterator it = EPropd.find(EP);
		it->second = Value;
		return 1;
	}
	else
	{
		EPropd.insert(make_pair(EP, Value));
		return 1;
	}
	return 0;
}
