#include "Dof.h"

DOF::DOF(int LocalDOFId_, DOFVar DF_) 
	:LocalDOFId(LocalDOFId_), DF(DF_)
{

}

DOF::DOF(int LocalDOFId_, int VaildTotalDOFId_, DOFVar DF_)
: LocalDOFId(LocalDOFId_), VaildTotalDOFId(VaildTotalDOFId_), DF(DF_)
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

void DOF::SetVaild(bool vaildflag)
{
	IsVaild = vaildflag;
}