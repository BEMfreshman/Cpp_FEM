#ifndef __ABSTRACTCONSTRAINT_H__
#define __ABSTRACTCONSTRAINT_H__

#include "BoundaryConditionType.h"
#include "DOFVar.h"
#include <Eigen\Eigen>

class FEMinfo;

typedef Eigen::Triplet<double> T_;

class Constraint
{
public:
	Constraint(int id,int NodeId,DOFVar DF,double Value);
	virtual ~Constraint() = 0;

	virtual BCType getBCType() const = 0;
	virtual int ModifyForceMatrix(FEMinfo* FEMInfomation, std::vector<T_>& tripleList) = 0;
	//�����غ�����

	int getNodeId();
	DOFVar getDOFVar();
	double getValue();

protected:
	int id;
	BCType BCT;

	int NodeId;
	DOFVar DF;
	double Value;

protected:

};


#endif