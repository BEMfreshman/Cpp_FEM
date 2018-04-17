#ifndef MATPROPVAR_H
#define MATPROPVAR_H

/*
 * 本文件记录材料属性值的枚举表
 */

enum MatVar
{
    E,    //各向同性E
    Nu,   //各向同性Nu
    G,    //各向同性G

    EOrt,    //各向异性E（多个数值）
    NuOrt,   //各向异性Nu（多个数值）
    GOrt     //各向异性G（多个数值）
};


enum MatStatus
{
    PlaneStress = 1,
    PlaneStrain,
    None, // 三维情况下的设置
};

enum MatMatrix
{
    //需要在材料类计算的材料矩阵
    DMatrix,        //D矩阵 ------ 线弹性材料
    DsMatrix,       //割线矩阵 -------- 材料非线性
    DTMatrix,       //切线矩阵 -------- 材料非线性

};


#endif // MATPROPVAR_H
