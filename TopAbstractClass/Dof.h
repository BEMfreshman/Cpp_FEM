#ifndef __DOF_H__
#define __DOF_H__

#include "DOFVar.h"
#include "Eigen/SparseCore"
using namespace std;

typedef Eigen::Triplet<double> T_;

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
	int getResidualKSize();

	int addresidualK(const T_& T);

	void SetVaildTotalDOFId(int VaildTotalDOFId);

	void SetAns(double ans);        //�������ֵ
	double getAns();


	T_ getResidualK(int i);

private:
	int LocalDOFId;
	int VaildTotalDOFId;
	bool IsVaild;

	DOFVar DF;

	vector<T_> residualK; //�����DOF��Ч����residualK����

	double ans;

};



#endif