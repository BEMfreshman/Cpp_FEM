#ifndef ABSTRACTMATERIAL_H
#define ABSTRACTMATERIAL_H

#include "matpropvar.h"
#include "Eigen/Eigen"

class Mat
{
public:
    Mat();
    virtual ~Mat() = 0;

    int GetValue(MatVar SMP,double *Value);
    int GetValue(MatVar SMP,int *Value);

    int GetValue(MatVar SMP,Eigen::ArrayXXd& Value);
    int GetValue(MatVar SMP,Eigen::ArrayXXi& Value);

    virtual int ComputeMatrix(MatMatrix matmatrix,Eigen::MatrixXd& matReturn) = 0;

public:


protected:
    std::map<MatVar,double> MatPropd;
    std::map<MatVar,int>    MatPropi;

    std::map<MatVar,Eigen::ArrayXXd> MatPropdarray;
    std::map<MatVar,Eigen::ArrayXXi> MatPropiarray;

};

#endif // ABSTRACTMATERIAL_H
