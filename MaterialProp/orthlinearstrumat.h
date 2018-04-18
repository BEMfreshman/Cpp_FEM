#ifndef ORTHLINEARSTRUMAT_H
#define ORTHLINEARSTRUMAT_H

#include "linearstrumat.h"

class OrthLinearStruMat:public LinearStruMat
{
public:
    OrthLinearStruMat(int dim);
    ~OrthLinearStruMat();
};

#endif // ORTHLINEARSTRUMAT_H
