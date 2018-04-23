#ifndef __ABSTRACTLOAD_H__
#define __ABSTRACTLOAD_H__

//���غ� ������
//�������غɵĸ���
//���غɴ������֣����߽��ѹ���߽�

#include "Eigen\Eigen"

class Load
{
public:
	Load(int id);
	virtual ~Load() = 0;

	int GetId();


protected:
	int id;                        //���غɵ�ID

	int NodeId;                    //�ܵ����غ�Ӱ���ID���
	
	Eigen::MatrixXd LoadValue;     //���ֵ

};



#endif