#ifndef LINEARSTATICMODEL_H
#define LINEARSTATICMODEL_H

#include "../TopAbstractClass/abstractfemmodel.h"

//继承abstractFEMModel的线性静态模型
class LinearStaticModel:public abstractFEMModel
{
public:
    LinearStaticModel(AbstractFileReader* InputFileReader);

    ~LinearStaticModel();

    void Solve();
};

#endif // LINEARMODEL_H
