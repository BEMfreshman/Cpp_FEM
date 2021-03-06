﻿#ifndef INPUTITEMNAME_H
#define INPUTITEMNAME_H

enum InputItemName
{
    //记录需要读出来的数据体
	Analysis_SolNum,
	Analysis_SolType,         //Sol的类型，2dPlaneStress,2dPlaneStrain,3d

	Vertex_Id,
	Vertex_CoordX,
	Vertex_CoordY,
	Vertex_CoordZ,
	SPC,                      //单点约束

	Element_Id,
	Element_Type,
	Element_VertexIdArray,     //组成Element的VertexId的编号
	Element_MatId,             //Element的材料编号
	Element_EPropId,           //Element的单元属性编号

	Mat_Id,
	Mat_LinearOrNot,           //线性还是非线性
	Mat_IsoOrNot,              //各向同性还是各向异性
	Mat_PropNameAndPropValue,

	EProp_Id,
	EProp_ElementName,         //单元属性名称 ---- Beam,Truss,Shell
	EProp_PropNameAndPropValue,

	//边界力载荷
	//分为集中力、分布力（均匀分布和线性分布）和压力
	Load_Id,
	Load_Name,
	Load_Value,           //力的大小（注意力可以是压力，也可以是应力，两者不同）
	Load_NodeId,          //受此Load影响的点ID
	Load_NodeNum,         //受此Load影响的点的数目

	Load_Pressure_ElementId,
	Load_Pressure_NodeId,
	Load_Pressure_Value,


	Constraint_Id,
	Constraint_Name,
	Constraint_NodeId,
	Constraint_DOFVarI,
	Constraint_Value,

};



#endif // INPUTITEMNAME_H
