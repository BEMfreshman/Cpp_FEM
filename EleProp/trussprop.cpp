#include "trussprop.h"

TrussProp::TrussProp(int id) :EProp(id)
{
   
}

TrussProp::~TrussProp()
{

}

int TrussProp::SetValue(const std::map<std::string, double>& EPropNameAndValue)
{
	std::map<std::string, double>::const_iterator it;
	EPropVar EPV;
	for (it = EPropNameAndValue.begin(); it != EPropNameAndValue.end(); it++)
	{
		if (it->first == "Area")
		{
			EPV = Area;
		}


		if (__SetValue(EPV, it->second) == 0)
		{
			printf("错误：单元属性设置错误\n");
			return 0;
		}
	}
	return 1;
}


