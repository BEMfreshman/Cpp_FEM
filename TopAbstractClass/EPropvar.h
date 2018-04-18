#ifndef __EPROPVAR_H_
#define __EPROPVAR_H_

enum EPropVar
{
	//CrossSection
	Area,      //面积
	Iy,        //Y轴惯性矩 ------ 抵抗弯曲的性质
	Iz,        //Z轴惯性矩 ------ 抵抗弯曲的性质
	Tx,        //X轴扭矩

	T,         //截面厚度   ----- 壳单元

	//弹簧单元
	SpringK,   //弹簧刚度
};



#endif