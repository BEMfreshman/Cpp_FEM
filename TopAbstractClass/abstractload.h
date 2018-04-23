#ifndef __ABSTRACTLOAD_H__
#define __ABSTRACTLOAD_H__

//力载荷 抽象类
//是所有载荷的父类
//力载荷存在两种，力边界和压力边界

#include "Eigen\Eigen"

class Load
{
public:
	Load(int id);
	virtual ~Load() = 0;

	int GetId();


protected:
	int id;                        //该载荷的ID

	int NodeId;                    //受到该载荷影响的ID编号
	
	Eigen::MatrixXd LoadValue;     //多个值

};



#endif