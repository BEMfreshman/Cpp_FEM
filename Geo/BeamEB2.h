#ifndef __BEAMEB2_H__
#define __BEAMEB2_H__

//#include "../TopAbstractClass/abstractelement.h"
#include "Line2.h"

class BeamEB2:public Line2
{
public:
	BeamEB2();   //默认构造函数
	BeamEB2(int ElementId, int MaterialId,
		int EPropId, Element::ElementType eletype,
		const Eigen::MatrixXi& VertexIdArray);

	~BeamEB2();

	BeamEB2(const BeamEB2& that);
	BeamEB2& operator=(const BeamEB2& that);

	Element* Clone() const;

	int GetSpecificMatrix(SparseMatrixType SMT, Eigen::MatrixXd& ReturnMatrix);

	int SetDOF(int dim);
protected:

	int ComputeStiffnessMatrix(Eigen::MatrixXd& matReturn);
	int ComputeMassMatrix(Eigen::MatrixXd& matReturn);

private:

	
};

#endif