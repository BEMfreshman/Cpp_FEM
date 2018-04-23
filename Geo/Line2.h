#ifndef __LINE2_H__
#define __LINE2_H__

#include "../TopAbstractClass/abstractelement.h"

class Line2:public Element
{
public:
	Line2();
	Line2(int ElementID,int MaterialId,
		Element::ElementType eletype,
		const Eigen::MatrixXi& VertexIdArray);

	virtual ~Line2();
	Line2(const Line2& that);

	Line2& operator=(const Line2& that);

	Element* Clone() const;

	virtual int GetSpecificMatrix(SparseMatrixType SMT, Eigen::MatrixXd& ReturnMatrix);

	virtual int SetDOF(int dim);

protected:
	virtual int ComputeStiffnessMatrix(Eigen::MatrixXd& matReturn);

	void GenerateLoacalGaussPointAndWeight(int Order);
	int ComputeShapeFunction(ShapeFunType SFT);
};



#endif