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

class FEMinfo;

typedef Eigen::SparseMatrix<double> SpMat;

using namespace std;

typedef Eigen::Triplet<double> T_;
class Load
{
public:
	Load(int id,const Eigen::MatrixXi& NodeId,const Eigen::MatrixXd Value);
	virtual ~Load() = 0;

	int GetId();

	virtual int ComputeForce(FEMinfo* FEMInformation, vector<T_>& tripleList) = 0;

	void addData(const Eigen::MatrixXi& NodeId, const Eigen::MatrixXd& Value);
	void setCoordId(int CoordId);

	const Eigen::MatrixXi getNodeId() const;
	const Eigen::MatrixXd getValue() const;
	int getCoordId() const;          //�����������
protected:
	int id;                        //���غɵ�ID
	int CoordId;                   //��������
	Eigen::MatrixXi NodeId;        //���Id�ϼ�
	Eigen::MatrixXd Value;         //Loadֵ�ô�С

protected:
	

};



#endif