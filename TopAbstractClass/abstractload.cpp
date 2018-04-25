#include "abstractload.h"

Load::Load(int id_) :id(id_)
{
	
}

Load::~Load()
{

}

int Load::GetId()
{
	return id;
}

void Load::addElement(Element* Ele)
{
	vector<Element*>::iterator it;
	it = find(ElementVec.begin(), ElementVec.end(), Ele);

	if (it != ElementVec.end())
	{
		//已经存在此Ele
		return;
	}
	else
	{
		ElementVec.push_back(Ele);
	}
}