#include "beamprop.h"

BeamProp::BeamProp(int id) :EProp(id)
{
    
}

BeamProp::~BeamProp()
{

}

int BeamProp::SetValue(const std::map<std::string, double>& EPropNameAndValue)
{
	std::map<std::string, double>::const_iterator it;
	EPropVar EPV;
	for (it = EPropNameAndValue.begin(); it != EPropNameAndValue.end(); it++)
	{
		if (it->first == "Area")
		{
			EPV = Area;
		}
		else if (it->first == "Iy")
		{
			EPV = Iy;
		}
		else if (it->first == "Iz")
		{
			EPV = Iz;
		}
		else if (it->first == "Tx")
		{
			EPV = Tx;
		}

		if (__SetValue(EPV, it->second) == 0)
		{
			printf("Failed\n");
			return 0;
		}
	}
	return 1;
}
