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
	//计算单元刚度矩阵或者单元质量矩阵
}

int BeamEB2::ComputeStiffnessMatrix(Eigen::MatrixXd& matReturn)
{
	//欧拉——伯努利梁
	//计算刚度矩阵

}