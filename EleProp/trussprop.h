#ifndef TRUSSPROP_H
#define TRUSSPROP_H

#include "Eigen/Eigen"
#include "../MaterialProp/mat.h"

using namespace Eigen;
/*
 * 杆单元截面属性
 * 仅支持各向同性材料
 */

class TrussProp
{
public:
    TrussProp();

    TrussProp(int id,double Area,double L,Mat* mat);

    void SetJ(double J);

    virtual ~TrussProp();

    bool IsIsoMat();   //检查是否为各向同性材料
    int GetId();
    double GetArea();
    double GetL();
    double GetJ();
    Mat* GetMat();

protected:
    //杆单元属性
    int id;      //单元属性ID
    double Area; //面积
    double L;    //长度
    double J;    //扭转常数
    Mat* mat;    //材料

};

#endif // TRUSSPROP_H
