#ifndef __NODELOAD_H__
#define __NODELOAD_H__

//�����غɣ������ڵ���

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
	int NodeId;        //���Id�ϼ�
	Eigen::MatrixXd Value;         //Loadֵ�ô�С

};



#endif