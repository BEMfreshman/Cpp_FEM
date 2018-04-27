#ifndef __DOF_H__
#define __DOF_H__

#include "DOFVar.h"

class DOF
{
public:
	DOF(int LocalDOFId,DOFVar DF);
	DOF(int LocalDOFId, int VaildTotalDOFId, DOFVar DF);
	~DOF();

	int getLocalDOFId();
	int getVaildTotalDOFId();
	bool getIsVaild();
	DOFVar getDOFVar();

	void SetVaild(bool vaildflag);

private:
	int LocalDOFId;
	int VaildTotalDOFId;
	bool IsVaild;

	DOFVar DF;

};



#endif