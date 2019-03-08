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
		else
		{
			printf("�Ƿ�����\n");
			return 0;
		}


		if (__SetValue(EPV, it->second) == 0)
		{
			printf("���󣺵�Ԫ�������ô���\n");
			return 0;
		}
	}
	return 1;
}


