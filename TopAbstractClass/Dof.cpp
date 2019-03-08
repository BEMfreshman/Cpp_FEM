#include "Dof.h"

DOF::DOF(int LocalDOFId_, DOFVar DF_) 
	:LocalDOFId(LocalDOFId_), DF(DF_)
{
	ans = 0.0;
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

int DOF::addresidualK(const T_& Value)
{
	residualK.push_back(Value);
	return 1;
}

int DOF::getResidualKSize()
{
	return residualK.size();
}

T_ DOF::getResidualK(int i)
{
	return residualK[i];
}

void DOF::SetAns(double ans)
{
	this->ans = ans;
}

double DOF::getAns()
{
	return ans;
}