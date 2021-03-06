﻿#ifndef MATPROPVAR_H
#define MATPROPVAR_H

/*
 * 本文件记录材料属性值的枚举表
 */

enum MatCategory           //材料类别
{
	Solid,                 //固体
	Liquid,                 //液体 
	
};

enum MatType
{
	Iso,           //各相同性
	Orth,          //正交各向异性
	Aniso,          //各向异性
	
};

enum MatVar
{
    E,    //各向同性E
    Nu,   //各向同性Nu
    G,    //各向同性G

	Ex,   //各向异性E（多个数值）
	Ey,
	Ez,

	Nuxy, //各向异性Nu（多个数值）
	Nuxz,
	Nuyz,
	
	Gx,  //各向异性G（多个数值）
	Gy,
	Gz,

	RHO,
};


enum MatStatus
{
    PlaneStress,
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
