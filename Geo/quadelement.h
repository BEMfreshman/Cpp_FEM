#ifndef QUADELEMENT_H
#define QUADELEMENT_H

/* 四边形单元
 * 4节点单元
 */

#include "../TopAbstractClass/abstractelement.h"

class QuadElement:public Element
{
public:
    QuadElement();
    QuadElement(int ElementId,
                int MaterialId,
                ElementType eletype,
                const Eigen::MatrixXi& VertexIdArray);
    ~QuadElement();

    QuadElement(const QuadElement& that);
    QuadElement& operator =(const QuadElement& that);

    Element* Clone() const;

	virtual int GetSpecificMatrix(SparseMatrixType SMT, vector<T_>& tripleList);

	virtual int SetDOF(int dim);

	virtual ElementType GetElementType();

protected:
	virtual int ComputeStiffnessMatrix(Eigen::MatrixXd& matReturn);

	void GenerateLoacalGaussPointAndWeight(int Order);
	int ComputeShapeFunction(ShapeFunType SFT);


};

#endif // QUADELEMENT_H
