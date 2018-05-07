#include "abstractconstraint.h"

Constraint::Constraint(int id_,int NodeId_,DOFVar DF_,double Value_)
:id(id_), NodeId(NodeId_), DF(DF_), Value(Value_)
{

}

Constraint::~Constraint()
{

}

int Constraint::getNodeId()
{
	return NodeId;
}

DOFVar Constraint::getDOFVar()
{
	return DF;
}

double Constraint::getValue()
{
	return Value;
}

