#ifndef BEAMPROP_H
#define BEAMPROP_H

/*
 * 梁单元属性
 * 仅支持各向同性材料
 */

#include "Eigen/Eigen"
#include "../MaterialProp/mat.h"

class BeamProp
{

public:
    BeamProp();
    virtual ~BeamProp();
protected:
    int id;      //单元属性ID
    double Area; //面积
    double L;    //长度
    double I;    //惯性矩
    Mat* mat;    //材料
};

#endif // BEAMPROP_H
