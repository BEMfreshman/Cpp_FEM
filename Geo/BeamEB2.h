#ifndef __BEAMEB2_H__
#define __BEAMEB2_H__

//#include "../TopAbstractClass/abstractelement.h"

/*
һά����Ԫ����������ϵͳΪxoy����ϵͳ
z��ͨ�������ģ�һά��Ԫ�նȾ�����㹫ʽ��
�Ĺ��Ծ�ΪIz


*/


#include "Line2.h"


class BeamEB2:public Line2
{
public:
	BeamEB2();   //Ĭ�Ϲ��캯��
	BeamEB2(int ElementId, int MaterialId,
		int EPropId, ElementType eletype,
		const Eigen::MatrixXi& VertexIdArray);

	~BeamEB2();

	BeamEB2(const BeamEB2& that);
	BeamEB2& operator=(const BeamEB2& that);

	Element* Clone() const;

	int GetSpecificMatrix(SparseMatrixType SMT, Eigen::MatrixXd& ReturnMatrix);

	int SetDOF(int dim);

	ElementType GetElementType();
protected:

	int ComputeStiffnessMatrix(Eigen::MatrixXd& matReturn);
	int ComputeMassMatrix(Eigen::MatrixXd& matReturn);


	
};

#endif