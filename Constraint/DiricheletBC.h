#ifndef __DIRICHLETBC_H__
#define __DIRICHLETBC_H__

#include "../TopAbstractClass/abstractconstraint.h"

//���ࣺConstraint�������ࣩ
//��һ��߽�����
//Ҳ����ָ���߽��ϵ��λ��ֵ

class DirichletBC:public Constraint
{
public:
	DirichletBC(int id,int NodeId,DOFVar DF,double Value);
	~DirichletBC();

	int ModifyForceMatrix(FEMinfo* FEMInfomation, std::vector<T_>& tripleList);

	BCType getBCType() const;

};

#endif