#include "Dof.h"
#include "DofManager.h"

DOF::DOF() :id(0), DM(NULL)
{

}

DOF::DOF(int id_, DofManager*DM_) : id(id_), DM(DM_)
{

}

int DOF::getid() const
{
	return id;
}

DofManager* DOF::getDM() const
{
	return DM;
}

DOF::~DOF()
{

}