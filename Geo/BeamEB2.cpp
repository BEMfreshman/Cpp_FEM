#include "BeamEB2.h"

BeamEB2::BeamEB2()
{

}

BeamEB2::BeamEB2(int ElementId,
	int MaterialId,
	int EPropId,
	Element::ElementType eletype,
	const Eigen::MatrixXi& VertexIdArray) :Element(ElementId, MaterialId, EPropId,
	eletype, VertexIdArray)
{

}

BeamEB2::~BeamEB2()
{

}

BeamEB2::BeamEB2(const BeamEB2 &that) :Element(that)
{

}

BeamEB2& BeamEB2::operator=(const BeamEB2& that)
{
	if (this != &that)
	{
		Element::operator= (that);
		return *this;
	}
	else
	{
		return *this;
	}
}

int BeamEB2::GetSpecificMatrix(SparseMatrixType SMT,
	Eigen::MatrixXd& ReturnMatrix)
{
	//���㵥Ԫ�նȾ�����ߵ�Ԫ��������
}

int BeamEB2::ComputeStiffnessMatrix(Eigen::MatrixXd& matReturn)
{
	//ŷ��������Ŭ����
	//����նȾ���

}