#include "Dof.h"

DOF::DOF(int LocalDOFId_, DOFVar DF_) 
	:LocalDOFId(LocalDOFId_), DF(DF_)
{

}

DOF::DOF(int LocalDOFId_, bool IsVaild_, DOFVar DF_)
: LocalDOFId(LocalDOFId_), IsVaild(IsVaild_), DF(DF_)
{

}

DOF::~DOF()
{

}

int DOF::getLocalDOFId()
{
	return LocalDOFId;
}

int DOF::getVaildTotalDOFId()
{
	return VaildTotalDOFId;
}

DOFVar DOF::getDOFVar()
{
	return DF;
}

bool DOF::getIsVaild()
{
	return IsVaild;
}

void DOF::SetVaildTotalDOFId(int VaildTotalDOFId)
{
	this->VaildTotalDOFId = VaildTotalDOFId;
}

int DOF::addresidualK(const Eigen::Triplet<double>& T)
{
	residualK.push_back(T);
	return 1;
}