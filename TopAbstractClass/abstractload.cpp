#include "abstractload.h"

Load::Load(int id_) 
	:id(id_), CoordId(0)
{
	
}

Load::~Load()
{

}

int Load::GetId() const
{
	return id;
}

int Load::getCoordId() const
{
	return CoordId;
}

void Load::setCoordId(int CoordId)
{
	this->CoordId = CoordId;
}