#ifndef __LINE2_H__
#define __LINE2_H__

#include "../TopAbstractClass/abstractelement.h"

class Line2:public Element
{
public:
	Line2();
	Line2(int ElementID,int MaterialId,
		ElementType eletype,
		int dim,
		const Eigen::MatrixXi& VertexIdArray);

	virtual ~Line2();
	Line2(const Line2& that);

	Line2& operator=(const Line2& that);

	Element* Clone() const;


	virtual int ComputeForceMatrixOnEle(const map<int, Eigen::MatrixXd>& Pressure,
		const LoadType LT,
		vector<T_>& tripList);

public:
	virtual int GetSpecificMatrix(SparseMatrixType SMT, vector<T_>& ReturnValue);

	virtual int SetDOF(int dim);

	virtual ElementType GetElementType();

protected:
	void ComputeJacMatrix(int GaussPointId, Eigen::MatrixXd& Jac);

	virtual int ComputeStiffnessMatrix(Eigen::MatrixXd& matReturn);
	void GenerateLoacalGaussPointAndWeight(int Order);
	virtual int ComputeShapeFunction();

	int ComputeElementLength();
	int ComputeTMatrix(int dim);

protected:
	double ElementLength;
	Eigen::MatrixXd T;             //总体局部转置矩阵

	// displacement_Local = T * displacement_Global
};



#endif