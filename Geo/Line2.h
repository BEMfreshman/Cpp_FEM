#ifndef __LINE2_H__
#define __LINE2_H__

#include "../TopAbstractClass/abstractelement.h"

class Line2:public Element
{
public:
	Line2();
	Line2(int ElementID,int MaterialId,
		ElementType eletype,
		const Eigen::MatrixXi& VertexIdArray);

	virtual ~Line2();
	Line2(const Line2& that);

	Line2& operator=(const Line2& that);

	Element* Clone() const;

	virtual int GetSpecificMatrix(SparseMatrixType SMT, vector<T_>& ReturnValue);

	virtual int SetDOF(int dim);

	virtual ElementType GetElementType();

protected:
	virtual int ComputeStiffnessMatrix(Eigen::MatrixXd& matReturn);

	void GenerateLoacalGaussPointAndWeight(int Order);
	int ComputeShapeFunction(ShapeFunType SFT);

	int ComputeElementLength();

	int ComputeTMatrix(int dim);

protected:
	double ElementLength;
	Eigen::MatrixXd T;             //代表局部坐标轴和全局坐标轴的旋转矩阵
};



#endif