#ifndef LINEARSTATICMODEL_H
#define LINEARSTATICMODEL_H

#include "../TopAbstractClass/abstractfemmodel.h"
#include "../TopAbstractClass/feminfo.h"

//继承abstractFEMModel的线性静态模型，完成101计算
//功能：
//组建K矩阵（刚度）
//组建f矩阵（载荷）
//计算解
//根据解组装其他的计算结果（例如米塞斯应力等）
class LinearStaticModel:public abstractFEMModel
{
public:
	LinearStaticModel(FEMinfo* FEMInformation);

    ~LinearStaticModel();

    void Solve();

protected:
	int BuildKMatrix();
	int BuildMMatrix();
	int BuildfMatrix();

	


};

#endif // LINEARMODEL_H
