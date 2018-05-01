#include "DiricheletBC.h"

DirichletBC::DirichletBC(int id, int NodeId, DOFVar DF, double Value) 
:Constraint(id,NodeId,DF,Value)
{
	BCT = Dirichelet;
}

DirichletBC::~DirichletBC()
{

}

BCType DirichletBC::getBCType() const
{
	return BCT;
}