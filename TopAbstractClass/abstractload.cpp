#include "abstractload.h"

Load::Load(int id_, const Eigen::MatrixXi& NodeId_,
	const Eigen::MatrixXd Value_) 
	:id(id_), CoordId(0), NodeId(NodeId_), Value(Value_)
{
	
}

Load::~Load()
{

}

int Load::GetId()
{
	return id;
}

void Load::addData(const Eigen::MatrixXi& NodeId, const Eigen::MatrixXd& Value)
{
	this->NodeId = NodeId;
	this->Value = Value;
}

const Eigen::MatrixXi Load::getNodeId() const
{
	return NodeId;
}

const Eigen::MatrixXd Load::getValue() const
{
	return Value;
}

int Load::getCoordId() const
{
	return CoordId;
}