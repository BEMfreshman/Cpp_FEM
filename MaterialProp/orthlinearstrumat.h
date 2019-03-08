#ifndef ORTHLINEARSTRUMAT_H
#define ORTHLINEARSTRUMAT_H

#include "linearstrumat.h"

class OrthLinearStruMat:public LinearStruMat
{
public:
    OrthLinearStruMat(int dim);
    ~OrthLinearStruMat();

	int ComputeMatrix(MatMatrix matmatrix, Eigen::MatrixXd& matReturn);
};

#endif // ORTHLINEARSTRUMAT_H
