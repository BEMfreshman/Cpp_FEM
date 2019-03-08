#ifndef __ELEMENTTYPE_H__
#define __ELEMENTTYPE_H__

enum ElementType
{
	//�Ȳε�Ԫ��״
	LINE2 = 1,             //�ߵ�Ԫ
	LINE3,
	TRIANGLE3,         //������
	TRIANGLE4,
	TRIANGLE6,
	QUADRILATERAL4,    //�ı���
	QUADRILATERAL8,
	QUADRILATERAL9,
	TETRAHEDRON4,      //������
	HEXAHEDRON8,       //������

	TRUSS,                //�˵�Ԫ
	BEAMEB2,              //ŷ��������Ŭ������Ԫ��2�ڵ㣩
	BEAMEB3,              //ŷ��������Ŭ������Ԫ��3�ڵ㣩
	BEAMT2,               //��ľ��������Ԫ��2�ڵ㣩
	BEAMT3,               //��ľ��������Ԫ��3�ڵ㣩
	SHELL,                //�ǵ�Ԫ

	POINT
};

#endif