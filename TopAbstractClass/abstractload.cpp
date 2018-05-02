#include "abstractload.h"

Load::Load(int id_) :id(id_), CoordId(0)
{
	
}

Load::~Load()
{

}

int Load::GetId()
{
	return id;
}

void Load::addData(const Eigen::VectorXi& NodeId, const Eigen::VectorXd& Value)
{
	this->NodeId = NodeId;
	this->Value = Value;
}

const Eigen::VectorXi Load::getNodeId() const
{
	return NodeId;
}

const Eigen::VectorXd Load::getValue() const
{
	return Value;
}

int Load::getCoordId() const
{
	return CoordId;
}