#ifndef __NODELOAD_H__
#define __NODELOAD_H__

//�����غɣ������ڵ���

#include "../TopAbstractClass/abstractload.h"

class NodeLoad :public Load
{
public:
	NodeLoad(int id);
	~NodeLoad();

	void ComputeEleForce(SpMat& ForceMatrix);

private:
	

};



#endif