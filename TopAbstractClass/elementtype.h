#ifndef __ELEMENTTYPE_H__
#define __ELEMENTTYPE_H__

enum ElementType
{
	//等参单元形状
	Line2 = 1,             //线单元
	Line3,
	Triangle3,         //三角形
	Triangle4,
	Triangle6,
	Quadrilateral4,    //四边形
	Quadrilateral8,
	Quadrilateral9,
	Tetrahedron4,      //四面体
	Hexahedron8,       //六面体

	Truss,                //杆单元
	BeamEB2,              //欧拉——伯努利梁单元（2节点）
	BeamEB3,              //欧拉——伯努利梁单元（3节点）
	BeamT2,               //铁木辛柯梁单元（2节点）
	BeamT3,               //铁木辛柯梁单元（3节点）
	Shell                 //壳单元
};

#endif