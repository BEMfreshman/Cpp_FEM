#ifndef ISOMAT_H
#define ISOMAT_H
/*
 * 各向同性材料
 * 在E,Nu,G中只有两个是独立变量
 * */
#include "mat.h"
#include "Eigen/Eigen"

using namespace Eigen;

class IsoMat:public Mat
{
public:
    IsoMat();
    virtual ~IsoMat();
    virtual void ComputeDMatrix(MatrixXd& Dmat); // 计算D矩阵

    void InitialEandNu(double* E,double* Nu);
    void InitialEandG(double* E,double* G);    //初始化E和G
    void InitialNuandG(double* Nu,double* G);  //初始化Nu和G

    double GetE();
    double GetNu();
    double GetG();

private:
    void CaculateE();
    void CaculateNu();
    void CaculateG();
};

class IsoMat2d:public IsoMat
{
public:
    enum StressOrStrain
    {
        //二维问题当中的平面应力或者平面应变问题
        PlaneStress,
        PlaneStrain
    };

    IsoMat2d();

    ~IsoMat2d();

    void ComputeDMatrix(MatrixXd& Dmat);
    // 计算D矩阵，用于二位平面应力和平面应变单元

protected:
    void InitialType(StressOrStrain type);

private:
    StressOrStrain type;
};


class IsoMat3d:public IsoMat
{
public:
    IsoMat3d();
    ~IsoMat3d();

    void ComputeDMatrix(MatrixXd& Dmat); // 计算D矩阵
};

#endif // ISOMAT_H
