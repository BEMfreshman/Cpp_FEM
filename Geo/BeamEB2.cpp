#include "BeamEB2.h"

BeamEB2::BeamEB2()
{

}

BeamEB2::BeamEB2(int ElementId,
	int MaterialId,
	int EPropId,
	Element::ElementType eletype,
	const Eigen::MatrixXi& VertexIdArray) :Line2(ElementId, MaterialId,
	eletype, VertexIdArray)
{
	this->EPropId = EPropId;
}

BeamEB2::~BeamEB2()
{

}

BeamEB2::BeamEB2(const BeamEB2 &that) :Line2(that)
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

Element* BeamEB2::Clone() const
{
	return new BeamEB2(*this);
}

int BeamEB2::GetSpecificMatrix(SparseMatrixType SMT,
	Eigen::MatrixXd& ReturnMatrix)
{
	//���㵥Ԫ�նȾ�����ߵ�Ԫ��������
	return 0;
}

int BeamEB2::ComputeStiffnessMatrix(Eigen::MatrixXd& matReturn)
{
	//ŷ��������Ŭ����
	//����նȾ���
	return 0;
}

int BeamEB2::ComputeMassMatrix(Eigen::MatrixXd& matReturn)
{
	return 0;
}

int BeamEB2::SetDOF(int dim)
{
	return 0;
}

