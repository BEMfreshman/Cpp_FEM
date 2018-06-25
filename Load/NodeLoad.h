#ifndef __NODELOAD_H__
#define __NODELOAD_H__

//集中载荷，作用于点上

#include "../TopAbstractClass/abstractload.h"

class NodeLoad :public Load
{
public:
	NodeLoad(int id, int NodeId,
		const Eigen::MatrixXd Value);
	~NodeLoad();

	int ComputeForce(FEMinfo* FEMInformation, vector<T_>& tripleList);
	LoadType getLoadType() const;

private:
	int NodeId;        //点的Id合集
	Eigen::MatrixXd Value;         //Load值得大小

};



#endif