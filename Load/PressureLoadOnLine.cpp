#include "PressureLoadOnLine.h"
#include "../TopAbstractClass/elementtype.h"
#include "../TopAbstractClass/feminfo.h"


PressureLoadOnLine::PressureLoadOnLine(int id, int ElementId_, const Eigen::VectorXi& NodeId_,
	const Eigen::MatrixXd Value_) :Load(id), ElementId(ElementId_), NodeId(NodeId_)
{
	// VectorXi  =  [1;2]
	// Value = [0 1 0;
    //          0 2 0];
}


int PressureLoadOnLine::ComputeForce(FEMinfo* FEMInformation, vector<T_>& tripleList)
{
	//首先判断这个ElementId对应的单元类型
	ElementType ET = FEMInformation->getElementById(ElementId)->GetElementType();
	int dim = FEMInformation->getdim();

}