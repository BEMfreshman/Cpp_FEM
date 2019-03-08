#ifndef __PRESSURELOADONLINE_H__
#define __PRESSURELOADONLINE_H__

#include "../TopAbstractClass/abstractload.h"

//���ߵ�Ԫ������̳��ࣩʩ�ӵ��غ�

class PressureLoadOnLine :public Load
{
public:
	PressureLoadOnLine(int id, int ElementId, const Eigen::VectorXi& NodeId,
		const Eigen::MatrixXd Value);
	~PressureLoadOnLine();

	int ComputeForce(FEMinfo* FEMInformation, vector<T_>& tripleList);
	LoadType getLoadType() const;

protected:

	int ElementId;                 //ʩ�ӷֲ���
	Eigen::VectorXi NodeId;        //���Id�ϼ�
	Eigen::MatrixXd Value;         //Loadֵ�ô�С
};




#endif