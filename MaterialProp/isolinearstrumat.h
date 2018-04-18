#ifndef ISOLINEARSTRUMAT_H
#define ISOLINEARSTRUMAT_H

#include "linearstrumat.h"

class IsoLinearStruMat:public LinearStruMat
{
public:
    IsoLinearStruMat(int dim);
    ~IsoLinearStruMat();
};

#endif // ISOLINEARSTRUMAT_H
