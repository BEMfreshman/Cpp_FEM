#include "PressureLoadOnLine.h"
#include "../TopAbstractClass/elementtype.h"
#include "../TopAbstractClass/feminfo.h"


PressureLoadOnLine::PressureLoadOnLine(int id, int ElementId_, const Eigen::VectorXi& NodeId_,
	const Eigen::MatrixXd Value_) :Load(id), ElementId(ElementId_), NodeId(NodeId_), Value(Value_)
{
	// VectorXi  =  [1;2]
	// Value = [0 1 0;
    //          0 2 0];
}

PressureLoadOnLine::~PressureLoadOnLine()
{

}


int PressureLoadOnLine::ComputeForce(FEMinfo* FEMInformation, vector<T_>& tripleList)
{
	//首先判断这个ElementId对应的单元类型
	Element* El = FEMInformation->getElementById(ElementId);
	ElementType ET = El->GetElementType();

	map<int, Eigen::MatrixXd> PressureOnPoint;
	for (int i = 0; i < NodeId.size(); i++)
	{
		int EachNodeId = NodeId(i);
		Eigen::MatrixXd EachValue(1, Value.cols());
		EachValue= Value.row(i);

		PressureOnPoint[EachNodeId] = EachValue;
	}

	El->ComputeForceMatrixOnEle(PressureOnPoint, getLoadType(),tripleList);

	return 1;
}

LoadType PressureLoadOnLine::getLoadType() const
{
	return LoadOnLine;
}