#ifndef ISOLINEARSTRUMAT_H
#define ISOLINEARSTRUMAT_H

#include "linearstrumat.h"

class IsoLinearStruMat:public LinearStruMat
{
public:
    IsoLinearStruMat(int dim);
    ~IsoLinearStruMat();

	int ComputeMatrix(MatMatrix matmatrix, Eigen::MatrixXd& matReturn);
};

#endif // ISOLINEARSTRUMAT_H
