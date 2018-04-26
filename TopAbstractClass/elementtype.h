#ifndef __ELEMENTTYPE_H__
#define __ELEMENTTYPE_H__

enum ElementType
{
	//�Ȳε�Ԫ��״
	Line2 = 1,             //�ߵ�Ԫ
	Line3,
	Triangle3,         //������
	Triangle4,
	Triangle6,
	Quadrilateral4,    //�ı���
	Quadrilateral8,
	Quadrilateral9,
	Tetrahedron4,      //������
	Hexahedron8,       //������

	Truss,                //�˵�Ԫ
	BeamEB2,              //ŷ��������Ŭ������Ԫ��2�ڵ㣩
	BeamEB3,              //ŷ��������Ŭ������Ԫ��3�ڵ㣩
	BeamT2,               //��ľ��������Ԫ��2�ڵ㣩
	BeamT3,               //��ľ��������Ԫ��3�ڵ㣩
	Shell                 //�ǵ�Ԫ
};

#endif