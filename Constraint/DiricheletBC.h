#ifndef __DIRICHLETBC_H__
#define __DIRICHLETBC_H__

#include "../TopAbstractClass/abstractconstraint.h"

//父类：Constraint（抽象类）
//第一类边界条件
//也就是指定边界上点的位移值

class DirichletBC:public Constraint
{
public:
	DirichletBC(int id,int NodeId,DOFVar DF,double Value);
	~DirichletBC();

	BCType getBCType() const;

};

#endif