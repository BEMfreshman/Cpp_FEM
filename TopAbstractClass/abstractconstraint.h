#ifndef __ABSTRACTCONSTRAINT_H__
#define __ABSTRACTCONSTRAINT_H__

#include "BoundaryConditionType.h"
#include "DOFVar.h"
#include <Eigen\Eigen>

class FEMinfo;

typedef Eigen::SparseMatrix<double> SpMat;

class Constraint
{
public:
	Constraint(int id,int NodeId,DOFVar DF,double Value);
	virtual ~Constraint() = 0;

	virtual BCType getBCType() const = 0;
	virtual void ModifyForceMatrix(FEMinfo* FEMInfomation, SpMat& f) const = 0;
	//–ﬁ Œ‘ÿ∫…’Û¡–

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