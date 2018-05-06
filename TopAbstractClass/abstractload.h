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
	int getCoordId() const;          //获得坐标轴编号
protected:
	int id;                        //该载荷的ID
	int CoordId;                   //坐标轴编号
	Eigen::MatrixXi NodeId;        //点的Id合集
	Eigen::MatrixXd Value;         //Load值得大小

protected:
	

};



#endif