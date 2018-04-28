#ifndef __ELEMENTTYPE_H__
#define __ELEMENTTYPE_H__

enum ElementType
{
	//等参单元形状
	LINE2 = 1,             //线单元
	LINE3,
	TRIANGLE3,         //三角形
	TRIANGLE4,
	TRIANGLE6,
	QUADRILATERAL4,    //四边形
	QUADRILATERAL8,
	QUADRILATERAL9,
	TETRAHEDRON4,      //四面体
	HEXAHEDRON8,       //六面体

	TRUSS,                //杆单元
	BEAMEB2,              //欧拉——伯努利梁单元（2节点）
	BEAMEB3,              //欧拉——伯努利梁单元（3节点）
	BEAMT2,               //铁木辛柯梁单元（2节点）
	BEAMT3,               //铁木辛柯梁单元（3节点）
	SHELL,                //壳单元

	POINT
};

#endif