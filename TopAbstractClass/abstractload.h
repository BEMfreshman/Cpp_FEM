#ifndef __ABSTRACTLOAD_H__
#define __ABSTRACTLOAD_H__

//���غ� ������
//�������غɵĸ���
//���غɴ������֣������غɺͷֲ��غɣ�ѹ���߽磩

//�ο�NASTRAN�Ĺؼ������÷���
//�ԵȲε�Ԫʩ�ӵ��غɺͶ�BEAM��TRUSS���غɻᱻ�ֿ�����

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
	int id;                        //���غɵ�ID

	vector<Element*> ElementVec;

protected:
	

};



#endif