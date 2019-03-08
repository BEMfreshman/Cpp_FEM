#ifndef __FEMINFOLIST_H__
#define __FEMINFOLIST_H__

#include <vector>
using namespace std;

class FEMinfo;

class FemInfoList
{
public:
	FemInfoList();
	~FemInfoList();

	void addData(FEMinfo* FI);

	int getSize() const ;
	
protected:
	vector<FEMinfo*> inforVec;
};


#endif