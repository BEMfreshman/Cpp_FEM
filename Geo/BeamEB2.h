#ifndef __BEAMEB2_H__
#define __BEAMEB2_H__

//#include "../TopAbstractClass/abstractelement.h"

/*
一维梁单元，所在坐标系统为xoy坐标系统
z轴通过其重心，一维单元刚度矩阵计算公式中
的惯性矩为Iz


*/


#include "Line2.h"


class BeamEB2:public Line2
{
public:
	BeamEB2();   //默认构造函数
	BeamEB2(int ElementId, int MaterialId,
		int EPropId, ElementType eletype,
		int dim,
		const Eigen::MatrixXi& VertexIdArray);

	~BeamEB2();

	BeamEB2(const BeamEB2& that);
	BeamEB2& operator=(const BeamEB2& that);

	Element* Clone() const;

	int GetSpecificMatrix(SparseMatrixType SMT, vector<T_>& ReturnValue);

	int SetDOF(int dim);

	int ComputeForceMatrixOnEle(const map<int, Eigen::MatrixXd>& Pressure,
		const LoadType LT,
		vector<T_>& tripList);

	ElementType GetElementType();
protected:


	int ComputeShapeFunction();
	int ComputeStiffnessMatrix(vector<T_>& ReturnValue);
	int ComputeMassMatrix(vector<T_>& ReturnValue);


protected:
	



	
};

#endif