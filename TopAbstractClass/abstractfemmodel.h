#ifndef ABSTRACTFEMMODEL_H
#define ABSTRACTFEMMODEL_H
#include "feminfo.h"
#include <iostream>
#include "Eigen\Eigen"
/*
 * FEMModel的抽象类
 * FEMModel（作为abstractFEMModel的派生类）
 * 向下可以派生出线性模型和非线性模型
 * 根据模型的不同
 * 指定不同的求解方法，并允许做特殊处理
 */

class BuildInFileReader;
class FEMinfo;

typedef Eigen::SparseMatrix<double> SpMat;


class abstractFEMModel
{
public:
    abstractFEMModel(FEMinfo* FEMInformation);

    virtual ~abstractFEMModel();

    //求解方法（尚未完成）

    virtual void Solve() = 0;
    //在Solve方法中指定OutputFilePath和OutputFileName

protected:

	int PreProcess();
	virtual int BuildKMatrix() = 0;
	virtual int BuildMMatrix() = 0;
	virtual int BuildfMatrix() = 0;


protected:

    FEMinfo* FemInformation;
    //有限元模型


    //保存所有的FEM信息

    std::string OutputFilePath;
    std::string OutputFileName;

	int ValidDOFNum;     
	int PerscribedDOFNum;
	//有效的DOF数目
	//通过遍历Vertex计算总的有效自由度
	//同时为各Vertex的有效DOF编号

	SpMat K;     //总体刚度矩阵
	SpMat M;     //总体质量矩阵
	SpMat f;     //总体载荷矩阵
    

};

#endif // ABSTRACTFEMMODEL_H
