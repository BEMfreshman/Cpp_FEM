#ifndef STRUCTUREMAT_H
#define STRUCTUREMAT_H

#include "../TopAbstractClass/abstractmaterial.h"
#include "../TopAbstractClass/matpropvar.h"


class StructureMat:public Mat
{
public:
    StructureMat(int dim);

	virtual int ComputeMatrix(MatMatrix matmatrix, Eigen::MatrixXd& matReturn) = 0;

    virtual ~StructureMat() = 0;
};

#endif // STRUCTUREMAT_H
