#ifndef __ABSTRACTLOAD_H__
#define __ABSTRACTLOAD_H__

//力载荷 抽象类
//是所有载荷的父类
//力载荷存在两种，集中载荷和分布载荷（压力边界）

//参考NASTRAN的关键字设置方法
//对等参单元施加的载荷和对BEAM，TRUSS的载荷会被分开处理

#include "Dof.h"
#include "abstractelement.h"
#include "Eigen\Eigen"
#include <vector>

typedef Eigen::SparseMatrix<double> SpMat;

using namespace std;

class Load
{
public:
	Load(int id);
	virtual ~Load() = 0;

	int GetId();

	virtual void ComputeEleForce(SpMat& ForceMatrix) = 0;

	void addElement(Element* Ele);


protected:
	int id;                        //该载荷的ID

	vector<Element*> ElementVec;

protected:
	

};



#endif