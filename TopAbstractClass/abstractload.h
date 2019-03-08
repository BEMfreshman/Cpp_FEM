#ifndef __ABSTRACTLOAD_H__
#define __ABSTRACTLOAD_H__

//���غ� ������
//�������غɵĸ���
//���غɴ������֣������غɺͷֲ��غɣ�ѹ���߽磩

//�ο�NASTRAN�Ĺؼ������÷���
//�ԵȲε�Ԫʩ�ӵ��غɺͶ�BEAM��TRUSS���غɻᱻ�ֿ�����

#include "Dof.h"
#include "abstractelement.h"
#include "LoadType.h"
#include "Eigen\Eigen"
#include <vector>


class FEMinfo;

typedef Eigen::SparseMatrix<double> SpMat;

using namespace std;

typedef Eigen::Triplet<double> T_;
class Load
{
public:
	Load(int id);
	virtual ~Load() = 0;

	int GetId() const;

	virtual int ComputeForce(FEMinfo* FEMInformation, vector<T_>& tripleList) = 0;
	virtual LoadType getLoadType() const = 0;

	void setCoordId(int CoordId);
	int getCoordId() const;          //�����������

protected:
	int id;                        //���غɵ�ID
	int CoordId;                   //��������


};



#endif