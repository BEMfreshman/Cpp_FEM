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
				int dim,
                const Eigen::MatrixXi& VertexIdArray);
    ~QuadElement();

    QuadElement(const QuadElement& that);
    QuadElement& operator =(const QuadElement& that);

    Element* Clone() const;

	virtual int GetSpecificMatrix(SparseMatrixType SMT, vector<T_>& tripleList);

	virtual int SetDOF(int dim);

	virtual ElementType GetElementType();

	int ComputeForceMatrixOnEle(const map<int, Eigen::MatrixXd>& Pressure,
		const LoadType LT,
		vector<T_>& tripList);

protected:
	virtual int ComputeStiffnessMatrix(vector<T_>& ReturnValue);
	int ComputeMassMatrix(vector<T_>& ReturnValue);

	void GenerateLoacalGaussPointAndWeight(int Order);
	int ComputeShapeFunction();

	int ComputeBMatrix(int GaussPointId,Eigen::MatrixXd& Bmat);

	void ComputeJacMatrix(int GaussPointId,Eigen::MatrixXd& Jac);

	void ComputeDMatrix(Eigen::MatrixXd& Dmat);
};

#endif // QUADELEMENT_H
