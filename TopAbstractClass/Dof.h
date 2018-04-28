#ifndef __DOF_H__
#define __DOF_H__

#include "DOFVar.h"
#include "Eigen/SparseCore"
using namespace std;

class DOF
{
public:
	DOF(int LocalDOFId,DOFVar DF);
	DOF(int LocalDOFId, bool IsVaild, DOFVar DF);
	~DOF();

	int getLocalDOFId();
	int getVaildTotalDOFId();
	bool getIsVaild();
	DOFVar getDOFVar();

	int addresidualK(const Eigen::Triplet<double>& T);

	void SetVaildTotalDOFId(int VaildTotalDOFId);

private:
	int LocalDOFId;
	int VaildTotalDOFId;
	bool IsVaild;

	DOFVar DF;

	vector<Eigen::Triplet<double>> residualK; //如果此DOF无效，则residualK存在

};



#endif