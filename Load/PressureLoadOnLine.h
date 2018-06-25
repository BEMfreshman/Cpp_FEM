#ifndef __PRESSURELOADONLINE_H__
#define __PRESSURELOADONLINE_H__

#include "../TopAbstractClass/abstractload.h"

//对线单元（及其继承类）施加的载荷

class PressureLoadOnLine :public Load
{
public:
	PressureLoadOnLine(int id, int ElementId, const Eigen::VectorXi& NodeId,
		const Eigen::MatrixXd Value);
	~PressureLoadOnLine();

	int ComputeForce(FEMinfo* FEMInformation, vector<T_>& tripleList);
	LoadType getLoadType() const;

protected:

	int ElementId;                 //施加分布力
	Eigen::VectorXi NodeId;        //点的Id合集
	Eigen::MatrixXd Value;         //Load值得大小
};




#endif