#ifndef ABSTRACTFEMMODEL_H
#define ABSTRACTFEMMODEL_H
#include "abstractfilereader.h"

#include <iostream>
/*
 * FEMModel的抽象类
 * FEMModel（作为abstractFEMModel的派生类）
 * 向下可以派生出线性模型和非线性模型
 * 根据模型的不同
 * 指定不同的求解方法，并允许做特殊处理
 */

class BuildInFileReader;
class FEMinfo;

class abstractFEMModel
{
public:
    enum FEMModelType
    {
        Static,
        Dynamic,

    };
    abstractFEMModel(AbstractFileReader* InputFileReader);

    virtual ~abstractFEMModel();

    //求解方法（尚未完成）

    virtual void Solve() = 0;
    //在Solve方法中指定OutputFilePath和OutputFileName
protected:

    std::vector<FEMinfo*> FemInformationVec;
    //可以容乃多个有限元模型
    //但是需要是相同的模型（都是线性或者都是非线性）


    //保存所有的FEM信息

    std::string OutputFilePath;
    std::string OutputFileName;

    FEMModelType FMT;

protected:
    //保存解的信息

};

#endif // ABSTRACTFEMMODEL_H
